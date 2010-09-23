#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    this->resize(QSize(800, 600).expandedTo(this->minimumSizeHint()));//���ó�ʼ���ڴ�С
    this->setWindowIcon(QIcon(":/images/books.png"));//���ñ�����ͼ��
    this->setWindowTitle(tr("��е��Ƹ����ֲ�"));//���ñ���������
    this->createActions();//��������
    this->createMenus();//�����˵���
    this->createToolBars();//����������
}

MainWindow::~MainWindow()
{}

//��������
void MainWindow::createActions()
{
    //�˳�
    exitAction = new QAction(tr("�˳�(&X)"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    //�Ի������
    aboutAction = new QAction(tr("����(&A)"), this);

    //����
    searchAction = new QAction(tr("����(&S)"),this);
    searchAction->setIcon(QIcon(":/images/search.png"));
    searchAction->setStatusTip(tr("�����������"));

    //����Ŀ¼����
    goHomeAction = new QAction(tr("����Ŀ¼"), this);
    goHomeAction->setIcon(QIcon(":/images/home.png"));
    goHomeAction->setStatusTip(tr("����Ŀ¼"));
}

//�����˵���
void MainWindow::createMenus()
{
    //�˵����ļ���
    fileMenu = menuBar()->addMenu(tr("�ļ�(&F)"));
    fileMenu->addAction(exitAction);

    //�˵������ߡ�
    toolsMenu = menuBar()->addMenu(tr("����(&T)"));

    //�˵���������
    helpMenu = menuBar()->addMenu(tr("����(&H)"));
    helpMenu->addAction(aboutAction);
}

void MainWindow::createToolBars()//������
{
    mainToolBar = addToolBar(tr("����(&S)"));
    searchLabel = new QLabel(tr(" ���� "));
    mainToolBar->addWidget(searchLabel);
    searchCombo = new QComboBox;
    searchCombo->clear();
    searchCombo->setEditable(true);
    searchCombo->insertItem(0,tr(""));
    searchCombo->setMinimumWidth(200);

    mainToolBar->addWidget(searchCombo);
    mainToolBar->addAction(searchAction);
    mainToolBar->addAction(goHomeAction);
    mainToolBar->setMovable(false);
}
