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
        this->readAd(1);//����������
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
        QMessageBox::critical(0,tr("�޷������ݿ�"),db.lastError().databaseText());//����ʧ�ܺ���ʾ��ʾ��
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
    if(fstMenuQuery.exec("SELECT menuitem, id FROM firstmenus;"))//�ж��������ݿ���һ��Ŀ¼
    {
        int fstNumRows = 0;//�����������ص�����
        if(db.driver()->hasFeature(QSqlDriver::QuerySize))//�ж������Ƿ����QuerySize
        {
            fstNumRows = fstMenuQuery.size();//�����ص���������fstNumRows
        }
        else
        {
            fstMenuQuery.last();//�������һ��
            fstNumRows = fstMenuQuery.at()+1;//�����ص���������fstNumRows
            fstMenuQuery.seek(-1);//���ص�һ��
        }
        if(fstNumRows>0)//�ж������õ��Ľ���Ƿ����0
        {
            menuTree = new QTreeView();//����Ŀ¼��
            treeModel = new QStandardItemModel(fstNumRows,1);//����Ŀ¼�Ĵ�С
            treeModel->setHeaderData(0,Qt::Horizontal,tr("Ŀ¼"));//����Ŀ¼ͷ
            int fstInt = 0;
            while(fstMenuQuery.next())//����һ��Ŀ¼
            {
                QStandardItem *fstItem = new QStandardItem(fstMenuQuery.value(0).toString());//�½�һ��Ŀ¼������
                fstItem->setData(1,Qt::UserRole);//����Ŀ¼����
                treeModel->setItem(fstInt,fstItem);//��һ��Ŀ¼���ص�Ŀ¼����
                fstInt++;//fstInt�Լ�

                if(secMenuQuery.exec("SELECT menuitem, id FROM secondmenus WHERE parentid = "+ fstMenuQuery.value(1).toString()))//�ж��Ƿ��ж���Ŀ¼
                {
                    int secNumRows = 0;//�����������ص�����
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
                    if(secNumRows>0)//�ж������õ��Ľ���Ƿ����0
                    {
                        while(secMenuQuery.next())//���ض���Ŀ¼
                        {
                            QStandardItem *secItem = new QStandardItem(secMenuQuery.value(0).toString());//�½�����Ŀ¼������
                            secItem->setData(2,Qt::UserRole);//����Ŀ¼����Ϊ2
                            fstItem->appendRow(secItem);//���ض���Ŀ¼

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
                                        QStandardItem *thdItem = new QStandardItem(thdMenuQuery.value(0).toString());//�½�����Ŀ¼������
                                        thdItem->setData(3,Qt::UserRole);//����Ŀ¼����Ϊ3
                                        secItem->appendRow(thdItem);//��������Ŀ¼
                                    }
                                }
                            }
                        }
                    }
                }
            }
            menuTree->setModel(treeModel);//����Ŀ¼����MODEL
            menuTree->setEditTriggers(QAbstractItemView::NoEditTriggers);//����Ϊ���ɱ༭
            menuTree->resizeColumnToContents(0);//�������Ŀ��
            mainSplitter->addWidget(menuTree);//��Ŀ¼���ص��������

            connect(menuTree,SIGNAL(clicked(QModelIndex)),this,SLOT(menuTreeClick(QModelIndex)));//���û������Ŀ¼ʱ������menuTreeClick����
        }
    }
}

void MainWindow::readAd(int adId)//��ȡ���
{
    adView = new AdGraphicsView;
    QSqlQuery adQuery;//�Թ�������
    if(adQuery.exec("SELECT aditem FROM adtable WHERE id = "+QString().setNum(adId)))
    {
        int adNumRows = 0;//�����������ص�����
        if(db.driver()->hasFeature(QSqlDriver::QuerySize))//�ж������Ƿ����QuerySize
        {
            adNumRows = adQuery.size();//�����ص���������fstNumRows
        }
        else
        {
            adQuery.last();//�������һ��
            adNumRows = adQuery.at()+1;//�����ص���������fstNumRows
            adQuery.seek(-1);//���ص�һ��
        }
        if(adNumRows>0)//�ж��Ƿ����0
        {
            while(adQuery.next())
            {
                this->adView->readAd(adQuery.value(0).toByteArray());//��ȡ���
            }            
        }
    }
    mainSplitter->addWidget(this->adView);
}

void MainWindow::menuTreeClick(QModelIndex)
{
    QVariant clickedItem = menuTree->selectionModel()->currentIndex().data(Qt::UserRole);
    QModelIndex index = menuTree->selectionModel()->currentIndex().child(0,0);
    if(index.data(Qt::DisplayRole).toString()==NULL)
    {
        switch(clickedItem.toInt())
        {
        case 1:
            {
                QMessageBox::critical(0,tr("�޷������ݿ�"),tr("1"));
            }
            break;

        case 2:
            {
                QMessageBox::critical(0,tr("�޷������ݿ�"),tr("2"));
            }
            break;

        case 3:
            {
                QMessageBox::critical(0,tr("�޷������ݿ�"),tr("3"));
            }
            break;
        default:
            break;
        }
    }
}
