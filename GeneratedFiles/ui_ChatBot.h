/********************************************************************************
** Form generated from reading UI file 'ChatBot.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATBOT_H
#define UI_CHATBOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatBotClass
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QVBoxLayout *mainLayout;
    QTextBrowser *textDisplay;
    QHBoxLayout *infoLayout;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *capabilitiesComboBox;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *inputLayout;
    QTextEdit *textInput;
    QPushButton *sendButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ChatBotClass)
    {
        if (ChatBotClass->objectName().isEmpty())
            ChatBotClass->setObjectName(QString::fromUtf8("ChatBotClass"));
        ChatBotClass->resize(1021, 638);
        centralWidget = new QWidget(ChatBotClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 901, 2117));
        mainLayout = new QVBoxLayout(gridLayoutWidget);
        mainLayout->setSpacing(10);
        mainLayout->setContentsMargins(11, 11, 11, 11);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        textDisplay = new QTextBrowser(gridLayoutWidget);
        textDisplay->setObjectName(QString::fromUtf8("textDisplay"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textDisplay->sizePolicy().hasHeightForWidth());
        textDisplay->setSizePolicy(sizePolicy);
        textDisplay->setMinimumSize(QSize(0, 200));

        mainLayout->addWidget(textDisplay);

        infoLayout = new QHBoxLayout();
        infoLayout->setSpacing(6);
        infoLayout->setObjectName(QString::fromUtf8("infoLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        infoLayout->addItem(horizontalSpacer_2);

        capabilitiesComboBox = new QComboBox(gridLayoutWidget);
        capabilitiesComboBox->setObjectName(QString::fromUtf8("capabilitiesComboBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(capabilitiesComboBox->sizePolicy().hasHeightForWidth());
        capabilitiesComboBox->setSizePolicy(sizePolicy1);
        capabilitiesComboBox->setEditable(false);

        infoLayout->addWidget(capabilitiesComboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        infoLayout->addItem(horizontalSpacer);

        infoLayout->setStretch(0, 1);
        infoLayout->setStretch(1, 10);
        infoLayout->setStretch(2, 100);

        mainLayout->addLayout(infoLayout);

        inputLayout = new QHBoxLayout();
        inputLayout->setSpacing(6);
        inputLayout->setObjectName(QString::fromUtf8("inputLayout"));
        textInput = new QTextEdit(gridLayoutWidget);
        textInput->setObjectName(QString::fromUtf8("textInput"));

        inputLayout->addWidget(textInput);

        sendButton = new QPushButton(gridLayoutWidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(sendButton->sizePolicy().hasHeightForWidth());
        sendButton->setSizePolicy(sizePolicy2);

        inputLayout->addWidget(sendButton);


        mainLayout->addLayout(inputLayout);

        ChatBotClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ChatBotClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1021, 21));
        ChatBotClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ChatBotClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ChatBotClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ChatBotClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ChatBotClass->setStatusBar(statusBar);

        retranslateUi(ChatBotClass);

        QMetaObject::connectSlotsByName(ChatBotClass);
    } // setupUi

    void retranslateUi(QMainWindow *ChatBotClass)
    {
        ChatBotClass->setWindowTitle(QApplication::translate("ChatBotClass", "ChatBot", nullptr));
        sendButton->setText(QApplication::translate("ChatBotClass", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatBotClass: public Ui_ChatBotClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATBOT_H
