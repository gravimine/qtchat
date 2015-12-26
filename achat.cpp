#include "achat.h"
#include "ACore/aclientserver.h"
#include "ACore/abbcodec.h"
using namespace ACore;
AChate MyKomnata;
AChat *CluChat;
ACore::ASettings setings;
bool isStart;
ACore::AAppCore ClusterChat("ClusterChat");
bool AChat::isSendCommand(QString message)
{
	if(message.toLatin1()[0]=='/') return true;
	else return false;
}
QString AChat::GetTextGroup(QString Groups)
{
	QString ReturnText="<font color=#0F0>Пользователь";
	QStringList GroupsList=Groups.split(", ");
	for(int i=0;i<GroupsList.size();i++)
	{
		if("ban") ReturnText="<font color=red>Администратор";
	}
	return ReturnText;
}
void AChat::AddLS(int ClientID,QString msg)
{
	PrivateMessage temp;
	temp.ClientID=ClientID;
	temp.isRealLS=false;
	temp.id=0;
	temp.msg=msg;
	MessageList << temp;
}
void AChat::RenderSmiles()
{
    QString str;
    for(int i=0;i<SmilesList.size();i++) str+="<IMG src=\""+SmilesList.value(i).url+"\">  "+SmilesList.value(i).code+"<br><br>";
    R->KabinUI->label->setText(str);
}

