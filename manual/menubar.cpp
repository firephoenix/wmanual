#include "menubar.h"

MenuBar::MenuBar(QWidget *parent)
    :QMenuBar(parent)
{
    //actions = new Actions(this);
    fileMenu = this->addMenu(tr("�ļ�"));
    //fileMenu->addAction(actions->exitAction);
    helpMenu = this->addMenu(tr("����"));
}

MenuBar::~MenuBar()
{}
