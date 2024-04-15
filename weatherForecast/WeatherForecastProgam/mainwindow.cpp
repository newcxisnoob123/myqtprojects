#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "weatherDate.h"

#include <QContextMenuEvent>
#include <QDateTime>
#include "weatherTool.h"
#include <QStringList>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //1.
    setWindowFlag(Qt::FramelessWindowHint);//设置窗口无边框
    setFixedSize(width(),height());//固定窗口大小
    //构建右键caidan
    mExitMenu=new QMenu(this);
    mExitACt=new QAction(this);
    mExitACt->setText("退出");
    mExitACt->setIcon(QIcon(":/res/close.png"));
    mExitMenu->addAction(mExitACt);
    connect(mExitACt,&QAction::triggered,this,[=](){
        qApp->quit();//退出窗口
    });

    //2.将控件添加到控件数组
    mDateList<<ui->lb_date0<<ui->lb_date1<<ui->lb_date2<<ui->lb_date3<<ui->lb_date4<<ui->lb_date5; //日期(天) label
    mWeekList<<ui->lb_week0<<ui->lb_week1<<ui->lb_week2<<ui->lb_week3<<ui->lb_week4<<ui->lb_week5;//日期(周) label
    mTypeList<<ui->lb_type0<<ui->lb_type1<<ui->lb_type2<<ui->lb_type3<<ui->lb_type4<<ui->lb_type5;//天气类型 label
    mTypeIconList<<ui->lb_typeIcon0<<ui->lb_typeIcon1<<ui->lb_typeIcon2<<ui->lb_typeIcon3<<ui->lb_typeIcon4<<ui->lb_typeIcon5;//天气类型图标 label
    mAqiList<<ui->lb_aqi0<<ui->lb_aqi1<<ui->lb_aqi2<<ui->lb_aqi3<<ui->lb_aqi4<<ui->lb_aqi5;//空气质量 label
    mFlList<<ui->lb_fl0<<ui->lb_fl1<<ui->lb_fl2<<ui->lb_fl3<<ui->lb_fl4<<ui->lb_fl5; // 风力 label
    mFxList<<ui->lb_fx0<<ui->lb_fx1<<ui->lb_fx2<<ui->lb_fx3<<ui->lb_fx4<<ui->lb_fx5; //风向 label
    mTypeIconMap.insert("晴", ":/res/type/Qing.png");
       mTypeIconMap.insert("多云", ":/res/type/DuoYun.png");
       mTypeIconMap.insert("阴", ":/res/type/Yin.png");
       mTypeIconMap.insert("雨", ":/res/type/Yu.png");
       mTypeIconMap.insert("雪", ":/res/type/Xue.png");
       mTypeIconMap.insert("沙尘暴", ":/res/type/ShaChenBao.png");

       mTypeIconMap.insert("雷阵雨", ":/res/type/LeiZhenYu.png");
       mTypeIconMap.insert("大雨", ":/res/type/DaYu.png");
       mTypeIconMap.insert("小雨", ":/res/type/XiaoYu.png");
       mTypeIconMap.insert("中雨", ":/res/type/ZhenYu.png");
       mTypeIconMap.insert("阵雨", ":/res/type/ZhenYu.png");
       mTypeIconMap.insert("暴雨", ":/weatherImages/type/BaoYu.png");
       mTypeIconMap.insert("大暴雨", ":/res/type/DaBaoYu.png");
       mTypeIconMap.insert("大到暴雨",":/res/type/DaDaoBaoYu.png");
       mTypeIconMap.insert("暴雨到大暴雨",":/res/type/BaoYuDaoDaBaoYu.png");
       mTypeIconMap.insert("大暴雨到特大暴雨",":/res/type/DaBaoYuDaoTeDaBaoYu.png");

       mTypeIconMap.insert("暴雪",":/res/type/BaoXue.png");
       mTypeIconMap.insert("大到暴雪",":/res/type/DaDaoBaoXue.png");
       mTypeIconMap.insert("大雪", ":/res/type/DaXue.png");
       mTypeIconMap.insert("小雪", ":/res/type/XiaoXue.png");
       mTypeIconMap.insert("中雪", ":/res/type/ZhenXue.png");


       mTypeIconMap.insert("雨夹雪", ":/res/type/YuJiaXue.png");
       mTypeIconMap.insert("霾", ":/res/type/Mai.png");
       mTypeIconMap.insert("扬沙", ":/res/type/YangSha.png");
       mTypeIconMap.insert("沙尘暴", ":/res/type/ShaChenBao.png");
       mTypeIconMap.insert("特大暴雨", ":/res/type/TeDaBaoYu.png");
       mTypeIconMap.insert("雾", "::/res/type/Wu.png");
       mTypeIconMap.insert("小到中雨", ":/res/type/XiaoDaoZhongYu.png");
       mTypeIconMap.insert("小到中雪", ":/res/type/XiaoDaoZhongXue.png");
       mTypeIconMap.insert("雨夹雪", ":/res/type/YuJiaXue.png");
       mTypeIconMap.insert("阵雪", ":/res/type/ZhenXue.png");

    //3.网络请求
    mNetworkAccessManager=new QNetworkAccessManager(this);
    connect(mNetworkAccessManager,&QNetworkAccessManager::finished,this,&MainWindow::onReplied);

    //4.直接在构造函数中请求天气数据
    //"101040100"是重庆的天气网城市代码
    //广州城市编码101280101
    //綦江区城市编码101043300
    getWeatherInfo("重庆市");

    //5.给标签过滤器添加事件
    //参数设定为this,也就是当前窗口对象mainWindow
    ui->lb_HightCurve->installEventFilter(this);
    ui->lb_LowCurve->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



