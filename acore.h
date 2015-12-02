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
void AAppCore::SendM(QString text)
    {
        MessageBoxNumber++;
        if(MessageBoxNumber>MAX_MESSAGE_BOX)
        {
            //Коментарий  сохранен в файле
            //Не сохранен
            qDebug() << text;
            return;
        }
        QMessageBox* pmbx =
                        new QMessageBox(QMessageBox::NoIcon,ProgramName,
                        text
                        );
        pmbx->exec();
        delete pmbx;
        MessageBoxNumber--;
    }
    void AAppCore::Error(QString text)
    {
        qDebug() << "Критическая ошибка: "+text;
        QMessageBox* pmbx =
                        new QMessageBox(QMessageBox::Critical,ProgramName+" fatal error",
                        text
                        );
        pmbx->exec();
        delete pmbx;
    }
    bool AAppCore::MessageQuest(QString text)
    {
        qDebug() << "Вопрос: "+text;
        QMessageBox* pmbx =
                            new QMessageBox(ProgramName,
                            text,
                            QMessageBox::Information,
                            QMessageBox::Yes,
                            QMessageBox::No,
                            QMessageBox::Cancel | QMessageBox::Escape);
        int n = pmbx->exec();
        delete pmbx;
        if (n == QMessageBox::Yes)return true;
        else return false;
    }

    void AAppCore::SetProgramName(QString name)
    {
        ProgramName=name;
    }
    AAppCore::AAppCore()
    {
        MessageBoxNumber=0;
        ProgramName="NULL";
    }
    AAppCore::~AAppCore()
    {

    }
    AAppCore::AAppCore(QString ProgName)
    {
        MessageBoxNumber=0;
        ProgramName=ProgName;
    }
class Sleeper: public QThread
{
public:
    static void msleep(int ms)
    {
        QThread::msleep(ms);
    }
};
QString html_find(QString htmlcode,QString sMin,QString sMax, int start=0)
{
    QString result;
    int iMin,iMax;
    iMin=htmlcode.indexOf(sMin,start)+sMin.size();
    iMax=htmlcode.indexOf(sMax,iMin);
    for(int i=iMin;i<iMax;i++) result+=htmlcode[i];
    return result;
}
QString html_find_s(QString htmlcode,QString html, int start=0)
{
    QString result;
    int iMin,iMax;
    QString sMax,sMin;
    sMin="<"+html+">";
    sMax="</"+html+">";
    iMin=htmlcode.indexOf(sMin,start)+sMin.size();
    iMax=htmlcode.indexOf(sMax,iMin);
    for(int i=iMin;i<iMax;i++) result+=htmlcode[i];
    return result;
}
QStringList splitStringArgs(QString value)
{
    QString _value;
    QStringList ReturnValue;
    bool isBlock=false;
    for(int i=0;i<value.size();i++)
    {
        if(value[i]=='\"'){
            if(!isBlock) isBlock=true;
            else isBlock=false;
        }
        else if(value[i]==' ')
        {
            if(!isBlock)
            {
                ReturnValue << _value;
                _value="";
            }
            else _value+=value[i];
        }
        else
        {
            _value+=value[i];
        }
    }
    ReturnValue << _value;
    return ReturnValue;
}
QString QtHtmlRecoder(QString html)
{
    QString result=html_find(html,REPLACE_TEXT_I,"</p>");
    return result;
}
QString SpecialSybmolCoder(QString value,bool isDecode)
{
    if(!isDecode) return value.replace("<","/k0001").replace(">","/k0002");
    else return value.replace("/k0001","<").replace("/k0002",">");
}

void ALog::SaveLog()
    {
        QFile logging;
        logging.setFileName(patch);
        logging.open(QIODevice::Append);
        for(int i=0;i<size();i++)
        {
            QString m=value(i)+"\n";
            logging.write(m.toLocal8Bit());
        }
        logging.close();
        clear();
    }
    QString ALog::toString()
    {
        QString result;
        for(int i=0;i<size();i++)
        {
            result+=value(i)+"\n";
        }
        return result;
    }
    QString ALog::toHTML()
    {
        QString result;
        for(int i=0;i<size();i++)
        {
            result+=value(i)+"<br>";
        }
        return result;
    }
    void ALog::operator <<(QString h)
    {
        append(dtime()+h);
    }
    void ALog::addInfo(QString h)
    {
        append("[info]"+dtime()+h);
    }
    void ALog::addError(QString h)
    {
        append("[error]"+dtime()+h);
    }
    void ALog::SetFile(QString data)
    {
        patch=data;
    }
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

