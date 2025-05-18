/********************************************************************************
** Form generated from reading UI file 'oknogra1.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OKNOGRA1_H
#define UI_OKNOGRA1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OknoGra1
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *minusButton;
    QPushButton *plusButton;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *SPINPRZYCISK;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *AUTOSPINPRZYCISK;
    QSpacerItem *horizontalSpacer_6;
    QLabel *infoLabel;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *ObrazekJapko;
    QLineEdit *JapkoEdit;
    QLineEdit *liczbaSymboliLineEdit_Japko;
    QLineEdit *kwotaWygranejLineEdit_Japko;
    QLabel *ObrazekBanan;
    QLineEdit *BananEdit;
    QLineEdit *liczbaSymboliLineEdit_Banan;
    QLineEdit *kwotaWygranejLineEdit_Banan;
    QLabel *ObrazekWinogrono;
    QLineEdit *WinogronkoEdit;
    QLineEdit *liczbaSymboliLineEdit_Winogronko;
    QLineEdit *kwotaWygranejLineEdit_Winogronko;
    QLabel *ObrazekWisnia;
    QLineEdit *WisniaEdit;
    QLineEdit *liczbaSymboliLineEdit_Wisnia;
    QLineEdit *kwotaWygranejLineEdit_Wisnia;
    QLabel *ObrazekAnanas;
    QLineEdit *AnanasEdit;
    QLineEdit *liczbaSymboliLineEdit_Ananas;
    QLineEdit *kwotaWygranejLineEdit_Ananas;
    QLabel *ObrazekKiwi;
    QLineEdit *KiwiEdit;
    QLineEdit *liczbaSymboliLineEdit_Kiwi;
    QLineEdit *kwotaWygranejLineEdit_Kiwi;
    QLabel *ObrazekBonus;
    QLineEdit *BonusEdit;
    QLineEdit *liczbaSymboliLineEdit_Bonus;
    QGridLayout *maszyna;
    QGridLayout *gridLayout_6;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_4;
    QLabel *saldoLabel;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_2;
    QLabel *StawkaLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *OknoGra1)
    {
        if (OknoGra1->objectName().isEmpty())
            OknoGra1->setObjectName("OknoGra1");
        OknoGra1->resize(721, 589);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OknoGra1->sizePolicy().hasHeightForWidth());
        OknoGra1->setProperty("SizePolicy", QVariant(sizePolicy));
        centralwidget = new QWidget(OknoGra1);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setProperty("SizePolicy", QVariant(sizePolicy));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        minusButton = new QPushButton(centralwidget);
        minusButton->setObjectName("minusButton");

        horizontalLayout_2->addWidget(minusButton);

        plusButton = new QPushButton(centralwidget);
        plusButton->setObjectName("plusButton");

        horizontalLayout_2->addWidget(plusButton);


        gridLayout_3->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        SPINPRZYCISK = new QPushButton(centralwidget);
        SPINPRZYCISK->setObjectName("SPINPRZYCISK");

        horizontalLayout->addWidget(SPINPRZYCISK);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        AUTOSPINPRZYCISK = new QPushButton(centralwidget);
        AUTOSPINPRZYCISK->setObjectName("AUTOSPINPRZYCISK");

        horizontalLayout->addWidget(AUTOSPINPRZYCISK);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);


        gridLayout_3->addLayout(horizontalLayout, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_3);


        gridLayout->addLayout(verticalLayout, 10, 3, 4, 2);

        infoLabel = new QLabel(centralwidget);
        infoLabel->setObjectName("infoLabel");
        QFont font;
        font.setPointSize(18);
        infoLabel->setFont(font);
        infoLabel->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        infoLabel->setFrameShape(QFrame::Shape::NoFrame);
        infoLabel->setLineWidth(1);
        infoLabel->setScaledContents(false);
        infoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(infoLabel, 10, 1, 2, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName("gridLayout_2");
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label, 0, 1, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_2, 0, 2, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_3, 0, 3, 1, 1);

        ObrazekJapko = new QLabel(widget);
        ObrazekJapko->setObjectName("ObrazekJapko");

        gridLayout_2->addWidget(ObrazekJapko, 1, 0, 1, 1);

        JapkoEdit = new QLineEdit(widget);
        JapkoEdit->setObjectName("JapkoEdit");

        gridLayout_2->addWidget(JapkoEdit, 1, 1, 1, 1);

        liczbaSymboliLineEdit_Japko = new QLineEdit(widget);
        liczbaSymboliLineEdit_Japko->setObjectName("liczbaSymboliLineEdit_Japko");

        gridLayout_2->addWidget(liczbaSymboliLineEdit_Japko, 1, 2, 1, 1);

        kwotaWygranejLineEdit_Japko = new QLineEdit(widget);
        kwotaWygranejLineEdit_Japko->setObjectName("kwotaWygranejLineEdit_Japko");

        gridLayout_2->addWidget(kwotaWygranejLineEdit_Japko, 1, 3, 1, 1);

        ObrazekBanan = new QLabel(widget);
        ObrazekBanan->setObjectName("ObrazekBanan");

        gridLayout_2->addWidget(ObrazekBanan, 2, 0, 1, 1);

        BananEdit = new QLineEdit(widget);
        BananEdit->setObjectName("BananEdit");

        gridLayout_2->addWidget(BananEdit, 2, 1, 1, 1);

        liczbaSymboliLineEdit_Banan = new QLineEdit(widget);
        liczbaSymboliLineEdit_Banan->setObjectName("liczbaSymboliLineEdit_Banan");

        gridLayout_2->addWidget(liczbaSymboliLineEdit_Banan, 2, 2, 1, 1);

        kwotaWygranejLineEdit_Banan = new QLineEdit(widget);
        kwotaWygranejLineEdit_Banan->setObjectName("kwotaWygranejLineEdit_Banan");

        gridLayout_2->addWidget(kwotaWygranejLineEdit_Banan, 2, 3, 1, 1);

        ObrazekWinogrono = new QLabel(widget);
        ObrazekWinogrono->setObjectName("ObrazekWinogrono");

        gridLayout_2->addWidget(ObrazekWinogrono, 3, 0, 1, 1);

        WinogronkoEdit = new QLineEdit(widget);
        WinogronkoEdit->setObjectName("WinogronkoEdit");

        gridLayout_2->addWidget(WinogronkoEdit, 3, 1, 1, 1);

        liczbaSymboliLineEdit_Winogronko = new QLineEdit(widget);
        liczbaSymboliLineEdit_Winogronko->setObjectName("liczbaSymboliLineEdit_Winogronko");

        gridLayout_2->addWidget(liczbaSymboliLineEdit_Winogronko, 3, 2, 1, 1);

        kwotaWygranejLineEdit_Winogronko = new QLineEdit(widget);
        kwotaWygranejLineEdit_Winogronko->setObjectName("kwotaWygranejLineEdit_Winogronko");

        gridLayout_2->addWidget(kwotaWygranejLineEdit_Winogronko, 3, 3, 1, 1);

        ObrazekWisnia = new QLabel(widget);
        ObrazekWisnia->setObjectName("ObrazekWisnia");

        gridLayout_2->addWidget(ObrazekWisnia, 4, 0, 1, 1);

        WisniaEdit = new QLineEdit(widget);
        WisniaEdit->setObjectName("WisniaEdit");

        gridLayout_2->addWidget(WisniaEdit, 4, 1, 1, 1);

        liczbaSymboliLineEdit_Wisnia = new QLineEdit(widget);
        liczbaSymboliLineEdit_Wisnia->setObjectName("liczbaSymboliLineEdit_Wisnia");

        gridLayout_2->addWidget(liczbaSymboliLineEdit_Wisnia, 4, 2, 1, 1);

        kwotaWygranejLineEdit_Wisnia = new QLineEdit(widget);
        kwotaWygranejLineEdit_Wisnia->setObjectName("kwotaWygranejLineEdit_Wisnia");

        gridLayout_2->addWidget(kwotaWygranejLineEdit_Wisnia, 4, 3, 1, 1);

        ObrazekAnanas = new QLabel(widget);
        ObrazekAnanas->setObjectName("ObrazekAnanas");

        gridLayout_2->addWidget(ObrazekAnanas, 5, 0, 1, 1);

        AnanasEdit = new QLineEdit(widget);
        AnanasEdit->setObjectName("AnanasEdit");

        gridLayout_2->addWidget(AnanasEdit, 5, 1, 1, 1);

        liczbaSymboliLineEdit_Ananas = new QLineEdit(widget);
        liczbaSymboliLineEdit_Ananas->setObjectName("liczbaSymboliLineEdit_Ananas");

        gridLayout_2->addWidget(liczbaSymboliLineEdit_Ananas, 5, 2, 1, 1);

        kwotaWygranejLineEdit_Ananas = new QLineEdit(widget);
        kwotaWygranejLineEdit_Ananas->setObjectName("kwotaWygranejLineEdit_Ananas");

        gridLayout_2->addWidget(kwotaWygranejLineEdit_Ananas, 5, 3, 1, 1);

        ObrazekKiwi = new QLabel(widget);
        ObrazekKiwi->setObjectName("ObrazekKiwi");

        gridLayout_2->addWidget(ObrazekKiwi, 6, 0, 1, 1);

        KiwiEdit = new QLineEdit(widget);
        KiwiEdit->setObjectName("KiwiEdit");

        gridLayout_2->addWidget(KiwiEdit, 6, 1, 1, 1);

        liczbaSymboliLineEdit_Kiwi = new QLineEdit(widget);
        liczbaSymboliLineEdit_Kiwi->setObjectName("liczbaSymboliLineEdit_Kiwi");

        gridLayout_2->addWidget(liczbaSymboliLineEdit_Kiwi, 6, 2, 1, 1);

        kwotaWygranejLineEdit_Kiwi = new QLineEdit(widget);
        kwotaWygranejLineEdit_Kiwi->setObjectName("kwotaWygranejLineEdit_Kiwi");

        gridLayout_2->addWidget(kwotaWygranejLineEdit_Kiwi, 6, 3, 1, 1);

        ObrazekBonus = new QLabel(widget);
        ObrazekBonus->setObjectName("ObrazekBonus");

        gridLayout_2->addWidget(ObrazekBonus, 7, 0, 1, 1);

        BonusEdit = new QLineEdit(widget);
        BonusEdit->setObjectName("BonusEdit");

        gridLayout_2->addWidget(BonusEdit, 7, 1, 1, 1);

        liczbaSymboliLineEdit_Bonus = new QLineEdit(widget);
        liczbaSymboliLineEdit_Bonus->setObjectName("liczbaSymboliLineEdit_Bonus");

        gridLayout_2->addWidget(liczbaSymboliLineEdit_Bonus, 7, 2, 1, 1);


        gridLayout->addWidget(widget, 0, 3, 2, 2);

        maszyna = new QGridLayout();
        maszyna->setObjectName("maszyna");

        gridLayout->addLayout(maszyna, 0, 0, 4, 3);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName("gridLayout_6");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_6->addItem(horizontalSpacer, 2, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_4, 1, 1, 1, 1);

        saldoLabel = new QLabel(centralwidget);
        saldoLabel->setObjectName("saldoLabel");
        QFont font1;
        font1.setPointSize(20);
        saldoLabel->setFont(font1);
        saldoLabel->setFrameShape(QFrame::Shape::NoFrame);
        saldoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_6->addWidget(saldoLabel, 2, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_5, 2, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_2, 3, 1, 1, 1);

        StawkaLabel = new QLabel(centralwidget);
        StawkaLabel->setObjectName("StawkaLabel");
        QFont font2;
        font2.setPointSize(16);
        StawkaLabel->setFont(font2);
        StawkaLabel->setAcceptDrops(false);
        StawkaLabel->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        StawkaLabel->setFrameShape(QFrame::Shape::NoFrame);
        StawkaLabel->setFrameShadow(QFrame::Shadow::Plain);
        StawkaLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_6->addWidget(StawkaLabel, 4, 1, 1, 1);


        gridLayout->addLayout(gridLayout_6, 2, 3, 2, 2);

        OknoGra1->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OknoGra1);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 721, 21));
        OknoGra1->setMenuBar(menubar);
        statusbar = new QStatusBar(OknoGra1);
        statusbar->setObjectName("statusbar");
        OknoGra1->setStatusBar(statusbar);

        retranslateUi(OknoGra1);

        QMetaObject::connectSlotsByName(OknoGra1);
    } // setupUi

    void retranslateUi(QMainWindow *OknoGra1)
    {
        OknoGra1->setWindowTitle(QCoreApplication::translate("OknoGra1", "MainWindow", nullptr));
        minusButton->setText(QCoreApplication::translate("OknoGra1", "-", nullptr));
        plusButton->setText(QCoreApplication::translate("OknoGra1", "+", nullptr));
        SPINPRZYCISK->setText(QCoreApplication::translate("OknoGra1", "SPINEK", nullptr));
        AUTOSPINPRZYCISK->setText(QCoreApplication::translate("OknoGra1", "AUTOSPIN", nullptr));
        infoLabel->setText(QCoreApplication::translate("OknoGra1", "Wygrane", nullptr));
        label->setText(QCoreApplication::translate("OknoGra1", "Szanse", nullptr));
        label_2->setText(QCoreApplication::translate("OknoGra1", "Ilosc", nullptr));
        label_3->setText(QCoreApplication::translate("OknoGra1", "Mnoznik", nullptr));
        ObrazekJapko->setText(QCoreApplication::translate("OknoGra1", "\360\237\215\216", nullptr));
        ObrazekBanan->setText(QCoreApplication::translate("OknoGra1", "\360\237\215\214", nullptr));
        ObrazekWinogrono->setText(QCoreApplication::translate("OknoGra1", "\360\237\215\207", nullptr));
        ObrazekWisnia->setText(QCoreApplication::translate("OknoGra1", "\360\237\215\222", nullptr));
        ObrazekAnanas->setText(QCoreApplication::translate("OknoGra1", "\360\237\215\215", nullptr));
        ObrazekKiwi->setText(QCoreApplication::translate("OknoGra1", "\360\237\245\235", nullptr));
        ObrazekBonus->setText(QCoreApplication::translate("OknoGra1", "\360\237\216\201", nullptr));
        saldoLabel->setText(QCoreApplication::translate("OknoGra1", "Kasa", nullptr));
        StawkaLabel->setText(QCoreApplication::translate("OknoGra1", "SpinPrice", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OknoGra1: public Ui_OknoGra1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OKNOGRA1_H
