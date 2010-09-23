#include <QApplication>
#include <QTextCodec>
#include <QFile>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    if(!QFile("../manual/manualdata.db3").exists())
    {
        QMessageBox::critical(0,QObject::tr("无法打开数据库"),QObject::tr("数据库文件不存在！"));
        return 0;
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");  //使用sqlite数据库驱动
    db.setDatabaseName("../manual/manualdata.db3");  //我们之前建立的数据库
    bool connectOK = db.open();  //尝试连接数据库
    if(!connectOK)
    {
        QMessageBox::critical(0,QObject::tr("无法打开数据库"),db.lastError().databaseText());
        return 0;
    }
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
