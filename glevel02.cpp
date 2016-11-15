#include "glevel02.h"
#include "pplocale.h"
#include "ppsettings.h"
#include <QPainter>
#include <QDebug>

GLevel02::GLevel02(QGraphicsItem *parent) : clItemBase(parent) {

    pxmpTiles = new QPixmap(":/data/textures/games/lvl02/Tiles.png");
    pxmpDesc = new QPixmap(":/data/textures/games/lvl02/desc.jpg");

    vctrImgTiles.push_back(QRect(0, 0, 64, 64));
    vctrImgTiles.push_back(QRect(64, 0, 64, 64));
    vctrImgTiles.push_back(QRect(128, 0, 64, 64));
    vctrImgTiles.push_back(QRect(192, 0, 64, 64));
    vctrImgTiles.push_back(QRect(256, 0, 64, 64));
    vctrImgTiles.push_back(QRect(320, 0, 64, 64));
    vctrImgTiles.push_back(QRect(384, 0, 64, 64));
    vctrImgTiles.push_back(QRect(452, 0, 64, 64));

    beginLevel();
}

//-------------------------------------------------------------
GLevel02::~GLevel02() {

}

//-------------------------------------------------------------
void GLevel02::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->fillRect(boundingRect(), Qt::transparent);

//    gSettings->drawText(painter, gLocale->getLocaleString("GameScreen", 10, "Level "), gSettings->setFontSettings(*gSettings->gameFonts.fntArial, 16, true), QRect(20, 10, 920, 40), Qt::yellow);

    painter->drawPixmap(160, 10, *pxmpDesc);

    if (curTouch && lastTouch) {
        timerTouch += gSettings->gameTime.dTime;
        if (timerTouch >= 500) {
            timerTouch = 0;
            int x = curTouch % 8;
            int y = curTouch / 8;
            fieldStat[x][y].stat = 0;

            x = lastTouch % 8;
            y = lastTouch / 8;
            fieldStat[x][y].stat = 0;
            curTouch = lastTouch = 0;
        }
    }

    QPoint pntCell;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            pntCell.setX(i * 70 + 203);
            pntCell.setY(j * 70 + 28);

            if (fieldStat[i][j].stat) {
                painter->drawPixmap(pntCell, *pxmpTiles, vctrImgTiles[fieldStat[i][j].type]);
            }
            else {
                painter->drawPixmap(pntCell, *pxmpTiles, vctrImgTiles[0]);
            }
        }
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//-------------------------------------------------------------
bool GLevel02::checkMouse(int mX, int mY, bool mStatCur, bool mStatPrev) {

    if (win || !leftMoves || (curTouch && lastTouch)) return clItemBase::checkMouse(mX, mY, mStatCur, mStatPrev);

    if (mStatCur && !mStatPrev) {

        qDebug() << mX << mY;
        mX -= 200;
        mY -= 25;

        QRect rectMouse(0, 0, 560, 420);
        if (rectMouse.contains(mX, mY)) {
            rectMouse = QRect((mX / 8) * 70 + 3, (mY / 6) * 70 + 3, 64, 64);
        }
        else {
            return clItemBase::checkMouse(mX, mY, mStatCur, mStatPrev);
        }

        if (rectMouse.contains(mX, mY)) {
            int x = mX / 8;
            int y = mY / 6;
            if (!curTouch && !fieldStat[x][y].stat) {
                curTouch = y * 8 + x;
            }
            else if (curTouch && !fieldStat[x][y].stat) {
                int curX = curTouch % 8;
                int curY = curTouch / 8;
                if (fieldStat[x][y].type == fieldStat[curX][curY].type) {
                    fieldStat[x][y].stat = fieldStat[curX][curY].stat = 2;
                    curTouch = 0;
                    checkWin();
                }
                else {
                    fieldStat[x][y].stat = 1;
                    lastTouch = y * 8 + x;
                    timerTouch = 0;
                }
            }
            else if (curTouch && fieldStat[x][y].stat == 1) {
                fieldStat[x][y].stat = 0;
                curTouch = 0;
            }
        }
    }

    return clItemBase::checkMouse(mX, mY, mStatCur, mStatPrev);
}

//-------------------------------------------------------------
void GLevel02::beginLevel() {

    curTouch = lastTouch = 0;
    leftMoves = 48;

    qsrand(gSettings->gameTime.cTime);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            fieldStat[i][j].type = 0;
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            fieldStat[i][j].stat = 0;
            fieldStat[i][j].type = qrand() % 6 + 1;

            int secI, secJ;
            do {
                secI = qrand() % 8;
                secJ = qrand() % 3 + 3;
            } while (fieldStat[secI][secJ].type);
            fieldStat[secI][secJ].stat = 0;
            fieldStat[secI][secJ].type = fieldStat[i][j].type;
        }
    }
}
//-------------------------------------------------------------
void GLevel02::checkWin() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
           if (!fieldStat[i][j].stat) return;        }
    }

    win = true;
}
