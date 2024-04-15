#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "page_login.h"
#include <QMainWindow>
#include "stusql.h"
#include "dialog_addstu.h"
#include "page_login.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    virtual void keyPressEvent(QKeyEvent*event);

    void on_pushButton_2_clicked();

    void on_pushButton_add_clicked();

    //void on_pushButton_3_clicked();
    void on_pushButton_delete_clicked();

    void on_pushButton_modify_clicked();

    void on_pushButton_search_clicked();

    //void on_pushButton_4_clicked();

    //void on_pushButton_reco_clicked();

    void on_pushButton_simulation_clicked();

    void on_pushButton_clear_clicked();

private:
    void updateTable();//刷新界面
private:
    Ui::MainWindow *ui;
    Page_Login page_login;
    stuSql*m_ptrStuSql;
    QStringList m_lNames;//构造一个存储名字信息的QStringList对象
    Dialog_AddStu m_dlgAddStu;
};
#endif // MAINWINDOW_H
