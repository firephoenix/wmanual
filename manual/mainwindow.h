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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);// 结构函数
    ~MainWindow();//析构函数

private:
    void createActions();//创建动作
    void createMenus();//创建菜单栏
    void createToolBars();//创建工具栏

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

};

#endif // MAINWINDOW_H
