#include <QApplication>
#include <QTextCodec>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    MainWindow mainWindow;
    if(!QFile("../manual/manualdata.db3").exists())//�ж����ݿ��ļ��Ƿ����
    {
        QMessageBox::critical(0,QObject::tr("�޷������ݿ�"),QObject::tr("���ݿ��ļ������ڣ�"));//���ݿ��ļ�����������ʾ��ʾ��
        return 0;
    }
    mainWindow.show();
    return app.exec();
}
