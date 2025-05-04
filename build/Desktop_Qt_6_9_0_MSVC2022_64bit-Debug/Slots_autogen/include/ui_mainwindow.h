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
    QLabel *label;
    QLineEdit *liczbaSymboliLineEdit_Kiwi;
    QLineEdit *liczbaSymboliLineEdit_Wisnia;
    QLineEdit *liczbaSymboliLineEdit_Bonus;
    QLineEdit *liczbaSymboliLineEdit_Banan;
    QLineEdit *liczbaSymboliLineEdit_Ananas;
    QLineEdit *liczbaSymboliLineEdit_Japko;
    QLineEdit *liczbaSymboliLineEdit_Winogronko;
    QLineEdit *kwotaWygranejLineEdit_Japko;
    QLineEdit *kwotaWygranejLineEdit_Wisnia;
    QLineEdit *kwotaWygranejLineEdit_Ananas;
    QLineEdit *kwotaWygranejLineEdit_Banan;
    QLineEdit *kwotaWygranejLineEdit_Winogronko;
    QLineEdit *kwotaWygranejLineEdit_Bonus;
    QLineEdit *kwotaWygranejLineEdit_Kiwi;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *plusButton;
    QPushButton *minusButton;
    QLabel *StawkaLabel;
    QLabel *saldoLabel;
    QLabel *infoLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(699, 551);
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
        verticalLayoutWidget->setGeometry(QRect(450, 10, 241, 171));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(verticalLayoutWidget);
        widget->setObjectName("widget");
        JapkoEdit = new QLineEdit(widget);
        JapkoEdit->setObjectName("JapkoEdit");
        JapkoEdit->setGeometry(QRect(30, 20, 61, 20));
        BananEdit = new QLineEdit(widget);
        BananEdit->setObjectName("BananEdit");
        BananEdit->setGeometry(QRect(30, 40, 61, 20));
        WinogronkoEdit = new QLineEdit(widget);
        WinogronkoEdit->setObjectName("WinogronkoEdit");
        WinogronkoEdit->setGeometry(QRect(30, 60, 61, 20));
        WisniaEdit = new QLineEdit(widget);
        WisniaEdit->setObjectName("WisniaEdit");
        WisniaEdit->setGeometry(QRect(30, 80, 61, 20));
        AnanasEdit = new QLineEdit(widget);
        AnanasEdit->setObjectName("AnanasEdit");
        AnanasEdit->setGeometry(QRect(30, 100, 61, 20));
        KiwiEdit = new QLineEdit(widget);
        KiwiEdit->setObjectName("KiwiEdit");
        KiwiEdit->setGeometry(QRect(30, 120, 61, 20));
        BonusEdit = new QLineEdit(widget);
        BonusEdit->setObjectName("BonusEdit");
        BonusEdit->setGeometry(QRect(30, 140, 61, 20));
        ObrazekJapko = new QLabel(widget);
        ObrazekJapko->setObjectName("ObrazekJapko");
        ObrazekJapko->setGeometry(QRect(10, 20, 16, 16));
        ObrazekBanan = new QLabel(widget);
        ObrazekBanan->setObjectName("ObrazekBanan");
        ObrazekBanan->setGeometry(QRect(10, 40, 16, 16));
        ObrazekWinogrono = new QLabel(widget);
        ObrazekWinogrono->setObjectName("ObrazekWinogrono");
        ObrazekWinogrono->setGeometry(QRect(10, 60, 16, 16));
        ObrazekWisnia = new QLabel(widget);
        ObrazekWisnia->setObjectName("ObrazekWisnia");
        ObrazekWisnia->setGeometry(QRect(10, 80, 16, 16));
        ObrazekAnanas = new QLabel(widget);
        ObrazekAnanas->setObjectName("ObrazekAnanas");
        ObrazekAnanas->setGeometry(QRect(10, 100, 16, 16));
        ObrazekKiwi = new QLabel(widget);
        ObrazekKiwi->setObjectName("ObrazekKiwi");
        ObrazekKiwi->setGeometry(QRect(10, 120, 16, 16));
        ObrazekBonus = new QLabel(widget);
        ObrazekBonus->setObjectName("ObrazekBonus");
        ObrazekBonus->setGeometry(QRect(10, 140, 16, 16));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 0, 41, 20));
        liczbaSymboliLineEdit_Kiwi = new QLineEdit(widget);
        liczbaSymboliLineEdit_Kiwi->setObjectName("liczbaSymboliLineEdit_Kiwi");
        liczbaSymboliLineEdit_Kiwi->setGeometry(QRect(100, 120, 61, 20));
        liczbaSymboliLineEdit_Wisnia = new QLineEdit(widget);
        liczbaSymboliLineEdit_Wisnia->setObjectName("liczbaSymboliLineEdit_Wisnia");
        liczbaSymboliLineEdit_Wisnia->setGeometry(QRect(100, 80, 61, 20));
        liczbaSymboliLineEdit_Bonus = new QLineEdit(widget);
        liczbaSymboliLineEdit_Bonus->setObjectName("liczbaSymboliLineEdit_Bonus");
        liczbaSymboliLineEdit_Bonus->setGeometry(QRect(100, 140, 61, 20));
        liczbaSymboliLineEdit_Banan = new QLineEdit(widget);
        liczbaSymboliLineEdit_Banan->setObjectName("liczbaSymboliLineEdit_Banan");
        liczbaSymboliLineEdit_Banan->setGeometry(QRect(100, 40, 61, 20));
        liczbaSymboliLineEdit_Ananas = new QLineEdit(widget);
        liczbaSymboliLineEdit_Ananas->setObjectName("liczbaSymboliLineEdit_Ananas");
        liczbaSymboliLineEdit_Ananas->setGeometry(QRect(100, 100, 61, 20));
        liczbaSymboliLineEdit_Japko = new QLineEdit(widget);
        liczbaSymboliLineEdit_Japko->setObjectName("liczbaSymboliLineEdit_Japko");
        liczbaSymboliLineEdit_Japko->setGeometry(QRect(100, 20, 61, 20));
        liczbaSymboliLineEdit_Winogronko = new QLineEdit(widget);
        liczbaSymboliLineEdit_Winogronko->setObjectName("liczbaSymboliLineEdit_Winogronko");
        liczbaSymboliLineEdit_Winogronko->setGeometry(QRect(100, 60, 61, 20));
        kwotaWygranejLineEdit_Japko = new QLineEdit(widget);
        kwotaWygranejLineEdit_Japko->setObjectName("kwotaWygranejLineEdit_Japko");
        kwotaWygranejLineEdit_Japko->setGeometry(QRect(170, 20, 61, 20));
        kwotaWygranejLineEdit_Wisnia = new QLineEdit(widget);
        kwotaWygranejLineEdit_Wisnia->setObjectName("kwotaWygranejLineEdit_Wisnia");
        kwotaWygranejLineEdit_Wisnia->setGeometry(QRect(170, 80, 61, 20));
        kwotaWygranejLineEdit_Ananas = new QLineEdit(widget);
        kwotaWygranejLineEdit_Ananas->setObjectName("kwotaWygranejLineEdit_Ananas");
        kwotaWygranejLineEdit_Ananas->setGeometry(QRect(170, 100, 61, 20));
        kwotaWygranejLineEdit_Banan = new QLineEdit(widget);
        kwotaWygranejLineEdit_Banan->setObjectName("kwotaWygranejLineEdit_Banan");
        kwotaWygranejLineEdit_Banan->setGeometry(QRect(170, 40, 61, 20));
        kwotaWygranejLineEdit_Winogronko = new QLineEdit(widget);
        kwotaWygranejLineEdit_Winogronko->setObjectName("kwotaWygranejLineEdit_Winogronko");
        kwotaWygranejLineEdit_Winogronko->setGeometry(QRect(170, 60, 61, 20));
        kwotaWygranejLineEdit_Bonus = new QLineEdit(widget);
        kwotaWygranejLineEdit_Bonus->setObjectName("kwotaWygranejLineEdit_Bonus");
        kwotaWygranejLineEdit_Bonus->setGeometry(QRect(170, 140, 61, 20));
        kwotaWygranejLineEdit_Kiwi = new QLineEdit(widget);
        kwotaWygranejLineEdit_Kiwi->setObjectName("kwotaWygranejLineEdit_Kiwi");
        kwotaWygranejLineEdit_Kiwi->setGeometry(QRect(170, 120, 61, 20));
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(100, 0, 41, 20));
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(170, 0, 41, 20));

        verticalLayout->addWidget(widget);

        plusButton = new QPushButton(centralwidget);
        plusButton->setObjectName("plusButton");
        plusButton->setGeometry(QRect(520, 370, 21, 18));
        minusButton = new QPushButton(centralwidget);
        minusButton->setObjectName("minusButton");
        minusButton->setGeometry(QRect(460, 370, 21, 20));
        StawkaLabel = new QLabel(centralwidget);
        StawkaLabel->setObjectName("StawkaLabel");
        StawkaLabel->setGeometry(QRect(480, 370, 37, 12));
        StawkaLabel->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        StawkaLabel->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignHCenter);
        saldoLabel = new QLabel(centralwidget);
        saldoLabel->setObjectName("saldoLabel");
        saldoLabel->setGeometry(QRect(470, 250, 71, 31));
        saldoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        infoLabel = new QLabel(centralwidget);
        infoLabel->setObjectName("infoLabel");
        infoLabel->setGeometry(QRect(280, 340, 101, 61));
        infoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 699, 17));
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
        label->setText(QCoreApplication::translate("MainWindow", "Szanse", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Ilosc", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Mnoznik", nullptr));
        plusButton->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        minusButton->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        StawkaLabel->setText(QCoreApplication::translate("MainWindow", "SpinPrice", nullptr));
        saldoLabel->setText(QCoreApplication::translate("MainWindow", "Kasa", nullptr));
        infoLabel->setText(QCoreApplication::translate("MainWindow", "Wygrane", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
