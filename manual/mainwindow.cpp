#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    this->resize(QSize(800,600).expandedTo(this->minimumSizeHint()));//设置初始化窗口大小
    this->setWindowIcon(QIcon(":/images/books.png"));//设置窗口标题栏图标
    this->setWindowTitle(tr("机械设计辅助手册"));//设置窗口标题栏标题
    //创建数据库连接

}

MainWindow::~MainWindow()
{}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}