//重写父类的虚函数
//父类中默认实现的是忽略右键菜单时事件
//重写之后就可以处理右键菜单事件
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    //弹出右键菜单
    mExitMenu->exec(QCursor::pos());//在鼠标单机的位置弹出按钮
    event->accept();//像系统表示字节已经处理这个信号了，不需要向上传递了。
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    mOffset=event->globalPos()-this->pos();//获取相对偏移量
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos()-mOffset);//使得窗口移动到这个为位置
}

void MainWindow::getWeatherInfo(QString cityName)
{
    QString cityCode= WeatherTool::getCityCode(cityName);//获取城市编码
    if(cityCode.isEmpty())
    {
        QMessageBox::warning(this,"天气","请检查城市是否输入有误",QMessageBox::Ok);
        return ;
    }
    QUrl url("http://t.weather.itboy.net/api/weather/city/"+cityCode);
    mNetworkAccessManager->get(QNetworkRequest(url));
}

void MainWindow::parxseJson(QByteArray &byteArry)
{
//    QJsonParseError error;
//        QJsonDocument doc = QJsonDocument::fromJson(byteArry,&error); //如果报错就会把错误信息写到error里
//        //报错直接退出
//        if(error.error != QJsonParseError::NoError)
//        {
//            return;
//        }

//        QJsonObject rootObj = doc.object();
//        //1.解析城市跟日期
//        mToday.city = rootObj.value("cityInfo").toObject().value("city").toString();
//        mToday.date = rootObj.value("date").toString();
//        qDebug()<<rootObj.value("date").toString();
//        //2.解析昨天yesterday数据
//        QJsonObject dataObj = rootObj.value("data").toObject();


//        QJsonObject yesterdayObj = dataObj.value("yesterday").toObject();
//        mDay[0].week = yesterdayObj.value("week").toString();
//        mDay[0].date = yesterdayObj.value("ymd").toString().toInt();
//        qDebug()<<mDay[0].date;
//        //天气类型
//        mDay[0].type = yesterdayObj.value("type").toString();

//        //空气指数
//        mDay[0].aqi =yesterdayObj.value("aqi").toDouble();

//        //温度，要分割取数据,"high":"高温 32℃"
//        QString highS;
//        highS = yesterdayObj.value("high").toString().split(" ").at(1); //高温 32℃ -> 32°C ，按空格切割，取第二个数据
//        mDay[0].high = highS.left(highS.length() - 1).toInt(); //长度减一，从左边开始计算取，32°c -> 32 ,在转换为int
//        QString lowS;
//        lowS = yesterdayObj.value("low").toString().split(" ").at(1);
//        mDay[0].low = lowS.left(lowS.length() - 1).toInt();

//        //风向，风力
//        mDay[0].fx = yesterdayObj.value("fx").toString();
//        mDay[0].fl = yesterdayObj.value("fl").toString();

//        //3.解析forecast中5天的数据 ,forecast当中包括15天的数据，数组形式
//        QJsonArray forecastArr = dataObj.value("forecast").toArray();
//        for(int i=0 ; i<5 ; i++)
//        {
//            QJsonObject forecastObj = forecastArr[i].toObject();

//            mDay[i+1].week = forecastObj.value("week").toString();
//            mDay[i+1].date = forecastObj.value("ymd").toString();
//            mDay[i+1].type = forecastObj.value("type").toString();
//            //空气指数
//            mDay[0].aqi =forecastObj.value("aqi").toDouble();

//            //温度，要分割取数据,"high":"高温 32℃"
//            QString highS;
//            highS = forecastObj.value("high").toString().split(" ").at(1);
//            mDay[i+1].high = highS.left(highS.length() - 1).toInt();
//            QString lowS;
//            lowS = forecastObj.value("low").toString().split(" ").at(1);
//            mDay[i+1].low = lowS.left(lowS.length() - 1).toInt();

//            //风向，风力
//            mDay[i+1].fx = forecastObj.value("fx").toString();
//            mDay[i+1].fl = forecastObj.value("fl").toString();
//        }

//        //4.解析今天的数据
//        mToday.wendu =dataObj.value("wendu").toInt();

//        mToday.ganmao =dataObj.value("ganmao").toString();

//        mToday.shidu = dataObj.value("shidu").toString();
//        mToday.pm25 =dataObj.value("pm25").toInt();
//        mToday.quality =dataObj.value("quality").toString();

//        //还有一些今天的天气数据在forecast里面
//        mToday.type = mDay[1].type; //上面存好了，直接用
//        mToday.high = mDay[1].high;
//        mToday.low = mDay[1].low;

//        mToday.fx = mDay[1].fx;
//        mToday.fl = mDay[1].fl;
//    //5.更新ui
//        updateUI();
//}

//void MainWindow::updateUI()
//{
//    //1.更新日期和城市
//    ui->lb_search_date->setText(QDateTime::fromString(mToday.date,"yyyyMMdd").toString("yyyy/MM/dd")+""+mDay[1].week);
//    ui->lb_city->setText(mToday.city);
//    //2.更新今天
//    ui->lb_icon->setPixmap(mTypeIconMap[mToday.type]);//设置对应天气图标

//    ui->lb_temperture->setText(QString::number(mToday.wendu)+"℃");//温度
//    //qDebug()<<mToday.wendu;
//    ui->lb_weather->setText(mToday.type);//天气
//    ui->lb_tempChange->setText(QString::number(mToday.low)+"~"+QString::number(mToday.high)+"℃");
//    ui->lb_ganmaoTable->setText("感冒指数:"+mToday.ganmao);
//    ui->lb_WinFX->setText(mToday.fx);
//    ui->lb_WinFL->setText(mToday.fl);
//    ui->lb_PM25Value->setText(QString::number(mToday.pm25));
//    ui->lb_HumidityValue->setText(mToday.shidu);
//    ui->lb_qualityValue->setText(mToday.quality);
//   //qDebug()<<mDay[0].date;
//    //3.更新6天
//    for(int i=0;i<6;++i)
//    {
//        //3.1更新时间和日期
//        mWeekList[i]->setText("周"+mDay[i].week.right(1));
//        ui->lb_week0->setText("昨天");
//        ui->lb_week1->setText("今天");
//        ui->lb_week2->setText("明天");
//        //QStringList ymdList=mDay[i].date.split("-");

//        //mDateList[i]->setText(ymdList[1]+"/"+ymdList[2]);//取月份和年份

//        //3.2更新天气类型和天气图标
//        mTypeList[i]->setText(mDay[i].type);
//        mTypeIconList[i]->setPixmap(mTypeIconMap[mDay[i].type]);
//        if(mDay[i].aqi>=0&&mDay[i].aqi<=50)
//        {
//            mAqiList[i]->setText("优");
//            mAqiList[i]->setStyleSheet("background-color:rgb(121,184,0);");
//        }else if(mDay[i].aqi>50&&mDay[i].aqi<=100)
//        {
//            mAqiList[i]->setText("良");
//            mAqiList[i]->setStyleSheet("background-color:rgb(255,187,23);");
//        }else if(mDay[i].aqi>100&&mDay[i].aqi<=150)
//        {
//            mAqiList[i]->setText("轻度污染");
//            mAqiList[i]->setStyleSheet("background-color:rgb(255,87,97);");
//        }else if(mDay[i].aqi>150&&mDay[i].aqi<=200)
//        {
//            mAqiList[i]->setText("中度污染");
//            mAqiList[i]->setStyleSheet("background-color:rgb(235,17,27);");
//        }else if(mDay[i].aqi>200&&mDay[i].aqi<=250)
//        {
//            mAqiList[i]->setText("重度污染");
//            mAqiList[i]->setStyleSheet("background-color:rgb(170,0,0);");
//        }
//        else
//        {
//            mAqiList[i]->setText("严重污染");
//            mAqiList[i]->setStyleSheet("background-color:rgb(110,0,0);");
//        }
//        //3.4更新风力和风向
//        mFxList[i]->setText(mDay[i].fx);
//        mFlList[i]->setText(mDay[i].fl);
//    }


    QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(byteArry,&error); //如果报错就会把错误信息写到error里
        //报错直接退出
        if(error.error != QJsonParseError::NoError)
        {
            return;
        }

        QJsonObject rootObj = doc.object();
        //1.解析城市跟日期
        mToday.city = rootObj.value("cityInfo").toObject().value("city").toString();
        mToday.date = rootObj.value("date").toString();
        qDebug()<<rootObj.value("date").toString();


        //2.解析剩余5几天的数据
        QJsonObject dataObj = rootObj.value("data").toObject();


        QJsonObject yesterdayObj = dataObj.value("yesterday").toObject();
        mDay[0].week = yesterdayObj.value("week").toString();
        mDay[0].date = yesterdayObj.value("ymd").toString().toInt();
        qDebug()<<mDay[0].date;
        //天气类型
        mDay[0].type = yesterdayObj.value("type").toString();

        //空气指数
        mDay[0].aqi =yesterdayObj.value("aqi").toDouble();

        //温度，要分割取数据,"high":"高温 32℃"
        QString highS;
        highS = yesterdayObj.value("high").toString().split(" ").at(1); //高温 32℃ -> 32°C ，按空格切割，取第二个数据
        mDay[0].high = highS.left(highS.length() - 1).toInt(); //长度减一，从左边开始计算取，32°c -> 32 ,在转换为int
        QString lowS;
        lowS = yesterdayObj.value("low").toString().split(" ").at(1);
        mDay[0].low = lowS.left(lowS.length() - 1).toInt();

        //风向，风力
        mDay[0].fx = yesterdayObj.value("fx").toString();
        mDay[0].fl = yesterdayObj.value("fl").toString();

        //3.解析forecast中5天的数据 ,forecast当中包括15天的数据，数组形式
        QJsonArray forecastArr = dataObj.value("forecast").toArray();
        for(int i=0 ; i<5 ; i++)
        {
            QJsonObject forecastObj = forecastArr[i].toObject();

            mDay[i+1].week = forecastObj.value("week").toString();
            mDay[i+1].date = forecastObj.value("ymd").toString();
            mDay[i+1].type = forecastObj.value("type").toString();
            //空气指数
            mDay[0].aqi =forecastObj.value("aqi").toDouble();

            //温度，要分割取数据,"high":"高温 32℃"
            QString highS;
            highS = forecastObj.value("high").toString().split(" ").at(1);
            mDay[i+1].high = highS.left(highS.length() - 1).toInt();
            QString lowS;
            lowS = forecastObj.value("low").toString().split(" ").at(1);
            mDay[i+1].low = lowS.left(lowS.length() - 1).toInt();

            //风向，风力
            mDay[i+1].fx = forecastObj.value("fx").toString();
            mDay[i+1].fl = forecastObj.value("fl").toString();
        }

        //4.解析今天的数据
        mToday.wendu =dataObj.value("wendu").toInt();

        mToday.ganmao =dataObj.value("ganmao").toString();

        mToday.shidu = dataObj.value("shidu").toString();
        mToday.pm25 =dataObj.value("pm25").toInt();
        mToday.quality =dataObj.value("quality").toString();

        //还有一些今天的天气数据在forecast里面
        mToday.type = mDay[1].type; //上面存好了，直接用
        mToday.high = mDay[1].high;
        mToday.low = mDay[1].low;

        mToday.fx = mDay[1].fx;
        mToday.fl = mDay[1].fl;
    //5.更新ui
        updateUI();
}

