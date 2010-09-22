#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QToolBar>
#include <QtGui/QAction>
#include <QtGui/QWidget>
#include <QtGui/QCloseEvent>
#include <QtGui/QMessageBox>
#include <QtGui/QLabel>
#include <QtGui/QComboBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtGui/QSplitter>
#include <QtGui/QTreeWidget>
#include <QtGui/QStandardItemModel>
#include <QSqlDriver>
#include <QtGui/QTreeWidgetItem>
#include <QStringList>
#include <QHeaderView>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>
#include <QtGui/QTableWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);//标题栏关闭事件

private slots:
    void about();//定义关于对话框
    void searchClick();//定义搜索
    void mainTreeClick(QTreeWidgetItem* treeItem,int col);//定义目录点击事件
    void about();//关于对话框
    void searchClick();//
    void mainTreeClick(QTreeWidgetItem* treeItem,int col);//定义鼠标单击树事件

private:
    void createActions();//声明事件
    void createMenus();//声明菜单栏
    void createToolBars();//声明工具栏
    void createStatusBar();//声明状态栏
    void createMainTree();//声明目录
    void readTable(QString);//声明表格

    QSqlDatabase db;//声明数据库
    bool connectOK;//数据库连接是否成功

    QMenu *fileMenu;//声明文件菜单
    QMenu *toolsMenu;//声明工具菜单
    QMenu *helpMenu;//声明帮助菜单

    QToolBar *mainToolBar;//声明主工具栏
    QLabel *searchLabel;//声明搜索标签
    QComboBox *searchCombo;//声明搜索框

    QAction *aboutAction;//声明关于动作
    QAction *exitAction;//声明退出动作
    QAction *searchAction;//声明搜索动作
    QAction *goHomeAction;//返回目录

    QSplitter *rightSplitter;//声明右窗口
    QSplitter *mainSplitter;//声明主窗口
    QLabel *picLabel;//默认右面板
    QTableWidget *dataTable;//声明表格
    QGraphicsScene *adScene;//声明广告场景
    QGraphicsView *adView;//声明广告视图
    QGraphicsScene *adScene;//广告场景
    QGraphicsView *adView;//广告片段
    QTableWidget *dataTable;
    QGraphicsScene noteScene;
    QGraphicsView noteView;

    QTreeWidget *mainTree;//声明目录
    QStandardItemModel *treeModel;//声明目录数据
};

#endif // MAINWINDOW_H
