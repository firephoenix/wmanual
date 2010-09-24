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
    MainWindow(QWidget *parent = 0);// �ṹ����
    ~MainWindow();//��������

protected:
    void closeEvent(QCloseEvent *event);//�ر��¼�

private slots:
    void menuTreeClick(QModelIndex);

private:    
    bool createConnect();//��������
    void createActions();//��������
    void createMenus();//�����˵���
    void createToolBars();//����������
    void createMenuTree();//����Ŀ¼��

private:
    QAction *exitAction;//�����˳�
    QAction *aboutAction;//��������
    QAction *searchAction;//��������
    QAction *goHomeAction;//��������Ŀ¼

    QMenu *fileMenu;//�����ļ��˵�
    QMenu *toolsMenu;//�������߲˵�
    QMenu *helpMenu;//���������˵�

    QToolBar *mainToolBar;//������������
    QLabel *searchLabel;//����������ǩ
    QComboBox *searchCombo;//����������

    QSqlDatabase db;//�������ݿ�
    QTreeView *menuTree;//����Ŀ¼��
    QStandardItemModel *treeModel;//����TREEMODE

    QSplitter *mainSplitter;//���������

};

#endif // MAINWINDOW_H
