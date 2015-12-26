#ifndef ANETWORK
#define ANETWORK
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QList>
#include <QString>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#define RESERVE_CODE 1024
struct AQuest
{
	QString post;
	int type;
	bool isPost;
};
struct ANetworkReply
{
	int Type;
	QString TextReply;
	QString TextError;
};

class ANetwork : public QObject
{
	Q_OBJECT
protected:
	QNetworkAccessManager *Network;
	int Type; //Тип запроса
	bool isSendPost; //Дебаг и отправленЛиПост
	bool isPoste;
	QList<AQuest> Posts;
	void RealPost(QString posti);
	void RealGet(QString geti);
signals:
	void ARequest(ANetworkReply reply);
	void FileFinished(QString text);
	public slots:
	void getReplyFinished(QNetworkReply*reply);

public:
	QNetworkRequest Server;
	bool isDebug;
	ANetwork();
	~ANetwork();
	void downloadFile(QString url);
	void setCookie(QString name,QString value);
	QString getCookie(QString name);
	void clearCookie(QString url);
	QList<QNetworkCookie> getCookies(QString url);
	void post(QString text, int Typ);
	void get(QString text, int Typ);
};



#endif // ANETWORK
