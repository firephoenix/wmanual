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
#include <QtGui/QTableView>
#include "adgraphicsview.h"
#include "ProxyModelWithHeaderModels.h"


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
    void createAd();//������
    void createTable();//������
    void readAd(int adId);//��ȡ���
    void readTable(int tableId);//��ȡ������
    void buildTableHeaderModel(QStandardItemModel& headerModel);//�󶨱�ͷ����
    void buildTableDataModel(QStandardItemModel& model);//������

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
    QSplitter *rightSplitter;//�����
    QTableView *dataTable;//���ݱ�

    QSplitter *mainSplitter;//���������

    AdGraphicsView *adView;//���
};

#endif // MAINWINDOW_H
