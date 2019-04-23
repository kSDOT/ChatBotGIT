#pragma once

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariant>
#include <QUrl>
#include <QFIle>
#include <functional>
#include <QTextStream>
class JsonParser {//singeleton
public:
	static JsonParser& getInstance() {
		static JsonParser instance;
		return instance;
	}
	JsonParser(const JsonParser&) = delete;              // NOT implementable
	void operator=(const JsonParser&) = delete;
	void setJsonFile(const QString&);
	QMap<QString, QString> readSettings();
	qint64 writeSettings(const QMap<QString, QString>&);
	JsonParser() = default;
	~JsonParser() = default;
private:
	QVariant toVariant(const QMap<QString, QString>&);
private:
	QString mFilePath;
	//QMap<QString, QString> settings;
};

