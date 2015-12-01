#include "mainwindow.h"
#include "dialog.h"
#include "form.h"
#include "registr.h"
#include "kabinet.h"
#include "loading.h"
#include <QApplication>
#include <QTime>
#include <QString>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTime* timer=new QTime();
    timer->start();
    MainWindow *WindMain=new MainWindow;
    Dialog *WindDialog=new Dialog;
    WindDialog->show();
    Form *WindMessage=new Form;
    registr *WindRegis=new registr;
    WindMessage->setWindowFlags(Qt::Popup);
    Kabinet *WindKabinet=new Kabinet;
    Loading *LoadWindow=new Loading;
    LoadWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    int InitUI=timer->elapsed();
    qDebug() << "Инициализация UI: "+QString::number(InitUI)+"мс";
    WindMain->OnStart();
    qDebug() << "Старт программы: "+QString::number(timer->elapsed()-InitUI)+"мс";
    WindMain->OnRequest();
    delete timer;
    a.exec();
    delete WindMain;
    delete WindMessage;
    delete WindDialog;
    delete WindRegis;
    delete WindKabinet;
    delete LoadWindow;
    return 0;
}