void AChat::WriteServerList(ACore::RecursionArray reply)
{
	int Servers=0,AllServers=0;
	ServersList.clear();
	QList<QString> keys=reply.keys();
	for(int i=0;i<keys.size();i++)
	{
		AServer tmp;
		ACore::RecursionArray tmp2=reply.value(keys.value(i)).toMap();
		tmp.name=tmp2.value("name").toString();
		tmp.ping=tmp2.value("ping").toString().toFloat();
		tmp.url=tmp2.value("url").toString().replace("<space>"," ");
		if(tmp.name.isEmpty()) tmp.name=tmp.url;
		tmp.region=tmp2.value("region").toString();
		tmp.status="offline";
		tmp.information=tmp2.value("info").toString();
		tmp.users=tmp2.value("users").toString().toInt();
		tmp.usersmax=tmp2.value("offusers").toString().toInt();

		R->KabinUI->listWidget->addItem(tmp.name);
		if(tmp2.value("key").toString()=="403")
		{
			R->LoadMenuUI->comboBox->addItem(tmp.name);
			tmp.status="online";
		}
		else  Servers++;
		AllServers++; ServersList<<tmp;
	}
	log<<QString::number(Servers)+" ot "+QString::number(AllServers)+" Servers";
}
void AChat::LSUp()
{
	HistoryNumberLS-=20;
}
void AChat::LSDown()
{
	if(HistoryNumberLS>0) HistoryNumberLS+=20;
}
void AChat::ReloadHistory()
{
	isReloadHostory=true;
	if(MyClient.com_id!=0) post("type=msglist&otMessages=25&room="+QString::number(GetKomnata())+"&maxMessages="+QString::number(HistoryNumberLS),tMessage);
}
void AChat::ReloadAllSMS()
{
	isReloadHostory=true;
	numLS=0;
	QString postiString;
	for(int i=0;i<ChatsList.size();i++)
	{
		int RoomID=ChatsList.value(i).KomID;
		if(RoomID!=MyClient.com_id) postiString+="/"+QString::number(RoomID);
	}
	post("type=onlineUsersRoom&room="+QString::number(MyClient.com_id)+postiString,tOnlineList);
}
QString AChat::OnlinetoHTML(ACore::RecursionArray Map)
{
	QString HTML;
	QList<QString> keys=Map.keys();
	QString allLS;
	for(int i=0;i<keys.size();i++)
	{
		QString Coloring;
		Client tmp;
		ACore::RecursionArray nMap=Map.value(QString::number(i)).toMap();
		tmp.id=nMap.value("userId").toString().toInt();
		tmp=ClientList.value(ClientList.indexOf(tmp));
		if(nMap.value("userOnlineStatus").toString()=="403") {Coloring="#0F0";}
		else {Coloring="#F00";}
		if(!tmp.name.isEmpty())allLS+=QString("<font size=2 color=%1>%2 <font color=#000>| ").arg(Coloring).arg(tmp.name);
	}
	HTML=Styled.Main.arg(allLS);
	return HTML;
}
void AChat::SetServer(QString name)
{
	log<<"New server: "+name;
	for(int i=0;i<ServersList.size();i++)
	{

		if(ServersList.value(i).name==name && ServersList.value(i).status !="offline") {
			{
				Server=QNetworkRequest(QUrl(ServersList.value(i).url));
				InitServerUrl=ServersList.value(i).url;
				ServerType=true;
			}
			setings["Server"]=ServersList.value(i).url;
			ADD_DEBUG "Server url: "+ServersList.value(i).url;
		}
	}
}
AServer AChat::FindServer(QString name)
{
	AServer returnServer;
	for(int i=0;i<ServersList.size();i++)
	{
		if(ServersList.value(i).name==name || ServersList.value(i).url==name) {
			returnServer=ServersList.value(i);
		}
	}
	return returnServer;
}
bool AChat::SendCommand(QString message)
{
	//QStringList ArgList=message.split(" ");
	QStringList ArgList=ACore::splitStringArgs(message);
	QString cmd=ArgList.value(0);
	if(cmd=="/ban")
	{
		if(ArgList.value(1).isEmpty()||ArgList.value(2).isEmpty()) SendMessage("Неверные аргументы");
		else
		{
			post("type=ban&id="+ArgList.value(1)+"&hour="+ArgList.value(2),tUnkown);
		}
		return true;
	}
	else if(cmd=="/post")
	{
		if(ArgList.value(1).isEmpty()) SendMessage("Невозможно отправить пустой запрос");
		else post(ArgList.value(1),tUnkown);
		return true;
	}
	else if(cmd=="/flood")
	{
		if(ArgList.value(1).isEmpty()||ArgList.value(2).isEmpty()) SendMessage("Неверные аргументы");
		for(int i=0;i<=ArgList.value(1).toInt();i++) {SendLS(ArgList.value(2));}
		return true;
	}
	else if(cmd=="/sin")
	{
		if(ArgList.value(1).toDouble()<0 || ArgList.value(1).toDouble() > 180) SendMessage("Неверные аргументы");
		ClusterChat.SendM(QString::number(qSin(ArgList.value(1).toDouble()*M_PI/180)));
		return true;
	}
	else if(cmd=="/valid")
	{
		if(ArgList.value(1).isEmpty()) SendMessage("Неверные аргументы");
		ClusterChat.SendM(SencureString(ArgList.value(1)));
		return true;
	}
	else if(cmd=="/sendls")
	{
		if(ArgList.value(1).isEmpty()) SendMessage("Невозможно отправить пустое сообщение");
		AddLS(MyClient.id,ArgList.value(1));
		R->MainUI->textBrowser->setText(ListToHTML());
		return true;
	}
	else return false;
}
void AChat::SetKomnata(int id)
{
	if(id!=KomnataID){

		KomnataID=id;
		MyClient.com_id=id;
		ReloadAllSMS();
		ADD_DEBUG "Комната выбрана: "+QString::number(id);

		MessageList.clear();
	}
}
void AChat::SMStoValues(ACore::RecursionArray Map,bool isClear)
{
	if(Map.isEmpty()) return;
	QList<QString> keys=Map.keys();
	if(isClear) MessageList.clear();
	for(int i=0;i<keys.size();i++)
	{
		PrivateMessage Temp;
		ACore::RecursionArray ValueMap=Map.value(QString::number(i)).toMap();
		Temp.ClientID=ValueMap.value("idUser").toString().toInt();
		Temp.id=ValueMap.value("id").toString().toInt();
		Temp.isRealLS=true;
		Temp.msg=ACore::SpecialSybmolCoder(ValueMap.value("textMessage").toString(),true);
		QStringList TimeData=ValueMap.value("dateMessage").toString().split(" ");
		Temp.data=TimeData.value(0);
		Temp.time=TimeData.value(1);
		if(!Temp.msg.isEmpty())MessageList << Temp;
	}

}
void AChat::SendMessage(QString text)
{
	bool tim1;
	tim1=timer->isActive();
	if(tim1) timer->stop();
	ClusterChat.SendM(text);
	if(tim1) timer->start(7000);
}
void AChat::SendErrorMessage(QString text)
{
	bool tim1;
	tim1=timer->isActive();
	if(tim1) timer->stop();
	ClusterChat.Error("Произошла ошибка при выполнении программы\nИнформация об ошибке:\n"+text+"\nЕсли ошибка повторится, обратитесь к разработчику или администратору сервера.");
	if(tim1) timer->start(7000);
}
QString AChat::GetErrorText(int ErrorID)
{
	QString ErrorText;
	if(ErrorID==517) ErrorText="Недостаточно привилегий";
	else if(ErrorID==399) ErrorText="Ошибка неверные аргументы";
	else if(ErrorID==404) ErrorText="Нет соединения с базой данных";
	else if(ErrorID==419) ErrorText="Ошибка запрошеный скрипт не найден";
	else if(ErrorID==408) ErrorText="Не верный пароль.";
	else if(ErrorID==410) ErrorText="Ошибка вы не авторизированы";
	else if(ErrorID==439) ErrorText="Ваш клиент не поддерживается";
	else if(ErrorID==426) ErrorText="Вы исчерпали ллимит комнат";
	else if(ErrorID==525) ErrorText="Регистрация на этом сервере запрещена";
	return ErrorText;
}
UniKey AChat::FindUniKey(QString id)
{
	UniKey result;
	for(int i=0;i<UniKeyList.size();i++)
	{
		if(UniKeyList.value(i).StringID==id)
		{
			result=UniKeyList.value(i);
			break;
		}
	}
	return result;
}
void AChat::login(QString loginit,QString passit,QString key)
{
	QString posti;

	if(Server.url().toString().isEmpty()) SendMessage("Сервер не выбран");
	if(key.isEmpty()){
		UniKey s;
        s.StringID=InitServerUrl+"."+loginit;
        MyUniKey=UniKeyList.value(UniKeyList.indexOf(s));
        MyUniKey.StringID=InitServerUrl+"."+loginit;
        if(UniKeyList.contains(s)  && setings["NoPassword"]==true)
        //posti="type=auth&login="+loginit+"&pass="+passit+"&init="+INIT_CLIENT+"&clientUnigue="+UniKeyList.value(UniKeyList.indexOf(s)).key+"&initV="+INIT_VERSION;
        {
            setCookie("userUnigue",MyUniKey.CookieCode);
            MyClient.Active=true;
            post("type=info&id=?",tGetMy);
            R->LoadWindowUI->label_2->setText(tr("Вход на сервер. Подождите..."));
            R->LoadWindow->show();
            log<< "login on [NoPasswordMode]";
        }
        else{
            if(loginit.isEmpty() || passit.isEmpty()) {SendMessage("Ошибка, поля Логин | Пароль не заполнены");
            return;}
            log<< "login...";
            posti="type=auth&login="+loginit+"&pass="+passit+"&init="+INIT_CLIENT+"&clientUnigue=?&initV="+INIT_VERSION;
        }
	}
	else {
        if(loginit.isEmpty() || passit.isEmpty()) {SendMessage("Ошибка, поля Логин | Пароль не заполнены");
        return;}
        log<< "login...";
		posti="type=auth&key="+key+"&login="+loginit+"&clientUnigue=?&pass="+passit+"&initialization="+INIT_CLIENT;
	}
    if(!posti.isEmpty())post(posti,tAuth);
    if(timer->isActive()) timer->stop();
}
void AChat::GetFileErrors()
{
	get("http://server-ClusterChat.esy.es/fileinfo.php",tGetError);
	log<<"Get Errors.txt";
}
void AChat::LoadSettings()
{
	setings["Debug"]=IS_DEBUG;
	setings["TimeFormat"]="[%1:%2:%3]";
	setings["Smiles"]=true;
    setings["SettingsVersion"]=1.0;
    setings["NoPassword"]=true;
	setings["Sencure"]=true;
	setings.LoadSettings();
	R->LoadMenuUI->lineEdit->setText(setings["Login"].toString());
	R->LoadMenuUI->lineEdit_2->setText(setings["Pass"].toString());
	if(setings["Smiles"].toBool()){R->KabinUI->checkBox->setChecked(1);
		isSmiles=true;}
	else
	{isSmiles=false;}
	if(setings["Sencure"].toBool()){R->KabinUI->checkBox_7->setChecked(1);
		isCensure=true;}
	else
	{isCensure=false;}
    if(setings["NoPassword"].toBool()){R->KabinUI->checkBox_6->setChecked(1);
        isNoPassMode=true;}
    else
    {isNoPassMode=false;}
	if(setings["Debug"].toBool()){R->KabinUI->checkBox_2->setChecked(1);
		isDebug=true;}
	else
	{isDebug=false;}
	RecursionArray KeysArray=setings["KeysList"].toMap();
	for(int i=0;i<KeysArray.size();i++)
	{
		RecursionArray KeyArray=KeysArray.value(QString::number(i)).toMap();
		UniKey s;
		s.StringID=KeyArray.value("Client").toString();
		s.key=KeyArray.value("Key").toString();
		s.CookieCode=KeyArray.value("Cookie").toString();
		UniKeyList << s;
	}

	Server=QNetworkRequest(QUrl(setings["Server"].toString()));
	InitServerUrl=setings["Server"].toString();
}
void AChat::CheckBoxUpdate()
{
	if(setings["Smiles"].toBool()) R->KabinUI->checkBox->setChecked(1);
	else R->KabinUI->checkBox->setChecked(0);
	if(setings["Debug"].toBool()) R->KabinUI->checkBox->setChecked(1);
	else R->KabinUI->checkBox->setChecked(0);
	if(!R->LoadMenuUI->lineEdit_2->text().isEmpty()) R->LoadMenuUI->checkBox->setChecked(1);
	else R->LoadMenuUI->checkBox->setChecked(0);
}
bool AChat::LoadStyle(QString path)
{
	log<<"Loading style "+path;
	QFile style;
	style.setFileName(path);
	QString data=QString(style.readAll());
	if(data.isEmpty()) data="<table width=100%>%1</table>\n<tr><td>%1<font size=3 color=#%2>%3<font color=#000>:%4<td align=right>%5</tr>\n%1";
	QStringList restyle=data.split("\n");
	Styled.Main=restyle.value(0);
	Styled.Message=restyle.value(1);
	Styled.TextMessage=restyle.value(2);
	log<< "Style loaded";
	return true;
}
AChate AChat::FindKomOfIndex(QString id)
{
	AChate returnChat;
	for(int i=0;i<ChatsList.size();i++)
	{
		if(ChatsList.value(i).Name==id)
		{
			returnChat=ChatsList.value(i);
			break;
		}
	}
	return returnChat;
}
AChate AChat::GetRoom(int id)
{
	return ChatsList.value(id);
}

