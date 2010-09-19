#include "menubar.h"

MenuBar::MenuBar(QWidget *parent)
    :QMenuBar(parent)
{
    //actions = new Actions(this);
    fileMenu = this->addMenu(tr("ÎÄ¼ş"));
    //fileMenu->addAction(actions->exitAction);
    helpMenu = this->addMenu(tr("°ïÖú"));
}

MenuBar::~MenuBar()
{}
