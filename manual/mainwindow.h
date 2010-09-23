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
    MainWindow(QWidget *parent = 0);// �ṹ����
    ~MainWindow();//��������

private:
    void createActions();//��������
    void createMenus();//�����˵���
    void createToolBars();//����������

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

};

#endif // MAINWINDOW_H