ASettings::ASettings(QString patch,ArrayFormates format)
    {
        file=patch;
        FileFormat=format;
    }

    void ASettings::LoadSettings()
    {
        QFile stream;
        stream.setFileName(file);
        stream.open(QIODevice::ReadOnly);
        switch(FileFormat)
        {
        case CfgFormat:
        {
            fromCfgFormat(stream.readAll());
            break;
        }
        case YumFormat:
        {
            fromYumFormat(stream.readAll());
            break;
        }
        }
    }
    void ASettings::SaveSettings()
    {
        QFile stream;
        stream.setFileName(file);
        stream.open(QIODevice::WriteOnly);
        switch(FileFormat)
        {
        case CfgFormat:
        {
            stream.write(toCFGFormat().toLocal8Bit());
            break;
        }
        case YumFormat:
        {
            stream.write(toYUMFormat().toLocal8Bit());
            break;
        }
        }
    }
QString dtime()
{
    QTime time=QTime::currentTime();
    QDate date=QDate::currentDate();
    QString datatime;
    datatime.sprintf("[%d.%d.%d][%d:%d:%d][%d]",date.day(),date.month(),date.year(),time.hour(),time.minute(),time.second(),time.msec());
    return datatime;
}
QString timeEx(QTime starture)
{
    QTime time=QTime::currentTime();
    int second=time.second()-starture.second();
    int minutes=time.minute()-starture.minute();
    int hour=time.hour()-starture.hour();
    QString result;
    if(hour>0) result+=QString::number(hour)+"h";
    if(minutes>0) result+=QString::number(minutes)+" min";
    if(second>0) result+=QString::number(second)+" s";
    return result;
}

QString timeEx(int second, int minutes=0,int hour=0)
{
    QTime time=QTime::currentTime();
    QString result;
    int oum=time.minute()*60+time.second()+time.hour()*60*60;
    int ouk=second+minutes*60+hour*60*60;
    int our=oum-ouk;
    int tmp=our/60;
         int ahour=tmp/60;
         int amin=GetOstatok(tmp,60);
         int asec=GetOstatok(our,60);
         if(ahour>0) result+=QString::number(ahour)+"h";
         if(amin>0) result+=QString::number(amin)+" min";
         if(asec>0) result+=QString::number(asec)+" s";
    return result;
}


QString dataEx(QDate starture)
{
    QDate time=QDate::currentDate();
    int year=time.year()-starture.year();
    int month=time.month()-starture.month();
    int day=time.day()-starture.day();
    QString result;
    if(year>0) result+=QString::number(year)+"year ";
    if(month>0) result+=QString::number(month)+"m ";
    if(day>0) result+=QString::number(day)+"d ";
    return result;
}
QString dataEx(int year,int month,int day)
{
    QDate time=QDate::currentDate();
    year=time.year()-year;
    month=time.month()-month;
    day=time.day()-day;
    QString result;
    if(year>0) result+=QString::number(year)+"year ";
    if(month>0) result+=QString::number(month)+"m ";
    if(day>0) result+=QString::number(day)+"d ";
    return result;
}
QString dataTimeEx(int second, int minutes=0,int hour=0,int year=0,int month=0,int day=0)
{
    QString result;
    QDateTime timedate;
    QDate date; date.setDate(year,month,day);
    QTime time; time.setHMS(hour,minutes,second);
    timedate.setDate(date);
    timedate.setTime(time);
    QDateTime datatime;datatime=QDateTime::currentDateTime();
    int our=timedate.secsTo(datatime);
    int tmp=our/60;
         int ahour=tmp/60;
         int amin=GetOstatok(tmp,60);
         int asec=GetOstatok(our,60);

    if(ahour/24>0) result+=QString::number(ahour/24)+"d ";
    if(GetOstatok(ahour,24)>0) result+=QString::number(GetOstatok(ahour,24))+"h ";
    if(amin>0) result+=QString::number(amin)+"min ";
    if(asec>0) result+=QString::number(asec)+"s ";


    return result;
}

