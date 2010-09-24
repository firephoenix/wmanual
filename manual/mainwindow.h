#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QSqlDatabase>
#include <QtGui/QMessageBox>
#include <QSqlError>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QToolBar>
#include <QtGui/QLabel>
#include <QtGui/QComboBox>
#include <QtGui/QTreeView>
#include <QtGui/QStandardItemModel>
#include <QSqlQuery>
#include <QFile>
#include <QSqlDriver>
#include <QtGui/QCloseEvent>
#include <QtGui/QSplitter>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);// 结构函数
    ~MainWindow();//析构函数

protected:
    void closeEvent(QCloseEvent *event);//关闭事件

private slots:
    void menuTreeClick(QModelIndex);

private:    
    bool createConnect();//创建连接
    void createActions();//创建动作
    void createMenus();//创建菜单栏
    void createToolBars();//创建工具栏
    void createMenuTree();//创建目录树

private:
    QAction *exitAction;//动作退出
    QAction *aboutAction;//动作关于
    QAction *searchAction;//动作搜索
    QAction *goHomeAction;//动作返回目录

    QMenu *fileMenu;//声明文件菜单
    QMenu *toolsMenu;//声明工具菜单
    QMenu *helpMenu;//声明帮助菜单

    QToolBar *mainToolBar;//声明主工具栏
    QLabel *searchLabel;//声明搜索标签
    QComboBox *searchCombo;//声明搜索框

    QSqlDatabase db;//声明数据库
    QTreeView *menuTree;//声明目录树
    QStandardItemModel *treeModel;//声明TREEMODE

    QSplitter *mainSplitter;//声明主面板

};

#endif // MAINWINDOW_H
