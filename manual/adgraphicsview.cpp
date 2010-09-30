#include "adgraphicsview.h"

AdGraphicsView::AdGraphicsView(QPixmap map)
{
    this->adMap = map;

    int width = this->adMap.width();
    int height = this->adMap.height();
    QLabel *cornerLabel = new QLabel(tr("¹ã¸æ"));

    QGraphicsScene *adScene = new QGraphicsScene(this);

    adScene->setSceneRect(-width/2,-height/2,width,height);

    this->setScene(adScene);
    this->setCacheMode(CacheBackground);

    QVBoxLayout *advLayout = new QVBoxLayout;
    advLayout->addWidget(cornerLabel);
    advLayout->addStretch();

    QHBoxLayout *adhLayout = new QHBoxLayout;
    adhLayout->addLayout(advLayout);
    adhLayout->addStretch();
    adhLayout->setDirection(QBoxLayout::RightToLeft);

    this->setLayout(adhLayout);
}

void AdGraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawPixmap(int(sceneRect().left()),int(sceneRect().top()),this->adMap);
}
