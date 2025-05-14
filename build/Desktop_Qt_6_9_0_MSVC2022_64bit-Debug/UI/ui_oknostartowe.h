/********************************************************************************
** Form generated from reading UI file 'oknostartowe.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OKNOSTARTOWE_H
#define UI_OKNOSTARTOWE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OknoStartowe
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *logoLabel;
    QHBoxLayout *horizontalLayout;
    QPushButton *firstGameButton;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *secondGameButton;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *exitButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *OknoStartowe)
    {
        if (OknoStartowe->objectName().isEmpty())
            OknoStartowe->setObjectName("OknoStartowe");
        OknoStartowe->resize(567, 392);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OknoStartowe->sizePolicy().hasHeightForWidth());
        OknoStartowe->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(OknoStartowe);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 561, 341));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        logoLabel = new QLabel(verticalLayoutWidget);
        logoLabel->setObjectName("logoLabel");

        verticalLayout->addWidget(logoLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        firstGameButton = new QPushButton(verticalLayoutWidget);
        firstGameButton->setObjectName("firstGameButton");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(firstGameButton->sizePolicy().hasHeightForWidth());
        firstGameButton->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(firstGameButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        secondGameButton = new QPushButton(verticalLayoutWidget);
        secondGameButton->setObjectName("secondGameButton");
        sizePolicy2.setHeightForWidth(secondGameButton->sizePolicy().hasHeightForWidth());
        secondGameButton->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(secondGameButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        exitButton = new QPushButton(verticalLayoutWidget);
        exitButton->setObjectName("exitButton");
        sizePolicy2.setHeightForWidth(exitButton->sizePolicy().hasHeightForWidth());
        exitButton->setSizePolicy(sizePolicy2);
        exitButton->setMinimumSize(QSize(0, 0));

        horizontalLayout_3->addWidget(exitButton);


        verticalLayout->addLayout(horizontalLayout_3);

        OknoStartowe->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OknoStartowe);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 567, 21));
        OknoStartowe->setMenuBar(menubar);
        statusbar = new QStatusBar(OknoStartowe);
        statusbar->setObjectName("statusbar");
        OknoStartowe->setStatusBar(statusbar);

        retranslateUi(OknoStartowe);

        QMetaObject::connectSlotsByName(OknoStartowe);
    } // setupUi

    void retranslateUi(QMainWindow *OknoStartowe)
    {
        OknoStartowe->setWindowTitle(QCoreApplication::translate("OknoStartowe", "OknoStartowe", nullptr));
        logoLabel->setText(QCoreApplication::translate("OknoStartowe", "TextLabel", nullptr));
        firstGameButton->setText(QCoreApplication::translate("OknoStartowe", "Gra 1", nullptr));
        secondGameButton->setText(QCoreApplication::translate("OknoStartowe", "Gra 2", nullptr));
        exitButton->setText(QCoreApplication::translate("OknoStartowe", "Wyj\305\233cie", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OknoStartowe: public Ui_OknoStartowe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OKNOSTARTOWE_H
