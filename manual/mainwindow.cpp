#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    this->resize(QSize(800, 600).expandedTo(this->minimumSizeHint()));//设置初始窗口大小
    this->setWindowIcon(QIcon(":/images/books.png"));//设置标题栏图标
    this->setWindowTitle(tr("机械设计辅助手册"));//设置标题栏标题
    if(this->createConnect())
    {
        mainSplitter = new QSplitter(Qt::Horizontal);//主面板
        this->createActions();//创建动作
        this->createMenus();//创建菜单栏
        this->createToolBars();//创建工具栏
        this->createMenuTree();//创建目录树

        this->setCentralWidget(mainSplitter);//加载主面板
    }
}

MainWindow::~MainWindow()
{}

//创建连接
bool MainWindow::createConnect()
{
    db = QSqlDatabase::addDatabase("QSQLITE");  //使用sqlite数据库驱动
    db.setDatabaseName("../manual/manualdata.db3");  //我们之前建立的数据库
    bool connectOK = db.open();  //尝试连接数据库
    if(!connectOK)//判断连接是否成功
    {
        QMessageBox::critical(0,QObject::tr("无法打开数据库"),db.lastError().databaseText());//连接失败后显示提示框
        return false;
    }
    return true;
}

void MainWindow::closeEvent(QCloseEvent *event)//事件“关闭”
{
    event->accept();
}

//创建动作
void MainWindow::createActions()
{
    //退出
    exitAction = new QAction(tr("退出(&X)"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    //对话框关于
    aboutAction = new QAction(tr("关于(&A)"), this);

    //搜索
    searchAction = new QAction(tr("搜索(&S)"),this);
    searchAction->setIcon(QIcon(":/images/search.png"));
    searchAction->setStatusTip(tr("搜索相关内容"));

    //返回目录动作
    goHomeAction = new QAction(tr("返回目录"), this);
    goHomeAction->setIcon(QIcon(":/images/home.png"));
    goHomeAction->setStatusTip(tr("返回目录"));
}

//创建菜单栏
void MainWindow::createMenus()
{
    //菜单“文件”
    fileMenu = menuBar()->addMenu(tr("文件(&F)"));
    fileMenu->addAction(exitAction);

    //菜单“工具”
    toolsMenu = menuBar()->addMenu(tr("工具(&T)"));

    //菜单“帮助”
    helpMenu = menuBar()->addMenu(tr("帮助(&H)"));
    helpMenu->addAction(aboutAction);
}

//创建工具栏
void MainWindow::createToolBars()
{
    mainToolBar = addToolBar(tr("搜索(&S)"));//创建工具条
    searchLabel = new QLabel(tr(" 搜索 "));//创建搜索标签
    mainToolBar->addWidget(searchLabel);//添加至工具条
    searchCombo = new QComboBox;//创建搜索框
    searchCombo->clear();//搜索框清空
    searchCombo->setEditable(true);//设置搜索框可编辑
    searchCombo->insertItem(0,tr(""));//搜索框添加第一项空白
    searchCombo->setMinimumWidth(200);//设置搜索框最小宽度

    mainToolBar->addWidget(searchCombo);//工具条上添加搜索框
    mainToolBar->addAction(searchAction);//工具条添加搜索按钮
    mainToolBar->addAction(goHomeAction);//工具添加返回目录按钮
    mainToolBar->setMovable(false);//工具设置为不可动
}

//创建目录树
void MainWindow::createMenuTree()
{
    QSqlQuery fstMenuQuery;//对firstmenus搜索
    QSqlQuery secMenuQuery;//对secondmenus搜索
    QSqlQuery thdMenuQuery;//对thirdmenus搜索
    if(fstMenuQuery.exec("SELECT menuitem, id FROM firstmenus;"))//判断搜索数据库是否成功
    {
        int fstNumRows = 0;//定义搜索返回的行数
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
            treeModel->setHeaderData(0,Qt::Horizontal,tr("目录"));
            int fstInt = 0;
            while(fstMenuQuery.next())//加载一级目录
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
                        while(secMenuQuery.next())//加载二级目录
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
                                    while(thdMenuQuery.next())//加载三级目录
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
            menuTree->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置为不可编辑
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
    QMessageBox::critical(0,QObject::tr("无法打开数据库"),QString().setNum(selectId));
    //QMessageBox::critical(0,QObject::tr("无法打开数据库"),val.toString());
}
