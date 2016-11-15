#ifndef GLEVEL_0_H
#define GLEVEL_0_H

#include "gitembase.h"
#include <QPen>

class GLevel0 : public clItemBase {
private:
    int leftMoves;

    int curTouch;

    QPen penLvl;

    QVector <QRect> vctrImgTiles;

    char fieldStat[6][8];

public:
    GLevel0(QGraphicsItem *parent = 0);
    ~GLevel0();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool checkMouse(int mX, int mY, bool mStatCur, bool mStatPrev);

protected:
    virtual void beginLevel();

};

#endif // GLEVEL_02_H
