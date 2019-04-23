#include "ChatBot.h"
#include <QQuickView>
ChatBot::ChatBot(const QUrl& url,  QObject* parent)
	:  mClient{ new SslClient{this} }, mFilter{ new KeyPressFilter{this} }, 
	mHistory{ new CommandHistory{this} }, mEngine{ new QQmlApplicationEngine{this} }, mSettings{JsonParser::getInstance().readSettings()}{
	this->setObjectName("ChatBot");
	QQmlContext* context = mEngine->rootContext();
	context->setContextProperty("controller", this);
	context->setContextProperty("settingsModel", toVariantList());
	mEngine->load(url);	
	auto rootObject = mEngine->rootObjects().first();
	auto a = rootObject->findChild<QObject*>("textInput");
	a->installEventFilter(mFilter);//install event filter on text Input


	//connections with qml file
	connect(rootObject, SIGNAL(submitCommandButtonPressed()), this, SLOT(commandReceived()));
	connect(this, SIGNAL(dataReceived(const QVariant&)), rootObject, SLOT(dataReceived(const QVariant&)));
	connect(this, SIGNAL(clearInputLine()), rootObject, SLOT(clearInputLine()));
    connect(rootObject, SIGNAL(capabilityRequested(QString)), mClient, SLOT(dataReceive(const QString&)));
    connect(rootObject, SIGNAL(capabilityGranted(QString)), mClient, SLOT(addCapability(const QString&)));
	connect(rootObject, SIGNAL(commandReply(QString)), mClient, SLOT(dataReceive(const QString&)));
	connect(mClient, SIGNAL(commandReceive(const QVariant&)), rootObject, SLOT(commandReceive(const QVariant&)));
    connect(mClient, SIGNAL(twitchCapabilities(const QVariant&)), rootObject, SLOT(capabilityResponse(const QVariant&)));
	connect(mHistory, SIGNAL(setInputLineTo(const QVariant&)), rootObject, SLOT(setInputLineTo(const QVariant&)));
	connect(rootObject, SIGNAL(textChanged(QString)), mHistory, SLOT(textChanged(const QString&)));// on text change give text to history
	connect(rootObject, SIGNAL(updateSettings(QVariant)), this, SLOT(updateSettings(const QVariant&)));

	connect(this, &ChatBot::inputReceived, mClient, &SslClient::dataReceive);
	connect(mClient, &SslClient::dataWrite, [this](const QString& data) {emit this->dataReceived(data.left(data.size()-2)); });//get rid of /r/n

	connect(mFilter, SIGNAL(commandReceived()), this, SLOT(commandReceived()));
	connect(mFilter, &KeyPressFilter::clearLine, [this]() {emit clearInputLine(); });

	connect(mFilter, &KeyPressFilter::commandHistory, mHistory, &CommandHistory::commandHistory);

	connect(this, &ChatBot::inputReceived, mHistory, &CommandHistory::addCommandHistory);

}

 void ChatBot::commandReceived() {//get command from input and clear input line
	 auto textInputObject = mEngine->rootObjects().first()->findChild<QObject*>("textInput");
	QString command = textInputObject->property("text").toString();
	commandReceived(command);
	 emit clearInputLine();
}
 void ChatBot::commandReceived(const QVariant& command) {//get command from input and clear input line
	 commandReceived(command.toString());
 }
 void ChatBot::commandReceived(const QString& command) {//send input received for processing
	 emit inputReceived(command);
 }
 QVariantList ChatBot::toVariantList() {
	 QVariantList variantList;
	 for (const auto& key : mSettings.keys()) {
		 QVariantMap variantMap;
		 variantMap["settingName"] = key;
		 variantMap["settingValue"] = mSettings.value(key);
		 variantList.append(variantMap);
	 }
	 return variantList;
 }
 void ChatBot::updateSettings(const QVariant& newValue) {
	 QQmlContext* context = mEngine->rootContext();

	 mSettings[newValue.toMap()["settingName"].toString()] = newValue.toMap()["settingValue"].toString();
	 JsonParser::getInstance().writeSettings(mSettings);
	 context->setContextProperty("settingModel", toVariantList());
 }

KeyPressFilter::KeyPressFilter(QObject* parent) :QObject{ parent } {}
bool KeyPressFilter::eventFilter(QObject* obj, QEvent* event) {
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
		if ((keyEvent->key() == Qt::Key_Enter || (keyEvent->key() == Qt::Key_Return))) {
			emit commandReceived();
			return true;
		}
		if ((keyEvent->key() == Qt::Key_Escape)) {
			emit clearLine();
			return true;
		}
		if ((keyEvent->key() == Qt::Key_Up)) {
			emit commandHistory(-1);
			return true;
		}
		if ((keyEvent->key() == Qt::Key_Down)) {
			emit commandHistory(1);
			return true;
		}
	}
	
	return QObject::eventFilter(obj, event);
}


CommandHistory::CommandHistory(QObject* parent) :QObject{ parent }, mCurrentLineString{ QString{} }{
	this->setObjectName("CommandHistory");
}
void CommandHistory::commandHistory(int direction) {
	if (mCommandsUsed.size() == 0)
		return;

	mCurrentHistoryIndex += direction;
	mCurrentHistoryIndex = std::clamp(mCurrentHistoryIndex, 0, mCommandsUsed.size());

	if (mCurrentHistoryIndex == mCommandsUsed.size())
		emit setInputLineTo(mCurrentLineString);
	else	
		emit setInputLineTo(mCommandsUsed[mCurrentHistoryIndex]);
}
void CommandHistory::resetHistoryIndex() {
	mCurrentHistoryIndex = mCommandsUsed.size();
}
void CommandHistory::addCommandHistory(const QString& command) {
	mCommandsUsed.push_back(command);
	resetHistoryIndex();
}
void CommandHistory::textChanged(const QString& argText) {//text changed on input line
	//if its not a text from history we are writing new word
	if (argText == "" || (argText != mCurrentLineString &&
	std::find(mCommandsUsed.begin(), mCommandsUsed.end(), argText) == mCommandsUsed.end())){
		resetHistoryIndex();
		mCurrentLineString = argText;
	}
}

/* MOVED TO QML
Capability::Capability(QString aDisplayName, QString aCommand, QObject* parent)
	:mDisplayName{aDisplayName}, mCommand{ aCommand }, QObject{ parent } {}

void Capability::set(bool) {
	if (mState == 1)
		return;
	mState = 1;
	emit gotSet();
}

bool Capability::isSet() const{
	return mState;
}

bool Capability::replyMatch(const QString& aReply){//checks if command is part of string
	if (QRegularExpressionMatch matchCommand = QRegularExpression{ "^.*CAP.*(:twitch.tv\/.*)$" }.match(getCommand());
		matchCommand.hasMatch()){ 
			if(aReply.contains(matchCommand.captured(1), Qt::CaseInsensitive)){
				set();
				return 1;
			}}
	return 0;
}

QString Capability::getCommand() const{
	return mCommand;
}

QString Capability::getDisplayName() const{
	return mDisplayName;
}
*/