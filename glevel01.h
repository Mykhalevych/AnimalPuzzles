#ifndef GLEVEL_01_H
#define GLEVEL_01_H

#include "gitembase.h"
#include <QPen>

class GLevel01 : public clItemBase {
private:
    float cur3l;
    float cur5l;
    int leftMoves;

    int curTouch;
    int stat;

    QPen penChoise;
    QVector<qreal> dashes;
    int timerDashes;


    QRect rectBarrel;
    QRect rect5l;
    QRect rect3l;

    enum {stNoProgress, stBarrelTo5l, stBarrelTo3l, st5lTo3l, st5lToBarrel, st3lTo5l, st3lToBarrel} curProgress;

public:
    GLevel01(QGraphicsItem *parent = 0);
    ~GLevel01();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool checkMouse(int mX, int mY, bool mStatCur, bool mStatPrev);

protected:
    virtual void beginLevel();

private:
    void makeProgress();
};

#endif // GLEVEL_01_H
