#include <QGuiApplication>
#include <QtNetwork>
#include "ChatBot.h"
#include <QGuiApplication>
#include <QQmlFileSelector>
#include <QApplication>
int main(int argc, char** argv) {
	QApplication::setEffectEnabled(Qt::UI_AnimateCombo, false);//disable dropdown animation
	QGuiApplication::setFont(QString{ "Calibri" });
	QGuiApplication app(argc, argv);
	app.setWindowIcon(QIcon{"Icons/WindowIcon.png"});
	JsonParser::getInstance().setJsonFile("persistent.json");
	if (!QSslSocket::supportsSsl()) {
		QMessageBox::information(0, "Secure Socket Client",
		"This system does not support SSL/TLS.");
		return -1;
	}
	ChatBot* c = new ChatBot{QUrl::fromLocalFile("window.qml"), &app};

	return app.exec();   
}
//todo:
//ssl error handling
//install/uninstall wizrd (ssl, qt)
