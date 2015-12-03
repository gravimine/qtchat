#ifndef ACHAT
#define ACHAT
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
#define ADD_DEBUG log<<
#define INIT_CLIENT "Qt"
#define INIT_VERSION "8.1"
#define API_VERSION "2.3"

#define IS_DEBUG false
#define TIMER_SENDLS 300
#define SENSORE_STRING "[цензура]"
#define foreash(n,mas) for(int n=0;n<mas.size();n++)
#define EXTRA_NETWORK false
#define DEFAULT_TEXT_TEXTBROWSER "<center><br><br><br><hr>Для начала работы откройте нужную комнату в списке справа -><br>Или создайте новую в \"личном кабинете\"<hr>"
static bool isStart;

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
static ACore::AAppCore ClusterChat("ClusterChat");

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

void SendDialogMessage(QString Text,QString Title="");
class AChat : public ANetwork
{
	Q_OBJECT
private:
	int KomnataID;
	ACore::ALog log;
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
	QTime timer3;
	QTimer *timer;
public:
	bool isSendCommand(QString message);
	//void post(QString text, int Typ);
	QString GetTextGroup(QString Groups);
	void AddLS(int ClientID,QString msg);
	void WriteServerList(ACore::RecursionArray reply);
	void LSUp();
	void LSDown();
	void ReloadHistory();
	void ReloadAllSMS();
	QString OnlinetoHTML(ACore::RecursionArray Map);
	void SetServer(QString name);
	AServer FindServer(QString name);
	bool SendCommand(QString message);
	void SetKomnata(int id);
	void SMStoValues(ACore::RecursionArray Map,bool isClear);
	void SendMessage(QString text);
	void SendErrorMessage(QString text);
	QString GetErrorText(int ErrorID);
	UniKey FindUniKey(QString id);
	void login(QString loginit,QString passit,QString key = "");
	void GetFileErrors();
	void LoadSettings();
	void CheckBoxUpdate();
	bool LoadStyle(QString path);
	AChate FindKomOfIndex(QString id);
	AChate GetRoom(int id);
	Client FindClientOfIndex(QString id);
	Client GetClient(int id);
	void functionA();
	AChat();
	~AChat();
	QString SencureString(QString str);
	ACore::ASettings *setings;
	void Registration(QString Login,QString name_and_family, QString Pass,QString EMail);
	void SendLSTimer();
	void SendLS(QString Text);
	void GetServersList();
	Client GetMyClient();
	void exit();
	void clearlist();
	UniClient GetUniClient(QString key);
	QString Reformat(QString TEXT);
	void WriteClients(ACore::RecursionArray Map);
	QString ListToHTML();
	int GetKomnata();
	public slots:
	void getReplyFinished(ANetworkReply reply);
	void updateCaption(); //Таймер сработал
	void updateCaption2();
};
static AChat *CluChat;
static AChate MyKomnata;
#endif // ACHAT

