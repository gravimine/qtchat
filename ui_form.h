/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(293, 104);
        Form->setStyleSheet(QStringLiteral("background-image: url(:/res/noitce.png);"));
        label = new QLabel(Form);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 291, 21));
        label->setStyleSheet(QStringLiteral(""));
        label_2 = new QLabel(Form);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 20, 293, 84));
        label_2->setStyleSheet(QStringLiteral(""));
        pushButton = new QPushButton(Form);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(275, -1, 18, 17));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "\320\235\320\276\320\262\320\276\320\265  \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265!", 0));
        label->setText(QApplication::translate("Form", "<FONT color=#CA2222 size=4><center><B>\320\235\320\276\320\262\320\276\320\265 \320\241\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265!", 0));
        label_2->setText(QApplication::translate("Form", "TextLabel", 0));
        pushButton->setText(QApplication::translate("Form", "X", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
