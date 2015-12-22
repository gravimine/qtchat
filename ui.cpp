#include "auimanager.h"
#include "achat.h"
#include <QDesktopWidget>
#include <QRect>
#include <QPoint>

void SendDialogMessage(QString Text,QString Title)
{
	R->MessageUI->label_2->setText(Text);
	R->MessageUI->label->setText(Title);

	QDesktopWidget desktop;
	QRect rect = desktop.availableGeometry(desktop.primaryScreen()); // прямоугольник с размерами экрана
	QPoint center = rect.center(); //координаты центра экрана
	center.setX(center.x()*2 - (R->Message->width()/2) - 150);  // учитываем половину ширины окна
	center.setY(center.y()*2 - (R->Message->height()/2) - 50);  // .. половину высоты
	R->Message->move(center);
	R->Message->show();
}


void Dialog::on_pushButton_3_clicked()
{
	R->Kabin->show();
	R->KabinUI->tabWidget->setCurrentIndex(1);
}
Loading::Loading(QWidget *parent) :
QWidget(parent),
ui(new Ui::Loading)
{
	ui->setupUi(this);
}

Loading::~Loading()
{
	delete ui;
}

void Kabinet::on_tabWidget_currentChanged(int index)
{
    if(index==6)
    {
        CluChat->RenderSmiles();
    }
}

Dialog::~Dialog(){delete ui;}
registr::registr(QWidget *parent) :
QDialog(parent),
ui(new Ui::registr)
{
	ui->setupUi(this);
	this->setWindowTitle(VERSION_CLIENT+"Регистстрация");
}
registr::~registr(){delete ui;}
Form::Form(QWidget *parent) :
QWidget(parent),
ui(new Ui::Form)
{
	ui->setupUi(this);

}
Form::~Form(){ delete ui;}
Kabinet::Kabinet(QWidget *parent) :
QDialog(parent),
ui(new Ui::Kabinet)
{
	ui->setupUi(this);
	ui->lineEdit_CreateRoom->hide();
	ui->label_CreateRoom->hide();
	this->setWindowTitle(VERSION_CLIENT+"Кабинет");

}
Kabinet::~Kabinet(){delete ui;}

void Form::on_pushButton_clicked()
{
	R->Message->setHidden(1);
}
void MainWindow::on_action_triggered()
{
	R->Kabin->show();
	R->KabinUI->tabWidget->setCurrentIndex(2);
}
void MainWindow::on_action_2_triggered()
{
	R->Kabin->show();
	R->KabinUI->tabWidget->setCurrentIndex(1);
}
void MainWindow::on_action_7_triggered()
{
	qApp->closeAllWindows();
}
void MainWindow::on_action_3_triggered()
{
	R->Kabin->show();
	R->KabinUI->tabWidget->setCurrentIndex(5);
}
void MainWindow::on_action_11_triggered()
{
	R->Kabin->show();
    R->KabinUI->tabWidget->setCurrentIndex(8);
}
void MainWindow::on_action_9_triggered()
{
	R->Kabin->show();
    R->KabinUI->tabWidget->setCurrentIndex(7);
}
void MainWindow::on_action_4_triggered()
{
    R->Kabin->show();
    R->KabinUI->tabWidget->setCurrentIndex(6);
    CluChat->RenderSmiles();
}
void MainWindow::on_action_13_triggered()
{
	R->Kabin->show();
	R->KabinUI->tabWidget->setCurrentIndex(4);
}
void MainWindow::on_action_8_triggered()
{
	R->Kabin->show();
	R->KabinUI->tabWidget->setCurrentIndex(3);
}
void MainWindow::on_action_5_triggered()
{
	R->Kabin->show();
	R->KabinUI->tabWidget->setCurrentIndex(0);
}
void Dialog::on_pushButton_2_clicked()
{
	R->Reg->show();
}
MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->setWindowTitle(VERSION_CLIENT);
}
Dialog::Dialog(QWidget *parent) :
QDialog(parent),
ui(new Ui::Dialog)
{
	ui->setupUi(this);
	this->setWindowTitle(VERSION_CLIENT+"Авторизция");
}
