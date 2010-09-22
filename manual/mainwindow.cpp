#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(QSize(800, 600).expandedTo(this->minimumSizeHint()));
    setWindowIcon(QIcon(":/images/books.png"));//设置窗口标题栏图标
    setWindowTitle(tr("机械设计辅助手册"));//设置窗口标题栏标题文字
    this->resize(QSize(800, 600).expandedTo(this->minimumSizeHint()));//设置初始化窗口大小
    setWindowIcon(QIcon(":/images/books.png"));//设置窗口图标
    setWindowTitle(tr("机械设计辅助手册"));//设置标题兰标题
    db = QSqlDatabase::addDatabase("QSQLITE");  //使用sqlite数据库驱动
    db.setDatabaseName("../manual/manualdata.db3");  //我们之前建立的数据库
    connectOK = db.open();  //尝试连接数据库
    if(connectOK)//判断连接数据库是否成功
    {
        createActions();//创建动作
        createMenus();//创建菜单栏
        createToolBars();//创建工具栏
        mainSplitter = new QSplitter(Qt::Horizontal);//主窗口,为水平分割的两个面板
        mainTree = new QTreeWidget;//定义目录树
        mainTree->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);//设置水平滚动条
        createMainTree();//创建目录树
        mainSplitter->addWidget(mainTree);
        mainTree = new QTreeWidget;//目录树
        mainTree->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);// 定义水平滚动条，当需要时就显示
        createMainTree();//创建目录树
        mainSplitter->addWidget(mainTree);//主窗口加载目录树
        //defaultScene = new QGraphicsScene;
        //defaultScene->addText("hello world!");//默认右窗口
        //defaultView = new QGraphicsView(defaultScene);
        //mainSplitter->addWidget(defaultView);
        picLabel = new QLabel(mainSplitter,0);
        QPixmap picPix(":/images/first.jpg");
        picLabel->setPixmap(picPix);
        mainSplitter->addWidget(picLabel);

        dataTable = new QTableWidget;
        dataTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        dataTable->setSelectionMode(QAbstractItemView::SingleSelection);
        dataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        rightSplitter = new QSplitter(Qt::Vertical);//右边窗口

        rightSplitter->setStretchFactor(1,1);
        rightSplitter->addWidget(dataTable);
        rightSplitter->hide();
        mainSplitter->addWidget(rightSplitter);
        mainSplitter->setStretchFactor(1,1);
        setCentralWidget(mainSplitter);

        createStatusBar();//创建状态栏
    }
    else
    {//打开数据库失败，显示数据库返回的失败描述
        QMessageBox::critical(0,tr("无法打开数据库"),db.lastError().databaseText());
    }
    //db.close();
}

MainWindow::~MainWindow()
{}

