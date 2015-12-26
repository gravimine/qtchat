#include "anetwork.h"
#include "aclientserver.h"
void ANetwork::RealPost(QString posti)
{
    qDebug() <<"RealPost:"+posti;
    Network->post(Server,posti.toLocal8Bit().data());
}
void ANetwork::RealGet(QString geti)
{
	Network->get(QNetworkRequest(QUrl(geti.toLocal8Bit().data())));
}
void ANetwork::getReplyFinished(QNetworkReply*reply)
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
		reply->deleteLater();
		_value.Type=Type;
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
ANetwork::ANetwork()
{
	Network = new QNetworkAccessManager(this);
	connect(Network, SIGNAL(finished(QNetworkReply*)),this, SLOT(getReplyFinished(QNetworkReply*)));
	isSendPost=0;
}
ANetwork::~ANetwork()
{
	delete Network;
}
void ANetwork::downloadFile(QString url)
{
	get(url,RESERVE_CODE);
}
void ANetwork::setCookie(QString name,QString value)
{
	QList<QNetworkCookie> cookies=Network->cookieJar()->cookiesForUrl(Server.url());
	cookies.append(QNetworkCookie(name.toLocal8Bit().data(), value.toLocal8Bit().data()));
	Network->cookieJar()->setCookiesFromUrl(cookies,Server.url());
}
QString ANetwork::getCookie(QString name)
{
	QList<QNetworkCookie> cookies=Network->cookieJar()->cookiesForUrl(Server.url());
	QNetworkCookie s;
	s.setName(name.toLocal8Bit().data());
	s.setDomain(Server.url().toString());
	return cookies.value(cookies.indexOf(s)).value();
}
void ANetwork::clearCookie(QString url)
{
	QList<QNetworkCookie> cookies;
	Network->cookieJar()->setCookiesFromUrl(cookies,url);
}
QList<QNetworkCookie> ANetwork::getCookies(QString url)
{
	return Network->cookieJar()->cookiesForUrl(url);
}

void ANetwork::post(QString text, int Typ)
{
    qDebug() <<"Post:"+text;
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
void ANetwork::get(QString text, int Typ)
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
	//if(Type!=tAuth) if(isDebug)log<< dtime()+ "Get:"+ text;
}

ATcpNetwork::ATcpNetwork()
{
	m_pTcpSocket = new QTcpSocket(this);
	connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
	connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
	connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
	this,         SLOT(slotError(QAbstractSocket::SocketError))
	);
}
void  ATcpNetwork::ConnectToServer(QString url,int port)
{
	m_pTcpSocket->connectToHost(url,port);
}
void ATcpNetwork::ClooseConnect()
{
	m_pTcpSocket->close();
}

ATcpNetwork::ATcpNetwork(const QString strHost,
int nPort)
{
	m_pTcpSocket = new QTcpSocket(this);

	m_pTcpSocket->connectToHost(strHost, nPort);
	connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
	connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
	connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
	this,         SLOT(slotError(QAbstractSocket::SocketError))
	);
}
void ATcpNetwork::post(QString text, int Typ)
{
	if(isSendPost==0) { m_pTcpSocket->write(text.toLocal8Bit()); Type=Typ;isSendPost=1;}
	else
	{
		AQuest tmp;
		tmp.post=text;
		tmp.type=Typ;
		tmp.isPost=true;
		Posts << tmp;
	}
}
void ATcpNetwork::slotReadyRead()
{
	ANetworkReply _value;
	_value.TextError="Unkown Error";
	_value.TextReply=QString::fromUtf8(m_pTcpSocket->readAll());
	_value.Type=Type;
	ARequestTcp(_value);
	if(Posts.size()>=1)
	{
		isSendPost=1;
		m_pTcpSocket->write(Posts.value(0).post.toLocal8Bit());
		Type=Posts.value(0).type;
		Posts.removeAt(0);
	}
	else isSendPost=0;

}
void ATcpNetwork::slotError(QAbstractSocket::SocketError err)
{
	QString strError =
	"Error: " + (err == QAbstractSocket::HostNotFoundError ?
	"Хост не найден" :
	err == QAbstractSocket::RemoteHostClosedError ?
	"Сервер закрыл соеденение" :
	err == QAbstractSocket::ConnectionRefusedError ?
	"The connection was refused." :
	QString(m_pTcpSocket->errorString())
	);
	ANetworkReply _value;
	_value.TextError=strError;
	_value.TextReply="";
	_value.Type=Type;
	ARequestTcp(_value);
}
void ATcpNetwork::slotConnected()
{
}
