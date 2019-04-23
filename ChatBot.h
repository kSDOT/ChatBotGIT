#pragma once

#include <QtWidgets/QMainWindow>
#include <QKeyEvent>
#include <QPushButton>
#include <QMessageBox>
#include <QVector>
#include <QBitArray>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "SslClient.h"
#include <QStandardItemModel>

class KeyPressFilter;
class CommandHistory;
class Capability;

class ChatBot : public QObject
{
	Q_OBJECT			
public:
	ChatBot(const QUrl&, QObject *parent = nullptr);
public slots:
	void commandReceived();
	void commandReceived(const QString&);
	void commandReceived(const QVariant&);
	void updateSettings(const QVariant&);
signals:
	void inputReceived(const QString& input);
	void dataReceived(const QVariant& data);
	void clearInputLine();
private:	
	QVariantList toVariantList();
private:
	SslClient* mClient;
	KeyPressFilter* mFilter;
	CommandHistory* mHistory;
	QVector<Capability*> mCapabilities;
	QQmlApplicationEngine* mEngine;
	QMap<QString, QString> mSettings;
};

class KeyPressFilter : public QObject {
	Q_OBJECT
public:
	KeyPressFilter(QObject* = nullptr);
signals:
	void commandReceived();
	void commandHistory(int);
	void clearLine();
protected:
	bool eventFilter(QObject*, QEvent*);
};

class CommandHistory : public QObject{
	Q_OBJECT
public:
	CommandHistory(QObject* = nullptr);
public slots:
	void textChanged(const QString&);
	void addCommandHistory(const QString&);
	void commandHistory(int);
signals:
	void setInputLineTo(const QVariant&);
private:
	void resetHistoryIndex();
private:
	QVector<QString> mCommandsUsed;
	int mCurrentHistoryIndex = 0;
	QString mCurrentLineString;
	
};
/*
class SettingObject : public QObject {
	Q_OBJECT
	
	
};
*/
/*MOVED TO QML
class Capability : public QObject {
	Q_OBJECT
	Q_PROPERTY(bool state READ isSet WRITE set NOTIFY gotSet)
	Q_PROPERTY(QString command READ getCommand)
	Q_PROPERTY(QString displayName READ getDisplayName)

public:
	Capability(QString, QString, QObject* = nullptr);
	Capability(QObject* parent = nullptr) : Capability{ "", "", parent } {}

public slots:
	void set(bool = true);
	bool isSet() const;
	bool replyMatch(const QString&);

	QString getCommand() const;
	QString getDisplayName() const;

signals:
	void gotSet();
private: 
	bool mState = 0;
	QString mDisplayName;
	QString mCommand;
};*/