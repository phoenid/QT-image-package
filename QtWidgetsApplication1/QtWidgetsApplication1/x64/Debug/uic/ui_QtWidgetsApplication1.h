/********************************************************************************
** Form generated from reading UI file 'QtWidgetsApplication1.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSAPPLICATION1_H
#define UI_QTWIDGETSAPPLICATION1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsApplication1Class
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QSplitter *splitter;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;

    void setupUi(QWidget *QtWidgetsApplication1Class)
    {
        if (QtWidgetsApplication1Class->objectName().isEmpty())
            QtWidgetsApplication1Class->setObjectName(QString::fromUtf8("QtWidgetsApplication1Class"));
        QtWidgetsApplication1Class->resize(1725, 1213);
        label = new QLabel(QtWidgetsApplication1Class);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 1441, 1071));
        lineEdit = new QLineEdit(QtWidgetsApplication1Class);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 1130, 391, 20));
        splitter = new QSplitter(QtWidgetsApplication1Class);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(1510, 100, 141, 211));
        splitter->setOrientation(Qt::Vertical);
        pushButton = new QPushButton(splitter);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        splitter->addWidget(pushButton);
        pushButton_2 = new QPushButton(splitter);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        splitter->addWidget(pushButton_2);
        pushButton_3 = new QPushButton(splitter);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        splitter->addWidget(pushButton_3);
        pushButton_4 = new QPushButton(splitter);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        splitter->addWidget(pushButton_4);
        pushButton_5 = new QPushButton(splitter);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        splitter->addWidget(pushButton_5);
        pushButton_6 = new QPushButton(QtWidgetsApplication1Class);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(1510, 320, 141, 38));
        pushButton_7 = new QPushButton(QtWidgetsApplication1Class);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(1510, 370, 141, 38));

        retranslateUi(QtWidgetsApplication1Class);

        QMetaObject::connectSlotsByName(QtWidgetsApplication1Class);
    } // setupUi

    void retranslateUi(QWidget *QtWidgetsApplication1Class)
    {
        QtWidgetsApplication1Class->setWindowTitle(QCoreApplication::translate("QtWidgetsApplication1Class", "QtWidgetsApplication1", nullptr));
        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "\346\211\223\345\274\200\345\233\276\345\203\217", nullptr));
        pushButton_2->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "\345\233\276\345\203\217\346\227\213\350\275\254", nullptr));
        pushButton_3->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "\345\233\276\345\203\217hsv\345\217\230\345\214\226", nullptr));
        pushButton_4->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "\345\233\276\345\203\217\351\224\220\345\214\226", nullptr));
        pushButton_5->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "\345\233\276\345\203\217\345\203\217\347\264\240\351\232\217\346\234\272\346\250\241\347\263\212", nullptr));
        pushButton_6->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "\346\222\255\346\224\276\350\247\206\351\242\221", nullptr));
        pushButton_7->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "\351\232\217\346\234\272\346\250\241\347\263\212", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsApplication1Class: public Ui_QtWidgetsApplication1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSAPPLICATION1_H
