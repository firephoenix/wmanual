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
    void closeEvent(QCloseEvent *event);//�ر��¼�

private slots:
    void about();
    void searchClick();
    void mainTreeClick(QTreeWidgetItem* treeItem,int col);

private:
    void createActions();//�����¼�
    void createMenus();//�����˵���
    void createToolBars();//����������
    void createStatusBar();//����״̬��
    void createMainTree();//����Ŀ¼
    void readTable(QString);//�������

    QSqlDatabase db;//�������ݿ�
    bool connectOK;//���ݿ������Ƿ�ɹ�

    QMenu *fileMenu;//�����ļ��˵�
    QMenu *toolsMenu;//�������߲˵�
    QMenu *helpMenu;//���������˵�

    QToolBar *mainToolBar;//������������
    QLabel *searchLabel;//����������ǩ
    QComboBox *searchCombo;//����������

    QAction *aboutAction;//�������ڶ���
    QAction *exitAction;//�����˳�����
    QAction *searchAction;//������������
    QAction *goHomeAction;//����Ŀ¼

    QSplitter *rightSplitter;//�����Ҵ���
    QSplitter *mainSplitter;//����������
    QLabel *picLabel;//Ĭ�������
    QTableWidget *dataTable;
    QGraphicsScene noteScene;
    QGraphicsView noteView;

    QTreeWidget *mainTree;//����Ŀ¼
    QStandardItemModel *treeModel;//����Ŀ¼����
};

#endif // MAINWINDOW_H
