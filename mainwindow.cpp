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
#include "acore.h"
#include "aclientserver.h"
#include "auimanager.h"
#define INIT_CLIENT "Qt"
#define INIT_VERSION "8.1"
#define API_VERSION "2.3"
#define IS_DEBUG "false"
#define TIMER_SENDLS 300
#define foreash(n,mas) for(int n=0;n<mas.size();n++)
#define EXTRA_NETWORK false
using namespace ACore;
#define ADD_DEBUG log<<
#define DEFAULT_TEXT_TEXTBROWSER "<center><br><br><br><hr>Для начала работы откройте нужную комнату в списке справа -><br>Или создайте новую в \"личном кабинете\"<hr>"
bool isStart;

struct AChate
{
    QString Name;
    int CreatedID;
    int KomID;
    bool isOpen;
    QList<int> ClientList;
    bool operator ==(AChate h)
    {
        if(KomID==h.KomID) return true;
        else return false;
    }
};
struct UniKey
{
    QString key;
    QString StringID;
    bool operator ==(UniKey h)
    {
        if(StringID==h.StringID) return true;
        else return false;
    }
};
struct UniClient
{
    QString date,lastDate;
    int idUser;
    QString Init;
    QString InitVersion;
    QString ip;
    QString key;
    bool operator ==(UniClient h)
    {
        if(key==h.key) return true;
        else return false;
    }
};
enum ChatTypes
{
    tUnkown,
    tAuth,
    tMessage,
    tGetID,
    tNewLS,
    tChats,
    tDefault,
    tExit,
    tGetInfo,
    tSetInfo,
    tCreateRoom,
    tRemoveRoom,
    tGetUngine,
    tGetError,
    tServerList,
    tAllNewLS,
    tOnlineList,
    tReg,
    tServerPixmap,
    tGetMy
};
struct PrivateMessage
{
    QString msg;
    QString data;
    QString time;
    int id;
    int ClientID;
    bool isRealLS;
};

struct Client
{
    QString name;
    int id;
    QString group;
    QString color;
    QString prefix;
    QString timezone;
    QString enterclient;
    QString region;
    QString versionClient;
    QString status;
    QString OnlineTime;
    bool Active;
    int com_id;
    bool operator ==(Client h)
    {
        if(id==h.id) return true;
        else return false;
    }
};
AAppCore ClusterChat("ClusterChat");
struct AServer
{
    QString name;
    float ping;
    QString url;
    QString region;
    QString status;
    QString information;
    QPixmap logo;
    int users,usersmax;
    bool operator ==(AServer h)
    {
        if(url==h.url) return true;
        else return false;
    }
};

struct Style
{
    QString Main;
    QString Message;
    QString TextMessage;
    QString Notify;
    QString OnlineList;
};

void SendDialogMessage(QString Text,QString Title="")
{
    R.MessageUI->label_2->setText(Text);
    R.MessageUI->label->setText(Title);

    QDesktopWidget desktop;
        QRect rect = desktop.availableGeometry(desktop.primaryScreen()); // прямоугольник с размерами экрана
        QPoint center = rect.center(); //координаты центра экрана
        center.setX(center.x()*2 - (R.Message->width()/2) - 150);  // учитываем половину ширины окна
        center.setY(center.y()*2 - (R.Message->height()/2) - 50);  // .. половину высоты
        R.Message->move(center);
        R.Message->show();
}

QTextBrowser *tmppp;


class AChat : public ATcpNetwork
{
    Q_OBJECT
private:
    int KomnataID;
    ALog log;
    Client MyClient;
    QString OnlineCashe;
    QList<QString> SendLSList;
    QTime SendLSOnTime;
    QList<PrivateMessage> MessageList;
    QList< QList<PrivateMessage> > MessageListOther;
    QList<AServer> ServersList;
    QList<Client> ClientList;
    QList<AChate> ChatsList;
    QList<UniKey> UniKeyList;
    QList<UniClient> UniClientList;
    QString MyUniKey,InitServerUrl;
    QString ReportMessage, passworda,logina,SetPath;
    int myID,HistoryNumberLS,TimerTick;
    bool isSmiles,isReloadHostory,ServerType,isCensure;
    QTime TimeStart;
    QTimer *timersendls;
    Style Styled;
    QSettings *styles;
    QString StylePath;
    int numLS;
    Client TimeClient;
    QSettings *errors;

public:
    QTimer *timer;
    bool isSendCommand(QString message)
    {
        if(message.toLatin1()[0]=='/') return true;
        else return false;
    }
    void post(QString text, int Typ)
    {
        if(ServerType) ANetwork::post(text,Typ);
        else ATcpNetwork::post(text,Typ);
    }

