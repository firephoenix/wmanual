#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    this->resize(QSize(800, 600).expandedTo(this->minimumSizeHint()));//���ó�ʼ���ڴ�С
    this->setWindowIcon(QIcon(":/images/books.png"));//���ñ�����ͼ��
    this->setWindowTitle(tr("��е��Ƹ����ֲ�"));//���ñ���������
    if(this->createConnect())
    {
        mainSplitter = new QSplitter(Qt::Horizontal);//�����
        this->createActions();//��������
        this->createMenus();//�����˵���
        this->createToolBars();//����������
        this->createMenuTree();//����Ŀ¼��

        this->setCentralWidget(mainSplitter);//���������
    }
}

MainWindow::~MainWindow()
{}

//��������
bool MainWindow::createConnect()
{
    db = QSqlDatabase::addDatabase("QSQLITE");  //ʹ��sqlite���ݿ�����
    db.setDatabaseName("../manual/manualdata.db3");  //����֮ǰ���������ݿ�
    bool connectOK = db.open();  //�����������ݿ�
    if(!connectOK)//�ж������Ƿ�ɹ�
    {
        QMessageBox::critical(0,QObject::tr("�޷������ݿ�"),db.lastError().databaseText());//����ʧ�ܺ���ʾ��ʾ��
        return false;
    }
    return true;
}

void MainWindow::closeEvent(QCloseEvent *event)//�¼����رա�
{
    event->accept();
}

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

//����������
void MainWindow::createToolBars()
{
    mainToolBar = addToolBar(tr("����(&S)"));//����������
    searchLabel = new QLabel(tr(" ���� "));//����������ǩ
    mainToolBar->addWidget(searchLabel);//�����������
    searchCombo = new QComboBox;//����������
    searchCombo->clear();//���������
    searchCombo->setEditable(true);//����������ɱ༭
    searchCombo->insertItem(0,tr(""));//��������ӵ�һ��հ�
    searchCombo->setMinimumWidth(200);//������������С���

    mainToolBar->addWidget(searchCombo);//�����������������
    mainToolBar->addAction(searchAction);//���������������ť
    mainToolBar->addAction(goHomeAction);//������ӷ���Ŀ¼��ť
    mainToolBar->setMovable(false);//��������Ϊ���ɶ�
}

//����Ŀ¼��
void MainWindow::createMenuTree()
{
    QSqlQuery fstMenuQuery;//��firstmenus����
    QSqlQuery secMenuQuery;//��secondmenus����
    QSqlQuery thdMenuQuery;//��thirdmenus����
    if(fstMenuQuery.exec("SELECT menuitem, id FROM firstmenus;"))//�ж��������ݿ��Ƿ�ɹ�
    {
        int fstNumRows = 0;//�����������ص�����
        if(db.driver()->hasFeature(QSqlDriver::QuerySize))
        {
            fstNumRows = fstMenuQuery.size();
        }
        else
        {
            fstMenuQuery.last();
            fstNumRows = fstMenuQuery.at()+1;
            fstMenuQuery.seek(-1);
        }
        if(fstNumRows>0)
        {
            menuTree = new QTreeView();
            treeModel = new QStandardItemModel(fstNumRows,1);
            treeModel->setHeaderData(0,Qt::Horizontal,tr("Ŀ¼"));
            int fstInt = 0;
            while(fstMenuQuery.next())//����һ��Ŀ¼
            {
                QStandardItem *fstItem = new QStandardItem(fstMenuQuery.value(0).toString());
                treeModel->setItem(fstInt,fstItem);
                fstInt++;

                if(secMenuQuery.exec("SELECT menuitem, id FROM secondmenus WHERE parentid = "+ fstMenuQuery.value(1).toString()))
                {
                    int secNumRows = 0;
                    if(db.driver()->hasFeature(QSqlDriver::QuerySize))
                    {
                        secNumRows = secMenuQuery.size();
                    }
                    else
                    {
                        secMenuQuery.last();
                        secNumRows = secMenuQuery.at()+1;
                        secMenuQuery.seek(-1);
                    }
                    if(secNumRows>0)
                    {
                        while(secMenuQuery.next())//���ض���Ŀ¼
                        {
                            QStandardItem *secItem = new QStandardItem(secMenuQuery.value(0).toString());
                            fstItem->appendRow(secItem);

                            if(thdMenuQuery.exec("SELECT menuitem, id FROM thirdmenus WHERE parentid = "+ secMenuQuery.value(1).toString()))
                            {
                                int thdNumRows = 0;
                                if(db.driver()->hasFeature(QSqlDriver::QuerySize))
                                {
                                    thdNumRows = thdMenuQuery.size();
                                }
                                else
                                {
                                    thdMenuQuery.last();
                                    thdNumRows = thdMenuQuery.at()+1;
                                    thdMenuQuery.seek(-1);
                                }
                                if(thdNumRows>0)
                                {
                                    while(thdMenuQuery.next())//��������Ŀ¼
                                    {
                                        QStandardItem *thdItem = new QStandardItem(thdMenuQuery.value(0).toString());
                                        secItem->appendRow(thdItem);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            menuTree->setModel(treeModel);
            menuTree->setEditTriggers(QAbstractItemView::NoEditTriggers);//����Ϊ���ɱ༭
            mainSplitter->addWidget(menuTree);

            connect(menuTree,SIGNAL(clicked(QModelIndex)),this,SLOT(menuTreeClick(QModelIndex)));
        }
    }
}

void MainWindow::menuTreeClick(QModelIndex)
{
    int selectId = menuTree->selectionModel()->currentIndex().row();
    //int rowNo = menuTree->selectionModel()->currentIndex();
    // index = menuTree->selectionModel()->currentIndex();

    //int value = menuTree->sortByColumn(0);
    //QVariant val = menuTree->currentIndex().data(Qt::UserRole);
    QMessageBox::critical(0,QObject::tr("�޷������ݿ�"),QString().setNum(selectId));
    //QMessageBox::critical(0,QObject::tr("�޷������ݿ�"),val.toString());
}
