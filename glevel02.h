#ifndef GLEVEL_02_H
#define GLEVEL_02_H

#include "gitembase.h"
#include <QPen>

class GLevel02 : public clItemBase {
private:
    int leftMoves;

    int curTouch;

    QPen penLvl;

    QVector <QRect> vctrImgTiles;

    char fieldStat[6][8];

public:
    GLevel02(QGraphicsItem *parent = 0);
    ~GLevel02();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool checkMouse(int mX, int mY, bool mStatCur, bool mStatPrev);

protected:
    virtual void beginLevel();

};

#endif // GLEVEL_02_H
