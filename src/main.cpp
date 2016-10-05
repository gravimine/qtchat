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
#include "include/auimanager.h"
UIModule *R;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    R=new UIModule();
    QTime* timer=new QTime();
    timer->start();
    MainWindow *WindMain=new MainWindow;
    Dialog *WindDialog=new Dialog;
    WindDialog->show();
    Form *WindMessage=new Form;
    registr *WindRegis=new registr;
    WindMessage->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    Kabinet *WindKabinet=new Kabinet;
    Loading *LoadWindow=new Loading;
    LoadWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    R->Kabin=WindKabinet;
    R->KabinUI=WindKabinet->ui;
    R->LoadMenu=WindDialog;
    R->LoadMenuUI=WindDialog->ui;
    R->LoadWindow=LoadWindow;
    R->LoadWindowUI=LoadWindow->ui;
    R->Main=WindMain;
    R->MainUI=WindMain->ui;
    R->Message=WindMessage;
    R->MessageUI=WindMessage->ui;
    R->Reg=WindRegis;
    R->RegUI=WindRegis->ui;
    int InitUI=timer->elapsed();
    qDebug() << "Инициализация UI: "+QString::number(InitUI)+"мс";
    if(a.arguments().contains("-template")) {qDebug() << "[main] Directory Template";
    WindMain->OnStart(1);
    }
    else WindMain->OnStart(0);
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