QString DeleteSpaceStart(QString str)
{
    int deleteSize=0;
    for(int i=0;str.toLocal8Bit()[i]==' ';i++) deleteSize++;
    return str.remove(0,deleteSize);
}

QString DeleteQuotes(QString str)
{
    if(str[0]=='"' && str[str.size()-1]=='"')
    return str.remove(0,1).remove(str.size()-2,1);
    else return str;
}



QString RecursionArray::_toHTMLTegsFormat(RecursionArray Map)
    {
        QString ReturnValue;
        int i=0;
        QList<QString> keys=Map.keys();
        while(i<keys.size())
        {
            ReturnValue+="<"+keys.value(i)+">";
            QString tmp= _toHTMLTegsFormat(Map.value(keys.value(i)).toMap());
            if(tmp.isEmpty()) ReturnValue+=VariantToString(Map.value(keys.value(i)));
            else ReturnValue+=tmp;
            ReturnValue+="</"+keys.value(i)+">";
            i++;
        }
        return ReturnValue;
    }
    QString RecursionArray::_toYUMFormat(RecursionArray Map,QString Tabulator)
    {
        QString ReturnValue;
        int i=0;
        QList<QString> keys=Map.keys();
        while(i<keys.size())
        {
            ReturnValue+="\n"+Tabulator+keys.value(i)+":";
            QString tmp= _toYUMFormat(Map.value(keys.value(i)).toMap(),Tabulator+" ");
            if(tmp.isEmpty()) ReturnValue+=VariantToString(Map.value(keys.value(i)));
            else ReturnValue+=tmp;
            i++;
        }
        return ReturnValue;
    }
    QString RecursionArray::_toCFGFormat(RecursionArray Map)
    {
        QString ReturnValue;
        int i=0;
        QList<QString> keys=Map.keys();
        while(i<keys.size())
        {
            QString TypeValue;
            QVariant Value=Map.value(keys.value(i));
            if(Value.type()==QVariant::String) TypeValue="S";
            else if(Value.type()==QVariant::Int) TypeValue="I";
            else if(Value.type()==QVariant::Bool) TypeValue="B";
            else
            {
                i++;
                continue;
            }

            QString tmp= _toCFGFormat(Map.value(keys.value(i)).toMap());
            if(tmp.isEmpty())
            {
                ReturnValue+="\n"+TypeValue+":"+keys.value(i)+"=";
                ReturnValue+=VariantToString(Map.value(keys.value(i)));
            }
            else
            {
                ReturnValue+="\n"+keys.value(i)+" {\n"+tmp+"\n}";
            }
            i++;
        }
        return ReturnValue;
    }
QString RecursionArray::printList(QList<QVariant> List)
    {
        QString ReturnValue="[";
        QVariant Value0=List.value(0);
        if(Value0.type()==QVariant::String) if(!Value0.toString().isEmpty()) ReturnValue+=Value0.toString();
        for(int i=1;i<List.size();i++)
        {
            QVariant Value=List.value(i);
            if(Value.type()==QVariant::String) if(!Value.toString().isEmpty())
                ReturnValue+=","+Value.toString();
        }
        ReturnValue+="]";
        return ReturnValue;
    }
