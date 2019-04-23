/*#pragma once // PASSED TO QML/JS
#include <QString>
#include <QHash>
#include <QObject>
#include <QRandomGenerator>
#include <QRegularExpression>
//SINGELETON CLASS
//holds all available commands
//matches a command request with command implementation
class Command : public QObject{ 
	Q_OBJECT
public:
	static Command& getInstance() {
		static Command instance;
		return instance;
	}

	Command();
	~Command() = default;

	Command(const Command&) = delete;              // NOT implementable
	void operator=(const Command&) = delete;
signals:
	void commandReply(const QString&);
public slots:
	void commandReceive(const QMap<QString, QString>&);
private slots:
	static void unrecognizedCommand(const QMap<QString, QString>&);
	static void rollDice(const QMap<QString, QString>&);
	static void printHelp(const QMap<QString, QString>&);
private:

	QString user;
	QString command;
	QHash<QString, QPair<std::function<void(const QMap<QString, QString>&)>, QString>>allCommands;

};
*/