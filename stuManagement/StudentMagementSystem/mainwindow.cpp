#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QFile>
#include <QCoreApplication>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QDebug>
#include <QHeaderView>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_ptrStuSql(nullptr)
{
    ui->setupUi(this);
    page_login.show();

    //槽函数
    auto func=[&](){
        this->show();
    };
    connect(&page_login,&Page_Login::SendLoginSuccess,this,func);
    ui->treeWidget->header()->setVisible(false);
    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(1);//设置一行
    QStringList qst;
    qst<<"学生信息管理系统";

    QTreeWidgetItem*pf=new QTreeWidgetItem(ui->treeWidget,qst);
    ui->treeWidget->addTopLevelItem(pf);//设置到根节点

    qst.clear();//清理数据
    qst<<"学生管理";
    QTreeWidgetItem*p1 = new QTreeWidgetItem(pf,qst);

    qst.clear();
    qst<<"管理员管理";
    QTreeWidgetItem*p2=new QTreeWidgetItem(pf,qst);

    //把两个子节点插入进父节点中
    pf->addChild(p1);
    pf->addChild(p2);
    qst.clear();
    ui->treeWidget->setCurrentItem(p1);//默认选中“学生管理”
    ui->treeWidget->expandAll();//设置树形结构默认全部展开
    m_ptrStuSql=stuSql::getinstance();//获取单例对象的指针
    m_ptrStuSql->init();//初始化

   m_lNames<< " 冯含莲";
   m_lNames<< " 亥家馨";
   m_lNames<< " 戊青曼";
   m_lNames<< " 军今雨";
   m_lNames<< " 帖阳伯";
   m_lNames<< " 丙菲菲";
   m_lNames<< " 翦沛萍";
   m_lNames<< " 似阳泽";
   m_lNames<< " 强访文";
   m_lNames<< " 姓如馨";
   m_lNames<< " 凭思菱";
   m_lNames<< " 伯绮琴";
   m_lNames<< " 夫欣荣";
   m_lNames<< " 叶若华";
   m_lNames<< " 塞逸明";
   m_lNames<< " 言奕奕";
   m_lNames<< " 沙友菱";
   m_lNames<< " 仪问萍";
   m_lNames<< " 汉高峻";
   m_lNames<< " 邶华辉";
   m_lNames<< " 蓬飞翼";
   m_lNames<< " 廉幼珊";
   m_lNames<< " 化易槐";
   m_lNames<< " 势源源";
   m_lNames<< " 鄞紫雪";
   m_lNames<< " 浮才艺";
   m_lNames<< " 叔思菱";
   m_lNames<< " 芒箫笛";
   m_lNames<< " 普佳美";
   m_lNames<< " 金乐天";
   m_lNames<< " 酆宛菡";
   m_lNames<< " 那语冰";
   m_lNames<< " 务骏哲";
   m_lNames<< " 甲睿思";
   m_lNames<< " 汪一璇";
   m_lNames<< " 裴闲静";
   m_lNames<< " 黎鸿宝";
   m_lNames<< " 牟烨磊";
   m_lNames<< " 奕思菱";
   m_lNames<< " 简文滨";
   m_lNames<< " 武问兰";
   m_lNames<< " 仝同甫";
   m_lNames<< " 九云淡";
   m_lNames<< " 邴宛丝";
   m_lNames<< " 皮含蕊";
   m_lNames<< " 犹浩思";
   m_lNames<< " 逄成益";
   m_lNames<< " 摩贞婉";
   m_lNames<< " 庹痴凝";
   m_lNames<< " 告雅健";
   m_lNames<< " 锐水蓝";
   m_lNames<< " 诗淑哲";
   m_lNames<< " 么谧辰";
   m_lNames<< " 敬灵慧";
   m_lNames<< " 权天慧";
   m_lNames<< " 用宇达";
   m_lNames<< " 洪紫菱";
   m_lNames<< " 潭溶溶";
   m_lNames<< " 士蔓菁";
   m_lNames<< " 桑思柔";
   m_lNames<< " 秘涵润";
   m_lNames<< " 雍念文";
   m_lNames<< " 始雁易";
   m_lNames<< " 敖煜祺";
   m_lNames<< " 阎清宁";
   m_lNames<< " 终新烟";
   m_lNames<< " 须芸溪";
   m_lNames<< " 占语芹";
   m_lNames<< " 伦学文";
   m_lNames<< " 薄田田";
   m_lNames<< " 钊明朗";
   m_lNames<< " 邓天悦";
   m_lNames<< " 耿琇云";
   m_lNames<< " 咎丽珠";
   m_lNames<< " 衷芳馥";
   m_lNames<< " 遇暮雨";
   m_lNames<< " 潘丽雅";
   m_lNames<< " 剑之玉";
   m_lNames<< " 壬从蓉";
   m_lNames<< " 于笑槐";
   m_lNames<< " 顾白桃";
   m_lNames<< " 宛星雨";
   m_lNames<< " 本思真";
   m_lNames<< " 首睿达";
   m_lNames<< " 孟乐容";
   m_lNames<< " 宏芳馥";
   m_lNames<< " 戢妙梦";
   m_lNames<< " 祢飞英";
   m_lNames<< " 植醉巧";
   m_lNames<< " 粘可心";
   m_lNames<< " 肖宏义";
   m_lNames<< " 充浩慨";
   m_lNames<< " 宰语丝";
   m_lNames<< " 杜新之";
   m_lNames<< " 巧安娴";
   m_lNames<< " 祖嘉实";
   m_lNames<< " 昂冷之";
   m_lNames<< " 逯佩玉";
   m_lNames<< " 休骏燕";
   m_lNames<< " 肇代桃";
   m_lNames<< " 能雪柳";

  updateTable();//刷新界面


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "警告", "确定退出?",QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
         exit(0);// 用户点击了"确定"按钮，执行退出操作
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)//按键刷新皮肤
{
    if(event->key()==Qt::Key_F6)//设置快捷键
    {
        QFile files;//定义一个文件对象
        auto filepath=QCoreApplication::applicationDirPath();//返回文件的路径
        files.setFileName(filepath+"//"+"stuqss.css");
        files.open(QIODevice::ReadOnly);//设置文件只读
        QString strQss=files.readAll();
        this->setStyleSheet(strQss);
        page_login.setStyleSheet(strQss);//设置登录页面的样式表
    }
}