Client AChat::FindClientOfIndex(QString id)
{
	Client returnClient;
	for(int i=0;i<ClientList.size();i++)
	{
		if(ClientList.value(i).name==id)
		{
			returnClient=ClientList.value(i);
			break;
		}
	}
	return returnClient;
}
Client AChat::GetClient(int id)
{
	Client returnClient;
	for(int i=0;i<ClientList.size();i++)
	{
		if(ClientList.value(i).id==id)
		{
			returnClient= ClientList.value(i);
			return returnClient;
			break;
		}
	}
	return returnClient;
}
AChat::AChat()
{
	SetPath=QDir().homePath();
	if(!QDir(SetPath+"/.ClusterChat").exists()) { QDir(SetPath).mkdir(".ClusterChat"); log<<"Create dir .ClusterChat";}
	log.SetFile(SetPath+"/.ClusterChat/ClusterChat.log");
	log<< "Start";
	ADD_DEBUG "Выбран путь для сохранения файлов: "+SetPath;
	isStart=false;
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	TimeStart=QTime::currentTime();
	#ifdef Q_OS_WIN32
	setings.setPatch(SetPath+"/.ClusterChat/settings.cfg",CfgFormat);
	#endif
	#ifdef Q_OS_LINUX
    setings.setPatch(SetPath+"/.config/ClusterChat.cfg",CfgFormat);
	#endif
	MyClient.com_id=0;
	ServerType=true;
	ADD_DEBUG QString::number(R->KabinUI->pushButton->geometry().height() );
	connect(this, SIGNAL(ARequest(ANetworkReply)),this, SLOT(getReplyFinished(ANetworkReply)));
	//Server=QNetworkRequest(QUrl("https://php-gravit.rhcloud.com/index.php"));
	timersendls=new QTimer(this);
	timer=new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateCaption()));
	connect(timersendls, SIGNAL(timeout()), this, SLOT(updateCaption2()));
    numLS=0;
    SmilesList << Smile(":)",":/res/smail.png") << Smile(":(",":/res/sadness.png")
               << Smile(":пфф:",":/res/rukalico.png") << Smile(":{}",":/res/zloi.png");
	isReloadHostory=false;
	HistoryNumberLS=0;
	TimerTick=0;
}
AChat::~AChat()
{
	log.SaveLog();

	QMap<QString,QVariant> KeysArray;
	for(int i=0;i<UniKeyList.size();i++)
	{
		QMap<QString,QVariant> KeyArray;
		UniKey s=UniKeyList.value(i);
		KeyArray["Client"]=s.StringID;
		KeyArray["Key"]=s.key;
		KeyArray["Cookie"]=s.CookieCode;
		KeysArray[QString::number(i)]=KeyArray;
	}
	setings["KeysList"]=KeysArray;
	setings.SaveSettings();
	delete timer;
	delete timersendls;
	ADD_DEBUG "Exit " + timeEx(timer3);
}
QString AChat::SencureString(QString str)
{
    return str.replace(QRegExp("сука"),SENSORE_STRING).replace(QRegExp("пид[^/s]р[^/s]{2}"),SENSORE_STRING)
	.replace(QRegExp("еба[^/s]{3}"),SENSORE_STRING).replace(QRegExp("ху[й|и|е][^/s]{3}"),SENSORE_STRING)
	.replace(QRegExp("блядь"),SENSORE_STRING);
}
void AChat::Registration(QString Login,QString name_and_family, QString Pass,QString EMail)
{
	post("type=regser&type2=reg&name_and_family="+name_and_family+"&login="+Login+"&pass="+Pass+"&email="+EMail,tReg);
}
void AChat::SendLSTimer()
{
	QString posti;
	for(int i=0;i<SendLSList.size();i++)
	posti+="&m_"+QString::number(MyClient.com_id)+"_"+QString::number(i+1)+"="+
	SpecialSybmolCoder(SendLSList.value(i)
	.replace("%","%25").replace("&","%26")
	.replace("+","%2B"),false);
	if(!posti.isEmpty())post("type=sendmsg"+posti,tNewLS);
	SendLSList.clear();
	timersendls->stop();
}
void AChat::SendLS(QString Text)
{
	if(SendLSOnTime.elapsed()<=TIMER_SENDLS) //Так делать нужно
	{
		if(!Text.isEmpty()) SendLSList << Text;
		timersendls->start(TIMER_SENDLS);
	}
	else
	{
		if(!isSendCommand(Text)){
            if(!isCensure) post("type=sendmsg&m_"+QString::number(MyClient.com_id)+"_1="+Text
            .replace("%","%25")
            .replace("&","%26").replace("+","%2B"),tNewLS);
            else post("type=sendmsg&m_"+QString::number(MyClient.com_id)+"_1="+SencureString(Text)
            .replace("%","%25")
            .replace("&","%26").replace("+","%2B"),tNewLS);
		}
		//if(!isSendCommand(Text)) post("type=sendmsg&message="+Text.replace("&","%26"),tNewLS);
		else SendCommand(Text);
	}
	SendLSOnTime.currentTime();
	SendLSOnTime.start();
}
void AChat::GetServersList()
{
	get("http://monitor.cluster-chat.ml/index.php",tServerList);
	log<<"Get server info...";
}
Client AChat::GetMyClient()
{
	return MyClient;
}
void AChat::exit()
{
	post("type=exit",tExit);
	ADD_DEBUG "Exit account";
}
void AChat::clearlist()
{
	MessageList.clear();
	ClientList.clear();
	OnlineCashe.clear();
	UniClientList.clear();
	Client s;
	s.com_id=0;
	MyClient=s;
}
UniClient AChat::GetUniClient(QString key)
{
	UniClient ReturnValue;
	for(int i=0;i<UniClientList.size();i++)
	{
		if(UniClientList.value(i).key==key) {ReturnValue=UniClientList.value(i);
			break;
		}
	}
	return ReturnValue;
}
QString AChat::Reformat(QString TEXT)
{
	TEXT.replace(QRegExp("COLOR=([^<]{6,6})"),"<font color=#\\1>");
	TEXT.replace(QRegExp("SIZE=([0-9]*)"),"<font size=\\1>");
	return TEXT;
}
void AChat::WriteClients(RecursionArray Map)
{
	QList<QString> keys=Map.keys();
	QString result;
	for(int i=0;i<keys.size();i++)
	{
		Client temp;
		RecursionArray ValueMap=Map.value(QString::number(i)).toMap();
		if(ValueMap.value("userOnlineStatus").toString()=="403") temp.Active=true;
		else temp.Active=false;
		temp.id=ValueMap.value("userId").toString().toInt();
		if(!ClientList.contains(temp))
		{
			if(isDebug)R->LoadWindowUI->label_2->setText(tr("Получение информации о пользователях"));
			if(result=="") result+=QString::number(temp.id);
			else result+="/"+QString::number(temp.id);
		}
	}
	if(MyClient.com_id!=0) {if(!isStart || isReloadHostory){post("type=msglist&room="+QString::number(GetKomnata()),tMessage);isReloadHostory=false;}
		else post("type=msglist&new=true&room="+QString::number(GetKomnata()),tMessage);}
	SendLSOnTime.start();
}
QString AChat::ListToHTML()
{
	QString HTML;
	QString TextMessages;
	int temp=0,nummers=0;
	QString allLS="";
	int ShowID=0;
	for(int i=0;i<MessageList.size();i++)
	{
		PrivateMessage ssLS=MessageList.value(i);
		ssLS.msg=Reformat(ssLS.msg);
        /*ssLS.msg.replace(":)","<IMG src=\":/res/smail.png\">")
        .replace("\n","<br>")
		.replace(":(","<IMG src=\":/res/sadness.png\">")
		.replace(":пфф:","<IMG src=\":/res/rukalico.png\">")
        .replace(":{}","<IMG src=\":/res/default/zloi.png\">");*/
        for(int i=0;i<SmilesList.size();i++) ssLS.msg.replace(SmilesList.value(i).code,"<IMG src=\""+SmilesList.value(i).url+"\">");
		Client ClientLS=GetClient(ssLS.ClientID);
		QStringList ListX=ssLS.time.split(":");
		QStringList ListY=ssLS.data.split("-");
		QString str=Styled.Message.arg(ClientLS.prefix).arg(ClientLS.color)
		.arg(ClientLS.name).arg(Styled.TextMessage.arg(ssLS.msg))
		.arg(dataTimeEx(ListX.value(2).toInt(),ListX.value(1).toInt(),ListX.value(0).toInt(),ListY.value(0).toInt(),ListY.value(1).toInt(),ListY.value(2).toInt()));
		if(!isCensure) allLS+=str;
		else allLS+=SencureString( str );
		nummers++;
		if(numLS<ssLS.id && !bool(ssLS.msg.isEmpty()))
		{
			numLS=ssLS.id;
			TextMessages=ClientLS.name+": "+ssLS.msg;
			temp=ssLS.ClientID;
			ShowID=ssLS.id;
			if(HistoryNumberLS<numLS) HistoryNumberLS=numLS;
		}
	}
	HTML=Styled.Main.arg(allLS);
	if(!TextMessages.isEmpty() && MyClient.id != temp && !R->MainUI->textEdit->hasFocus()) {
		SendDialogMessage(TextMessages,tr("<center><b>Новое Сообщение"));
		log<< "Send Dialog Message ID: "+ QString::number(ShowID)+" Text:"+ TextMessages;}
	return HTML;
}
int AChat::GetKomnata(){ return MyClient.com_id;}
void AChat::getReplyFinished(ANetworkReply reply) //Принят ответ сервера
{
	RecursionArray ValuesMap;ValuesMap.fromHTMLTegsFormat(reply.TextReply);
	RecursionArray ReplyMap=ValuesMap.value("arg").toMap();
	QString Text;
	Text=ValuesMap.value("key").toString();
	if(isDebug)qDebug() << ValuesMap.print();
	int Type=reply.Type;
	if(Text.toInt() > 300 && Text.toInt() <600)
	{
		QString sma=GetErrorText(Text.toInt());
		if(!sma.isEmpty()) SendMessage(sma);
	}

	if(reply.TextError!="Unknown error"&&reply.TextError!="Неизвестная ошибка")
	{
		SendErrorMessage(tr("Ошибка при получении данных с сервера ")+reply.TextError);
	}
	switch (Type) {
	case tUnkown:
		{
			SendMessage(Text);
			break;
		}
	case tAuth:
		{
			if(Text=="403"){
				MyClient.Active=true;
				post("type=info&id=?",tGetMy);
				if(!ValuesMap.value("сlientUnigue").toString().isEmpty())
				{
					UniKey s;
                    s.StringID=MyUniKey.StringID;
					s.key=ValuesMap.value("сlientUnigue").toString();
					s.CookieCode=ValuesMap.value("userUnigue").toString();
                    MyUniKey=s;
					if(!UniKeyList.contains(s)) UniKeyList << s;
				}
				R->LoadWindowUI->label_2->setText(tr("Вход на сервер. Подождите..."));
				R->LoadWindow->show();
				log<< "login on";
			}
			else{
				SendMessage(tr("Ошибка авторизации"));log<< "login Error: "+ Text;
				SendMessage(Text); MyClient.Active=false;}
			break;
		}
	case tGetError:
		{
			QFile errorsp;
			errorsp.setFileName(SetPath+"/Errors.txt");
			errorsp.open(QIODevice::WriteOnly);
			errorsp.write(Text.toLocal8Bit());
			errorsp.close();
			break;
		}
	case tSetInfo:
		{
			if(Text=="402") SendMessage(tr("Ошибка изменения. Код ошибки:")+Text);
			break;
		}
	case tOnlineList:
		{
			R->MainUI->labelOnline->setText(OnlinetoHTML(ReplyMap.value("0").toMap()));
			WriteClients(ReplyMap.value("0").toMap());
			break;
		}
	case tGetInfo:
		{
			QList<QString> keys=ReplyMap.keys();
			for(int i=0;i<keys.size();i++)
			{
				Client temp;
				RecursionArray ValueMap=ReplyMap.value(QString::number(i)).toMap();
				if(ValueMap.value("onlineStatus").toString()!="403") temp.Active=true;
				else temp.Active=false;
				temp.name=ValueMap.value("real_name").toString();
				if(temp.name.isEmpty()) continue;
				temp.id=ValueMap.value("id").toString().toInt();
				temp.prefix=ValueMap.value("prefix").toString();
				temp.color=ValueMap.value("colored").toString();
				temp.group=ValueMap.value("group").toString();
				temp.timezone=ValueMap.value("timeZone").toString();
				temp.enterclient=ValueMap.value("init").toString();
				temp.versionClient=ValueMap.value("initV").toString();
				temp.status=ValueMap.value("status").toString();
				temp.region=ValueMap.value("na").toString();
				temp.OnlineTime=ValueMap.value("data").toString();
				R->KabinUI->listWidget_2->addItem(temp.name);
				ClientList << temp;
			}
			if(isDebug) R->LoadWindowUI->label_2->setText(tr("Получение списка доступных комнат"));
			QString postiString;
			for(int i=0;i<ChatsList.size();i++)
			{
				int RoomID=ChatsList.value(i).KomID;
				if(RoomID!=MyClient.com_id) postiString+="/"+QString::number(RoomID);
			}
			if(MyClient.com_id!=0)post( tr("type=onlineUsersRoom&room=") +QString::number(MyClient.com_id)+postiString,tOnlineList);
			else post("type=onlineUsersRoom&room="+postiString,tOnlineList);
			break;
		}
	case tExit:
		{
			if(Text=="403"){
				R->LoadMenu->show();
				R->Main->setHidden(1);
				R->MainUI->textBrowser->setHtml(DEFAULT_TEXT_TEXTBROWSER);
				clearlist();
				timer->stop();
				MyClient.Active=false;}
			else if(ClusterChat.MessageQuest("На сообщение о выходе сервер отреагировал отрицательно. Выйти принудительно?"))
			{
				R->LoadMenu->show();
				R->Main->setHidden(1);
				R->MainUI->textBrowser->setHtml(DEFAULT_TEXT_TEXTBROWSER);
				clearlist();
				timer->stop();
				MyClient.Active=false;
			}
			break;
		}
	case tGetMy:
		{
			if(isDebug)R->LoadWindowUI->label_2->setText("Получение списка пользователей");
			RecursionArray MyClientMap=ReplyMap.value("0").toMap();
			MyClient.name=MyClientMap.value("real_name").toString();
			MyClient.id=MyClientMap.value("id").toString().toInt();
			MyClient.color=MyClientMap.value("colored").toString();
			MyClient.prefix=MyClientMap.value("prefix").toString();
			MyClient.group=MyClientMap.value("group").toString();
			MyClient.timezone=MyClientMap.value("timeZone").toString();
			MyClient.enterclient=MyClientMap.value("init").toString();
			MyClient.versionClient=MyClientMap.value("initV").toString();
			MyClient.status=MyClientMap.value("status").toString();
			MyClient.region=MyClientMap.value("na").toString();
			MyClient.OnlineTime=MyClientMap.value("data").toString();
			ClientList << MyClient;
			R->KabinUI->labelMyColor->setText("<font color=#"+MyClient.color+">#"+MyClient.color);
			R->KabinUI->lineEditMyName->setText(MyClient.name);
			R->KabinUI->label_Prem->setText(GetTextGroup(MyClient.group));
			ADD_DEBUG "My ID:" + QString::number(MyClient.id);
			LoadStyle(StylePath);
			post("type=rooms&typeRoom=all",tChats);
			break;
		}
	case tRemoveRoom:
		{
			if(Text!="403") ClusterChat.SendM("Комната не была удалена.");
			else post("type=rooms&typeRoom=all",tChats);
			break;
		}
	case tCreateRoom:
		{
			if(Text!="403") ClusterChat.SendM("Комната не была создана.");
			else post("type=rooms&typeRoom=all",tChats);
			break;
		}
	case tServerList:
		{
			WriteServerList(ReplyMap);
            AServer tmp;
            tmp.name="Server3";
            tmp.url="http://php-gravit.rhcloud.com/index.php";
            tmp.status="403";
            ServersList << tmp;
            R->LoadMenuUI->comboBox->addItem("Server3");
			break;
		}
	case tGetUngine:
		{
			R->KabinUI->listWidget_4->clear();
			MapFind(i,ReplyMap,keys)
			{
				RecursionArray ValueMap=ReplyMap.value(keys.value(i)).toMap();
				UniClient tmp;
				tmp.date=ValueMap.value("date").toString();
				tmp.idUser=ValueMap.value("idUser").toString().toInt();
				tmp.Init=ValueMap.value("init").toString();
				tmp.InitVersion=ValueMap.value("initV").toString();
				tmp.ip=ValueMap.value("ip").toString();
				tmp.key=ValueMap.value("unigie").toString();
				tmp.lastDate=ValueMap.value("lastDate").toString();
				if(!UniClientList.contains(tmp)) {
					UniClientList << tmp;}
			}

			for(int i=0;i<UniClientList.size();i++) R->KabinUI->listWidget_4->addItem(UniClientList.value(i).key);
			break;
		}
	case tNewLS:
		{
			if(Text!="403") SendMessage("Ошибка отправки ЛС: "+Text);
			if(MyClient.com_id!=0) post("type=msglist&new=true&room="+QString::number(GetKomnata()),tMessage);
			break;
		}
	case tChats:
		{

			QList<QString> keys=ReplyMap.keys();
			QStringList result;
			for(int i=0;i<keys.size();i++)
			{
				AChate temp2;
				RecursionArray ValueMap=ReplyMap.value(QString::number(i)).toMap();
				temp2.KomID=ValueMap.value("id").toString() .toInt();
				temp2.CreatedID=ValueMap.value("idUserCreat").toString() .toInt();
				temp2.Name=ValueMap.value("nameTextRoom").toString() ;
				QStringList UsersRoom=ValueMap.value("idsUsers").toString().split(", ");
				UsersRoom << QString::number(temp2.CreatedID);
				for(int j=0;j<UsersRoom.size();j++)
				{
					int res=UsersRoom.value(j).toInt();
					temp2.ClientList << res;
					if(!result.contains(QString::number(res))){
						result<<UsersRoom.value(j);
					}
				}
				if(!ChatsList.contains(temp2)){
					ChatsList<<temp2;
					R->MainUI->listWidget->addItem( temp2.Name+" "+ QString::number(temp2.KomID));
					R->KabinUI->listWidget_3->addItem( temp2.Name);}
			}
			R->Main->show();
			R->LoadWindow->setHidden(1);
			R->LoadMenu->setHidden(1);
			QString tmp;
			for(int i=0;i<result.size();i++) tmp+="/"+result.value(i);
			tmp.remove(0,1);
			post("type=info&id="+tmp,tGetInfo);
			timer->start(7000);
			break;
		}
	case tReg:
		{
			if(Text=="403") SendMessage("Регистрация прошла успешно. Проверьте вашу почту и подтвердите свой E-Mail.");
			else SendMessage("Ошибка: "+Text);
			break;
		}
    case tDeleteUniKey:
       {
           if(Text=="403") break;
           else
           { ClusterChat.Error("Нельзя удалить текущий ключ доступа"); break; }
       }
	case tMessage:
		{
			if(Text=="303") break;
			if(!isStart || isReloadHostory)
			{
				SMStoValues(ReplyMap.value("0").toMap(),true);
				isReloadHostory=false;
			}
			else SMStoValues(ReplyMap.value("0").toMap(),false);
			isStart=true;
            QString Texte=ListToHTML();
            QTextCursor s=R->MainUI->textBrowser->textCursor();
            if(TexteCashe!=MessageList.length()){
                R->MainUI->textBrowser->setHtml(Texte);
                TexteCashe=MessageList.length();
                QTextCursor k(R->MainUI->textBrowser->document());
                k=s;
                if(s.position()==0) R->MainUI->textBrowser->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);
                else R->MainUI->textBrowser->setTextCursor(k);
            }
			break;
		}
	default:
		SendMessage(Text);
		break;
	}
	R->KabinUI->textBrowser->setText(log.toHTML());
}
void AChat::DelUniKey(QString key)
{
    post("type=setUnigue&typeCommand=delete&userUnigue="+key,tDeleteUniKey);
    for(int i=0;i<UniClientList.size();i++)
    {
        if(UniClientList.value(i).key==key)
        {
            UniClientList.removeAt(i);
        }
    }
    R->KabinUI->listWidget_4->clear();
    for(int i=0;i<UniClientList.size();i++) R->KabinUI->listWidget_4->addItem(UniClientList.value(i).key);
}
UniKey AChat::currentUniKey()
{
    return MyUniKey;
}

void AChat::updateCaption() //Таймер сработал
{
	if(MyClient.Active)
	{
		if(TimerTick!=10) {if(MyClient.com_id!=0) post("type=msglist&new=true&room="+QString::number(GetKomnata()),tMessage);
			else {QString postiString;
				for(int i=0;i<ChatsList.size();i++)
				{
					int RoomID=ChatsList.value(i).KomID;
					if(RoomID!=MyClient.com_id) postiString+="/"+QString::number(RoomID);
				}
				post("type=onlineUsersRoom&room="+QString::number(MyClient.com_id)+postiString,tOnlineList);TimerTick=0;}}
		TimerTick++;
	}
	R->KabinUI->textBrowser->setText(log.toHTML());
}
void AChat::updateCaption2()
{
	SendLSTimer();
}