    QString GetTextGroup(QString Groups)
    {
        QString ReturnText="<font color=#0F0>Пользователь";
        QStringList GroupsList=Groups.split(", ");
        for(int i=0;i<GroupsList.size();i++)
        {
            if("ban") ReturnText="<font color=red>Администратор";
        }
        return ReturnText;
    }
    void AddLS(int ClientID,QString msg)
    {
        PrivateMessage temp;
        temp.ClientID=ClientID;
        temp.isRealLS=false;
        temp.id=0;
        temp.msg=msg;
        MessageList << temp;
    }
    void WriteServerList(RecursionArray reply)
    {
        int Servers=0,AllServers=0;
        ServersList.clear();
        QList<QString> keys=reply.keys();
        for(int i=0;i<keys.size();i++)
        {
            AServer tmp;
            RecursionArray tmp2=reply.value(keys.value(i)).toMap();
            tmp.name=tmp2.value("name").toString();
            tmp.ping=tmp2.value("ping").toString().toFloat();
            tmp.url=tmp2.value("url").toString().replace("<space>"," ");
            if(tmp.name.isEmpty()) tmp.name=tmp.url;
            tmp.region=tmp2.value("region").toString();
            tmp.status="offline";
            tmp.information=tmp2.value("info").toString();
            tmp.users=tmp2.value("users").toString().toInt();
            tmp.usersmax=tmp2.value("offusers").toString().toInt();

            R.KabinUI->listWidget->addItem(tmp.name);
            if(tmp2.value("key").toString()=="403")
            {
                R.LoadMenuUI->comboBox->addItem(tmp.name);
                tmp.status="online";
            }
            else  Servers++;
            AllServers++; ServersList<<tmp;
        }
        log<<QString::number(Servers)+" ot "+QString::number(AllServers)+" Servers";
    }
    void LSUp()
    {
        HistoryNumberLS-=20;
    }
    void LSDown()
    {
        if(HistoryNumberLS>0) HistoryNumberLS+=20;
    }
    void ReloadHistory()
    {
        isReloadHostory=true;
        if(MyClient.com_id!=0) post("type=msglist&otMessages=25&room="+QString::number(GetKomnata())+"&maxMessages="+QString::number(HistoryNumberLS),tMessage);
    }
    void ReloadAllSMS()
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
    QString OnlinetoHTML(RecursionArray Map)
    {
        QString HTML;
        QList<QString> keys=Map.keys();
        QString allLS;
        for(int i=0;i<keys.size();i++)
        {
            QString Coloring;
            Client tmp;
            RecursionArray nMap=Map.value(QString::number(i)).toMap();
            tmp.id=nMap.value("userId").toString().toInt();
            tmp=ClientList.value(ClientList.indexOf(tmp));
            if(nMap.value("userOnlineStatus").toString()=="403") {Coloring="#0F0";}
            else {Coloring="#F00";}
            if(!tmp.name.isEmpty())allLS+=QString("<font size=2 color=%1>%2 <font color=#000>| ").arg(Coloring).arg(tmp.name);
        }
        HTML=Styled.Main.arg(allLS);
        return HTML;
    }
    void SetServer(QString name)
    {
        log<<"New server: "+name;
        for(int i=0;i<ServersList.size();i++)
        {

            if(ServersList.value(i).name==name && ServersList.value(i).status !="offline") {
                if(ServersList.value(i).name[0]=='~')
                {
                    ServerType=false;
                    QStringList Srv=ServersList.value(i).name.replace("~","").split(":");
                    ConnectToServer(Srv.value(0),Srv.value(1).toInt());
                }
                else
                {
                    Server=QNetworkRequest(QUrl(ServersList.value(i).url));
                    InitServerUrl=ServersList.value(i).url;
                    ServerType=true;
                }
                setings->SetKey("Server",ServersList.value(i).url);
                ADD_DEBUG "Server url: "+ServersList.value(i).url;
            }
        }
    }
    AServer FindServer(QString name)
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
    bool SendCommand(QString message)
    {
        //QStringList ArgList=message.split(" ");
        QStringList ArgList=splitStringArgs(message);
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
        else if(cmd=="/sendls")
        {
            if(ArgList.value(1).isEmpty()) SendMessage("Невозможно отправить пустое сообщение");
            AddLS(MyClient.id,ArgList.value(1));
            R.MainUI->textBrowser->setText(ListToHTML());
            return true;
        }
        else return false;
    }
    void SetKomnata(int id)
    {
        if(id!=KomnataID){

        KomnataID=id;
        MyClient.com_id=id;
        ReloadAllSMS();
        ADD_DEBUG "Комната выбрана: "+QString::number(id);

        MessageList.clear();
        }
    }
    void SMStoValues(RecursionArray Map,bool isClear)
    {
        if(Map.isEmpty()) return;
        QList<QString> keys=Map.keys();
        if(isClear) MessageList.clear();
        for(int i=0;i<keys.size();i++)
        {
            PrivateMessage Temp;
            RecursionArray ValueMap=Map.value(QString::number(i)).toMap();
            Temp.ClientID=ValueMap.value("idUser").toString().toInt();
            Temp.id=ValueMap.value("id").toString().toInt();
            Temp.isRealLS=true;
            Temp.msg=SpecialSybmolCoder(ValueMap.value("textMessage").toString(),true);
            QStringList TimeData=ValueMap.value("dateMessage").toString().split(" ");
            Temp.data=TimeData.value(0);
            Temp.time=TimeData.value(1);
            if(!Temp.msg.isEmpty())MessageList << Temp;
        }

    }
    void SendMessage(QString text)
    {
        bool tim1;
        tim1=timer->isActive();
        if(tim1) timer->stop();
        ClusterChat.SendM(text);
        if(tim1) timer->start(7000);
    }
    void SendErrorMessage(QString text)
    {
        bool tim1;
        tim1=timer->isActive();
        if(tim1) timer->stop();
        ClusterChat.Error("Произошла ошибка при выполнении программы\nИнформация об ошибке:\n"+text+"\nЕсли ошибка повторится, обратитесь к разработчику или администратору сервера.");
        if(tim1) timer->start(7000);
    }
    QString GetErrorText(int ErrorID)
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
    UniKey FindUniKey(QString id)
    {
        for(int i=0;i<UniKeyList.size();i++)
        {
            if(UniKeyList.value(i).StringID==id)
            {
                return UniKeyList.value(i);
                break;
            }
        }
    }
    void login(QString loginit,QString passit,QString key = "")
    {
        QString posti;
        if(loginit.isEmpty() || passit.isEmpty()) SendMessage("Ошибка, поля Логин | Пароль не заполнены");
        if(Server.url().toString().isEmpty()) SendMessage("Сервер не выбран");
        if(key.isEmpty()){
            UniKey s;
            s.StringID=InitServerUrl+"."+loginit;
            MyUniKey=s.StringID;
            if(UniKeyList.contains(s))
            posti="type=auth&login="+loginit+"&pass="+passit+"&init="+INIT_CLIENT+"&clientUnigue="+UniKeyList.value(UniKeyList.indexOf(s)).key+"&initV="+INIT_VERSION;
            else posti="type=auth&login="+loginit+"&pass="+passit+"&init="+INIT_CLIENT+"&clientUnigue=?&initV="+INIT_VERSION;
        }
        else {
            posti="type=auth&key="+key+"&login="+loginit+"&clientUnigue=?&pass="+passit+"&initialization="+INIT_CLIENT;
        }
        post(posti,tAuth);
        if(timer->isActive()) timer->stop();
        log<< "login...";
    }
    void GetFileErrors()
    {
        get("http://server-ClusterChat.esy.es/fileinfo.php",tGetError);
        log<<"Get Errors.txt";
    }
    void LoadSettings()
    {
        setings->AddKey("Debug",IS_DEBUG);
        setings->AddKey("TimeFormat","[%1:%2:%3]");
        setings->AddKey("Smiles","true");
        setings->AddKey("Login","");
        setings->AddKey("Pass","");
        setings->AddKey("Server","");
        setings->LoadSettings();
        R.LoadMenuUI->lineEdit->setText(setings->GetKey("Login"));
        R.LoadMenuUI->lineEdit_2->setText(setings->GetKey("Pass"));
        if(setings->GetKey("Smiles")=="true"){R.KabinUI->checkBox->setChecked(1);
        isSmiles=true;}
        else
        {isSmiles=false;}
        if(setings->GetKey("Debug")=="true"){R.KabinUI->checkBox_2->setChecked(1);
        isDebug=true;}
        else
        {isDebug=false;}
        QStringList List1,List2;
        List1=setings->Main->value("KeysList1").toStringList();
        List2=setings->Main->value("KeysList2").toStringList();
        for(int i=0;i<List1.size();i++)
        {
            UniKey s;
            s.StringID=List1.value(i);
            s.key=List2.value(i);
            UniKeyList << s;
        }
        Server=QNetworkRequest(QUrl(setings->GetKey("Server")));
        InitServerUrl=setings->GetKey("Server");
    }
    void CheckBoxUpdate()
    {
        if(setings->GetKey("Smiles")=="true") R.KabinUI->checkBox->setChecked(1);
        else R.KabinUI->checkBox->setChecked(0);
        if(setings->GetKey("Debug")=="true") R.KabinUI->checkBox->setChecked(1);
        else R.KabinUI->checkBox->setChecked(0);
        if(!R.LoadMenuUI->lineEdit_2->text().isEmpty()) R.LoadMenuUI->checkBox->setChecked(1);
        else R.LoadMenuUI->checkBox->setChecked(0);
    }
    bool LoadStyle(QString path)
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
    QTime timer3;
    AChate FindKomOfIndex(QString id)
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
    AChate GetRoom(int id)
    {
        return ChatsList.value(id);
    }

