/********************************************************************************
** Form generated from reading UI file 'loading.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADING_H
#define UI_LOADING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Loading
{
public:
    QLabel *label;
    QLabel *label_2;
    QFrame *frame;

    void setupUi(QWidget *Loading)
    {
        if (Loading->objectName().isEmpty())
            Loading->setObjectName(QStringLiteral("Loading"));
        Loading->resize(283, 53);
        label = new QLabel(Loading);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 41, 51));
        label_2 = new QLabel(Loading);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(69, 14, 221, 20));
        frame = new QFrame(Loading);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 0, 282, 52));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        frame->raise();
        label_2->raise();
        label->raise();

        retranslateUi(Loading);

        QMetaObject::connectSlotsByName(Loading);
    } // setupUi

    void retranslateUi(QWidget *Loading)
    {
        Loading->setWindowTitle(QApplication::translate("Loading", "Form", 0));
        label->setText(QApplication::translate("Loading", "<center><img height=40 src=:/res/Loader.png>", 0));
        label_2->setText(QApplication::translate("Loading", "\320\237\320\276\320\264\320\276\320\266\320\264\320\270\321\202\320\265,\320\270\320\264\320\265\321\202 \320\267\320\260\320\263\321\200\321\203\320\267\320\272\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class Loading: public Ui_Loading {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADING_H
