/********************************************************************************
** Form generated from reading UI file 'registr.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTR_H
#define UI_REGISTR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_registr
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEditLogin;
    QLineEdit *lineEditPass;
    QLineEdit *lineEditName;
    QLineEdit *lineEditFamelye;
    QLineEdit *lineEditEmail;
    QLabel *label_6;
    QLineEdit *lineEdit;
    QPushButton *pushButton_3;

    void setupUi(QDialog *registr)
    {
        if (registr->objectName().isEmpty())
            registr->setObjectName(QStringLiteral("registr"));
        registr->resize(400, 300);
        pushButton = new QPushButton(registr);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(0, 260, 121, 27));
        pushButton_2 = new QPushButton(registr);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(300, 260, 85, 27));
        label = new QLabel(registr);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 60, 71, 16));
        label_2 = new QLabel(registr);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 80, 71, 16));
        label_3 = new QLabel(registr);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 100, 71, 16));
        label_4 = new QLabel(registr);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 120, 81, 16));
        label_5 = new QLabel(registr);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 140, 71, 16));
        lineEditLogin = new QLineEdit(registr);
        lineEditLogin->setObjectName(QStringLiteral("lineEditLogin"));
        lineEditLogin->setGeometry(QRect(90, 60, 271, 20));
        lineEditPass = new QLineEdit(registr);
        lineEditPass->setObjectName(QStringLiteral("lineEditPass"));
        lineEditPass->setGeometry(QRect(90, 80, 271, 20));
        lineEditName = new QLineEdit(registr);
        lineEditName->setObjectName(QStringLiteral("lineEditName"));
        lineEditName->setGeometry(QRect(90, 100, 271, 20));
        lineEditFamelye = new QLineEdit(registr);
        lineEditFamelye->setObjectName(QStringLiteral("lineEditFamelye"));
        lineEditFamelye->setGeometry(QRect(90, 120, 271, 20));
        lineEditEmail = new QLineEdit(registr);
        lineEditEmail->setObjectName(QStringLiteral("lineEditEmail"));
        lineEditEmail->setGeometry(QRect(90, 140, 271, 20));
        label_6 = new QLabel(registr);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(60, 180, 241, 21));
        lineEdit = new QLineEdit(registr);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(58, 195, 243, 26));
        pushButton_3 = new QPushButton(registr);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(120, 260, 181, 27));

        retranslateUi(registr);

        QMetaObject::connectSlotsByName(registr);
    } // setupUi

    void retranslateUi(QDialog *registr)
    {
        registr->setWindowTitle(QApplication::translate("registr", "UChat 3.1 \320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", 0));
        pushButton->setText(QApplication::translate("registr", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", 0));
        pushButton_2->setText(QApplication::translate("registr", "\320\235\320\260\320\267\320\260\320\264", 0));
        label->setText(QApplication::translate("registr", "<B>\320\222\320\260\321\210 \320\233\320\276\320\263\320\270\320\275", 0));
        label_2->setText(QApplication::translate("registr", "<B>\320\222\320\260\321\210 \320\237\320\260\321\200\320\276\320\273\321\214", 0));
        label_3->setText(QApplication::translate("registr", "<B>\320\222\320\260\321\210\320\265 \320\230\320\274\321\217", 0));
        label_4->setText(QApplication::translate("registr", "<B>\320\222\320\260\321\210\320\260 \321\204\320\260\320\274\320\270\320\273\320\270\321\217", 0));
        label_5->setText(QApplication::translate("registr", "<B>\320\222\320\260\321\210 E-Mail", 0));
        label_6->setText(QApplication::translate("registr", "<b>\320\232\320\273\321\216\321\207 \320\277\320\276\320\264\320\262\320\265\321\200\320\266\320\264\320\265\320\275\320\270\321\217(\320\277\320\276\321\201\320\273\320\265 \321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\320\270)", 0));
        pushButton_3->setText(QApplication::translate("registr", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214 E-Mail", 0));
    } // retranslateUi

};

namespace Ui {
    class registr: public Ui_registr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTR_H
