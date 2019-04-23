#pragma once
#include <QObject>
#include <QtNetwork>
#include <QRegularExpression>
#include <QSslError>
#include <vector>
#include "JsonParser.h"
class ReplyParser;
class SslClient : public QObject
{					
	Q_OBJECT

public:
	SslClient(QObject* =nullptr);
	~SslClient() = default;
public slots:
	void dataReceive(const QString&);//data to write to socket
	void addCapability(const QString&); //needed for parser
private slots:
	//basic functionality
	void socketEncrypted();
	void socketReadyRead();
	void sendData(const QString&);
	void pong();
	void setupSecureSocket();
	//error handling
	void sslErrors(const QList<QSslError>&);
	
signals:
	void dataWrite(const QString&);
	void twitchCapabilities(const QVariant&);
	void parseReply(const QString&);
	void commandReceive(const QVariant& data);
private:
	QSslSocket* mSocket;
	ReplyParser* mReplyParser;
	bool mHandlingSocketError;
};

class ReplyParser : public QObject {
	Q_OBJECT
public:
	ReplyParser(QObject* = nullptr);
	~ReplyParser();
	/*enum Capability{
		Membership = 0x1,
		Tags = 0x2,
		Commands = 0x4,
		ChatRooms =0x8
	};
	Q_DECLARE_FLAGS(Capabilities, Capability)*/
public slots:
	void parseReply(const QString&);
	void addCapability(const QString&);
signals:
	void ping();
	void twitchCapabilities(const QString&);
	void dataWrite(const QString&);
	void commandReceive(const QVariant&);

private:
	std::map<QString, bool> capabilityValues;
 };
//Q_DECLARE_OPERATORS_FOR_FLAGS(ReplyParser::Capabilities)
