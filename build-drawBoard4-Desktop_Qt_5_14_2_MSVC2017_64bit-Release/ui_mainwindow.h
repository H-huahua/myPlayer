/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QWidget *centralwidget;
    QCheckBox *LineCheckBox;
    QCheckBox *textCheckBox;
    QCheckBox *rectangleCheckBox;
    QCheckBox *circleCheckBox;
    QPushButton *boldBtn;
    QPushButton *IncreaseBtn;
    QPushButton *decreaseBtn;
    QPushButton *italicBtn;
    QComboBox *colorComboBox;
    QPushButton *fillColorButton;
    QCheckBox *fillCheckBox;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        LineCheckBox = new QCheckBox(centralwidget);
        LineCheckBox->setObjectName(QString::fromUtf8("LineCheckBox"));
        LineCheckBox->setGeometry(QRect(0, 40, 73, 31));
        textCheckBox = new QCheckBox(centralwidget);
        textCheckBox->setObjectName(QString::fromUtf8("textCheckBox"));
        textCheckBox->setGeometry(QRect(0, 160, 73, 31));
        rectangleCheckBox = new QCheckBox(centralwidget);
        rectangleCheckBox->setObjectName(QString::fromUtf8("rectangleCheckBox"));
        rectangleCheckBox->setGeometry(QRect(0, 80, 73, 31));
        circleCheckBox = new QCheckBox(centralwidget);
        circleCheckBox->setObjectName(QString::fromUtf8("circleCheckBox"));
        circleCheckBox->setGeometry(QRect(0, 120, 73, 31));
        boldBtn = new QPushButton(centralwidget);
        boldBtn->setObjectName(QString::fromUtf8("boldBtn"));
        boldBtn->setGeometry(QRect(100, 0, 51, 31));
        IncreaseBtn = new QPushButton(centralwidget);
        IncreaseBtn->setObjectName(QString::fromUtf8("IncreaseBtn"));
        IncreaseBtn->setGeometry(QRect(0, 0, 51, 31));
        decreaseBtn = new QPushButton(centralwidget);
        decreaseBtn->setObjectName(QString::fromUtf8("decreaseBtn"));
        decreaseBtn->setGeometry(QRect(50, 0, 51, 31));
        italicBtn = new QPushButton(centralwidget);
        italicBtn->setObjectName(QString::fromUtf8("italicBtn"));
        italicBtn->setGeometry(QRect(150, 0, 51, 31));
        colorComboBox = new QComboBox(centralwidget);
        colorComboBox->setObjectName(QString::fromUtf8("colorComboBox"));
        colorComboBox->setGeometry(QRect(200, 0, 151, 31));
        fillColorButton = new QPushButton(centralwidget);
        fillColorButton->setObjectName(QString::fromUtf8("fillColorButton"));
        fillColorButton->setGeometry(QRect(350, 0, 141, 31));
        fillCheckBox = new QCheckBox(centralwidget);
        fillCheckBox->setObjectName(QString::fromUtf8("fillCheckBox"));
        fillCheckBox->setGeometry(QRect(0, 200, 73, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        LineCheckBox->setText(QCoreApplication::translate("MainWindow", "\347\233\264\347\272\277", nullptr));
        textCheckBox->setText(QCoreApplication::translate("MainWindow", "\346\226\207\345\255\227", nullptr));
        rectangleCheckBox->setText(QCoreApplication::translate("MainWindow", "\347\237\251\345\275\242", nullptr));
        circleCheckBox->setText(QCoreApplication::translate("MainWindow", "\345\234\206\345\275\242", nullptr));
        boldBtn->setText(QCoreApplication::translate("MainWindow", "\345\212\240\347\262\227", nullptr));
        IncreaseBtn->setText(QCoreApplication::translate("MainWindow", "\345\242\236\345\244\247", nullptr));
        decreaseBtn->setText(QCoreApplication::translate("MainWindow", "\345\207\217\345\260\217", nullptr));
        italicBtn->setText(QCoreApplication::translate("MainWindow", "\346\226\234\344\275\223", nullptr));
        fillColorButton->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\345\241\253\345\205\205\351\242\234\350\211\262", nullptr));
        fillCheckBox->setText(QCoreApplication::translate("MainWindow", "\345\241\253\345\205\205", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\350\217\234\345\215\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
