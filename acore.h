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
#include "amath.h"
#define MAX_MESSAGE_BOX 2
#define REPLACE_TEXT_I "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
//#define REPLACE_TEXT_II "<body style=\" font-family:\'MS Shell Dlg 2\'; font-size:8.25pt; font-weight:400; font-style:normal;\">"
namespace ACore
{
QString dtime();
class AAppCore
{
public:
    void SendM(QString text)
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
    void Error(QString text)
    {
        qDebug() << "Критическая ошибка: "+text;
        QMessageBox* pmbx =
                        new QMessageBox(QMessageBox::Critical,ProgramName+" fatal error",
                        text
                        );
        pmbx->exec();
        delete pmbx;
    }
    bool MessageQuest(QString text)
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
    void SetProgramName(QString name)
    {
        ProgramName=name;
    }
    AAppCore()
    {
        MessageBoxNumber=0;
        ProgramName="NULL";
    }
    ~AAppCore()
    {

    }
    AAppCore(QString ProgName)
    {
        MessageBoxNumber=0;
        ProgramName=ProgName;
    }
    QStringList splitStringArgs(QString value)
    {
        QString _value;
        QStringList ReturnValue;
        bool isBlock;
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
    QMap<QString,QVariant> splitStringHTML(QString value)
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
            //NameValue.reserve(iMax-iMin); //Выделение памяти
            NameValue=value.mid(iMin+1,iMax-iMin-1);
            //qDebug() <<value.mid(iMin+1,iMax-iMin-1);
            //for(int j=iMin+1;j<iMax;j++) NameValue+=value[j]; //Заполнение имени переменной
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
            //sValue.reserve(nMax-iMax); //Выделение памяти
            sValue=value.mid(iMax+1,nMax-iMax-1);
            //for(int j=iMax+1;j<nMax;j++) sValue+=value[j]; //Заполнение значения переменной
            QMap<QString,QVariant> temp=splitStringHTML(sValue); //Рекурсия
            if(sValue.isEmpty() || NameValue.isEmpty()) {
                int tmp=iMax-iMin;
                i=nMax+tmp;
                continue; }
            if(temp.isEmpty()) //Если рекурсия не нашла других значений переменной
            ReturnValue[NameValue] = sValue; //Запись элемента в Map
            else
            ReturnValue[NameValue] = temp; //Запись элемента в Map
            int tmp=iMax-iMin; //Переход к следующему
            i=nMax+tmp;}
        }
        return ReturnValue; //Возврат готового Map
    }
    QString printMap(QMap<QString,QVariant> Map,QString NameMap="",QString Tabulator="")
    {
        QString ReturnValue;
        int i=0;
        QList<QString> keys=Map.keys();
        if(keys.size()<=0) return "";
        ReturnValue+="\n"+Tabulator+"QMap("+NameMap+")\n"+Tabulator+"(\n";
        while(i<keys.size())
        {
            QString NameKey=keys.value(i);
            QVariant tmp=Map.value(NameKey);
            if(tmp.type()!=QVariant::Map) ReturnValue+=Tabulator+"\t["+NameKey+"] = ";
            if(tmp.type()==QVariant::String) ReturnValue+= Map.value(NameKey).toString();
            else if(tmp.type()==QVariant::Map) {
                ReturnValue+=printMap(Map.value(NameKey).toMap(),NameKey,Tabulator+"\t");
            }
            else ReturnValue+="Unkown()";
            ReturnValue+="\n";
            i++;
        }
        ReturnValue+=Tabulator+")";
        return ReturnValue;
    }
    QString UnsplitStringHTML(QMap<QString,QVariant> Map)
    {
        QString ReturnValue;
        int i=0;
        QList<QString> keys=Map.keys();
        while(i<keys.size())
        {
            ReturnValue+="<"+keys.value(i)+">";
            QString tmp= UnsplitStringHTML(Map.value(keys.value(i)).toMap());
            if(tmp.isEmpty()) ReturnValue+=Map.value(keys.value(i)).toString();
            else ReturnValue+=tmp;
            ReturnValue+="</"+keys.value(i)+">";
            i++;
        }
        return ReturnValue;
    }
    QString QtHtmlRecoder(QString html)
    {
        //QString result=html_find(html,REPLACE_TEXT_II,"</body>").replace(REPLACE_TEXT_I,"").replace("</p>","");
        QString result=html_find(html,REPLACE_TEXT_I,"</p>");
        return result;
    }
    QString SpecialSybmolCoder(QString value,bool isDecode)
    {
        if(!isDecode) return value.replace("<","\t0001").replace(">","\t0002");
        else return value.replace("\t0001","<").replace("\t0002",">");
    }