    Client FindClientOfIndex(QString id)
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
    Client GetClient(int id)
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
    void functionA()
    {
        int sum = 0;
        while (sum < 10e5)
            sum++;
    }
    AChat()
    {
        SetPath=QDir().homePath();
        if(!QDir(SetPath+"/.ClusterChat").exists()) { QDir(SetPath).mkdir(".ClusterChat"); log<<"Create dir .ClusterChat";}
        log.SetFile(SetPath+"/.ClusterChat/ClusterChat.log");
        log<< "Start";
        ADD_DEBUG "Выбран путь для сохранения файлов: "+SetPath;
        isStart=false;
        functionA();
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
        TimeStart=QTime::currentTime();
        #ifdef Q_OS_WIN32
        setings=new ASettings(SetPath+"/.ClusterChat/settings.ini");
        #endif
        #ifdef Q_OS_LINUX
        setings=new ASettings(SetPath+"/.config/ClusterChat.ini");
        #endif
        MyClient.com_id=0;
        RecursionArray tmpp;
        tmpp.fromYumFormat("Value:Name1\nValue2:Name2\nValues:\n Value1:1\n Value2:2\nValue3:3");
        qDebug() << tmpp.toYUMFormat();
        ServerType=true;
        ADD_DEBUG QString::number(R.KabinUI->pushButton->geometry().height() );
        errors=new QSettings(SetPath+"/.ClusterChat/Errors.txt", QSettings::IniFormat);
        errors->setIniCodec(QTextCodec::codecForName("UTF-8"));
        styles=new QSettings(SetPath+"/.ClusterChat/Style.ini", QSettings::IniFormat);
        connect(this, SIGNAL(ARequest(ANetworkReply)),this, SLOT(getReplyFinished(ANetworkReply)));
        connect(this, SIGNAL(ARequestTcp(ANetworkReply)),this, SLOT(getReplyFinished(ANetworkReply)));
        //Server=QNetworkRequest(QUrl("https://php-gravit.rhcloud.com/index.php"));
        timersendls=new QTimer(this);
        timer=new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateCaption()));
        connect(timersendls, SIGNAL(timeout()), this, SLOT(updateCaption2()));
        setings->Main->beginGroup("Main");
        errors->beginGroup("Errors");
        styles->beginGroup("Styles");
        numLS=0;
        isReloadHostory=false;
        HistoryNumberLS=0;
        TimerTick=0;
    }
    ~AChat()
    {
        log.SaveLog();
        setings->SaveSettings();
        QStringList List1,List2;

        for(int i=0;i<UniKeyList.size();i++)
        {
            UniKey s;
            s=UniKeyList.value(i);
            List1 << s.StringID;
            List2 << s.key;
        }
        setings->Main->setValue("KeysList1",List1);
        setings->Main->setValue("KeysList2",List2);
        setings->Main->sync();
        delete timer;
        delete errors;
        delete setings;
        delete styles;
        delete timersendls;
        log<< "Exit " + timeEx(timer3);
    }
    ASettings *setings;
    void Registration(QString Login,QString name_and_family, QString Pass,QString EMail)
    {
        post("type=regser&type2=reg&name_and_family="+name_and_family+"&login="+Login+"&pass="+Pass+"&email="+EMail,tReg);
    }
    void SendLSTimer()
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
    void SendLS(QString Text)
    {
        if(SendLSOnTime.elapsed()<=TIMER_SENDLS) //Так делать нужно
        {
            if(!Text.isEmpty()) SendLSList << Text;
            timersendls->start(TIMER_SENDLS);
        }
        else
        {
        if(!isSendCommand(Text))
            post("type=sendmsg&m_"+QString::number(MyClient.com_id)+"_1="+SpecialSybmolCoder(Text
                                                                        .replace("%","%25").replace("&","%26")
                                                                        .replace("+","%2B"),false),tNewLS);
        //if(!isSendCommand(Text)) post("type=sendmsg&message="+Text.replace("&","%26"),tNewLS);
        else SendCommand(Text);
        }
        SendLSOnTime.currentTime();
        SendLSOnTime.start();
    }
    void GetServersList()
    {
        get("http://monitor.cluster-chat.ml/index.php",tServerList);
        log<<"Get server info...";
    }
    Client GetMyClient()
    {
        return MyClient;
    }
    void exit()
    {
        post("type=exit",tExit);
        ADD_DEBUG "Exit account";
    }
    void clearlist()
    {
                MessageList.clear();
                ClientList.clear();
                OnlineCashe.clear();
                UniClientList.clear();
                Client s;
                s.com_id=0;
                MyClient=s;
    }
    UniClient GetUniClient(QString key)
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
    QString Reformat(QString TEXT)
    {
        TEXT.replace(QRegExp("COLOR=([^<]{6,6})"),"<font color=#\\1>");
        TEXT.replace(QRegExp("SIZE=([0-9]*)"),"<font size=\\1>");
        return TEXT;
    }
    void WriteClients(RecursionArray Map)
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
                if(isDebug)R.LoadWindowUI->label_2->setText("Получение информации о пользователях");
                if(result=="") result+=QString::number(temp.id);
                else result+="/"+QString::number(temp.id);
            }
        }
        if(MyClient.com_id!=0) {if(!isStart || isReloadHostory){post("type=msglist&room="+QString::number(GetKomnata()),tMessage);isReloadHostory=false;}
        else post("type=msglist&new=true&room="+QString::number(GetKomnata()),tMessage);}
        SendLSOnTime.start();
    }
    QString ListToHTML()
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
            ssLS.msg.replace(":)","<IMG src=\":/res/smail.png\">")
                    .replace(":(","<IMG src=\":/res/sadness.png\">")
                    .replace(":пфф:","<IMG src=\":/res/rukalico.png\">")
                    .replace(":{}","<IMG src=\":/res/default/zloi.png\">");
            Client ClientLS=GetClient(ssLS.ClientID);
            QStringList ListX=ssLS.time.split(":");
            QStringList ListY=ssLS.data.split("-");
            allLS+=Styled.Message.arg(ClientLS.prefix).arg(ClientLS.color)
                    .arg(ClientLS.name).arg(Styled.TextMessage.arg(ssLS.msg)).arg(dataTimeEx(ListX.value(2).toInt(),ListX.value(1).toInt(),ListX.value(0).toInt(),ListY.value(0).toInt(),ListY.value(1).toInt(),ListY.value(2).toInt()));
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
        if(!TextMessages.isEmpty() && MyClient.id != temp && !R.MainUI->textEdit->hasFocus()) {
            SendDialogMessage(TextMessages,"<center><b>Новое Сообщение");
            log<< "Send Dialog Message ID: "+ QString::number(ShowID)+" Text:"+ TextMessages;}
        return HTML;
    }
    int GetKomnata(){ return MyClient.com_id;}
