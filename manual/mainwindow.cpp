#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(QSize(800, 600).expandedTo(this->minimumSizeHint()));
    setWindowIcon(QIcon(":/images/books.png"));//���ô��ڱ�����ͼ��
    setWindowTitle(tr("��е��Ƹ����ֲ�"));//���ô��ڱ�������������
    this->resize(QSize(800, 600).expandedTo(this->minimumSizeHint()));//���ó�ʼ�����ڴ�С
    setWindowIcon(QIcon(":/images/books.png"));//���ô���ͼ��
    setWindowTitle(tr("��е��Ƹ����ֲ�"));//���ñ���������
    db = QSqlDatabase::addDatabase("QSQLITE");  //ʹ��sqlite���ݿ�����
    db.setDatabaseName("../manual/manualdata.db3");  //����֮ǰ���������ݿ�
    connectOK = db.open();  //�����������ݿ�
    if(connectOK)//�ж��������ݿ��Ƿ�ɹ�
    {
        createActions();//��������
        createMenus();//�����˵���
        createToolBars();//����������
        mainSplitter = new QSplitter(Qt::Horizontal);//������,Ϊˮƽ�ָ���������
        mainTree = new QTreeWidget;//����Ŀ¼��
        mainTree->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);//����ˮƽ������
        createMainTree();//����Ŀ¼��
        mainSplitter->addWidget(mainTree);
        mainTree = new QTreeWidget;//Ŀ¼��
        mainTree->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);// ����ˮƽ������������Ҫʱ����ʾ
        createMainTree();//����Ŀ¼��
        mainSplitter->addWidget(mainTree);//�����ڼ���Ŀ¼��
        //defaultScene = new QGraphicsScene;
        //defaultScene->addText("hello world!");//Ĭ���Ҵ���
        //defaultView = new QGraphicsView(defaultScene);
        //mainSplitter->addWidget(defaultView);
        picLabel = new QLabel(mainSplitter,0);
        QPixmap picPix(":/images/first.jpg");
        picLabel->setPixmap(picPix);
        mainSplitter->addWidget(picLabel);

        dataTable = new QTableWidget;
        dataTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        dataTable->setSelectionMode(QAbstractItemView::SingleSelection);
        dataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        rightSplitter = new QSplitter(Qt::Vertical);//�ұߴ���

        rightSplitter->setStretchFactor(1,1);
        rightSplitter->addWidget(dataTable);
        rightSplitter->hide();
        mainSplitter->addWidget(rightSplitter);
        mainSplitter->setStretchFactor(1,1);
        setCentralWidget(mainSplitter);

        createStatusBar();//����״̬��
    }
    else
    {//�����ݿ�ʧ�ܣ���ʾ���ݿⷵ�ص�ʧ������
        QMessageBox::critical(0,tr("�޷������ݿ�"),db.lastError().databaseText());
    }
    //db.close();
}

MainWindow::~MainWindow()
{}

