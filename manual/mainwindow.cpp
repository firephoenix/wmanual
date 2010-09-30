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
        this->readAd(1);//创建广告面板
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
        QMessageBox::critical(0,tr("无法打开数据库"),db.lastError().databaseText());//连接失败后显示提示框
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
    if(fstMenuQuery.exec("SELECT menuitem, id FROM firstmenus;"))//判断搜索数据库中一级目录
    {
        int fstNumRows = 0;//定义搜索返回的行数
        if(db.driver()->hasFeature(QSqlDriver::QuerySize))//判断驱动是否包含QuerySize
        {
            fstNumRows = fstMenuQuery.size();//将返回的行数赋于fstNumRows
        }
        else
        {
            fstMenuQuery.last();//移至最后一行
            fstNumRows = fstMenuQuery.at()+1;//将返回的行数赋于fstNumRows
            fstMenuQuery.seek(-1);//返回第一行
        }
        if(fstNumRows>0)//判断搜索得到的结果是否大于0
        {
            menuTree = new QTreeView();//建立目录树
            treeModel = new QStandardItemModel(fstNumRows,1);//设置目录的大小
            treeModel->setHeaderData(0,Qt::Horizontal,tr("目录"));//设置目录头
            int fstInt = 0;
            while(fstMenuQuery.next())//加载一级目录
            {
                QStandardItem *fstItem = new QStandardItem(fstMenuQuery.value(0).toString());//新建一级目录各子项
                fstItem->setData(1,Qt::UserRole);//设置目录阶数
                treeModel->setItem(fstInt,fstItem);//将一级目录加载到目录树中
                fstInt++;//fstInt自加

                if(secMenuQuery.exec("SELECT menuitem, id FROM secondmenus WHERE parentid = "+ fstMenuQuery.value(1).toString()))//判断是否有二级目录
                {
                    int secNumRows = 0;//定义搜索返回的行数
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
                    if(secNumRows>0)//判断搜索得到的结果是否大于0
                    {
                        while(secMenuQuery.next())//加载二级目录
                        {
                            QStandardItem *secItem = new QStandardItem(secMenuQuery.value(0).toString());//新建二级目录各子项
                            secItem->setData(2,Qt::UserRole);//设置目录阶数为2
                            fstItem->appendRow(secItem);//加载二级目录

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
                                        QStandardItem *thdItem = new QStandardItem(thdMenuQuery.value(0).toString());//新建三级目录各子项
                                        thdItem->setData(3,Qt::UserRole);//设置目录阶数为3
                                        secItem->appendRow(thdItem);//加载三级目录
                                    }
                                }
                            }
                        }
                    }
                }
            }
            menuTree->setModel(treeModel);//设置目录树的MODEL
            menuTree->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置为不可编辑
            menuTree->resizeColumnToContents(0);//设置树的宽度
            mainSplitter->addWidget(menuTree);//将目录加载到主面板中

            connect(menuTree,SIGNAL(clicked(QModelIndex)),this,SLOT(menuTreeClick(QModelIndex)));//当用户点击树目录时，启动menuTreeClick函数
        }
    }
}

void MainWindow::readAd(int adId)//读取广告
{
    adView = new AdGraphicsView;
    QSqlQuery adQuery;//对广告表单搜索
    if(adQuery.exec("SELECT aditem FROM adtable WHERE id = "+QString().setNum(adId)))
    {
        int adNumRows = 0;//定义搜索返回的行数
        if(db.driver()->hasFeature(QSqlDriver::QuerySize))//判断驱动是否包含QuerySize
        {
            adNumRows = adQuery.size();//将返回的行数赋于fstNumRows
        }
        else
        {
            adQuery.last();//移至最后一行
            adNumRows = adQuery.at()+1;//将返回的行数赋于fstNumRows
            adQuery.seek(-1);//返回第一行
        }
        if(adNumRows>0)//判断是否大于0
        {
            while(adQuery.next())
            {
                this->adView->readAd(adQuery.value(0).toByteArray());//读取广告
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
                QMessageBox::critical(0,tr("无法打开数据库"),tr("1"));
            }
            break;

        case 2:
            {
                QMessageBox::critical(0,tr("无法打开数据库"),tr("2"));
            }
            break;

        case 3:
            {
                QMessageBox::critical(0,tr("无法打开数据库"),tr("3"));
            }
            break;
        default:
            break;
        }
    }
}
