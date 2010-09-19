#ifndef MENUBAR_H
#define MENUBAR_H

#include <QtGui/QMenuBar>
#include "actions.h"

class MenuBar : public QMenuBar
{
    Q_OBJECT

public:
    MenuBar(QWidget *parent = 0);
    ~MenuBar();

private:
    //Actions *actions;
    QMenu *fileMenu;
    QMenu *helpMenu;
};

#endif // MENUBAR_H
