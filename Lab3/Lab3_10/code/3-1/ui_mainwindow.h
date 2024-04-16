/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCheckBox *LED_1;
    QCheckBox *LED_2;
    QCheckBox *LED_3;
    QCheckBox *LED_4;
    QLabel *label;
    QPushButton *get_led_switch;
    QPushButton *get_led;
    QTextEdit *textEdit;
    QLabel *label_1;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        LED_1 = new QCheckBox(centralWidget);
        LED_1->setObjectName(QStringLiteral("LED_1"));
        LED_1->setGeometry(QRect(90, 30, 92, 23));
        LED_2 = new QCheckBox(centralWidget);
        LED_2->setObjectName(QStringLiteral("LED_2"));
        LED_2->setGeometry(QRect(90, 60, 92, 23));
        LED_3 = new QCheckBox(centralWidget);
        LED_3->setObjectName(QStringLiteral("LED_3"));
        LED_3->setGeometry(QRect(90, 100, 92, 23));
        LED_4 = new QCheckBox(centralWidget);
        LED_4->setObjectName(QStringLiteral("LED_4"));
        LED_4->setGeometry(QRect(90, 130, 92, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(160, 30, 67, 17));
        get_led_switch = new QPushButton(centralWidget);
        get_led_switch->setObjectName(QStringLiteral("get_led_switch"));
        get_led_switch->setGeometry(QRect(160, 110, 121, 25));
        get_led = new QPushButton(centralWidget);
        get_led->setObjectName(QStringLiteral("get_led"));
        get_led->setGeometry(QRect(70, 160, 89, 25));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(160, 60, 104, 41));
        label_1 = new QLabel(centralWidget);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setGeometry(QRect(20, 20, 41, 31));
        label_1->setPixmap(QPixmap(QString::fromUtf8("../../../Downloads/p1.png")));
        label_1->setScaledContents(true);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 90, 41, 31));
        label_3->setPixmap(QPixmap(QString::fromUtf8("../../../Downloads/p1.png")));
        label_3->setScaledContents(true);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 50, 41, 31));
        label_2->setPixmap(QPixmap(QString::fromUtf8("../../../Downloads/p1.png")));
        label_2->setScaledContents(true);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 120, 41, 41));
        label_4->setPixmap(QPixmap(QString::fromUtf8("../../../Downloads/p1.png")));
        label_4->setScaledContents(true);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        LED_1->setText(QApplication::translate("MainWindow", "LED1", Q_NULLPTR));
        LED_2->setText(QApplication::translate("MainWindow", "LED2", Q_NULLPTR));
        LED_3->setText(QApplication::translate("MainWindow", "LED3", Q_NULLPTR));
        LED_4->setText(QApplication::translate("MainWindow", "LED4", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Times", Q_NULLPTR));
        get_led_switch->setText(QApplication::translate("MainWindow", "LED Switching", Q_NULLPTR));
        get_led->setText(QApplication::translate("MainWindow", "LED Shing", Q_NULLPTR));
        label_1->setText(QString());
        label_3->setText(QString());
        label_2->setText(QString());
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