void MainWindow::on_pushButton_2_clicked()
{


}

void MainWindow::on_pushButton_add_clicked()
{
    m_dlgAddStu.setType(true);
    m_dlgAddStu.exec();
    updateTable();
}



void MainWindow::updateTable()
{
    ui->tableWidget->clear();//把头清理掉
    ui->tableWidget->setColumnCount(9);//设置8列，告诉编译器有多少列
    QStringList qst;
    qst<<"序号"<<"id"<<"姓名"<<"年龄"<<"年级"<<"班级"<<"学号"<<"电话"<<"微信";
    ui->tableWidget->setHorizontalHeaderLabels(qst);//重新设置表格的标题
    ui->tableWidget->verticalHeader()->setVisible(false);//禁止显示行号
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自动等宽
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置一次选中一行
    ui->tableWidget->setStyleSheet("QTableWidget::item:selected { background-color: #93d5dc; }");//选中一行高亮显示
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格信息不能直接修改

    auto stucount=m_ptrStuSql->getStuCount();//获取学生的人数
    ui->label_stucout->setText(QString("学生总数：%1").arg(stucount));
    QList<StuInfo> LStudents=m_ptrStuSql->getPageStu(0,stucount);//分页获取学生的信息


    ui->tableWidget->setRowCount(stucount);//设置表的行数(有多少学生设置多少行)
    for(int i=0;i<LStudents.size();++i)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i)));//设置第i行的序号
       ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(LStudents[i].id)));//设置id
       ui->tableWidget->setItem(i,2,new QTableWidgetItem(LStudents[i].name));//设置第i行的姓名
       ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(LStudents[i].age)));//设置第i行的年龄
       ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(LStudents[i].grade)));//设置第i行的年纪
       ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(LStudents[i].stuclass)));//设置第i行的班级号
       ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString::number(LStudents[i].stuid)));//设置第i行的学号
       ui->tableWidget->setItem(i,7,new QTableWidgetItem(LStudents[i].phone));//设置第i行的电话
       ui->tableWidget->setItem(i,8,new QTableWidgetItem(LStudents[i].wechat));//设置第i行的微信
    }

}



void MainWindow::on_pushButton_delete_clicked()
{
    int i=ui->tableWidget->currentRow();//获取当前选中的行
    if(i>=0)
    {

        QMessageBox::StandardButton reply;
        reply = QMessageBox::warning(nullptr, "警告", "确定删除?",QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            int id=ui->tableWidget->item(i,1)->text().toUInt();
            bool ret=m_ptrStuSql->delStu(id);

            if(true==ret)
            {
                QMessageBox::information(nullptr,"信息","删除成功");
            }
            else
            {
                QMessageBox::information(nullptr,"信息","失败");
            }
        }
    }
    else
    {
         QMessageBox::warning(nullptr,"警告","未选中删除行");
         return ;
    }
    updateTable();
}

