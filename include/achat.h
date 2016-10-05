#ifndef ACHAT_H
#define ACHAT_H
#include <QString>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QVariant>
#include <QTime>
#include <QTextBrowser>
#include <QTextCodec>
#include "anetwork.h"
#include "auimanager.h"
#include "acore.h"
#include "abbcodec.h"
#include "atcpclient.h"
#include "asound.h"
#include "alog.h"
#include "asettings.h"
#include <QLinkedList>
#define ADD_DEBUG logs<<
#define foreash(n,mas) for(int n=0;n<mas.size();n++)
#define DEFAULT_TEXT_TEXTBROWSER "<center><br><br><br><hr>Для начала работы откройте нужную комнату в списке справа -><br>Или создайте новую в \"личном кабинете\"<hr>"
struct PrivateMessage
{
    QString msg;
    QString data;
    QString time;
    int id;
    int ClientID;
    bool isRealLS,isCommand;
};
class AAppCore
{
public:
    void SendM(QString text);
    void Error(QString text);
    bool MessageQuest(QString text);
    void SetProgramName(QString name);
    AAppCore();
    ~AAppCore();
    AAppCore(QString ProgName);
protected:
    int MessageBoxNumber;
    QString ProgramName;
};
using ANetwork::ANetworkReply;
enum ProgramStatus
{
    Loading,
    AuthServer,
    Wait,
    Exit
};
enum UpdateType
{
    updateUniKey,
    updateHistoryMessage,
    updateMessage,
    updateClients
};
enum ServerType
{
    srvDefaultPHP,
    srvTCPJava,
    srvTCPInHTTPJava,
    srvTCPQt,
    srvTCPInHTTPQt
};
class ANetworkInterface :public ANetwork::ANetworkAccessManager
{
    Q_OBJECT
public:
    ANetwork::ATCPClient* tcpclient;
    ServerType srvtype;
    ANetworkInterface();
    ~ANetworkInterface();
    void post(QString post, int typ);
    void post(ACore::RecursionArray post, int typ);
    int ReplyType;
public slots:
    void ReadCliented(QString read);
signals:
    void InterfaceRead(ANetworkReply s);
};
extern ProgramStatus isStart;
struct AChatRoom
{
	QString Name;
	int CreatedID;
    int KomID,endLS;
    bool isOpen,isDostupe;
	QList<int> ClientList;
    QList<PrivateMessage> messages;
    bool operator ==(AChatRoom h)
	{
		if(KomID==h.KomID) return true;
		else return false;
	}
};
struct UniKey
{
	QString key;
	QString StringID;
	QString CookieCode;
	bool operator ==(UniKey h)
	{
		if(StringID==h.StringID) return true;
		else return false;
	}
    UniKey() {}
    UniKey(QString key1, QString StringID1,QString CookieCode1)
    {
        key=key1;
        StringID=StringID1;
        CookieCode=CookieCode1;
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
struct AMessage
{
    QString text;
    bool isCommand;
};
struct Smile
{
    QString code;
    QString url;
    Smile() {}
    Smile(QString _code,QString _url)
    {
        code=_code;
        url=_url;
    }
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
    bool FullRavno(Client h)
    {
        if(id!=h.id) return false;
        else if(name!=h.name) return false;
        else if(prefix!=h.prefix) return false;
        else if(status!=h.status) return false;
        else if(group!=h.group) return false;
        else return true;
    }
};
extern AAppCore ClusterChat;

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
    ServerType type;
	bool operator ==(AServer h)
	{
		if(url==h.url) return true;
		else return false;
	}
    AServer() {}
    AServer(QString _name,QString _url,QString _region,QString _status,QString _info,ServerType _type)
    {
        name=_name;
        url=_url;
        type=_type;
        region=_region;
        status=_status;
        information=_info;
    }
};

struct Style
{
	QString Main;
	QString Message;
	QString TextMessage;
    QString AdvanceMessage;
	QString Notify;
    QString cmdAraim;
	QString OnlineList;
};
extern ACore::ASettings setings;
extern ACore::ALog logs;
extern AMultimedia::ASound audioNotice;

void SendDialogMessage(QString Text,QString Title="");
#ifdef Q_OS_LINUX
class AChatAudioThread : public QThread
{
    void run();
};
extern AChatAudioThread audioThread;
#endif
class AChat : public ANetworkInterface
{
	Q_OBJECT
protected:
	Client MyClient;
    QList<AMessage> SendLSList;
    QTime SendLSOnTime;
    ANetwork::ATCPClient tcpClient;
	QList<AServer> ServersList;
    QList<Smile> SmilesList;
	QList<Client> ClientList;
    QList<AChatRoom> RoomsList;
	QList<UniKey> UniKeyList;
    QList<ACore::BBCodeRule> BBCodeRules;
	QList<UniClient> UniClientList;
    QString InitServerUrl;
    UniKey MyUniKey;
    QString ReportMessage,SetPath,TCPHost;
    int HistoryNumberLS,TimerTick,TexteCashe,CurrentChatIndex;
    bool isSmiles,isReloadHostory,isCensure,isNoPassMode;
	QTime TimeStart;
	QTimer *timersendls;
	Style Styled;
	QString StylePath;
	Client TimeClient;
    AChatRoom MyKomnata;
	QTimer *timer;
    bool isSendCommand(QString message);
    void WriteServerList(ACore::RecursionArray reply);
    QString OnlinetoHTML(AChatRoom room);
    void SearchNewLS();
    QString RenderMessages();
public:
    enum ChatTypes
    {
        tUnknown,
        tAuth,
        tMessage,
        tGetID,
        tNewLS,
        tChats,
        tDefault,
        tGetServerInfo,
        tExit,
        tGetInfo,
        tSetInfo,
        tCreateRoom,
        tRemoveRoom,
        tUniDeleteAll,
        tGetUngine,
        tServerList,
        tAllNewLS,
        tOnlineList,
        tReg,
        tServerInfo2,
        tDeleteUniKey,
        tServerPixmap,
        tGetMy
    };
	QString GetTextGroup(QString Groups);
	void AddLS(int ClientID,QString msg);
    void DelUniKey(QString key);
	void LSUp();
	void LSDown();
	void ReloadHistory();
	void ReloadAllSMS();
    void UniKeyDeleteAll();
	void SetServer(QString name);
	AServer FindServer(QString name);
    bool ExecCommand(QString message);
	void SetKomnata(int id);
	void SMStoValues(ACore::RecursionArray Map,bool isClear);
	void SendMessage(QString text);
	void SendErrorMessage(QString text);
	QString GetErrorText(int ErrorID);
	UniKey FindUniKey(QString id);
    UniKey currentUniKey();
	void login(QString loginit,QString passit,QString key = "");
    void SendSvrCommand(QString cmd);
	void LoadSettings();
	void CheckBoxUpdate();
    AChatRoom currentRoom();
	bool LoadStyle(QString path);
    AChatRoom FindKomOfIndex(QString id);
    AChatRoom GetRoom(int id);
	Client FindClientOfIndex(QString id);
	Client GetClient(int id);
    AChat(int mode);
	~AChat();
    void RenderSmiles();
	void Registration(QString Login,QString name_and_family, QString Pass,QString EMail);
	void SendLSTimer();
	void SendLS(QString Text);
	void GetServersList();
    Client currentClient();
	void exit();
	void clearlist();
	UniClient GetUniClient(QString key);
	void WriteClients(ACore::RecursionArray Map);
	public slots:
    void getReplyFinished(ANetworkReply reply);
	void updateCaption(); //Таймер сработал
    void slotUpdateLogs();
	void updateCaption2();
    void slotConnected();
    void slotRead(QString read);
};
extern AChat *CluChat;

#endif // ACHAT

