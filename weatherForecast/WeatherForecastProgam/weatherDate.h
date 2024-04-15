#ifndef WEATHERDATE_H
#define WEATHERDATE_H
//定义今日的数据
#include <QString>
class Today{
public:
    Today()
    {
        city ="重庆";
        date ="28";
        ymd="2023-7-28";
        wendu = 25;
        type ="多云";
        high = 30;
        low = 18;
        ganmao ="感冒指数";
        shidu = "0%";
        pm25 = 0;
        fx ="南风";
        fl ="2级";
        quality ="无数据";
    }
    QString city; //城市名
    QString date;//日期
    QString ymd; //年月日

    int wendu;//温度
    QString type;//天气类型
    int high; //最高温
    int low; //最低温
    QString ganmao;//感冒指数
    QString shidu;//湿度
    int pm25; //pm2.5
    QString fx;//风向
    QString fl;// 风的等级
    QString quality; //空气质量
};
//定义6天的数据

class Day{
public:
    Day()
    {
        week ="周五";
        date ="29";
        ymd="2023-7-29";
        type ="多云";

        aqi = 0; //空气指数，优

        high = 0;
        low = 0;

        fx ="南风";
        fl ="2级";
    }
    QString week; //星期几
    QString date; //日期
     QString ymd; //年月日
    QString type; //天气类型
    int aqi; //接口
    int high; //最高温
    int low; //最低温
    QString fx;//风向
    QString fl;//风的等级
};
#endif // WEATHERDATE_H
