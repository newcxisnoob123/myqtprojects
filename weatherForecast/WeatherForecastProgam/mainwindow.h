#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMenu>
#include <QMainWindow>
#include <QMouseEvent>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "weatherDate.h"
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void onReplied(QNetworkReply*reply);//定义槽函数
protected:
    //重写虚函数
  void contextMenuEvent(QContextMenuEvent *event);
  void mousePressEvent(QMouseEvent*event);//鼠标单机事件
  void mouseMoveEvent(QMouseEvent*event);

  //获取天气数据、解析JSON、更新UI
  void getWeatherInfo(QString cityCode);//获取城市编码
  void parxseJson(QByteArray&byteArry);//解析JSon数据
  void updateUI();

private slots:
  void on_bt_search_clicked();

private:
  QMenu*mExitMenu; //右键退出菜单
  QAction*mExitACt;//退出行为--菜单项
  QPoint mOffset;//移动窗口时候，鼠标与窗口左上角的偏移
  //http请求
  QNetworkAccessManager*mNetworkAccessManager;
  Today mToday;
  Day mDay[6];

  //星期和日期
  QList<QLabel*> mWeekList;
  QList<QLabel*> mDateList;

  //天气和天气图标
  QList<QLabel*> mTypeList;
  QList<QLabel*> mTypeIconList;

  //天气污染指数
  QList<QLabel*> mAqiList;

  //风力和风向
  QList<QLabel*> mFlList;
  QList<QLabel*> mFxList;

  QMap<QString,QString>mTypeIconMap;
private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
