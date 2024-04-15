#include "dialog_addstu.h"
#include "ui_dialog_addstu.h"
#include "stusql.h"
#include <QMessageBox>
#include <QDebug>
Dialog_AddStu::Dialog_AddStu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_AddStu)
{
    ui->setupUi(this);
}

Dialog_AddStu::~Dialog_AddStu()
{
    delete ui;
}

void Dialog_AddStu::setType(bool isSetAdd,StuInfo info)//判断是添加学生信息还是修改学生信息(用于对话框的复用)
{
    m_isAdd=isSetAdd;
    m_info=info;
    ui->lineEdit_stuname->setText(info.name);
    ui->spinBox_stuage->setValue(info.age);
    ui->lineEdit_stuclass->setText(QString::number(info.stuclass));
    ui->lineEdit_stugrade->setText(QString::number(info.grade));
    ui->lineEdit_stuid->setText(QString::number(info.stuid));
    ui->lineEdit_stuphone->setText(info.phone);
    ui->lineEdit_stuwechat->setText(info.wechat);
}

void Dialog_AddStu::on_pushButton_2_clicked()
{
    this->window()->close();//关闭窗口
    //this->hide();
}

void Dialog_AddStu::on_pushButton_save_clicked()
{
    StuInfo info;
    auto ptr=stuSql::getinstance();
    info.id=m_info.id;
    info.name=ui->lineEdit_stuname->text();
    info.age=ui->spinBox_stuage->text().toUInt();
    info.grade=ui->lineEdit_stugrade->text().toUInt();
    info.stuclass=ui->lineEdit_stuclass->text().toUInt();
    info.stuid=ui->lineEdit_stuid->text().toUInt();
    info.phone=ui->lineEdit_stuphone->text();
    info.wechat=ui->lineEdit_stuwechat->text();
    if(m_isAdd)
    {
        ptr->addStu(info);//添加学生信息
        QMessageBox::information(nullptr,"学生信息","存储成功");
    }
    else
    {
        //qDebug()<<"id: "<<info.id;
        ptr->UpdateStuInfo(info);//更新学生信息
        QMessageBox::information(nullptr,"学生信息","修改成功");
    }
    this->hide();

}