public slots:
    void getReplyFinished(ANetworkReply reply) //Принят ответ сервера
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
            SendErrorMessage("Ошибка при получении данных с сервера "+reply.TextError);
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
                    s.StringID=MyUniKey;
                    s.key=ValuesMap.value("сlientUnigue").toString();
                    if(!UniKeyList.contains(s)) UniKeyList << s;
                }
                R.LoadWindowUI->label_2->setText("Вход на сервер. Подождите...");
                R.LoadWindow->show();
                log<< "login on";
            }
            else{
                SendMessage("Ошибка авторизации");log<< "login Error: "+ Text;
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
            if(Text=="402") SendMessage("Ошибка изменения. Код ошибки:"+Text);
            break;
        }
        case tOnlineList:
        {
            R.MainUI->labelOnline->setText(OnlinetoHTML(ReplyMap.value("0").toMap()));
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
                R.KabinUI->listWidget_2->addItem(temp.name);
                ClientList << temp;
            }
            if(isDebug) R.LoadWindowUI->label_2->setText("Получение списка доступных комнат");
            QString postiString;
            for(int i=0;i<ChatsList.size();i++)
            {
                int RoomID=ChatsList.value(i).KomID;
                if(RoomID!=MyClient.com_id) postiString+="/"+QString::number(RoomID);
            }
            if(MyClient.com_id!=0)post("type=onlineUsersRoom&room="+QString::number(MyClient.com_id)+postiString,tOnlineList);
            else post("type=onlineUsersRoom&room="+postiString,tOnlineList);
            break;
        }
        case tExit:
        {
            if(Text=="403"){
            R.LoadMenu->show();
            R.Main->setHidden(1);
            R.MainUI->textBrowser->setHtml(DEFAULT_TEXT_TEXTBROWSER);
            clearlist();
            timer->stop();
            MyClient.Active=false;}
            else if(ClusterChat.MessageQuest("На сообщение о выходе сервер отреагировал отрицательно. Выйти принудительно?"))
            {
                  R.LoadMenu->show();
                  R.Main->setHidden(1);
                  R.MainUI->textBrowser->setHtml(DEFAULT_TEXT_TEXTBROWSER);
                  clearlist();
                  timer->stop();
                  MyClient.Active=false;
            }
            break;
        }
        case tGetMy:
        {
            if(isDebug)R.LoadWindowUI->label_2->setText("Получение списка пользователей");
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
            R.KabinUI->labelMyColor->setText("<font color=#"+MyClient.color+">#"+MyClient.color);
            R.KabinUI->lineEditMyName->setText(MyClient.name);
            R.KabinUI->label_Prem->setText(GetTextGroup(MyClient.group));
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
            break;
        }
        case tGetUngine:
        {
            R.KabinUI->listWidget_4->clear();
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

            for(int i=0;i<UniClientList.size();i++) R.KabinUI->listWidget_4->addItem(UniClientList.value(i).key);
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
                R.MainUI->listWidget->addItem( temp2.Name+" "+ QString::number(temp2.KomID));
                R.KabinUI->listWidget_3->addItem( temp2.Name);}
            }
            R.Main->show();
            R.LoadWindow->setHidden(1);
            R.LoadMenu->setHidden(1);
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
            R.MainUI->textBrowser->setHtml(Texte);
            R.MainUI->textBrowser->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);
            break;
        }
        default:
            SendMessage(Text);
            break;
        }
        R.KabinUI->textBrowser->setText(log.toHTML());
    }
    void updateCaption() //Таймер сработал
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
        R.KabinUI->textBrowser->setText(log.toHTML());
    }
    void updateCaption2()
    {
        SendLSTimer();
    }
};
#include "mainwindow.moc"
AChat *CluChat;
AChate MyKomnata;
bool isCreareRoom=false;
void Kabinet::on_pushButton_CreateRoom_clicked()
{
    if(!isCreareRoom)
    {
        R.KabinUI->label_CreateRoom->show();
        R.KabinUI->lineEdit_CreateRoom->show();
        R.KabinUI->pushButton_CreateRoom->setText("Применить");
        isCreareRoom=true;
    }
    else
    {
        R.KabinUI->label_CreateRoom->hide();
        R.KabinUI->lineEdit_CreateRoom->hide();
        QString NameRoom=R.KabinUI->lineEdit_CreateRoom->text();
        R.KabinUI->pushButton_CreateRoom->setText("Создать комнату");
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

MainWindow::~MainWindow()
{
    delete ui;
    delete CluChat;
}
void Kabinet::on_listWidget_clicked(const QModelIndex &index)
{

    AServer tmp=CluChat->FindServer(index.data().toString());
    R.KabinUI->label_nameserver->setText("Имя сервера: "+tmp.name);
    if(tmp.status!="offline")R.KabinUI->label_serverstatus->setText("Статус: <font color=#0F0>online");
    else R.KabinUI->label_serverstatus->setText("Статус: <font color=#F00>offline");
    R.KabinUI->label_serveronline->setText("Онлайн: "+QString::number(tmp.users)+" из "+QString::number(tmp.usersmax));
    R.KabinUI->label_url->setText("URL: "+tmp.url);
    R.KabinUI->label_serverinfo->setText("Описание сервера:\n"+tmp.information);
    R.KabinUI->label_region->setText("Регион: "+tmp.region);
}
void Kabinet::on_listWidget_4_clicked(const QModelIndex &index)
{
    UniClient tmp=CluChat->GetUniClient(index.data().toString());
    R.KabinUI->label_ClientVersion_Uni->setText("Версия: "+tmp.Init+" "+tmp.InitVersion);
    R.KabinUI->label__UniKey_Uni->setText("Уникальный ключ: "+tmp.key);
    R.KabinUI->label_LastData_Uni->setText("Дата последнего входа: "+tmp.lastDate);
    R.KabinUI->label_Data_Uni->setText("Дата первого входа: "+tmp.date);
    R.KabinUI->label_IP_Uni->setText("IP адрес: "+tmp.ip);

}

void Kabinet::on_listWidget_3_clicked(const QModelIndex &index)
{
    AChate tmp=CluChat->FindKomOfIndex(index.data().toString());
    Client Creater=CluChat->GetClient(tmp.CreatedID);
    MyKomnata=tmp;
    R.KabinUI->label_NameKom->setText("Имя комнаты: "+tmp.Name);
    R.KabinUI->label_NumKom->setText("Номер комнаты: "+QString::number(tmp.KomID));
    R.KabinUI->label_Creater->setText("Создатель комнаты: "+Creater.name);
    R.KabinUI->listWidget_5->clear();
    for(int i=0;i<tmp.ClientList.size();i++)
    {
        Client s=CluChat->GetClient(tmp.ClientList.value(i));
        if(!s.name.isEmpty() && s.id!=tmp.CreatedID)
            R.KabinUI->listWidget_5->addItem(s.name);
    }
}
void  Kabinet::on_listWidget_2_clicked(const QModelIndex &index)
{
    Client  tmp=CluChat->FindClientOfIndex(index.data().toString());
    R.KabinUI->label_NameUser->setText("Имя пользователя: "+tmp.name);
    R.KabinUI->label_RegionUser->setText("Страна: "+tmp.region);
    if(tmp.Active){R.KabinUI->label_StatusUser->setText("<center><font color=green>Онлайн"); R.KabinUI->label_TimeOnlineUser->setText("");}
    else {R.KabinUI->label_StatusUser->setText("<center><font color=red>Оффлайн"); R.KabinUI->label_TimeOnlineUser->setText("Был(а) в:"+tmp.OnlineTime);}
    R.KabinUI->label_EnterClientUser->setText("Версия клиента: "+tmp.enterclient+" "+tmp.versionClient);
    R.KabinUI->laabel_TextStatus->setText("Статус: "+tmp.status);
    R.KabinUI->label_RegionUser->setText("Страна: "+tmp.region);
    R.KabinUI->label_TomeZomeUser->setText("Часовой пояс: "+tmp.timezone);
}

void Kabinet::on_pushButton_clicked()
{
    Client tmp=CluChat->GetMyClient();
    QString posti="type=setInfo&id="+QString::number(tmp.id);
    if(tmp.name!=R.KabinUI->lineEditMyName->text())
        posti+="&real_name="+R.KabinUI->lineEditMyName->text();
    CluChat->post(posti,tSetInfo);
}
void Dialog::on_checkBox_stateChanged(int arg1)
{
    if(arg1==2) {CluChat->setings->SetKey("Login",R.LoadMenuUI->lineEdit->text());
    CluChat->setings->SetKey("Pass",R.LoadMenuUI->lineEdit_2->text());}
}

void Kabinet::on_checkBox_5_stateChanged(int arg1)
{
    if(arg1==2) {CluChat->setings->SetKey("VirtualHost","true");}
    else {CluChat->setings->SetKey("VirtualHost","false");}
}

void Kabinet::on_checkBox_clicked(bool checked)
{
    if(checked) {CluChat->setings->SetKey("Smiles","true");}
    else CluChat->setings->SetKey("Smiles","false");
}
void Kabinet::on_checkBox_2_clicked(bool checked)
{
    if(checked) {CluChat->setings->SetKey("Debug","true");}
    else CluChat->setings->SetKey("Debug","false");
}
void MainWindow::OnStart()
{
    CluChat=new AChat;
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
    if(!CluChat->Server.url().isEmpty())
    CluChat->login(R.LoadMenuUI->lineEdit->text(),R.LoadMenuUI->lineEdit_2->text());
    else ClusterChat.SendM("Выберите сервер для входа");
}
void registr::on_pushButton_2_clicked()
{
    R.Reg->setHidden(1);
}
void registr::on_pushButton_3_clicked()
{

    CluChat->login(R.RegUI->lineEditLogin->text(),R.RegUI->lineEditPass->text(),R.RegUI->lineEdit->text());
}

void registr::on_pushButton_clicked()
{
    if(!R.RegUI->lineEditLogin->text().isEmpty()) if(!R.RegUI->lineEditPass->text().isEmpty())
        if(!R.RegUI->lineEditName->text().isEmpty()) if(!R.RegUI->lineEditFamelye->text().isEmpty())
            if(!R.RegUI->lineEditEmail->text().isEmpty())
    CluChat->Registration(R.RegUI->lineEditLogin->text(),R.RegUI->lineEditName->text()+" "+R.RegUI->lineEditFamelye->text(),
                       R.RegUI->lineEditPass->text(),R.RegUI->lineEditEmail->text());
    else ClusterChat.SendM("Неверно заполнены поля");
    else ClusterChat.SendM("Неверно заполнены поля");
    else ClusterChat.SendM("Неверно заполнены поля");
    else ClusterChat.SendM("Неверно заполнены поля");
    else ClusterChat.SendM("Неверно заполнены поля");
}
void MainWindow::on_commandLinkButton_clicked()
{
    if(!R.MainUI->textEdit->toPlainText().isEmpty()) CluChat->SendLS(QtHtmlRecoder(R.MainUI->textEdit->toHtml()));
    R.MainUI->textEdit->setHtml("");
    R.MainUI->textEdit->setFocus();
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
