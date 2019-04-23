#include "SslClient.h"

SslClient::SslClient(QObject* parent)
	: QObject{ parent }, mReplyParser{ new ReplyParser{this} }, mHandlingSocketError{ false }, mSocket{nullptr}{
	this->setObjectName("SslClient");
	setupSecureSocket();
	//connect(&Command::getInstance(), &Command::commandReply, this, &SslClient::dataReceive);//passed to QML/JS
	connect(this, &SslClient::parseReply, mReplyParser, &ReplyParser::parseReply);
	connect(mReplyParser, &ReplyParser::ping, this, &SslClient::pong);
	
	//singal-> signal connection to forward the signals	
    connect(mReplyParser, &ReplyParser::twitchCapabilities, this, &SslClient::twitchCapabilities);
    connect(mReplyParser, &ReplyParser::commandReceive, this, &SslClient::commandReceive);
	connect(mReplyParser, &ReplyParser::dataWrite, this, &SslClient::dataWrite);
}

void SslClient::setupSecureSocket() {
	if (mSocket)
		return;
	mSocket = new QSslSocket(this);

	connect(mSocket, &QSslSocket::encrypted, this, &SslClient::socketEncrypted);
	connect(mSocket, &QSslSocket::readyRead, this, &SslClient::socketReadyRead);

	auto values = JsonParser::getInstance().readSettings();
	mSocket->connectToHostEncrypted(values["SSL Hostname"], static_cast<quint16>(values["SSL Hostport"].toInt()));

	this->sendData("PASS " + QString(values["Oauth Token"]));
	
	this->sendData("NICK " + QString(values["Bot Username"]));
}

void SslClient::addCapability(const QString& capability){
	mReplyParser->addCapability(capability);
}

void SslClient::socketEncrypted() {
	const QSslCipher cipher = mSocket->sessionCipher();
	const QString ciperInfo = QString("%1, %2 (%3/%4)").arg(cipher.authenticationMethod())
													   .arg(cipher.name()).arg(cipher.usedBits()).arg(cipher.supportedBits());
}

void SslClient::socketReadyRead(){//get data from socket and emit the data
	QString reply = QString::fromUtf8(mSocket->readAll());
	emit parseReply(reply);
}

void SslClient::dataReceive(const QString& data) {//data received from input or from command
	this->sendData(data);
}

void SslClient::sendData(const QString& data) {//forward data to ssl server
	mSocket->write(data.toUtf8() + "\r\n");
}

void SslClient::pong() {
	sendData(QString("PONG :tmi.twitch.tv"));
}

void SslClient::sslErrors(const QList<QSslError>& errors) {
	for (const auto& error : errors) 
		emit dataWrite(error.errorString());
}

ReplyParser::ReplyParser(QObject* parent) : QObject{ parent } {
	capabilityValues["Membership"] = 0;
	capabilityValues["Tags"] = 0;
	capabilityValues["Commands"] = 0;
	capabilityValues["Chat Rooms"] = 0;
}
ReplyParser::~ReplyParser(){}

void ReplyParser::addCapability(const QString& capability){
	capabilityValues[capability] = 1;
}

void ReplyParser::parseReply(const QString& reply){

	if (QRegularExpression re("PING :tmi.twitch.tv"); re.match(reply).hasMatch()) // PING-PONG server reply
		emit ping();


	else if  (QRegularExpressionMatch regexMatch = QRegularExpression{ "^(?:@(?<tags>.*))?:(?<userName>.*)(!|@|(?<server>\.tmi\.twitch\.tv))\s?\
(?<command>.*?) #(?<channel>.*) :(?<message>.*)\r$" }.match(reply);
																							regexMatch.hasMatch()) {//privmsg to chatroom or command to bot
		 //[@tags]<username>.tmi.twitch.tv <command> #<channel>: Msg

		QVariantMap metaData;
		
		if (regexMatch.captured("tags") != QString()) {//if tags were enabled
			metaData.insert("hasTags", "true");
			QRegularExpression tagParser{ "(?<attribute>.*?)=(?<value>.*?)(?:;| )" };//parse all attribute=value; tags
			QRegularExpressionMatchIterator tags = tagParser.globalMatch(regexMatch.captured("tags"));


		    while (tags.hasNext()) {
				QRegularExpressionMatch instance = tags.next();
				metaData.insert(instance.captured("attribute"), instance.captured("value"));
			}
		}
		else
			metaData.insert("hasTags", "false");
		
		metaData.insert("userName", regexMatch.captured("userName").split(QRegularExpression{ "!|@" }).first());
		metaData.insert("server", regexMatch.captured("server"));
		metaData.insert("serverCommand", regexMatch.captured("command"));
		metaData.insert("channel", regexMatch.captured("channel"));

		if(QRegularExpressionMatch messageRegex = QRegularExpression{ "^(?:\s?)!(?:\s?)(?<message>.*?)(?<messageArgs> .*)?$" }.match(regexMatch.captured("message")); 
																						  messageRegex.hasMatch()){ //command to bot
			//[@tags]<username>.tmi.twitch.tv <command> #<channel>: !Msg [messageArgs]
			metaData.insert("message", messageRegex.captured("message"));
			metaData.insert("messageArgs", messageRegex.captured("messageArgs").right(messageRegex.captured("messageArgs").size()-1));
			//messageArgs comes from regex with leading " " that should be removed
			emit commandReceive(metaData);
		}
		else {//normal message, not command
			QString modifiedReply = QString("@%1 -> %2: %3\r\n")
														.arg(metaData["channel"].toString())
														.arg(metaData["userName"].toString())
														.arg(regexMatch.captured("message"));
			emit dataWrite(modifiedReply);
		}
		
	}
	else if (QRegularExpression regex{ "^:tmi\.twitch\.tv CAP.*" }; regex.match(reply).hasMatch()) //Server ACK of a Cap
		emit twitchCapabilities(reply);
	else
		emit dataWrite(reply);//nothing special, generic reply
}