void MainWindow::createActions()//����
{
    //�˳�
    exitAction = new QAction(tr("�˳�(&X)"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    //�Ի������
    aboutAction = new QAction(tr("����(&A)"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    //����
    searchAction = new QAction(tr("����(&S)"),this);
    searchAction->setIcon(QIcon(":/images/search.png"));
    searchAction->setStatusTip(tr("�����������"));
    connect(searchAction, SIGNAL(triggered()),this,SLOT(searchClick()));

    //����Ŀ¼����
    goHomeAction = new QAction(tr("����Ŀ¼"), this);
    goHomeAction->setIcon(QIcon(":/images/home.png"));
    goHomeAction->setStatusTip(tr("����Ŀ¼"));
    connect(goHomeAction, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()//�˵���
{
    //�˵����ļ���
    fileMenu = menuBar()->addMenu(tr("�ļ�(&F)"));
    fileMenu->addAction(exitAction);

    //�˵������ߡ�
    toolsMenu = menuBar()->addMenu(tr("����(&T)"));

    //�˵���������
    helpMenu = menuBar()->addMenu(tr("����(&H)"));
    helpMenu->addAction(aboutAction);
}

void MainWindow::createToolBars()//������
{
    mainToolBar = addToolBar(tr("����(&S)"));
    searchLabel = new QLabel(tr(" ���� "));
    mainToolBar->addWidget(searchLabel);
    searchCombo = new QComboBox;
    searchCombo->clear();
    searchCombo->setEditable(true);
    searchCombo->insertItem(0,tr(""));
    searchCombo->setMinimumWidth(200);
    QSqlQuery searchQuery;  //�½�һ����ѯ��ʵ��
    if (searchQuery.exec("SELECT keyword FROM search ORDER BY count DESC limit 10;"))   //�����г��������ǰ10���¼
    {//���β�ѯ�ɹ�
        int searchIndex = 1;
        while(searchQuery.next())
        {
            searchCombo->insertItem(searchIndex,searchQuery.value(0).toString());
            searchIndex++;
        }
    }
    mainToolBar->addWidget(searchCombo);
    mainToolBar->addAction(searchAction);
    mainToolBar->addAction(goHomeAction);
    mainToolBar->setMovable(false);
}

void MainWindow::closeEvent(QCloseEvent *event)//�¼����رա�
{
    event->accept();
}

void MainWindow::createStatusBar()//״̬��
{

}

void MainWindow::about()//�Ի������
{
    QMessageBox::about(this, tr("���ڻ�е��Ƹ����ֲ�"),
                       tr("<h2>��е��Ƹ����ֲ� 0.1</h2>"
                          "<p>Copyright &copy; 2010 ��˹�����"
                          "<p>��е��Ƹ����ֲ���һ������ʦ�ڻ�е���ʱ�Ĳο��ֲ�."));
}

void MainWindow::searchClick()
{
    this->about();
}

void MainWindow::createMainTree()//����Ŀ¼��
{
    QStringList treeColumnTitle;
    treeColumnTitle.append(QString::fromLocal8Bit("Ŀ¼"));
    mainTree->setHeaderLabels(treeColumnTitle);
    mainTree->header()->setResizeMode(QHeaderView::ResizeToContents );
    mainTree->header()->setStretchLastSection(true);
    QSqlQuery treeFirstQuery;
    QSqlQuery treeSecondQuery;
    QSqlQuery treeThirdQuery;
    if(treeFirstQuery.exec("SELECT menuitem, id FROM firstmenus;"))
    {
       int treeNumRows = 0;
       if(db.driver()->hasFeature(QSqlDriver::QuerySize))
       {
           treeNumRows = treeFirstQuery.size();
       }
       else
       {
           treeFirstQuery.last();
           treeNumRows = treeFirstQuery.at()+1;
           treeFirstQuery.seek(-1);
       }
       if(treeNumRows>0)
        {
            while(treeFirstQuery.next())
            {
                QTreeWidgetItem *firstMenus = new QTreeWidgetItem(mainTree);
                firstMenus->setText(0,treeFirstQuery.value(0).toString());
                firstMenus->setData(0,Qt::UserRole,1);
                if(treeSecondQuery.exec("SELECT menuitem, id FROM secondmenus where parentid = "+treeFirstQuery.value(1).toString()))
                {
                    int treeSecNumRows = 0;
                    if(db.driver()->hasFeature(QSqlDriver::QuerySize))
                    {
                        treeSecNumRows = treeSecondQuery.size();
                    }
                    else
                    {
                        treeSecondQuery.last();
                        treeSecNumRows = treeSecondQuery.at()+1;
                        treeSecondQuery.seek(-1);
                    }
                    if(treeSecNumRows>0)
                    {
                        while(treeSecondQuery.next())
                        {
                            QTreeWidgetItem *secMenus = new QTreeWidgetItem(firstMenus);
                            secMenus->setText(0,treeSecondQuery.value(0).toString());
                            secMenus->setData(0,Qt::UserRole,2);
                            if(treeThirdQuery.exec("SELECT menuitem, id FROM thirdmenus where parentid = "+treeSecondQuery.value(1).toString()))
                            {
                                int treeThdNumRows = 0;
                                if(db.driver()->hasFeature(QSqlDriver::QuerySize))
                                {
                                    treeThdNumRows = treeThirdQuery.size();
                                }
                                else
                                {
                                    treeThirdQuery.last();
                                    treeThdNumRows = treeThirdQuery.at()+1;
                                    treeThirdQuery.seek(-1);
                                }
                                if(treeThdNumRows>0)
                                {
                                    while(treeThirdQuery.next())
                                    {
                                        QTreeWidgetItem *thdMenus = new QTreeWidgetItem(secMenus);
                                        thdMenus->setText(0,treeThirdQuery.value(0).toString());
                                        thdMenus->setData(0,Qt::UserRole,3);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
   }
    connect(mainTree,SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(mainTreeClick(QTreeWidgetItem*,int)));
}

void MainWindow::mainTreeClick(QTreeWidgetItem* treeItem,int)
{
    QSqlQuery treeClickQuery;
    mainTree->currentItem();
    QVariant value = mainTree->currentItem()->data(0,Qt::UserRole);
    int valueInt = value.toInt();
    int hasChildren = treeItem->childCount();
    if(hasChildren>0)
    {
        if(!(rightSplitter->isHidden()))
        {
            rightSplitter->hide();
        }
        picLabel->show();
    }
    else
    {
        if(!(picLabel->isHidden()))
        {
            picLabel->hide();
            rightSplitter->show();
        }
        switch(valueInt)
        {
        case 1:
            break;
        case 2:
            dataTable->clear();
            if(treeClickQuery.exec("SELECT tableid FROM secondmenus WHERE menuitem = '"+mainTree->currentItem()->text(0)+"';"))
            {
                while(treeClickQuery.next())
                {
                    this->readTable(treeClickQuery.value(0).toString());
                }
            }
            break;
        case 3:
            dataTable->clear();
            if(treeClickQuery.exec("SELECT tableid FROM thirdmenus WHERE menuitem = '"+mainTree->currentItem()->text(0)+"';"))
            {
                while(treeClickQuery.next())
                {
                    this->readTable(treeClickQuery.value(0).toString());
                }
            }
            break;
        default:
            break;
        }
    }
}

void MainWindow::readTable(QString tableid)
{
    QStringList tableHeaders;
    QSqlQuery headerQuery;
    QSqlQuery bodyQuery;
    QSqlQuery noteQuery;

    if(headerQuery.exec("SELECT headitem FROM tableheader WHERE tableid = '"+ tableid+"';"))
    {
        int tableNumRows = 0;        
        if(db.driver()->hasFeature(QSqlDriver::QuerySize))
        {
            tableNumRows = headerQuery.size();
        }
        else
        {
            headerQuery.last();
            tableNumRows = headerQuery.at()+1;
            headerQuery.seek(-1);
        }
        if(tableNumRows>0)
        {
            dataTable->setColumnCount(tableNumRows);
            while(headerQuery.next())
            {
                tableHeaders.append(headerQuery.value(0).toString());
            }
            dataTable->setHorizontalHeaderLabels(tableHeaders);
            dataTable->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents );
            if(bodyQuery.exec("SELECT * FROM tablebody WHERE tableid = '"+tableid+"';"))
            {
                int tableNumCols = 0;
                if(db.driver()->hasFeature(QSqlDriver::QuerySize))
                {
                    tableNumCols = bodyQuery.size();
                }
                else
                {
                    bodyQuery.last();
                    tableNumCols = bodyQuery.at()+1;
                    bodyQuery.seek(-1);
                }
                int cols = tableNumCols/tableNumRows;
                QMessageBox::about(this, tr("���ڻ�е��Ƹ����ֲ�"),QString().setNum(cols));
                dataTable->setRowCount(cols);
                for(int i=0; i<cols; i++)
                {
                    for(int j=0; j<tableNumRows; j++)
                    {
                        bodyQuery.next();
                        dataTable->setItem(i,j,new QTableWidgetItem(bodyQuery.value(1).toString()));
                    }
                }
            }
        }
    }
    if(noteQuery.exec("SELECT noteitem FROM tablenote WHERE tableid = '"+tableid+"';"))
    {
        int noteNum = 0;
        if(db.driver()->hasFeature(QSqlDriver::QuerySize))
        {
            noteNum = noteQuery.size();
        }
        else
        {
            noteQuery.last();
            noteNum = noteQuery.at()+1;
            noteQuery.seek(-1);
        }
        if(noteNum>0)
        {
            while(noteQuery.next())
            {

            }
        }
    }
}
