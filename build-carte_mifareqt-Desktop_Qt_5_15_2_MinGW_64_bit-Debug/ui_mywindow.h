/********************************************************************************
** Form generated from reading UI file 'mywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWINDOW_H
#define UI_MYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyWindow
{
public:
    QPushButton *Connect;
    QTextEdit *Display;
    QPushButton *Exit;

    void setupUi(QWidget *MyWindow)
    {
        if (MyWindow->objectName().isEmpty())
            MyWindow->setObjectName(QString::fromUtf8("MyWindow"));
        MyWindow->resize(800, 600);
        Connect = new QPushButton(MyWindow);
        Connect->setObjectName(QString::fromUtf8("Connect"));
        Connect->setGeometry(QRect(130, 340, 93, 29));
        Display = new QTextEdit(MyWindow);
        Display->setObjectName(QString::fromUtf8("Display"));
        Display->setGeometry(QRect(260, 310, 351, 87));
        Exit = new QPushButton(MyWindow);
        Exit->setObjectName(QString::fromUtf8("Exit"));
        Exit->setGeometry(QRect(540, 110, 93, 29));

        retranslateUi(MyWindow);

        QMetaObject::connectSlotsByName(MyWindow);
    } // setupUi

    void retranslateUi(QWidget *MyWindow)
    {
        MyWindow->setWindowTitle(QCoreApplication::translate("MyWindow", "MyWindow", nullptr));
        Connect->setText(QCoreApplication::translate("MyWindow", "Connect", nullptr));
        Exit->setText(QCoreApplication::translate("MyWindow", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyWindow: public Ui_MyWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWINDOW_H
