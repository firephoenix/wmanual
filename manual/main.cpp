#include <QApplication>
#include <QTextCodec>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
