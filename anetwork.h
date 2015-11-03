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
private:
QNetworkAccessManager *Network;
int Type; //Тип запроса
bool isSendPost; //Дебаг и отправленЛиПост
bool isPoste;
QList<AQuest> Posts;
void RealPost(QString posti)
{
   //posti+="&typed="+QString::number(Type);
   qDebug() << "RealPost:"+posti;
   //Server.setRawHeader("Accept-Encoding","gzip");
   Network->post(Server,posti.toLocal8Bit().data());
}
void RealGet(QString geti)
{
    qDebug() << "RealGet:"+geti;
    Network->get(QNetworkRequest(QUrl(geti.toLocal8Bit().data())));
}
signals:
void ARequest(ANetworkReply reply);
void FileFinished(QString text);
public slots:
void getReplyFinished(QNetworkReply*reply)
{

    if(Type==RESERVE_CODE)
    {
        FileFinished(QString::fromUtf8(reply->readAll()));
    }
    else
    {
    ANetworkReply _value;
    _value.TextError=reply->errorString();
    _value.TextReply=QString::fromUtf8(reply->readAll()) ;
    qDebug() << reply->rawHeader("Content-Encoding");
    reply->deleteLater();
    _value.Type=Type;
    qDebug() << "Return:"+_value.TextReply;
    ARequest(_value);
    }
    if(Posts.size()>=1)
    {
        isSendPost=1;
        if(Posts.value(0).isPost)RealPost(Posts.value(0).post);
        else RealGet(Posts.value(0).post);
        Type=Posts.value(0).type;
        Posts.removeAt(0);
    }
    else isSendPost=0;
}

public:
    QNetworkRequest Server;
    bool isDebug;
    ANetwork()
    {
        Network = new QNetworkAccessManager(this);
        connect(Network, SIGNAL(finished(QNetworkReply*)),this, SLOT(getReplyFinished(QNetworkReply*)));
        isSendPost=0;
    }
    ~ANetwork()
    {
        delete Network;
    }
    void DownloadFile(QString url)
    {
        get(url,RESERVE_CODE);
    }
    void SetCookie(QString name,QString value)
    {
        QList<QNetworkCookie> cookies=Network->cookieJar()->cookiesForUrl(Server.url());
        cookies.append(QNetworkCookie(name.toLocal8Bit().data(), value.toLocal8Bit().data()));
        Network->cookieJar()->setCookiesFromUrl(cookies,Server.url());
    }
    QString GetCookie(QString name)
    {
        QList<QNetworkCookie> cookies=Network->cookieJar()->cookiesForUrl(Server.url());
        QNetworkCookie s;
        s.setName(name.toLocal8Bit().data());
        s.setDomain(Server.url().toString());
        return cookies.value(cookies.indexOf(s)).value();
    }
    void ClearCookie(QString url)
    {
        QList<QNetworkCookie> cookies;
        Network->cookieJar()->setCookiesFromUrl(cookies,url);
    }

    void post(QString text, int Typ)
    {
        qDebug() << "Post:"+text;
        if(isSendPost==0) {RealPost(text); Type=Typ;isSendPost=1;}
        else
        {
            AQuest tmp;
            tmp.post=text;
            tmp.type=Typ;
            tmp.isPost=true;
            Posts << tmp;
        }

        //if(Type!=tAuth) if(isDebug)log<< dtime()+ "Post:"+ text;
    }
    void get(QString text, int Typ)
    {

        if(isSendPost==0) {RealGet(text); Type=Typ;isSendPost=1;}
        else
        {
            AQuest tmp;
            tmp.post=text;
            tmp.type=Typ;
            tmp.isPost=false;
            Posts << tmp;
        }
        qDebug() << "Get:"+text;
        //if(Type!=tAuth) if(isDebug)log<< dtime()+ "Get:"+ text;
    }
};

#endif // ANETWORK

