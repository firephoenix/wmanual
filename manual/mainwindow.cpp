#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    this->setWindowIcon(QIcon(":/images/books.png"));
    this->setWindowTitle(tr("��е��Ƹ����ֲ�"));
}

MainWindow::~MainWindow()
{}