void MainWindow::updateUI()
{
    //1.更新日期和城市
    ui->lb_search_date->setText(QDateTime::fromString(mToday.date,"yyyyMMdd").toString("yyyy/MM/dd")+""+mDay[1].week);
    ui->lb_city->setText(mToday.city);
    //2.更新今天
    ui->lb_icon->setPixmap(mTypeIconMap[mToday.type]);//设置对应天气图标

    ui->lb_temperture->setText(QString::number(mToday.wendu)+"℃");//温度
    //qDebug()<<mToday.wendu;
    ui->lb_weather->setText(mToday.type);//天气
    ui->lb_tempChange->setText(QString::number(mToday.low)+"~"+QString::number(mToday.high)+"℃");
    ui->lb_ganmaoTable->setText("感冒指数:"+mToday.ganmao);
    ui->lb_WinFX->setText(mToday.fx);
    ui->lb_WinFL->setText(mToday.fl);
    ui->lb_PM25Value->setText(QString::number(mToday.pm25));
    ui->lb_HumidityValue->setText(mToday.shidu);
    ui->lb_qualityValue->setText(mToday.quality);
   //qDebug()<<mDay[0].date;
    //3.更新6天
    for(int i=0;i<6;++i)
    {
        //3.1更新时间和日期
        mWeekList[i]->setText("周"+mDay[i].week.right(1));
        ui->lb_week0->setText("昨天");
        ui->lb_week1->setText("今天");
        ui->lb_week2->setText("明天");
        //QStringList ymdList=mDay[i].date.split("-");

        //mDateList[i]->setText(ymdList[1]+"/"+ymdList[2]);//取月份和年份

        //3.2更新天气类型和天气图标
        mTypeList[i]->setText(mDay[i].type);
        mTypeIconList[i]->setPixmap(mTypeIconMap[mDay[i].type]);
        if(mDay[i].aqi>=0&&mDay[i].aqi<=50)
        {
            mAqiList[i]->setText("优");
            mAqiList[i]->setStyleSheet("background-color:rgb(121,184,0);");
        }else if(mDay[i].aqi>50&&mDay[i].aqi<=100)
        {
            mAqiList[i]->setText("良");
            mAqiList[i]->setStyleSheet("background-color:rgb(255,187,23);");
        }else if(mDay[i].aqi>100&&mDay[i].aqi<=150)
        {
            mAqiList[i]->setText("轻度污染");
            mAqiList[i]->setStyleSheet("background-color:rgb(255,87,97);");
        }else if(mDay[i].aqi>150&&mDay[i].aqi<=200)
        {
            mAqiList[i]->setText("中度污染");
            mAqiList[i]->setStyleSheet("background-color:rgb(235,17,27);");
        }else if(mDay[i].aqi>200&&mDay[i].aqi<=250)
        {
            mAqiList[i]->setText("重度污染");
            mAqiList[i]->setStyleSheet("background-color:rgb(170,0,0);");
        }
        else
        {
            mAqiList[i]->setText("严重污染");
            mAqiList[i]->setStyleSheet("background-color:rgb(110,0,0);");
        }
        //3.4更新风力和风向
        mFxList[i]->setText(mDay[i].fx);
        mFlList[i]->setText(mDay[i].fl);
    }

    
}
void MainWindow::onReplied(QNetworkReply *reply)//所有数据都封装在了reply中，获取成功直接解析reply即可
{

    int status_code=reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//获取状态码(200就表示成功)

         qDebug()<<"operatiron:"<<reply->operation();//操作方式(pos/get)
         qDebug()<<"status_conde:"<<status_code;//状态码
         qDebug()<<"url:"<<reply->url();//url
         qDebug()<<"raw header:"<<reply->rawHeaderList();//请求头
         if(reply->error()!=QNetworkReply::NoError||200!=status_code)
         {
             qDebug()<<reply->errorString().toLatin1().data();
             QMessageBox::warning(this,"天气","请求数据失败!");
         }
         else
         {
             QByteArray byteArry=reply->readAll();
             qDebug()<<"read all:"<<byteArry.data();
             parxseJson(byteArry);// 传参解析
         }
         reply->deleteLater();
}


void MainWindow::on_bt_search_clicked()
{
    QString retStr=ui->lb_search->text();
    getWeatherInfo(retStr);
}
