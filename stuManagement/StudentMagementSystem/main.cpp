#include "mainwindow.h"
#include "page_login.h"
#include <QApplication>
#include "stusql.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   // w.show();
    stuSql sql;//创建一个stuSql对象
    return a.exec();
}
