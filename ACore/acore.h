#ifndef ACORE
#define ACORE
#include <QSettings>
#include <QString>
#include <QList>
#include <QMap>
#include <QFile>
#include <QMessageBox>
#include <QThread>
#include <QByteArray>
#include <QDate>
#include <QDateTime>
#include "amath.h"
#define MAX_MESSAGE_BOX 2
#define REPLACE_TEXT_I "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
#define MapFind(n,Map,keyd) QStringList keyd=Map.keys(); for(int n=0;n<keyd.size();n++)
#define foreash(n,mas) for(int n=0;n<mas.size();n++)
//#define REPLACE_TEXT_II "<body style=\" font-family:\'MS Shell Dlg 2\'; font-size:8.25pt; font-weight:400; font-style:normal;\">"
namespace ACore
{
	enum ArrayFormates
	{
		StdHTMLTagesFormat,
		YumFormat,
		IniFormat,
		CfgFormat,
		ExtraHTMLTagesFormat
	};
	class RecursionArray : public QMap<QString,QVariant>
	{
	private:
		QString _toHTMLTegsFormat(RecursionArray Map);
		QString _toYUMFormat(RecursionArray Map,QString Tabulator="");
		QString _toCFGFormat(RecursionArray Map);
	public:
		static QString printList(QList<QVariant> List);
		static QString printMap(RecursionArray Map,QString NameMap="",QString Tabulator="");
		static QString VariantToString(QVariant tmp);
		QMap<QString,QVariant> fromYumFormat(QString yum,QString level="", bool isReturn=false);
		QMap<QString,QVariant> fromCfgFormat(QString yum, bool isReturn=false);
		RecursionArray(QMap<QString,QVariant> h);
		RecursionArray();
		QMap<QString,QVariant> fromHTMLTegsFormat(QString value, bool isReturn=false);
		QString toHTMLTegsFormat();
		QString toYUMFormat();
		QString toCFGFormat();
		QString print();
	};
	class ALog : public QStringList
	{
	public:
		void SaveLog();
		QString toString();
		QString toHTML();
		void operator <<(QString h);
		void addInfo(QString h);
		void addError(QString h);
		void SetFile(QString data);
	protected:
		QString patch;
	};
	class ASettings : public RecursionArray
	{
	public:
		ASettings(QString patch,ArrayFormates format);
		void LoadSettings();
		void SaveSettings();
	protected:
		QString file;
		ArrayFormates FileFormat;
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
	QString dtime();

	class Sleeper: public QThread
	{
	public:
		static void msleep(int ms)
		{
			QThread::msleep(ms);
		}
	};
	QString html_find(QString htmlcode,QString sMin,QString sMax, int start=0);
	QString html_find_s(QString htmlcode,QString html, int start=0);
	QStringList splitStringArgs(QString value);
	QString QtHtmlRecoder(QString html);
	QString SpecialSybmolCoder(QString value,bool isDecode);


	struct ASett
	{
		QString value;
		QString value_std;
		QString key;
		bool operator ==(ASett h)
		{
			if(key==h.key) return true;
			else return false;
		}
	};
	QString timeEx(QTime starture);

	QString timeEx(int second, int minutes=0,int hour=0);


	QString dataEx(QDate starture);
	QString dataEx(int year,int month,int day);
	QString dataTimeEx(int second, int minutes=0,int hour=0,int year=0,int month=0,int day=0);

	QString DeleteSpaceStart(QString str);

	QString DeleteQuotes(QString str);

}
#endif // ACORE

