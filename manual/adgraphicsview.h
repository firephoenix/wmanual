#ifndef ADGRAPHICSVIEW_H
#define ADGRAPHICSVIEW_H

#include <QtGui/QGraphicsView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPixmap>

class AdGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    AdGraphicsView(QPixmap map);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    QPixmap adMap;
};

#endif // ADGRAPHICSVIEW_H
