#ifndef AUIMANAGER
#define AUIMANAGER
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "registr.h"
#include "ui_registr.h"
#include "form.h"
#include "ui_form.h"
#include "kabinet.h"
#include "ui_kabinet.h"
#include "loading.h"
#include "ui_loading.h"

#define VERSION_CLIENT QString("СlusterChat 8.0 ")
class UIModule
{
public:
    MainWindow *Main;
    Ui::MainWindow *MainUI;
    Kabinet *Kabin;
    Ui::Kabinet *KabinUI;
    Form *Message;
    Ui::Form *MessageUI;
    registr *Reg;
    Ui::registr *RegUI;
    Dialog *LoadMenu;
    Ui::Dialog *LoadMenuUI;
    Loading *LoadWindow;
    Ui::Loading *LoadWindowUI;
};
UIModule R;
void Dialog::on_pushButton_3_clicked()
{
    R.Kabin->show();
    R.KabinUI->tabWidget->setCurrentIndex(1);
}
Loading::Loading(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Loading)
{
    ui->setupUi(this);
    R.LoadWindow=this;
    R.LoadWindowUI=ui;
}

Loading::~Loading()
{
    delete ui;
}


Dialog::~Dialog(){delete ui;}
registr::registr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registr)
{
    ui->setupUi(this);
    R.RegUI=ui;
    R.Reg=this;
    this->setWindowTitle(VERSION_CLIENT+"Регистстрация");
}
registr::~registr(){delete ui;}
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    R.MessageUI=ui;
    R.Message=this;
}
Form::~Form(){ delete ui;}
Kabinet::Kabinet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Kabinet)
{
    ui->setupUi(this);
    R.Kabin=this;
    R.KabinUI=ui;
    ui->lineEdit_CreateRoom->hide();
    ui->label_CreateRoom->hide();
    this->setWindowTitle(VERSION_CLIENT+"Кабинет");

}
Kabinet::~Kabinet(){delete ui;}

void Form::on_pushButton_clicked()
{
    R.Message->setHidden(1);
}
void MainWindow::on_action_triggered()
{
    R.Kabin->show();
    R.KabinUI->tabWidget->setCurrentIndex(2);
}
void MainWindow::on_action_2_triggered()
{
    R.Kabin->show();
    R.KabinUI->tabWidget->setCurrentIndex(1);
}
void MainWindow::on_action_7_triggered()
{
    qApp->closeAllWindows();
}
void MainWindow::on_action_3_triggered()
{
    R.Kabin->show();
    R.KabinUI->tabWidget->setCurrentIndex(5);
}
void MainWindow::on_action_11_triggered()
{
    R.Kabin->show();
    R.KabinUI->tabWidget->setCurrentIndex(7);
}
void MainWindow::on_action_9_triggered()
{
    R.Kabin->show();
    R.KabinUI->tabWidget->setCurrentIndex(6);
}
void MainWindow::on_action_13_triggered()
{
    R.Kabin->show();
    R.KabinUI->tabWidget->setCurrentIndex(4);
}
void MainWindow::on_action_8_triggered()
{
    R.Kabin->show();
    R.KabinUI->tabWidget->setCurrentIndex(3);
}
void MainWindow::on_action_5_triggered()
{
    R.Kabin->show();
    R.KabinUI->tabWidget->setCurrentIndex(0);
}
void Dialog::on_pushButton_2_clicked()
{
    R.Reg->show();
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    R.MainUI=ui;
    R.Main=this;
    this->setWindowTitle(VERSION_CLIENT);
}
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    R.LoadMenuUI=ui;
    R.LoadMenu=this;
    this->setWindowTitle(VERSION_CLIENT+"Авторизция");
}

#endif // AUIMANAGER

