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
        QMessageBox::critical(0,QObject::tr("�޷������ݿ�"),QObject::tr("���ݿ��ļ������ڣ�"));
        return 0;
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");  //ʹ��sqlite���ݿ�����
    db.setDatabaseName("../manual/manualdata.db3");  //����֮ǰ���������ݿ�
    bool connectOK = db.open();  //�����������ݿ�
    if(!connectOK)
    {
        QMessageBox::critical(0,QObject::tr("�޷������ݿ�"),db.lastError().databaseText());
        return 0;
    }
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
