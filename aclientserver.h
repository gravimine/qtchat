#ifndef ACLIENTSERVER
#define ACLIENTSERVER
#include <QTcpSocket>
#include <QTime>
#include <QString>
#include <QByteArray>
#include <anetwork.h>
class ATcpNetwork : public ANetwork {
Q_OBJECT
protected:
    QTcpSocket* m_pTcpSocket;
    quint16     m_nNextBlockSize;
    int Type; //Тип запроса
    bool isSendPost;
    bool isPoste;
    QList<AQuest> Posts;
public:
    ATcpNetwork()
    {
        m_pTcpSocket = new QTcpSocket(this);
        connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
        connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
        connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                this,         SLOT(slotError(QAbstractSocket::SocketError))
               );
    }
    void  ConnectToServer(QString url,int port)
    {
        m_pTcpSocket->connectToHost(url,port);
    }
    void ClooseConnect()
    {
        m_pTcpSocket->close();
    }

    ATcpNetwork(const QString strHost,
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
    void post(QString text, int Typ)
    {
        qDebug() << "Post:"+text;
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
public slots:
    void slotReadyRead()
    {
        ANetworkReply _value;
        _value.TextError="Unkown Error";
        _value.TextReply=QString::fromUtf8(m_pTcpSocket->readAll());
        _value.Type=Type;
        qDebug() << "Return:"+_value.TextReply;
        ARequestTcp(_value);
        if(Posts.size()>=1)
        {
            isSendPost=1;
            m_pTcpSocket->write(Posts.value(0).post.toLocal8Bit());
            Type=Posts.value(0).type;
            Posts.removeAt(0);
        }
        else isSendPost=0;
        qDebug() << "Read";

    }
    void slotError(QAbstractSocket::SocketError err)
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
    void slotConnected()
    {
        qDebug() << "Connect";
    }
signals:
void ARequestTcp(ANetworkReply reply);
};








#endif // ACLIENTSERVER

