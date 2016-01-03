#include <QString>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QVariant>
#include <QDesktopWidget>
#include <QRect>
#include <QPoint>
#include <QTime>
#include <QTextBrowser>
#include <QTextCodec>
#include "achat.h"
using namespace ACore;



QTextBrowser *tmppp;


//#include "mainwindow.moc"

bool isCreareRoom=false;
void Kabinet::on_pushButton_CreateRoom_clicked()
{
	if(!isCreareRoom)
	{
        R->KabinUI->label_CreateRoom->show();
        R->KabinUI->lineEdit_CreateRoom->show();
        R->KabinUI->pushButton_CreateRoom->setText("Применить");
		isCreareRoom=true;
	}
	else
	{
        R->KabinUI->label_CreateRoom->hide();
        R->KabinUI->lineEdit_CreateRoom->hide();
        QString NameRoom=R->KabinUI->lineEdit_CreateRoom->text();
        R->KabinUI->pushButton_CreateRoom->setText("Создать комнату");
		if(ClusterChat.MessageQuest("Вы действительно хотите создать комнату \""+NameRoom+"\"?"))
		CluChat->post("type=addRoom&nameTextRoom="+NameRoom, tCreateRoom);
		isCreareRoom=false;
	}
}
void  Kabinet::on_pushButton_2_clicked()
{
	CluChat->post("type=getUnigue",tGetUngine);

}
void Kabinet::on_pushButton_4_clicked()
{
    AChate MyKomnata=CluChat->currentRoom();
	QString NameRoom=MyKomnata.Name;
	if(MyKomnata.CreatedID!=CluChat->GetMyClient().id)
	{
		ClusterChat.SendM("Вы не владеете комнатой \""+NameRoom+"\".");
	} else
	if(ClusterChat.MessageQuest("Вы действительно хотите удалить комнату \""+NameRoom+"\"?\nВся переписка БУДЕТ УДАЛЕНА!"))
	if(ClusterChat.MessageQuest("Подтвердите свои действия:\n1.Удаление комнаты \""+NameRoom+"\"?Вся переписка БУДЕТ УДАЛЕНА!"))
	{
		CluChat->post("type=deleteRoom&room="+QString::number(MyKomnata.KomID),tRemoveRoom);
	}
}
void Kabinet::on_pushButton_9_clicked()
{
    QString tmp=R->KabinUI->listWidget_4->currentItem()->text();
    if(CluChat->currentUniKey().CookieCode!=tmp)CluChat->DelUniKey(tmp);
    else ClusterChat.Error("Нельзя удалить текущий ключ доступа");
}

MainWindow::~MainWindow()
{
	delete ui;
	delete CluChat;
}
void Kabinet::on_listWidget_clicked(const QModelIndex &index)
{

	AServer tmp=CluChat->FindServer(index.data().toString());
    R->KabinUI->label_nameserver->setText("Имя сервера: "+tmp.name);
    if(tmp.status!="offline")R->KabinUI->label_serverstatus->setText("Статус: <font color=#0F0>online");
    else R->KabinUI->label_serverstatus->setText("Статус: <font color=#F00>offline");
    R->KabinUI->label_serveronline->setText("Онлайн: "+QString::number(tmp.users)+" из "+QString::number(tmp.usersmax));
    R->KabinUI->label_url->setText("URL: "+tmp.url);
    R->KabinUI->label_serverinfo->setText("Описание сервера:\n"+tmp.information);
    R->KabinUI->label_region->setText("Регион: "+tmp.region);
}
void MainWindow::on_pushButton_clicked()
{
    CluChat->SendCommandAraim();
}

void Kabinet::on_listWidget_4_clicked(const QModelIndex &index)
{
	UniClient tmp=CluChat->GetUniClient(index.data().toString());
    R->KabinUI->label_ClientVersion_Uni->setText("Версия: "+tmp.Init+" "+tmp.InitVersion);
    R->KabinUI->label__UniKey_Uni->setText("Уникальный ключ: "+tmp.key);
    R->KabinUI->label_LastData_Uni->setText("Дата последнего входа: "+tmp.lastDate);
    R->KabinUI->label_Data_Uni->setText("Дата первого входа: "+tmp.date);
    R->KabinUI->label_IP_Uni->setText("IP адрес: "+tmp.ip);
}