void MainWindow::on_pushButton_modify_clicked()
{
    StuInfo info;
   // qDebug()<<"id: "<<info.name;
    int i=ui->tableWidget->currentRow();//获取当前选中行
    if(i>=0)
    {
        //qDebug()<<"id: "<<info.id;
        //qDebug()<<ui->tableWidget->item(i,1)->text().toUInt();
        info.id=ui->tableWidget->item(i,1)->text().toUInt();
        info.name=ui->tableWidget->item(i,2)->text();
        info.age=ui->tableWidget->item(i,3)->text().toUInt();
        info.grade=ui->tableWidget->item(i,4)->text().toUInt();
        info.stuclass=ui->tableWidget->item(i,5)->text().toUInt();
        info.stuid=ui->tableWidget->item(i,6)->text().toUInt();
        info.phone=ui->tableWidget->item(i,7)->text();
        info.wechat=ui->tableWidget->item(i,8)->text();
        m_dlgAddStu.setType(false,info);
        m_dlgAddStu.exec();
    }
    else
    {
     QMessageBox::warning(nullptr, "警告", "请选择行！");
    }
    updateTable();
}

void MainWindow::on_pushButton_search_clicked()
{
    QString stuFilter=ui->lineEdit_search->text();
    if(stuFilter.isEmpty())
    {
        QMessageBox::warning(nullptr,"警告","搜索不能为空!");
        updateTable();
        return;
    }
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(9);
    QStringList qst;
    qst<<"序号"<<"id"<<"姓名"<<"年龄"<<"年级"<<"班级"<<"学号"<<"电话"<<"微信";
    ui->tableWidget->setHorizontalHeaderLabels(qst);
    auto stucount=m_ptrStuSql->getStuCount();
    ui->label_stucout->setText(QString("学生总数：%1").arg(stucount));
    QList<StuInfo> LStudents=m_ptrStuSql->getPageStu(0,stucount);

    int index=0;

    for(int i=0;i<LStudents.size();++i)
    {
        if(!LStudents[i].name.contains(stuFilter))
        {
            continue;
        }

        ui->tableWidget->setItem(index,0,new QTableWidgetItem(QString::number(index+1)));//设置第i行的序号
       ui->tableWidget->setItem(index,1,new QTableWidgetItem(QString::number(LStudents[i].id)));//设置id
       ui->tableWidget->setItem(index,2,new QTableWidgetItem(LStudents[i].name));//设置第i行的姓名
       ui->tableWidget->setItem(index,3,new QTableWidgetItem(QString::number(LStudents[i].age)));//设置第i行的年龄
       ui->tableWidget->setItem(index,4,new QTableWidgetItem(QString::number(LStudents[i].grade)));//设置第i行的年纪
       ui->tableWidget->setItem(index,5,new QTableWidgetItem(QString::number(LStudents[i].stuclass)));//设置第i行的班级号
       ui->tableWidget->setItem(index,6,new QTableWidgetItem(QString::number(LStudents[i].stuid)));//设置第i行的学号
       ui->tableWidget->setItem(index,7,new QTableWidgetItem(LStudents[i].phone));//设置第i行的电话
       ui->tableWidget->setItem(index,8,new QTableWidgetItem(LStudents[i].wechat));//设置第i行的微信
        index++;
    }
    if(index==0)
    {
        updateTable();
        QMessageBox::information(nullptr,"警告","未找到相关信息!");
        ui->lineEdit_search->setText("");

        return;
    }
    ui->tableWidget->setRowCount(index);
}


void MainWindow::on_pushButton_simulation_clicked()
{
    QRandomGenerator grade,classid;//设置随机值
    grade.seed(0);//初始化种子
    classid.seed(0);
    QList<StuInfo> listinfo;
    for(int i=0;i<m_lNames.size();++i)//制作多条数据
    {
        auto uiclass= classid.bounded(1,8);
        auto uigrade=grade.bounded(7,10);//设置7-9之间的随机数（左闭右开）
        StuInfo info;
        info.name=m_lNames[i];
        if(i%2)
        {
            info.age=12;
        }
        else
        {
            info.age=14;
        }
        info.grade=uigrade;
        info.stuclass=uiclass;
        info.stuid=20223;
        info.phone="139993274";
        info.wechat="zcs_1244";
        listinfo.append(info);
    }
     bool ret=m_ptrStuSql->addStuList(listinfo);
     if(ret)
     {
          updateTable();
         QMessageBox::information(nullptr,"消息","添加成功");//要判空

     }
     else
     {
         QMessageBox::warning(nullptr,"消息","添加失败");//要判空
     }


}

void MainWindow::on_pushButton_clear_clicked()
{
    m_ptrStuSql->clearStuInfo();//清空学生信息
    updateTable();
}
