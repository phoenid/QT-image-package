/********************************************************************************
** Form generated from reading UI file 'QtWidgetsClass.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSCLASS_H
#define UI_QTWIDGETSCLASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsClassClass
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *QtWidgetsClassClass)
    {
        if (QtWidgetsClassClass->objectName().isEmpty())
            QtWidgetsClassClass->setObjectName(QString::fromUtf8("QtWidgetsClassClass"));
        QtWidgetsClassClass->resize(600, 400);
        label = new QLabel(QtWidgetsClassClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 170, 91, 20));
        lineEdit = new QLineEdit(QtWidgetsClassClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(250, 170, 121, 20));
        pushButton = new QPushButton(QtWidgetsClassClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(180, 210, 75, 23));
        pushButton_2 = new QPushButton(QtWidgetsClassClass);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(270, 210, 75, 23));

        retranslateUi(QtWidgetsClassClass);

        QMetaObject::connectSlotsByName(QtWidgetsClassClass);
    } // setupUi

    void retranslateUi(QDialog *QtWidgetsClassClass)
    {
        QtWidgetsClassClass->setWindowTitle(QCoreApplication::translate("QtWidgetsClassClass", "QtWidgetsClass", nullptr));
        label->setText(QCoreApplication::translate("QtWidgetsClassClass", "\350\257\267\350\276\223\345\205\245\346\227\213\350\275\254\350\247\222\345\272\246\357\274\232", nullptr));
        lineEdit->setText(QCoreApplication::translate("QtWidgetsClassClass", "0", nullptr));
        pushButton->setText(QCoreApplication::translate("QtWidgetsClassClass", "\347\241\256\345\256\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("QtWidgetsClassClass", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsClassClass: public Ui_QtWidgetsClassClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSCLASS_H
