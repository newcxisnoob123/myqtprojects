#ifndef DIALOG_ADDSTU_H
#define DIALOG_ADDSTU_H
#include "stusql.h"
#include <QDialog>

namespace Ui {
class Dialog_AddStu;
}

class Dialog_AddStu : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_AddStu(QWidget *parent = nullptr);
    ~Dialog_AddStu();
    void setType(bool isSetAdd,StuInfo stuinfo={});//类型设置

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_save_clicked();

private:
    Ui::Dialog_AddStu *ui;
    bool m_isAdd;//复用对话空(判断是否为添加学生信息)
//    int m_id;//保存id值
    StuInfo m_info;
    stuSql*m_ptrUserSql;
};

#endif // DIALOG_ADDSTU_H
