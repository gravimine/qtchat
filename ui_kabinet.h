/********************************************************************************
** Form generated from reading UI file 'kabinet.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KABINET_H
#define UI_KABINET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Kabinet
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_9;
    QLineEdit *lineEdit;
    QPushButton *pushButton_6;
    QCheckBox *checkBox_10;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_7;
    QWidget *tab_2;
    QCheckBox *checkBox_4;
    QLabel *label_10;
    QLabel *label_11;
    QListWidget *listWidget;
    QLabel *label_nameserver;
    QLabel *label_url;
    QLabel *label_region;
    QLabel *label_serverstatus;
    QLabel *label_serveronline;
    QLabel *label_serverinfo;
    QLabel *label_serverpixmap;
    QWidget *tab_3;
    QLabel *label_3;
    QLineEdit *lineEditMyName;
    QLabel *label_5;
    QLabel *label_Prem;
    QLabel *label_6;
    QLabel *labelMyColor;
    QPushButton *pushButton;
    QLabel *label_24;
    QComboBox *comboBox;
    QWidget *tab_8;
    QListWidget *listWidget_4;
    QLabel *label_ClientVersion_Uni;
    QLabel *label_LastData_Uni;
    QLabel *label_IP_Uni;
    QLabel *label_Data_Uni;
    QLabel *label__UniKey_Uni;
    QLabel *label_26;
    QPushButton *pushButton_2;
    QCheckBox *checkBox_6;
    QWidget *tab_4;
    QLabel *label_2;
    QLabel *label_NameKom;
    QLabel *label_NumKom;
    QLabel *label_Creater;
    QPushButton *pushButton_CreateRoom;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *label_17;
    QListWidget *listWidget_3;
    QPushButton *pushButton_5;
    QLabel *label_30;
    QLineEdit *lineEdit_CreateRoom;
    QLabel *label_CreateRoom;
    QListWidget *listWidget_5;
    QWidget *tab_7;
    QListWidget *listWidget_2;
    QLabel *label_4;
    QLabel *label_StatusUser;
    QLabel *label_NameUser;
    QLabel *label_PermissionUser;
    QLabel *label_EnterClientUser;
    QLabel *label_RegionUser;
    QLabel *label_TomeZomeUser;
    QLabel *laabel_TextStatus;
    QLabel *label_TimeOnlineUser;
    QWidget *tab_5;
    QTextBrowser *textBrowser;
    QWidget *tab_6;
    QLabel *label_19;

    void setupUi(QDialog *Kabinet)
    {
        if (Kabinet->objectName().isEmpty())
            Kabinet->setObjectName(QStringLiteral("Kabinet"));
        Kabinet->resize(584, 388);
        tabWidget = new QTabWidget(Kabinet);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 2, 586, 387));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        checkBox = new QCheckBox(tab);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(0, 10, 571, 17));
        checkBox_2 = new QCheckBox(tab);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(0, 32, 571, 17));
        checkBox_3 = new QCheckBox(tab);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setGeometry(QRect(0, 54, 571, 20));
        checkBox_5 = new QCheckBox(tab);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));
        checkBox_5->setGeometry(QRect(0, 80, 571, 17));
        checkBox_7 = new QCheckBox(tab);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));
        checkBox_7->setGeometry(QRect(0, 102, 581, 17));
        checkBox_8 = new QCheckBox(tab);
        checkBox_8->setObjectName(QStringLiteral("checkBox_8"));
        checkBox_8->setGeometry(QRect(0, 127, 581, 17));
        checkBox_9 = new QCheckBox(tab);
        checkBox_9->setObjectName(QStringLiteral("checkBox_9"));
        checkBox_9->setGeometry(QRect(0, 152, 581, 17));
        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(0, 170, 491, 20));
        pushButton_6 = new QPushButton(tab);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(500, 170, 75, 23));
        checkBox_10 = new QCheckBox(tab);
        checkBox_10->setObjectName(QStringLiteral("checkBox_10"));
        checkBox_10->setGeometry(QRect(0, 195, 581, 17));
        lineEdit_2 = new QLineEdit(tab);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(0, 212, 491, 20));
        pushButton_7 = new QPushButton(tab);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(500, 212, 75, 23));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        checkBox_4 = new QCheckBox(tab_2);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));
        checkBox_4->setGeometry(QRect(140, 30, 201, 17));
        label_10 = new QLabel(tab_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(140, 10, 431, 16));
        label_11 = new QLabel(tab_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(140, 50, 431, 16));
        listWidget = new QListWidget(tab_2);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 10, 131, 341));
        label_nameserver = new QLabel(tab_2);
        label_nameserver->setObjectName(QStringLiteral("label_nameserver"));
        label_nameserver->setGeometry(QRect(140, 70, 431, 16));
        label_url = new QLabel(tab_2);
        label_url->setObjectName(QStringLiteral("label_url"));
        label_url->setGeometry(QRect(140, 90, 431, 21));
        label_region = new QLabel(tab_2);
        label_region->setObjectName(QStringLiteral("label_region"));
        label_region->setGeometry(QRect(140, 110, 431, 16));
        label_serverstatus = new QLabel(tab_2);
        label_serverstatus->setObjectName(QStringLiteral("label_serverstatus"));
        label_serverstatus->setGeometry(QRect(140, 130, 431, 18));
        label_serveronline = new QLabel(tab_2);
        label_serveronline->setObjectName(QStringLiteral("label_serveronline"));
        label_serveronline->setGeometry(QRect(140, 150, 431, 20));
        label_serverinfo = new QLabel(tab_2);
        label_serverinfo->setObjectName(QStringLiteral("label_serverinfo"));
        label_serverinfo->setGeometry(QRect(140, 180, 421, 111));
        label_serverpixmap = new QLabel(tab_2);
        label_serverpixmap->setObjectName(QStringLiteral("label_serverpixmap"));
        label_serverpixmap->setGeometry(QRect(440, 70, 101, 101));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(0, 20, 61, 16));
        lineEditMyName = new QLineEdit(tab_3);
        lineEditMyName->setObjectName(QStringLiteral("lineEditMyName"));
        lineEditMyName->setGeometry(QRect(60, 20, 161, 20));
        label_5 = new QLabel(tab_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(0, 70, 61, 16));
        label_Prem = new QLabel(tab_3);
        label_Prem->setObjectName(QStringLiteral("label_Prem"));
        label_Prem->setGeometry(QRect(70, 70, 171, 16));
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(0, 50, 71, 16));
        labelMyColor = new QLabel(tab_3);
        labelMyColor->setObjectName(QStringLiteral("labelMyColor"));
        labelMyColor->setGeometry(QRect(70, 50, 161, 16));
        pushButton = new QPushButton(tab_3);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(470, 330, 111, 31));
        label_24 = new QLabel(tab_3);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(0, 90, 101, 16));
        comboBox = new QComboBox(tab_3);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(110, 87, 161, 22));
        tabWidget->addTab(tab_3, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QStringLiteral("tab_8"));
        listWidget_4 = new QListWidget(tab_8);
        listWidget_4->setObjectName(QStringLiteral("listWidget_4"));
        listWidget_4->setGeometry(QRect(0, 50, 111, 261));
        label_ClientVersion_Uni = new QLabel(tab_8);
        label_ClientVersion_Uni->setObjectName(QStringLiteral("label_ClientVersion_Uni"));
        label_ClientVersion_Uni->setGeometry(QRect(120, 60, 451, 16));
        label_LastData_Uni = new QLabel(tab_8);
        label_LastData_Uni->setObjectName(QStringLiteral("label_LastData_Uni"));
        label_LastData_Uni->setGeometry(QRect(120, 100, 451, 16));
        label_IP_Uni = new QLabel(tab_8);
        label_IP_Uni->setObjectName(QStringLiteral("label_IP_Uni"));
        label_IP_Uni->setGeometry(QRect(120, 80, 451, 16));
        label_Data_Uni = new QLabel(tab_8);
        label_Data_Uni->setObjectName(QStringLiteral("label_Data_Uni"));
        label_Data_Uni->setGeometry(QRect(120, 120, 451, 16));
        label__UniKey_Uni = new QLabel(tab_8);
        label__UniKey_Uni->setObjectName(QStringLiteral("label__UniKey_Uni"));
        label__UniKey_Uni->setGeometry(QRect(120, 140, 451, 18));
        label_26 = new QLabel(tab_8);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(0, 30, 571, 16));
        pushButton_2 = new QPushButton(tab_8);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(460, 330, 111, 31));
        checkBox_6 = new QCheckBox(tab_8);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));
        checkBox_6->setGeometry(QRect(0, 10, 571, 17));
        checkBox_6->setTristate(true);
        tabWidget->addTab(tab_8, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        label_2 = new QLabel(tab_4);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(120, 0, 331, 16));
        label_NameKom = new QLabel(tab_4);
        label_NameKom->setObjectName(QStringLiteral("label_NameKom"));
        label_NameKom->setGeometry(QRect(129, 20, 451, 19));
        label_NumKom = new QLabel(tab_4);
        label_NumKom->setObjectName(QStringLiteral("label_NumKom"));
        label_NumKom->setGeometry(QRect(129, 45, 441, 16));
        label_Creater = new QLabel(tab_4);
        label_Creater->setObjectName(QStringLiteral("label_Creater"));
        label_Creater->setGeometry(QRect(130, 67, 441, 16));
        pushButton_CreateRoom = new QPushButton(tab_4);
        pushButton_CreateRoom->setObjectName(QStringLiteral("pushButton_CreateRoom"));
        pushButton_CreateRoom->setGeometry(QRect(141, 332, 151, 30));
        pushButton_3 = new QPushButton(tab_4);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(292, 332, 113, 30));
        pushButton_4 = new QPushButton(tab_4);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(405, 332, 171, 30));
        label_17 = new QLabel(tab_4);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(130, 100, 451, 16));
        listWidget_3 = new QListWidget(tab_4);
        listWidget_3->setObjectName(QStringLiteral("listWidget_3"));
        listWidget_3->setGeometry(QRect(0, 20, 121, 311));
        pushButton_5 = new QPushButton(tab_4);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(0, 332, 141, 30));
        label_30 = new QLabel(tab_4);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(130, 120, 441, 16));
        lineEdit_CreateRoom = new QLineEdit(tab_4);
        lineEdit_CreateRoom->setObjectName(QStringLiteral("lineEdit_CreateRoom"));
        lineEdit_CreateRoom->setEnabled(true);
        lineEdit_CreateRoom->setGeometry(QRect(330, 290, 161, 20));
        label_CreateRoom = new QLabel(tab_4);
        label_CreateRoom->setObjectName(QStringLiteral("label_CreateRoom"));
        label_CreateRoom->setGeometry(QRect(330, 263, 161, 20));
        listWidget_5 = new QListWidget(tab_4);
        listWidget_5->setObjectName(QStringLiteral("listWidget_5"));
        listWidget_5->setGeometry(QRect(130, 140, 151, 161));
        tabWidget->addTab(tab_4, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        listWidget_2 = new QListWidget(tab_7);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setGeometry(QRect(0, 10, 131, 351));
        label_4 = new QLabel(tab_7);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(140, 0, 441, 16));
        label_StatusUser = new QLabel(tab_7);
        label_StatusUser->setObjectName(QStringLiteral("label_StatusUser"));
        label_StatusUser->setGeometry(QRect(140, 12, 441, 16));
        label_NameUser = new QLabel(tab_7);
        label_NameUser->setObjectName(QStringLiteral("label_NameUser"));
        label_NameUser->setGeometry(QRect(140, 40, 431, 16));
        label_PermissionUser = new QLabel(tab_7);
        label_PermissionUser->setObjectName(QStringLiteral("label_PermissionUser"));
        label_PermissionUser->setGeometry(QRect(140, 160, 431, 16));
        label_EnterClientUser = new QLabel(tab_7);
        label_EnterClientUser->setObjectName(QStringLiteral("label_EnterClientUser"));
        label_EnterClientUser->setGeometry(QRect(140, 80, 431, 16));
        label_RegionUser = new QLabel(tab_7);
        label_RegionUser->setObjectName(QStringLiteral("label_RegionUser"));
        label_RegionUser->setGeometry(QRect(140, 100, 431, 16));
        label_TomeZomeUser = new QLabel(tab_7);
        label_TomeZomeUser->setObjectName(QStringLiteral("label_TomeZomeUser"));
        label_TomeZomeUser->setGeometry(QRect(140, 120, 431, 16));
        laabel_TextStatus = new QLabel(tab_7);
        laabel_TextStatus->setObjectName(QStringLiteral("laabel_TextStatus"));
        laabel_TextStatus->setGeometry(QRect(140, 60, 431, 16));
        label_TimeOnlineUser = new QLabel(tab_7);
        label_TimeOnlineUser->setObjectName(QStringLiteral("label_TimeOnlineUser"));
        label_TimeOnlineUser->setGeometry(QRect(140, 140, 431, 16));
        tabWidget->addTab(tab_7, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        textBrowser = new QTextBrowser(tab_5);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(0, 0, 581, 361));
        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        label_19 = new QLabel(tab_6);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(0, 0, 581, 361));
        tabWidget->addTab(tab_6, QString());

        retranslateUi(Kabinet);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Kabinet);
    } // setupUi

    void retranslateUi(QDialog *Kabinet)
    {
        Kabinet->setWindowTitle(QApplication::translate("Kabinet", "Dialog", 0));
        checkBox->setText(QApplication::translate("Kabinet", "\320\230\321\201\320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\321\214 \321\201\320\274\320\260\320\271\320\273\321\213", 0));
        checkBox_2->setText(QApplication::translate("Kabinet", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \320\276\321\202\320\273\320\260\320\264\320\276\321\207\320\275\321\213\320\265 \320\267\320\260\320\277\320\270\321\201\320\270", 0));
        checkBox_3->setText(QApplication::translate("Kabinet", "\320\236\321\202\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265 \320\276\321\210\320\270\320\261\320\276\320\272", 0));
        checkBox_5->setText(QApplication::translate("Kabinet", "\320\230\321\201\320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\321\214 \320\262\320\270\321\200\321\202\321\203\320\260\320\273\321\214\320\275\321\213\320\271 \321\201\320\265\321\200\320\262\320\265\321\200 \320\264\320\273\321\217 \320\262\321\205\320\276\320\264\320\260", 0));
        checkBox_7->setText(QApplication::translate("Kabinet", "\320\244\320\270\320\273\321\214\321\202\321\200\320\276\320\262\320\260\321\202\321\214 \320\275\320\265\321\206\320\265\320\275\320\267\321\203\321\200\320\275\321\213\320\265 \321\201\320\273\320\276\320\262\320\260", 0));
        checkBox_8->setText(QApplication::translate("Kabinet", "\320\220\320\262\321\202\320\276\320\274\320\260\321\202\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \320\262\321\205\320\276\320\264", 0));
        checkBox_9->setText(QApplication::translate("Kabinet", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214\321\201\320\272\320\270\320\271 \321\201\321\202\320\270\320\273\321\214 \320\276\321\202\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\271 (HTML)", 0));
        pushButton_6->setText(QApplication::translate("Kabinet", "\320\236\320\232", 0));
        checkBox_10->setText(QApplication::translate("Kabinet", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214\321\201\320\272\320\276\320\265 \320\224\320\220\320\242\320\220/\320\222\320\240\320\225\320\234\320\257", 0));
        pushButton_7->setText(QApplication::translate("Kabinet", "\320\236\320\232", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Kabinet", "\320\236\320\261\321\211\320\270\320\265 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0));
        checkBox_4->setText(QApplication::translate("Kabinet", "\320\236\321\202\320\276\320\261\321\200\320\260\320\266\320\260\321\202\321\214 \320\262 \321\201\320\277\320\270\321\201\320\272\320\265", 0));
        label_10->setText(QApplication::translate("Kabinet", "<b><center>\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0));
        label_11->setText(QApplication::translate("Kabinet", "<b><center>\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", 0));
        label_nameserver->setText(QString());
        label_url->setText(QString());
        label_region->setText(QString());
        label_serverstatus->setText(QString());
        label_serveronline->setText(QString());
        label_serverinfo->setText(QString());
        label_serverpixmap->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Kabinet", "\320\241\320\265\321\200\320\262\320\265\321\200\320\260", 0));
        label_3->setText(QApplication::translate("Kabinet", "<b>\320\230\320\274\321\217", 0));
        label_5->setText(QApplication::translate("Kabinet", "<b>\320\237\321\200\320\260\320\262\320\260", 0));
        label_Prem->setText(QApplication::translate("Kabinet", "<font color=green>\320\237\320\276\320\273\321\214\320\276\320\262\320\260\321\202\320\265\320\273\321\214", 0));
        label_6->setText(QApplication::translate("Kabinet", "<b>\320\246\320\262\320\265\321\202", 0));
        labelMyColor->setText(QApplication::translate("Kabinet", "<font color=#00F>#00F", 0));
        pushButton->setText(QApplication::translate("Kabinet", "C\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0));
        label_24->setText(QApplication::translate("Kabinet", "<b>\320\247\320\260\321\201\320\276\320\262\320\276\320\271 \320\277\320\276\321\217\321\201:", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Kabinet", "\320\234\320\276\320\271 \320\260\320\272\320\272\320\260\321\203\320\275\321\202", 0));
        label_ClientVersion_Uni->setText(QString());
        label_LastData_Uni->setText(QString());
        label_IP_Uni->setText(QString());
        label_Data_Uni->setText(QString());
        label__UniKey_Uni->setText(QString());
        label_26->setText(QApplication::translate("Kabinet", "<b><center>\320\241\320\277\320\270\321\201\320\276\320\272 \320\260\320\262\321\202\320\276\321\200\320\270\320\267\320\270\321\200\320\276\320\262\320\260\320\275\320\275\321\213\321\205 \320\272\320\276\320\274\320\277\321\214\321\216\321\202\320\265\321\200\320\276\320\262", 0));
        pushButton_2->setText(QApplication::translate("Kabinet", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \321\201\320\277\320\270\321\201\320\272\320\270", 0));
        checkBox_6->setText(QApplication::translate("Kabinet", "\320\222\321\213\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \320\277\320\276\320\262\321\202\320\276\321\200\320\275\321\203\321\216 \320\260\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\216(\320\221\320\265\320\267\320\276\320\277\320\260\321\201\321\202\320\275\320\276)", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_8), QApplication::translate("Kabinet", "\320\221\320\265\320\267\320\276\320\277\320\260\321\201\321\202\320\275\320\276\321\201\321\202\321\214", 0));
        label_2->setText(QApplication::translate("Kabinet", "<b><center>\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", 0));
        label_NameKom->setText(QString());
        label_NumKom->setText(QString());
        label_Creater->setText(QString());
        pushButton_CreateRoom->setText(QApplication::translate("Kabinet", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\272\320\276\320\274\320\275\320\260\321\202\321\203", 0));
        pushButton_3->setText(QApplication::translate("Kabinet", "\320\237\321\200\320\270\320\263\320\273\320\260\321\201\320\270\321\202\321\214", 0));
        pushButton_4->setText(QApplication::translate("Kabinet", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\272\320\276\320\274\320\275\320\260\321\202\321\203", 0));
        label_17->setText(QApplication::translate("Kabinet", "\320\241\320\262\320\276\320\261\320\276\320\264\320\275\320\260\321\217 \320\272\320\276\320\274\320\275\320\260\321\202\320\260: <font color=red>\320\235\320\265\321\202", 0));
        pushButton_5->setText(QApplication::translate("Kabinet", "\320\237\320\265\321\200\320\265\320\271\321\202\320\270", 0));
        label_30->setText(QApplication::translate("Kabinet", "\320\243\321\207\320\260\321\201\321\202\320\275\320\270\320\272\320\270:", 0));
        label_CreateRoom->setText(QApplication::translate("Kabinet", "<center>\320\230\320\274\321\217 \320\272\320\276\320\274\320\275\320\260\321\202\321\213", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("Kabinet", "\320\234\320\276\320\270 \321\207\320\260\321\202\321\213", 0));
        label_4->setText(QApplication::translate("Kabinet", "<b><center>\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", 0));
        label_StatusUser->setText(QString());
        label_NameUser->setText(QString());
        label_PermissionUser->setText(QString());
        label_EnterClientUser->setText(QString());
        label_RegionUser->setText(QString());
        label_TomeZomeUser->setText(QString());
        laabel_TextStatus->setText(QString());
        label_TimeOnlineUser->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("Kabinet", "\320\243\321\207\320\260\321\201\321\202\320\275\320\270\320\272\320\270", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("Kabinet", "\320\233\320\276\320\263\320\270", 0));
        label_19->setText(QApplication::translate("Kabinet", "<center>\320\222\320\265\321\200\321\201\320\270\321\217: 8.1<br>\320\222\320\265\321\200\321\201\320\270\321\217 ACore: 2.3<br><br><br><hr><font color=red size=5>\320\234\321\203\320\273\321\214\321\202\320\270\320\277\320\273\320\260\321\202\321\204\320\276\321\200\320\274\320\265\320\275\320\275\321\213\320\271 \320\272\320\273\320\270\320\265\320\275\321\202 Cluster-Chat</font><br>\320\240\320\260\320\267\321\200\320\260\320\261\320\276\321\202\321\207\320\270\320\272 \320\272\320\273\320\270\320\265\320\275\321\202\320\260 Gravit<br>\320\241\320\265\321\200\320\262\320\265\321\200\320\260 \320\277\321\200\320\265\320\264\320\276\321\201\321\202\320\260\320\262\320\273\320\265\320\275\321\213 Ulin</font><hr>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("Kabinet", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", 0));
    } // retranslateUi

};

namespace Ui {
    class Kabinet: public Ui_Kabinet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KABINET_H
