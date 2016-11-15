#include "glevel0.h"
#include "pplocale.h"
#include "ppsettings.h"
#include <QPainter>

GLevel0::GLevel0(QGraphicsItem *parent) : clItemBase(parent) {

    pxmpTiles = new QPixmap(":/data/textures/games/lvl02/Tiles.png");

    beginLevel();
}

//-------------------------------------------------------------
GLevel0::~GLevel0() {

}

//-------------------------------------------------------------
void GLevel0::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->fillRect(boundingRect(), Qt::transparent);

    gSettings->drawText(painter, gLocale->getLocaleString("GameScreen", 10, "Level "), gSettings->setFontSettings(*gSettings->gameFonts.fntArial, 16, true), QRect(20, 10, 920, 40), Qt::yellow);

    painter->drawPixmap(214, 60, *pxmpTiles);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//-------------------------------------------------------------
bool GLevel0::checkMouse(int mX, int mY, bool mStatCur, bool mStatPrev) {

    if (win || !leftMoves) clItemBase::checkMouse(mX, mY, mStatCur, mStatPrev);

    return clItemBase::checkMouse(mX, mY, mStatCur, mStatPrev);
}

//-------------------------------------------------------------
void GLevel0::beginLevel() {

    curTouch = 0;
    leftMoves = 48;
    curTouch = 0;
}
