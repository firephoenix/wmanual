#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QCloseEvent>
#include <QSqlDatabase>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);//结构函数
    ~MainWindow();//析构函数

protected:
    void closeEvent(QCloseEvent *event);//标题栏关闭事件

private slots:
    void about();//定义关于对话框

private:
    QSqlDatabase db;//声明数据库
    bool conneckOK;//数据库连接是否成功

    void createActions();//声明动作
    void createMenus();//声明菜单
    void createToolBars();//声明工具栏
    void createMenuTree();//声明目录树
    void createTable();//声明表格

};

#endif // MAINWINDOW_H