void MainWindow::createActions()//动作
{
    //退出
    exitAction = new QAction(tr("退出(&X)"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    //对话框关于
    aboutAction = new QAction(tr("关于(&A)"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    //搜索
    searchAction = new QAction(tr("搜索(&S)"),this);
    searchAction->setIcon(QIcon(":/images/search.png"));
    searchAction->setStatusTip(tr("搜索相关内容"));
    connect(searchAction, SIGNAL(triggered()),this,SLOT(searchClick()));

    //返回目录动作
    goHomeAction = new QAction(tr("返回目录"), this);
    goHomeAction->setIcon(QIcon(":/images/home.png"));
    goHomeAction->setStatusTip(tr("返回目录"));
    connect(goHomeAction, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()//菜单栏
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

void MainWindow::createToolBars()//工具栏
{
    mainToolBar = addToolBar(tr("搜索(&S)"));
    searchLabel = new QLabel(tr(" 搜索 "));
    mainToolBar->addWidget(searchLabel);
    searchCombo = new QComboBox;
    searchCombo->clear();
    searchCombo->setEditable(true);
    searchCombo->insertItem(0,tr(""));
    searchCombo->setMinimumWidth(200);
    QSqlQuery searchQuery;  //新建一个查询的实例
    if (searchQuery.exec("SELECT keyword FROM search ORDER BY count DESC limit 10;"))   //尝试列出搜索表的前10项记录
    {//本次查询成功
        int searchIndex = 1;
        while(searchQuery.next())
        {
            searchCombo->insertItem(searchIndex,searchQuery.value(0).toString());
            searchIndex++;
        }
    }
    mainToolBar->addWidget(searchCombo);
    mainToolBar->addAction(searchAction);
    mainToolBar->addAction(goHomeAction);
    mainToolBar->setMovable(false);
}

void MainWindow::closeEvent(QCloseEvent *event)//事件“关闭”
{
    event->accept();
}

void MainWindow::createStatusBar()//状态栏
{

}

void MainWindow::about()//对话框关于
{
    QMessageBox::about(this, tr("关于机械设计辅助手册"),
                       tr("<h2>机械设计辅助手册 0.1</h2>"
                          "<p>Copyright &copy; 2010 凤凰工作室"
                          "<p>机械设计辅助手册是一个工程师在机械设计时的参考手册."));
}

void MainWindow::searchClick()
{
    this->about();
}

void MainWindow::createMainTree()//创建目录树
{
    QStringList treeColumnTitle;
    treeColumnTitle.append(QString::fromLocal8Bit("目录"));
    mainTree->setHeaderLabels(treeColumnTitle);
    mainTree->header()->setResizeMode(QHeaderView::ResizeToContents );
    mainTree->header()->setStretchLastSection(true);
    QSqlQuery treeFirstQuery;
    QSqlQuery treeSecondQuery;
    QSqlQuery treeThirdQuery;
    if(treeFirstQuery.exec("SELECT menuitem, id FROM firstmenus;"))
    {
       int treeNumRows = 0;
       if(db.driver()->hasFeature(QSqlDriver::QuerySize))
       {
           treeNumRows = treeFirstQuery.size();
       }
       else
       {
           treeFirstQuery.last();
           treeNumRows = treeFirstQuery.at()+1;
           treeFirstQuery.seek(-1);
       }
       if(treeNumRows>0)
        {
            while(treeFirstQuery.next())
            {
                QTreeWidgetItem *firstMenus = new QTreeWidgetItem(mainTree);
                firstMenus->setText(0,treeFirstQuery.value(0).toString());
                firstMenus->setData(0,Qt::UserRole,1);
                if(treeSecondQuery.exec("SELECT menuitem, id FROM secondmenus where parentid = "+treeFirstQuery.value(1).toString()))
                {
                    int treeSecNumRows = 0;
                    if(db.driver()->hasFeature(QSqlDriver::QuerySize))
                    {
                        treeSecNumRows = treeSecondQuery.size();
                    }
                    else
                    {
                        treeSecondQuery.last();
                        treeSecNumRows = treeSecondQuery.at()+1;
                        treeSecondQuery.seek(-1);
                    }
                    if(treeSecNumRows>0)
                    {
                        while(treeSecondQuery.next())
                        {
                            QTreeWidgetItem *secMenus = new QTreeWidgetItem(firstMenus);
                            secMenus->setText(0,treeSecondQuery.value(0).toString());
                            secMenus->setData(0,Qt::UserRole,2);
                            if(treeThirdQuery.exec("SELECT menuitem, id FROM thirdmenus where parentid = "+treeSecondQuery.value(1).toString()))
                            {
                                int treeThdNumRows = 0;
                                if(db.driver()->hasFeature(QSqlDriver::QuerySize))
                                {
                                    treeThdNumRows = treeThirdQuery.size();
                                }
                                else
                                {
                                    treeThirdQuery.last();
                                    treeThdNumRows = treeThirdQuery.at()+1;
                                    treeThirdQuery.seek(-1);
                                }
                                if(treeThdNumRows>0)
                                {
                                    while(treeThirdQuery.next())
                                    {
                                        QTreeWidgetItem *thdMenus = new QTreeWidgetItem(secMenus);
                                        thdMenus->setText(0,treeThirdQuery.value(0).toString());
                                        thdMenus->setData(0,Qt::UserRole,3);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
   }
    connect(mainTree,SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(mainTreeClick(QTreeWidgetItem*,int)));
}

void MainWindow::mainTreeClick(QTreeWidgetItem* treeItem,int)
{
    QSqlQuery treeClickQuery;
    mainTree->currentItem();
    QVariant value = mainTree->currentItem()->data(0,Qt::UserRole);
    int valueInt = value.toInt();
    int hasChildren = treeItem->childCount();
    if(hasChildren>0)
    {
        if(!(rightSplitter->isHidden()))
        {
            rightSplitter->hide();
        }
        picLabel->show();
    }
    else
    {
        if(!(picLabel->isHidden()))
        {
            picLabel->hide();
            rightSplitter->show();
        }
        switch(valueInt)
        {
        case 1:
            break;
        case 2:
            dataTable->clear();
            if(treeClickQuery.exec("SELECT tableid FROM secondmenus WHERE menuitem = '"+mainTree->currentItem()->text(0)+"';"))
            {
                while(treeClickQuery.next())
                {
                    this->readTable(treeClickQuery.value(0).toString());
                }
            }
            break;
        case 3:
            dataTable->clear();
            if(treeClickQuery.exec("SELECT tableid FROM thirdmenus WHERE menuitem = '"+mainTree->currentItem()->text(0)+"';"))
            {
                while(treeClickQuery.next())
                {
                    this->readTable(treeClickQuery.value(0).toString());
                }
            }
            break;
        default:
            break;
        }
    }
}

void MainWindow::readTable(QString tableid)
{
    QStringList tableHeaders;
    QSqlQuery headerQuery;
    QSqlQuery bodyQuery;
    QSqlQuery noteQuery;

    if(headerQuery.exec("SELECT headitem FROM tableheader WHERE tableid = '"+ tableid+"';"))
    {
        int tableNumRows = 0;        
        if(db.driver()->hasFeature(QSqlDriver::QuerySize))
        {
            tableNumRows = headerQuery.size();
        }
        else
        {
            headerQuery.last();
            tableNumRows = headerQuery.at()+1;
            headerQuery.seek(-1);
        }
        if(tableNumRows>0)
        {
            dataTable->setColumnCount(tableNumRows);
            while(headerQuery.next())
            {
                tableHeaders.append(headerQuery.value(0).toString());
            }
            dataTable->setHorizontalHeaderLabels(tableHeaders);
            dataTable->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents );
            if(bodyQuery.exec("SELECT * FROM tablebody WHERE tableid = '"+tableid+"';"))
            {
                int tableNumCols = 0;
                if(db.driver()->hasFeature(QSqlDriver::QuerySize))
                {
                    tableNumCols = bodyQuery.size();
                }
                else
                {
                    bodyQuery.last();
                    tableNumCols = bodyQuery.at()+1;
                    bodyQuery.seek(-1);
                }
                int cols = tableNumCols/tableNumRows;
                QMessageBox::about(this, tr("关于机械设计辅助手册"),QString().setNum(cols));
                dataTable->setRowCount(cols);
                for(int i=0; i<cols; i++)
                {
                    for(int j=0; j<tableNumRows; j++)
                    {
                        bodyQuery.next();
                        dataTable->setItem(i,j,new QTableWidgetItem(bodyQuery.value(1).toString()));
                    }
                }
            }
        }
    }
    if(noteQuery.exec("SELECT noteitem FROM tablenote WHERE tableid = '"+tableid+"';"))
    {
        int noteNum = 0;
        if(db.driver()->hasFeature(QSqlDriver::QuerySize))
        {
            noteNum = noteQuery.size();
        }
        else
        {
            noteQuery.last();
            noteNum = noteQuery.at()+1;
            noteQuery.seek(-1);
        }
        if(noteNum>0)
        {
            while(noteQuery.next())
            {

            }
        }
    }
}
