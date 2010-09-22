#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QCloseEvent>
#include <QSqlDatabase>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);//�ṹ����
    ~MainWindow();//��������

protected:
    void closeEvent(QCloseEvent *event);//�������ر��¼�

private slots:
    void about();//������ڶԻ���

private:
    QSqlDatabase db;//�������ݿ�
    bool conneckOK;//���ݿ������Ƿ�ɹ�

    void createActions();//��������
    void createMenus();//�����˵�
    void createToolBars();//����������
    void createMenuTree();//����Ŀ¼��
    void createTable();//�������

};

#endif // MAINWINDOW_H