void Kabinet::on_listWidget_3_clicked(const QModelIndex &index)
{
	AChate tmp=CluChat->FindKomOfIndex(index.data().toString());
	Client Creater=CluChat->GetClient(tmp.CreatedID);
    R->KabinUI->label_NameKom->setText("Имя комнаты: "+tmp.Name);
    R->KabinUI->label_NumKom->setText("Номер комнаты: "+QString::number(tmp.KomID));
    R->KabinUI->label_Creater->setText("Создатель комнаты: "+Creater.name);
    R->KabinUI->listWidget_5->clear();
	for(int i=0;i<tmp.ClientList.size();i++)
	{
		Client s=CluChat->GetClient(tmp.ClientList.value(i));
		if(!s.name.isEmpty() && s.id!=tmp.CreatedID)
        R->KabinUI->listWidget_5->addItem(s.name);
	}
}
void  Kabinet::on_listWidget_2_clicked(const QModelIndex &index)
{
	Client  tmp=CluChat->FindClientOfIndex(index.data().toString());
    R->KabinUI->label_NameUser->setText("Имя пользователя: "+tmp.name);
    R->KabinUI->label_RegionUser->setText("Страна: "+tmp.region);
    if(tmp.Active){R->KabinUI->label_StatusUser->setText("<center><font color=green>Онлайн"); R->KabinUI->label_TimeOnlineUser->setText("");}
    else {R->KabinUI->label_StatusUser->setText("<center><font color=red>Оффлайн"); R->KabinUI->label_TimeOnlineUser->setText("Был(а) в:"+tmp.OnlineTime);}
    R->KabinUI->label_EnterClientUser->setText("Версия клиента: "+tmp.enterclient+" "+tmp.versionClient);
    R->KabinUI->laabel_TextStatus->setText("Статус: "+tmp.status);
    R->KabinUI->label_RegionUser->setText("Страна: "+tmp.region);
    R->KabinUI->label_TomeZomeUser->setText("Часовой пояс: "+tmp.timezone);
}

void Kabinet::on_pushButton_clicked()
{
	Client tmp=CluChat->GetMyClient();
	QString posti="type=setInfo&id="+QString::number(tmp.id);
    if(tmp.name!=R->KabinUI->lineEditMyName->text())
    posti+="&real_name="+R->KabinUI->lineEditMyName->text();
	CluChat->post(posti,tSetInfo);
}
void Dialog::on_checkBox_stateChanged(int arg1)
{
    if(arg1==2) {setings["Login"]=R->LoadMenuUI->lineEdit->text();
        if(setings["NoPassword"]==false) setings["Pass"]=R->LoadMenuUI->lineEdit_2->text();}
    else
      {if(setings["NoPassword"]==true) setings["Login"]=R->LoadMenuUI->lineEdit->text();
              setings["Pass"]="";}
}
void Kabinet::on_checkBox_7_stateChanged(int arg1)
{
	if(arg1==2) {setings["Sencure"]=true;}
	else {setings["Sencure"]=false;}
}

void Kabinet::on_checkBox_5_stateChanged(int arg1)
{
	if(arg1==2) {setings["VirtualHost"]=true;}
	else {setings["VirtualHost"]=false;}
}

void Kabinet::on_checkBox_clicked(bool checked)
{
	if(checked) {setings["Smiles"]=true;}
	else setings["Smiles"]=false;
}
void Kabinet::on_checkBox_2_clicked(bool checked)
{
	if(checked) {setings["Debug"]=true;}
	else setings["Debug"]=false;
}
void MainWindow::OnStart()
{
    CluChat=new AChat();
	CluChat->LoadSettings();
    CluChat->CheckBoxUpdate();
}
void MainWindow::OnRequest()
{
	CluChat->GetServersList();
}
void Dialog::on_comboBox_activated(const QString &arg1)
{
	CluChat->SetServer(arg1);
}
void Dialog::on_pushButton_clicked()
{
    if(!CluChat->url().isEmpty())
    CluChat->login(R->LoadMenuUI->lineEdit->text(),R->LoadMenuUI->lineEdit_2->text());
	else ClusterChat.SendM("Выберите сервер для входа");
}
void registr::on_pushButton_2_clicked()
{
    R->Reg->setHidden(1);
}
void registr::on_pushButton_3_clicked()
{

    CluChat->login(R->RegUI->lineEditLogin->text(),R->RegUI->lineEditPass->text(),R->RegUI->lineEdit->text());
}

void registr::on_pushButton_clicked()
{
    if(!R->RegUI->lineEditLogin->text().isEmpty()) if(!R->RegUI->lineEditPass->text().isEmpty())
    if(!R->RegUI->lineEditName->text().isEmpty()) if(!R->RegUI->lineEditFamelye->text().isEmpty())
    if(!R->RegUI->lineEditEmail->text().isEmpty())
    CluChat->Registration(R->RegUI->lineEditLogin->text(),R->RegUI->lineEditName->text()+" "+R->RegUI->lineEditFamelye->text(),
    R->RegUI->lineEditPass->text(),R->RegUI->lineEditEmail->text());
	else ClusterChat.SendM("Неверно заполнены поля");
	else ClusterChat.SendM("Неверно заполнены поля");
	else ClusterChat.SendM("Неверно заполнены поля");
	else ClusterChat.SendM("Неверно заполнены поля");
	else ClusterChat.SendM("Неверно заполнены поля");
}
void MainWindow::on_commandLinkButton_clicked()
{
    if(!isFullEmpry(R->MainUI->textEdit->toPlainText())) CluChat->SendLS(R->MainUI->textEdit->toPlainText());
    R->MainUI->textEdit->setHtml("");
    R->MainUI->textEdit->setFocus();
}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
	QStringList lst=index.data().toString().split(" ");
	CluChat->SetKomnata(lst.value(lst.size()-1).toInt());
}
void MainWindow::on_action_6_triggered()
{
	CluChat->exit();
}

void MainWindow::on_pushButton_2_clicked()
{
	CluChat->LSUp();
	CluChat->ReloadHistory();
}

void MainWindow::on_pushButton_3_clicked()
{
	CluChat->LSDown();
	CluChat->ReloadHistory();
}
