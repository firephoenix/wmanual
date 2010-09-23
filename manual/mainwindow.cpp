#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    this->resize(QSize(800, 600).expandedTo(this->minimumSizeHint()));//设置初始窗口大小
    this->setWindowIcon(QIcon(":/images/books.png"));//设置标题栏图标
    this->setWindowTitle(tr("机械设计辅助手册"));//设置标题栏标题
    this->createActions();//创建动作
    this->createMenus();//创建菜单栏
    this->createToolBars();//创建工具栏
}

MainWindow::~MainWindow()
{}

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

    mainToolBar->addWidget(searchCombo);
    mainToolBar->addAction(searchAction);
    mainToolBar->addAction(goHomeAction);
    mainToolBar->setMovable(false);
}
