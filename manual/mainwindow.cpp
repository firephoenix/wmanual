#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    this->setWindowIcon(QIcon(":/images/books.png"));
    this->setWindowTitle(tr("��е��Ƹ����ֲ�"));

    menuBar = new MenuBar;
    this->setMenuBar(menuBar);

    this->resize(QSize(800,600).expandedTo(this->minimumSizeHint()));
}

MainWindow::~MainWindow()
{}
