#include "JsonParser.h"
#include <QDebug>
void JsonParser::setJsonFile(const QString& url) {
	mFilePath = url;
}
QMap<QString, QString> JsonParser:: readSettings() {
	QMap<QString, QString>  settings;
	QFile jsonFile{ mFilePath };
	if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
		return QMap<QString, QString>();
	QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());
	QJsonObject mapToRead = doc.object();
	for (const auto& key : mapToRead.keys())
		settings[key] = mapToRead.value(key).toString();
	return settings;
}
qint64 JsonParser::writeSettings(const QMap<QString, QString>& settings) {
	QFile jsonFile{ mFilePath };
	if (!jsonFile.open(QFile::WriteOnly | QFile::Text))
		return 0.0;

	QJsonDocument doc{ QJsonDocument::fromVariant(toVariant(settings)) };

	qint64 bytesWritten = jsonFile.write(doc.toJson());
	jsonFile.close();
	return bytesWritten;
}
QVariant JsonParser::toVariant(const QMap<QString, QString>& settings) {
	QVariantMap mapToWrite;
	for (const auto& key : settings.keys())//structured binding not working, qmap doesnt return pair?
		mapToWrite[key] = settings.value(key);
	return mapToWrite;
}
