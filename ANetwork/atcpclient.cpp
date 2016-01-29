#include "atcpclient.h"

ATCPClient::ATCPClient()
{
    socket = new QTcpSocket();
    connect(socket, SIGNAL(connected()), SLOT(slotConected()));
    connect(socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));

}

void ATCPClient::connectToHost(QString Host,int port)
{
    qDebug() << "Conecting to host";
    socket->connectToHost(Host,port);
}
void ATCPClient::slotConected()
{
    signalConnected();
    qDebug() << "Conected to host";
}
void ATCPClient::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
            "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                         "The host was not found." :
                         err == QAbstractSocket::RemoteHostClosedError ?
                         "The remote host is closed." :
                         err == QAbstractSocket::ConnectionRefusedError ?
                         "The connection was refused." :
                         QString(socket->errorString())
                        );
    qDebug() << strError;
}
void ATCPClient::slotReadyRead()
{
    QString a=socket->readAll();
    signalRead(a);
    qDebug() << "Read:"+a;
}
QTcpSocket* ATCPClient::currentSocket()
{
    return socket;
}

void ATCPClient::Send(QString data)
{
    QByteArray  arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_2);
        out << quint16(0)  << data;

        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));

        socket->write(arrBlock);
}
ATCPClient::~ATCPClient()
{
    delete socket;
    qDebug() << "Destroyter";
}
