#include "page_login.h"
#include "ui_page_login.h"
#include <QTimer>
#include <QDebug>
Page_Login::Page_Login(QWidget *parent) :
    QWidget(parent),

    ui(new Ui::Page_Login)
{
    ui->setupUi(this);

}

Page_Login::~Page_Login()
{
    delete ui;
}

void Page_Login::on_pushButton_exit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "警告", "确定退出?",QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
         exit(0);// 用户点击了"确定"按钮，执行退出操作
    } else {
        // 用户点击了"取消"按钮，不执行退出操作
    }

}


void Page_Login::on_pushButton_login_clicked()
{
    //数据库查找用户名和密码

    //失败就提示

    //成功就进入主窗口
    QString UserAccount=ui->lineEdit_username->text();
    QString UserPassward=ui->lineEdit_passward->text();
    if(0==UserAccount.size())
    {
        ui->label_hint->setText("用户名不能为空!");
        // 创建一个单次触发的定时器，两秒后触发
            QTimer::singleShot(2000, [this]() {
                // 定时器触发时执行的lambda表达式，清空标签的文本
                ui->label_hint->setText("");
            });
    }
    else if(0==UserPassward.size())
    {
        ui->label_hint->setText("密码不能为空!");
        QTimer::singleShot(2000, [this]() {
            // 定时器触发时执行的lambda表达式，清空标签的文本
            ui->label_hint->setText("");
        });
    }
    else
    {
        ui->label_hint->setText("");
        auto ptr=stuSql::getinstance();
        bool ret=ptr->isExsit(UserAccount);
        if(ret)
        {
            QString retPassward=ptr->getUserPassward(UserAccount);
            if(UserPassward==retPassward)
            {
                //userNameText=UserAccount;//保存用户名
                QMessageBox::information(nullptr,"消息","登录成功");
                this->hide();//隐藏窗口
                emit SendLoginSuccess();
            }
            else
            {
                QMessageBox::warning(nullptr,"警告","用户名或者密码有误");
                clearText();
            }
        }
        else
        {
            QMessageBox::warning(nullptr,"警告","该用户不存在");
            clearText();
        }
    }
}

void Page_Login::clearText()
{
    ui->lineEdit_passward->setText("");
    ui->lineEdit_username->setText("");
}

