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
	ATcpNetwork();
	void  ConnectToServer(QString url,int port);
	void ClooseConnect();
	ATcpNetwork(const QString strHost,
	int nPort);
	void post(QString text, int Typ);
	public slots:
	void slotReadyRead();
	void slotError(QAbstractSocket::SocketError err);
	void slotConnected();
signals:
	void ARequestTcp(ANetworkReply reply);
};
#endif // ACLIENTSERVER