private:
    int MessageBoxNumber;
    QString ProgramName;
};
class Sleeper: public QThread
{
public:
    static void msleep(int ms)
    {
        QThread::msleep(ms);
    }
};


template <typename T1, typename T2>
class ATable
{
public:
    T2 value(T1 SkeyH,T1 SkeyV)
    {

        if(!keyH.contains(SkeyH)) return T2();
        if(!keyV.contains(SkeyV)) return T2();
        Intx2 S=GetPosition(SkeyH,SkeyV);
        return Values.value(S.int1).value(S.int2);
    }
    void AddKeyH(T1 SKeyH)
    {
        if(!keyH.contains(SKeyH)) keyH << SKeyH;
        //if(!keyV.contains(SKeyV)) keyV << SkeyV;
    }
    void AddKeyV(T1 SKeyV)
    {
        if(!keyV.contains(SKeyV)) keyV << SKeyV;
    }
    void SetValue(int h,int v,T2 value)
    {
        QList<T1> HTmp=Values.value(h);
        HTmp.replace(v,value);
        Values.replace(h,HTmp);

    }
    void SetValue(T1 SkeyH,T1 SkeyV,T2 value)
    {
         Intx2 S=GetPosition(SkeyH,SkeyV);
        QList<T1> HTmp=Values.value(S.int1);
        if(HTmp.size()>S.int2)HTmp.replace(S.int2,value);
        else HTmp << value;
        if(Values.size()>S.int2)Values.replace(S.int1,HTmp);
        else Values << HTmp;
    }
private:
    QList<T1> keyV;
    QList<T1> keyH;
    QList< QList<T2> > Values;
    struct Intx2
    {
        int int1;
        int int2;
    };
    Intx2 GetPosition(T1 H,T1 V)
    {
        Intx2 ReturnValue;
        for(int i;i<keyH.size();i++)
        {
            if(keyH.value(i)==H)
            {
                ReturnValue.int1=i;
                break;
            }
        }
        for(int i;i<keyV.size();i++)
        {
            if(keyV.value(i)==V)
            {
                ReturnValue.int2=i;
                break;
            }
        }
        return ReturnValue;
    }
};








class ALog : public QStringList
{
public:
    void SaveLog()
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
    QString toString()
    {
        QString result;
        for(int i=0;i<size();i++)
        {
            result+=value(i)+"\n";
        }
        return result;
    }
    QString toHTML()
    {
        QString result;
        for(int i=0;i<size();i++)
        {
            result+=value(i)+"<br>";
        }
        return result;
    }
    void operator <<(QString h)
    {
        append(dtime()+h);
    }

    void SetFile(QString data)
    {
        patch=data;
    }
private:
    QString patch;
};

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

class ASettings
{
public:
    QSettings *Main;
    void AddKey(QString _key,QString _stdtext)
    {
        ASett temp;
        temp.key=_key;
        temp.value_std=_stdtext;
        temp.value=_stdtext;
        config << temp;
    }
    ASettings(QString patch)
    {
        Main=new QSettings(patch,QSettings::IniFormat);
    }

    QString GetKey(QString _key)
    {
        QString temp;
        for(int i=0;i<config.size();i++)
        {
            if(config.value(i).key==_key)
            {
                temp=config.value(i).value;
            }
        }
        return temp;
    }
    QString AddGetKey(QString _key,QString _stdvalue)
    {
        AddKey(_key,_stdvalue);
        return Main->value(_key,_stdvalue).toString();
    }

    void SetKey(QString _key,QString _value)
    {
        for(int i=0;i<config.size();i++)
        {
            if(config.value(i).key==_key)
            {
                ASett temp=config.value(i);
                temp.value=_value;
                config.replace(i,temp);
            }
        }
    }

    void LoadSettings()
    {
        for(int i=0;i<config.size();i++)
        {
            SetKey(config.value(i).key,Main->value(config.value(i).key,config.value(i).value_std).toString());
        }
    }
    void toStandart() //По умолчанию
    {
        for(int i=0;i<config.size();i++)
        {
            config.value(i).value=config.value(i).value_std;
        }
    }

    void SaveSettings()
    {
        for(int i=0;i<config.size();i++)
        {
            Main->setValue(config.value(i).key,config.value(i).value.toLocal8Bit());
        }
        Main->sync();
    }

private:
    QList<ASett> config;
};
QString dtime()
{
    QTime time=QTime::currentTime();
    QDate date=QDate::currentDate();
    QString datatime="["+QString::number(date.day())+"."+QString::number(date.month())+"."+QString::number(date.year())+"]";
    datatime+="["+QString::number(time.hour())+":"+QString::number(time.minute())+":"+QString::number(time.second())+"x"+QString::number(time.msec())+"]";
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
}
#endif // ACORE