QString RecursionArray::printMap(RecursionArray Map,QString NameMap,QString Tabulator)
    {
        QString ReturnValue;
        int i=0;
        QList<QString> keys=Map.keys();
        if(keys.size()<=0) return "";
        ReturnValue+=Tabulator+"QMap("+NameMap+")\n"+Tabulator+"{\n";
        while(i<keys.size())
        {
            QString NameKey=keys.value(i);
            QVariant tmp=Map.value(NameKey);
            if(tmp.type()!=QVariant::Map) ReturnValue+=Tabulator+"   ["+NameKey+"] = ";
            if(tmp.type()==QVariant::String) ReturnValue+= Map.value(NameKey).toString();
            else if(tmp.type()==QVariant::ByteArray) ReturnValue+= QString(Map.value(NameKey).toByteArray());
            else if(tmp.type()==QVariant::List) ReturnValue+=printList(Map.value(NameKey).toList());
            else if(tmp.type()==QVariant::Int) ReturnValue+=QString::number(Map.value(NameKey).toInt());
            else if(tmp.type()==QVariant::Double) ReturnValue+=QString::number(Map.value(NameKey).toDouble());
            else if(tmp.type()==QVariant::Bool)
            {
                if(tmp.toBool()) ReturnValue+="true";
                else ReturnValue+="false";
            }
            else if(tmp.type()==QVariant::Map) {
                ReturnValue+=printMap(Map.value(NameKey).toMap(),NameKey,Tabulator+"   ");
            }
            else ReturnValue+="Unkown()";
            ReturnValue+="\n";
            i++;
        }
        ReturnValue+=Tabulator+"}";
        return ReturnValue;
    }
