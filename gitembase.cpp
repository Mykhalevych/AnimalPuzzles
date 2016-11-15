#include "gitembase.h"
#include "ppsettings.h"

clItemBase::clItemBase(QGraphicsItem *parent) : QGraphicsItem(parent) {
    win = false;
    pxmpTiles = 0;

    beginLevel();
}

//-------------------------------------------------------------
clItemBase::~clItemBase() {
    if (pxmpTiles) {
        delete pxmpTiles;
    }
}

//-------------------------------------------------------------
QRectF clItemBase::boundingRect() const {
    return QRectF(0, 0, 960, 500);
}

//-------------------------------------------------------------
void clItemBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//-------------------------------------------------------------
void clItemBase::updateLevel() {
    int myX = gSettings->gameMouse.mouseX - sceneBoundingRect().x();
    int myY = gSettings->gameMouse.mouseY - sceneBoundingRect().y();

    if (!win) {
        checkMouse(myX, myY, gSettings->gameMouse.mouseCurState, gSettings->gameMouse.mousePrevState);
    }

    update();
}

//-------------------------------------------------------------
bool clItemBase::checkMouse(int mX, int mY, bool mStatCur, bool mStatPrev) {

    Q_UNUSED(mStatPrev);
    return boundingRect().contains(mX, mY) && mStatCur;
}

//-------------------------------------------------------------
bool clItemBase::isWin() const {
    return win;
}

//-------------------------------------------------------------
void clItemBase::repeat() {
    win = false;
    beginLevel();
    update();
}

//-------------------------------------------------------------
void clItemBase::beginLevel() {

}

//-------------------------------------------------------------
