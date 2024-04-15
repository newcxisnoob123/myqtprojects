#ifndef WEATHERTOOL_H
#define WEATHERTOOL_H
#include <QMap>
#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QFile>
class WeatherTool
{

public:
    static void initCityMap()
    {
        //1.读取文件
        QString filePath("D:/Code/QTProjects/cityCode.json");
        QFile file(filePath);
        file.open(QIODevice::ReadOnly|QIODevice::Text);//以文本只读的方式打开文件
        QByteArray json=file.readAll();//全部读取
        file.close();//关闭文件

        //2.解析，写入到map
        QJsonParseError err;
        QJsonDocument doc= QJsonDocument::fromJson(json,&err);
        if(err.error!=QJsonParseError::NoError)//错误
        {
            return ;
        }
        if(!doc.isArray())//不是数组形式
        {
            return ;
        }
        QJsonArray cities=doc.array();
        for(int i=0;i<cities.size();++i)
        {
            QString city=cities[i].toObject().value("name").toString();
            QString cityCode=cities[i].toObject().value("code").toString();
            if(cityCode.size()>0)
            {
                mcityMap.insert(city,cityCode);
            }
        }
    }
    static QString getCityCode(QString cityName)
    {
        if(mcityMap.isEmpty())
        {
            initCityMap();//初始化
        }
       auto it= mcityMap.find(cityName);
       if(it==mcityMap.end())//未找到
       {
           it=mcityMap.find(cityName+"区");//二次查询
       }
       if(it!=mcityMap.end())//说明找到了
       {
           return it.value();
       }
       return "";

    }
    private:
        static QMap<QString,QString> mcityMap;
};
QMap<QString,QString> WeatherTool::mcityMap={};

#endif // WEATHERTOOL_H