QString RecursionArray::VariantToString(QVariant tmp)
    {
        if(tmp.type()==QVariant::String) return  tmp.toString();
        else if(tmp.type()==QVariant::ByteArray) return QString(tmp.toByteArray());
        else if(tmp.type()==QVariant::List) return printList(tmp.toList());
        else if(tmp.type()==QVariant::Int) return QString::number(tmp.toInt());
        else if(tmp.type()==QVariant::Double) return QString::number(tmp.toDouble());
        else if(tmp.type()==QVariant::Bool)
        {
            if(tmp.toBool()) return "true";
            else return "false";
        }
        else if(tmp.type()==QVariant::Map) {
            return printMap(tmp.toMap());
        }
        else return "Unkown()";
    }
    QMap<QString,QVariant> RecursionArray::fromYumFormat(QString yum,QString level, bool isReturn)
    {
        QStringList fromBR=yum.split("\n");
        QMap<QString,QVariant> ReturnMap;
        for(int i=0;i<fromBR.size();i++)
        {
            QString ValueString=fromBR.value(i);
            if(level.size()>0) ValueString.remove(0,level.size());
            if(ValueString.toLocal8Bit()[0]=='#') continue;
            int position=ValueString.indexOf(":");
            if(position<=0) continue;
            QString NameValue=ValueString.mid(0,position);
            QString Value=ValueString.mid(position+1);
            if(!Value.isEmpty())
            {
                 if(isReturn) ReturnMap[NameValue]=Value;
                 else operator [](NameValue)=Value;
            }
            else
            {
                int unusedsize=0;bool stop=true; QString sendString,nextLevel;
                nextLevel=level+ " ";
                while (stop) {

                    if(fromBR.value(i+unusedsize+1).mid(0,nextLevel.size())==nextLevel){
                        unusedsize++;
                        sendString+=fromBR.value(i+unusedsize)+"\n";
                    }
                    else stop=false;
                }
                QMap<QString,QVariant> ValueMap=fromYumFormat(sendString,nextLevel,true);
                if(isReturn) ReturnMap[NameValue]=ValueMap;
                else operator [](NameValue)=ValueMap;
                i+=unusedsize;
            }
        }
        return ReturnMap;
    }
    QMap<QString,QVariant> RecursionArray::fromCfgFormat(QString yum, bool isReturn)
    {
        QStringList fromBR=yum.split("\n");
        QMap<QString,QVariant> ReturnMap;
        for(int i=0;i<fromBR.size();i++)
        {
            QString ValueString=fromBR.value(i);
            ValueString=DeleteSpaceStart(ValueString);
            if(ValueString[0]=='#') continue;
            int position=ValueString.indexOf("=");
            if(position<=0 && ValueString.indexOf("{")<=0 && ValueString.indexOf("}")<=0) continue;
            QString NameValue=ValueString.mid(0,position);
            QString tmp=ValueString.mid(position+1);
            QStringList ListValued;
            ListValued << NameValue.mid(0,1);
            ListValued << NameValue.mid(2);
            ListValued << ValueString.mid(position+1);
            NameValue=DeleteQuotes(ListValued.value(1));
            QVariant Value;
            if(ListValued.value(0)=="I") Value=ListValued.value(2).toInt();
            else if(ListValued.value(0)=="S") {if(!tmp.isEmpty()) Value=ListValued.value(2);}
            else if(ListValued.value(0)=="B")
            {
                if(ListValued.value(2).toLower().indexOf("false")>=0) Value=false;
                else if(ListValued.value(2).toLower().indexOf("true")>=0) Value=true;
            }
            if(ValueString.indexOf("{")<=0)
            {
                 if(isReturn) ReturnMap[NameValue]=Value;
                 else operator [](NameValue)=Value;
            }
            else
            {

                int unusedsize=0;bool stop=true; QString sendString;
                while (stop) {
                    QString x=fromBR.value(i+unusedsize+1);
                    if(x.indexOf("}")>=0 || unusedsize>fromBR.size()-i) stop=false;
                    else {
                        unusedsize++;
                        sendString+=fromBR.value(i+unusedsize)+"\n";
                    }
                }

                QMap<QString,QVariant> ValueMap=fromCfgFormat(sendString,true);
                QString sNameValue=DeleteQuotes(ValueString.remove("{").split(" ").value(0));
                qDebug() << ValueString;
                if(isReturn) ReturnMap[sNameValue]=ValueMap;
                else operator [](sNameValue)=ValueMap;
                i+=unusedsize;
            }
        }
        return ReturnMap;
    }
    RecursionArray::RecursionArray(QMap<QString,QVariant> h)
    {
        QMap::operator =(h);
    }
    RecursionArray::RecursionArray()
    {
    }
    QMap<QString,QVariant> RecursionArray::fromHTMLTegsFormat(QString value, bool isReturn)
    {
       QMap<QString,QVariant> ReturnValue; //Возвращаемый массив
       int i=0;
       while(i<value.size()) //Главный цикл
        {
            int iMin=value.indexOf("<",i); //Поиск символа <
            if(iMin<0) break;
            int iMax=value.indexOf(">",iMin); //Поиск символа >
            if(iMax<0) break;
            QString NameValue;//Имя переменной
            NameValue=value.mid(iMin+1,iMax-iMin-1);
            int nextiMin=value.indexOf("<"+NameValue+">",iMax); //Поиск <ИмяПеременной>
            int nMax=value.indexOf("</"+NameValue+">",iMax); //Поиск закрывающего тега
            if(nextiMin!=-1) if(nextiMin<nMax) //Если существует еще по крайней мере один <ИмяПеременной>
            {
                int numNextiMin=0; //Колличество включений <ИмяПеременной>
                while(nextiMin!=-1 && nextiMin<nMax) //Получаю колличество включений
                {nextiMin=value.indexOf("<"+NameValue+">",nextiMin+1);
                numNextiMin+=1; }
                while(numNextiMin!=0) //Использую колличество включений для определения последнего закрывающего тега
                {nMax=value.indexOf("</"+NameValue+">",nMax+1);
                numNextiMin-=1;}
            }
             if(nMax<0) //Если nMax невалидный
            {
                i=iMax+2;
            }
            else {
            QString sValue; //Значение переменной
            sValue=value.mid(iMax+1,nMax-iMax-1);
            QMap<QString,QVariant> temp=fromHTMLTegsFormat(sValue,true); //Рекурсия

            if(sValue.isEmpty() || NameValue.isEmpty()) {
                int tmp=iMax-iMin;
                i=nMax+tmp;
                continue; }
            if(temp.isEmpty()) //Если рекурсия не нашла других значений переменной
                if(isReturn) ReturnValue[NameValue]=sValue;
                else operator [](NameValue)=sValue; //Запись элемента в Map
            else
                if(isReturn) ReturnValue[NameValue]=temp;
                else operator [](NameValue)=temp; //Запись элемента в Map
            int tmp=iMax-iMin; //Переход к следующему
            i=nMax+tmp;}
        }
        return ReturnValue; //Возврат готового Map
    }
    QString RecursionArray::toHTMLTegsFormat()
    {
        return _toHTMLTegsFormat(*this);
    }
    QString RecursionArray::toYUMFormat()
    {
        return _toYUMFormat(*this);
    }
    QString RecursionArray::toCFGFormat()
    {
        return _toCFGFormat(*this);
    }
    QString RecursionArray::print()
    {
        return printMap(*this);
    }

}
#endif // ACORE

