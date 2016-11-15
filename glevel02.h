#ifndef GLEVEL_02_H
#define GLEVEL_02_H

#include "gitembase.h"
#include <QPen>

struct structCell {
    int type;
    int stat;
};

class GLevel02 : public clItemBase {
private:
    int leftMoves;

    int curTouch;
    int lastTouch;
    qint64 timerTouch;

    QPen penLvl;

    QVector <QRect> vctrImgTiles;

    structCell fieldStat[8][6];

    QPixmap *pxmpDesc;

public:
    GLevel02(QGraphicsItem *parent = 0);
    ~GLevel02();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool checkMouse(int mX, int mY, bool mStatCur, bool mStatPrev);

protected:
    virtual void beginLevel();

private:
    void checkWin();

};

#endif // GLEVEL_02_H
