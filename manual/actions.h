#ifndef ACTIONS_H
#define ACTIONS_H

#include <QtGui/QAction>

class Actions : public QAction
{
    Q_OBJECT

public:
    Actions(QAction *parent = 0);
    ~Actions();

    //QAction *exitAction;
};

#endif // ACTIONS_H
