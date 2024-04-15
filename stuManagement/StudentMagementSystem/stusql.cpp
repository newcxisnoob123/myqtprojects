#include "stusql.h"
#include <QMessageBox>
#include <QCoreApplication>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
stuSql*stuSql::ptrstuSql=nullptr;
stuSql::stuSql(QObject *parent)
    : QObject(parent)
{
    init();//初始化数据库
    UserInfo info;
    UserInfo info1;
    info.username="chen";
    info.passward="1234";
    info.auth="admin";
    info1.username="xiao";
    info1.passward="1234";
    info1.auth="admin";
    addUser(info);
    addUser(info1);
    getALLUser();
    qDebug()<<isExsit("chen");
    info1.passward="666";
    updateUser(info1);
    delUser("xiao");
    //getPageStu(2,2);
    //delStu(18);
//    StuInfo s;
//    s.id=8;
//    s.name="李飞";
    //UpdateStuInfo(s);

//    StuInfo s;//定义一个学生信息对象
//    s.name="王五";
//    for(int i=0;i<2;i++)//循环添加两个学生对象数据
//    {
//        addStu(s);
//    }
    //getStuCount();
    //QSqlQuery q("",db);
   // q.exec("INSERT INTO student VALUES (NULL, '张三', 12, 3, 2, 1, 15940224444, 'asdzhang')");//插入一个数据
    // + db.lastError().text()
}

void stuSql::init()
{
    if (QSqlDatabase::drivers().isEmpty())
        QMessageBox::information(nullptr, tr("No database drivers found"),
                                 tr("This demo requires at least one Qt database driver. "
                                    "Please check the documentation how to build the "
                                    "Qt SQL plugins."));
    //qDebug()<<"No database drivers found";
    m_db = QSqlDatabase::addDatabase("QSQLITE");//添加数据库表存放的位置
#if 0
    auto str=QCoreApplication::applicationDirPath()+"management.db";
    qDebug()<<str;
#endif

    m_db.setDatabaseName("D:\\Code\\ManageMent\\management.db");//判断数据库有没有打开
    if (!m_db.open())
        qDebug()<<"db not open";
        //QMessageBox::warning(nullptr, tr("Unable to open database"), tr("An error occurred while"));
}

quint32 stuSql::getStuCount()//统计学生的人数
{
    QSqlQuery sql(m_db);
    sql.exec("select count(id)from student");
    quint8 counts=0;
    while(sql.next())
    {
       counts=sql.value(0).toUInt();//统计次数
       //count++;
    }
    //qDebug()<<counts;
    return counts;
}

QList<StuInfo> stuSql::getPageStu(quint32 page, quint32 stucount)//分页查看学生信息
{
    QList<StuInfo> ls;
    QSqlQuery sql(m_db);
    QString strsql=QString("select * from student order by id limit %1 offset %2").
            arg(stucount).arg(page*stucount);
    sql.exec(strsql);
    StuInfo info;
    while(sql.next())
    {
       info.id=sql.value(0).toUInt();
       info.name=sql.value(1).toString();
       info.age=sql.value(2).toUInt();
       info.grade=sql.value(3).toUInt();
       info.stuclass=sql.value(4).toUInt();
       info.stuid=sql.value(5).toUInt();
       info.phone=sql.value(6).toString();
       info.wechat=sql.value(7).toString();
       ls.push_back(info);
    }

    return ls;
}

bool stuSql::addStu(StuInfo info)//添加学生信息
{
    QSqlQuery sql(m_db);
    QString strSql=QString("insert into student values(null,'%1',%2,%3,%4,%5,'%6','%7')").//字符串应该加引号
            arg(info.name).
            arg(info.age).
            arg(info.grade).
            arg(info.stuclass).
            arg(info.stuid).
            arg(info.phone).
            arg(info.wechat);
    return sql.exec(strSql);
}

bool stuSql::addStuList(QList<StuInfo> lt)
{
    QSqlQuery sql(m_db);
    m_db.transaction();
    bool allInsertedSuccessfully = true;

    for(const auto& info : lt)
    {
        QString strSql = QString("INSERT INTO student VALUES(NULL, '%1', %2, %3, %4, '%5', '%6', '%7')")
            .arg(info.name)
            .arg(info.age)
            .arg(info.grade)
            .arg(info.stuclass)
            .arg(info.stuid)
            .arg(info.phone)
            .arg(info.wechat);

        if(!sql.exec(strSql))
        {
            allInsertedSuccessfully = false;
            break; // 如果一个插入失败，则退出循环
        }
    }

    if(allInsertedSuccessfully)
    {
        m_db.commit();
    }
    else
    {
        m_db.rollback(); // 如果有任何错误，回滚事务
    }

    return allInsertedSuccessfully;
}

