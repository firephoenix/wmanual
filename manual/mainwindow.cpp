#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    this->resize(QSize(800,600).expandedTo(this->minimumSizeHint()));//���ó�ʼ�����ڴ�С
    this->setWindowIcon(QIcon(":/images/books.png"));//���ô��ڱ�����ͼ��
    this->setWindowTitle(tr("��е��Ƹ����ֲ�"));//���ô��ڱ���������
    //�������ݿ�����

}

MainWindow::~MainWindow()
{}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}
