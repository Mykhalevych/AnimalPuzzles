#ifndef GITEMBASE_H
#define GITEMBASE_H

#include <QGraphicsItem>

class clItemBase : public QGraphicsItem {

protected:
    bool win;

    QPixmap *pxmpTiles;

public:
    clItemBase(QGraphicsItem *parent = 0);
    ~clItemBase();

    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) ;
    QRectF boundingRect() const;

    virtual void updateLevel();
    virtual void repeat();
    virtual bool checkMouse(int mX, int mY, bool mStatCur, bool mStatPrev);

    virtual bool isWin() const;

protected:
    virtual void beginLevel();
};

#endif // GITEMBASE_H
