#ifndef PAGE_LOGIN_H
#define PAGE_LOGIN_H

#include <QWidget>
#include <QMessageBox>
#include "stusql.h"
namespace Ui {
class Page_Login;
}

class Page_Login : public QWidget
{
    Q_OBJECT

public:
    explicit Page_Login(QWidget *parent = nullptr);
    ~Page_Login();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_login_clicked();
signals:
    //发送成功的信号
    void SendLoginSuccess();

private:
    Ui::Page_Login *ui;
    void clearText();//清空输入框文本

};

#endif // PAGE_LOGIN_H
