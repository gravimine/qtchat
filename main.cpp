#include "mainwindow.h"
#include "dialog.h"
#include "form.h"
#include "registr.h"
#include "kabinet.h"
#include "loading.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *WindMain=new MainWindow;
    Dialog *WindDialog=new Dialog;
    WindDialog->show();
    Form *WindMessage=new Form;
    registr *WindRegis=new registr;
    WindMessage->setWindowFlags(Qt::Popup);
    Kabinet *WindKabinet=new Kabinet;
    Loading *LoadWindow=new Loading;
    LoadWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    WindMain->OnStart();
    a.exec();
    delete WindMain;
    delete WindMessage;
    delete WindDialog;
    delete WindRegis;
    delete WindKabinet;
    delete LoadWindow;
    return 0;
}
