/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *SPINPRZYCISK;
    QWidget *gridLayoutWidget;
    QGridLayout *maszyna;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QLineEdit *JapkoEdit;
    QLineEdit *BananEdit;
    QLineEdit *WinogronkoEdit;
    QLineEdit *WisniaEdit;
    QLineEdit *AnanasEdit;
    QLineEdit *KiwiEdit;
    QLineEdit *BonusEdit;
    QLabel *ObrazekJapko;
    QLabel *ObrazekBanan;
    QLabel *ObrazekWinogrono;
    QLabel *ObrazekWisnia;
    QLabel *ObrazekAnanas;
    QLabel *ObrazekKiwi;
    QLabel *ObrazekBonus;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(563, 458);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        SPINPRZYCISK = new QPushButton(centralwidget);
        SPINPRZYCISK->setObjectName("SPINPRZYCISK");
        SPINPRZYCISK->setGeometry(QRect(460, 290, 80, 61));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(10, 10, 421, 261));
        maszyna = new QGridLayout(gridLayoutWidget);
        maszyna->setObjectName("maszyna");
        maszyna->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(450, 10, 101, 151));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(verticalLayoutWidget);
        widget->setObjectName("widget");
        JapkoEdit = new QLineEdit(widget);
        JapkoEdit->setObjectName("JapkoEdit");
        JapkoEdit->setGeometry(QRect(30, 0, 61, 20));
        BananEdit = new QLineEdit(widget);
        BananEdit->setObjectName("BananEdit");
        BananEdit->setGeometry(QRect(30, 20, 61, 20));
        WinogronkoEdit = new QLineEdit(widget);
        WinogronkoEdit->setObjectName("WinogronkoEdit");
        WinogronkoEdit->setGeometry(QRect(30, 40, 61, 20));
        WisniaEdit = new QLineEdit(widget);
        WisniaEdit->setObjectName("WisniaEdit");
        WisniaEdit->setGeometry(QRect(30, 60, 61, 20));
        AnanasEdit = new QLineEdit(widget);
        AnanasEdit->setObjectName("AnanasEdit");
        AnanasEdit->setGeometry(QRect(30, 80, 61, 20));
        KiwiEdit = new QLineEdit(widget);
        KiwiEdit->setObjectName("KiwiEdit");
        KiwiEdit->setGeometry(QRect(30, 100, 61, 20));
        BonusEdit = new QLineEdit(widget);
        BonusEdit->setObjectName("BonusEdit");
        BonusEdit->setGeometry(QRect(30, 120, 61, 20));
        ObrazekJapko = new QLabel(widget);
        ObrazekJapko->setObjectName("ObrazekJapko");
        ObrazekJapko->setGeometry(QRect(10, 0, 16, 16));
        ObrazekBanan = new QLabel(widget);
        ObrazekBanan->setObjectName("ObrazekBanan");
        ObrazekBanan->setGeometry(QRect(10, 20, 16, 16));
        ObrazekWinogrono = new QLabel(widget);
        ObrazekWinogrono->setObjectName("ObrazekWinogrono");
        ObrazekWinogrono->setGeometry(QRect(10, 40, 16, 16));
        ObrazekWisnia = new QLabel(widget);
        ObrazekWisnia->setObjectName("ObrazekWisnia");
        ObrazekWisnia->setGeometry(QRect(10, 60, 16, 16));
        ObrazekAnanas = new QLabel(widget);
        ObrazekAnanas->setObjectName("ObrazekAnanas");
        ObrazekAnanas->setGeometry(QRect(10, 80, 16, 16));
        ObrazekKiwi = new QLabel(widget);
        ObrazekKiwi->setObjectName("ObrazekKiwi");
        ObrazekKiwi->setGeometry(QRect(10, 100, 16, 16));
        ObrazekBonus = new QLabel(widget);
        ObrazekBonus->setObjectName("ObrazekBonus");
        ObrazekBonus->setGeometry(QRect(10, 120, 16, 16));

        verticalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 563, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        SPINPRZYCISK->setText(QCoreApplication::translate("MainWindow", "SPINEK", nullptr));
        ObrazekJapko->setText(QCoreApplication::translate("MainWindow", "\360\237\215\216", nullptr));
        ObrazekBanan->setText(QCoreApplication::translate("MainWindow", "\360\237\215\214", nullptr));
        ObrazekWinogrono->setText(QCoreApplication::translate("MainWindow", "\360\237\215\207", nullptr));
        ObrazekWisnia->setText(QCoreApplication::translate("MainWindow", "\360\237\215\222", nullptr));
        ObrazekAnanas->setText(QCoreApplication::translate("MainWindow", "\360\237\215\215", nullptr));
        ObrazekKiwi->setText(QCoreApplication::translate("MainWindow", "\360\237\245\235", nullptr));
        ObrazekBonus->setText(QCoreApplication::translate("MainWindow", "\360\237\216\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
