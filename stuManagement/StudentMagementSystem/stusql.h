#ifndef STUSQL_H
#define STUSQL_H
#include <QtSql/QSqlDatabase>
#include <QObject>

//定义学生信息的结构体
struct StuInfo
{
    int id;//id
    QString name;//姓名
    quint8 age;//年龄
    quint16 stuclass;//班级
    quint16 grade;//年级
    quint32 stuid;//学生id
    QString phone;//电话
    QString wechat;//微信

};

//定义用户数据结构体
struct UserInfo
{
    QString username;//用户名
    QString passward;//密码
    QString auth;//权限

};

class stuSql : public QObject
{
    Q_OBJECT
public:
    explicit stuSql(QObject *parent = nullptr);
    //初始化数据
    void init();
    //查询所有学生人数
    quint32 getStuCount();
    //查询第几页的学生数据(页数从零开始)
    QList<StuInfo>getPageStu(quint32 page,quint32 stucount);
    //添加学生信息
    bool addStu(StuInfo);
    bool addStuList(QList <StuInfo> lt);
    //删除学生信息
    bool delStu(int id);
    //清空学生表
    bool clearStuInfo();
    //修改学生信息
    bool UpdateStuInfo(StuInfo info);
    //查询所以用户
    QList<UserInfo> getALLUser();
    //查询用户是否存在
    bool isExsit(QString strUser);
    QString getUserPassward(QString strUser);
    //更新用户信息
    bool updateUser(UserInfo info);
    //添加单个用户
    bool addUser(UserInfo info);
    //删除单个用户
    bool delUser(QString strUserName);
public:

    static stuSql*getinstance()//构造单例对象
    {
        if(nullptr==ptrstuSql)
        {
            ptrstuSql=new stuSql;
        }
        return ptrstuSql;
    }


signals:

private:
    QSqlDatabase m_db;
     static stuSql*ptrstuSql;
     //static stuSql*ptrUserSql;
};

#endif // STUSQL_H
