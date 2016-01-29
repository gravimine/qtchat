#ifndef ATCPCLIENT_H
#define ATCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "anetwork.h"
class ATCPClient : public QObject
{
    Q_OBJECT
protected:
    QTcpSocket* socket;
public:
    ATCPClient();
    ~ATCPClient();
    void connectToHost(QString Host,int port);
    void Send(QString data);
    QTcpSocket* currentSocket();
signals:
    void signalConnected();
    void signalRead(QString read);
public slots:
    void slotConected();
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError error);
};

class ATcpInHttpInterface
{
public:
    QString UserAgent;
    QString Accept;
    QString Host;
    QString AcceptEncoding;
    QString Connection;

};


#endif // ATCPCLIENT_H