bool stuSql::delStu(int id) //根据学生id删除学生信息
{
    QSqlQuery sql(m_db);
    return sql.exec(QString("delete from student where id=%1").arg(id));
}



bool stuSql::clearStuInfo() //清空学生表信息
{
    QSqlQuery sql(m_db);
    sql.exec("delete from student");
    return sql.exec(QString("delete from sqlite_sequence where name = 'student'"));
}

bool stuSql::UpdateStuInfo(StuInfo info)//修改学生信息
{
    //qDebug()<<info.id<<endl;
    QSqlQuery sql(m_db);
    QString strSql=QString("update student set name='%1',age=%2,grade=%3,class=%4,studentid=%5,"
                           "phone='%6',wechat='%7' where id=%8").//字符串应该加引号(这里是数据库里面定义的关键词)

            arg(info.name).//这里的关键字都是自己定义的
            arg(info.age).
            arg(info.grade).
            arg(info.stuclass).
            arg(info.stuid).
            arg(info.phone).
            arg(info.wechat).
            arg(info.id);
     bool ret=sql.exec(strSql);
    // qDebug()<<strSql;
    QSqlError errors=sql.lastError();
    if(errors.isValid())
    {
        qDebug()<<errors.text();

    }
    return ret;

}

QList<UserInfo> stuSql::getALLUser() //获取所有用户
{
    QList<UserInfo> uerlist;
    QSqlQuery sql(m_db);

    sql.exec("select * from username");
    UserInfo info;
    while(sql.next())
    {
       info.username=sql.value(0).toString();
       info.passward=sql.value(1).toString();
       info.auth=sql.value(2).toString();
       uerlist.push_back(info);
    }
    return uerlist;
}

bool stuSql::isExsit(QString strUser) //判定用户是否存在
{
    QSqlQuery sql(m_db);

    sql.exec(QString("select *from username where username='%1'").arg(strUser));
    return sql.next();
}

QString stuSql::getUserPassward(QString strUser)//查询用户密码
{

    QSqlQuery sql(m_db);
       QString password;

       // 准备 SQL 查询，使用参数化查询以防止 SQL 注入攻击
       sql.prepare("SELECT password FROM username WHERE username = :user");
       sql.bindValue(":user", strUser);
       if (sql.exec()) {
           // 如果查询成功，检查是否有结果返回
           if (sql.next()) {
               // 获取密码字段的值
               password = sql.value(0).toString();
           } else {
               // 没有找到对应的用户，可以抛出一个异常或返回一个特殊值
               // 例如: password = "not_found";
           }
       } else {
           // 查询执行失败，可以记录错误或抛出异常
           // 例如: qDebug() << "Error executing query:" << sql.lastError().text();
       }

       return password;
//    QSqlQuery sql(m_db);

//    sql.exec(QString("select *from username where username='%1'").arg(strUser));
//    return
}

bool stuSql::updateUser(UserInfo info)
{

    QSqlQuery sql(m_db);
    QString strSql=QString("update username set password='%1',auth='%2' where username='%3'").//字符串应该加引号(这里是数据库里面定义的关键词)

           //这里的关键字都是自己定义的
            arg(info.passward).
            arg(info.auth).
            arg(info.username);

     bool ret=sql.exec(strSql);
    QSqlError errors=sql.lastError();
    if(errors.isValid())
    {
        qDebug()<<errors.text();

    }
    return ret;
}

bool stuSql::addUser(UserInfo info)//添加单个用户
{
    QSqlQuery sql(m_db);
    QString strSql=QString("INSERT INTO username VALUES ('%1', '%2', '%3')").//字符串应该加引号(这里是数据库里面定义的关键词)

            arg(info.username).//这里的关键字都是自己定义的
            arg(info.passward).
            arg(info.auth);
    return sql.exec(strSql);

}

bool stuSql::delUser(QString strUserName)
{

    QSqlQuery sql(m_db);
   return sql.exec(QString("delete from username where username='%1'").arg(strUserName));

}

