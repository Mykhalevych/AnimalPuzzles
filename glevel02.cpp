#include "glevel02.h"
#include "pplocale.h"
#include "ppsettings.h"
#include <QPainter>

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
    vctrImgTiles.push_back(QRect(448, 0, 64, 64));
    vctrImgTiles.push_back(QRect(512, 0, 64, 64));

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

    painter->drawPixmap(180, 10, *pxmpDesc);

    if (curTouch && lastTouch) {
        timerTouch += gSettings->gameTime.dTime;
        if (timerTouch >= 750) {
            timerTouch = 0;
            int x = curTouch % 9 - 1;
            int y = curTouch / 9 - 1;
            fieldStat[x][y].stat = 0;

            x = lastTouch % 9 - 1;
            y = lastTouch / 9 - 1;
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

    QString txt = (leftMoves || !win) ? gLocale->getLocaleString("GameScreen", 8, "Left moves - %1").arg(leftMoves) : gLocale->getLocaleString("GameScreen", 9, "You win! Go next!");
    gSettings->drawText(painter, txt, gSettings->setFontSettings(*gSettings->gameFonts.fntArial, 16, true), QRect(20, 460, 920, 40),  (leftMoves || win) ? Qt::yellow : Qt::red);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//-------------------------------------------------------------
bool GLevel02::checkMouse(int mX, int mY, bool mStatCur, bool mStatPrev) {

    if (!clItemBase::checkMouse(mX, mY, mStatCur, mStatPrev)) return false;
    if (win || !leftMoves || (curTouch && lastTouch)) return clItemBase::checkMouse(mX, mY, mStatCur, mStatPrev);

    if (mStatCur && !mStatPrev) {

        mX -= 200;
        mY -= 25;

        QRect rectMouse(0, 0, 560, 420);
        if (rectMouse.contains(mX, mY)) {
            rectMouse = QRect((mX / 70) * 70 + 3, (mY / 70) * 70 + 3, 64, 64);
        }
        else {
            return clItemBase::checkMouse(mX, mY, mStatCur, mStatPrev);
        }

        if (rectMouse.contains(mX, mY)) {
            int x = mX / 70;
            int y = mY / 70;
            if (!curTouch && !fieldStat[x][y].stat) {
                curTouch = (y + 1) * 9 + (x + 1);
                fieldStat[x][y].stat = 1;
            }
            else if (curTouch && !lastTouch && !fieldStat[x][y].stat) {
                int curX = curTouch % 9 - 1;
                int curY = curTouch / 9 - 1;
                if (fieldStat[x][y].type == fieldStat[curX][curY].type) {
                    fieldStat[x][y].stat = fieldStat[curX][curY].stat = 2;
                    curTouch = 0;
                    checkWin();
                }
                else {
                    fieldStat[x][y].stat = 1;
                    lastTouch = (y + 1) * 9 + (x + 1);
                    timerTouch = 0;
                }
                leftMoves--;
            }
            else if (curTouch && !lastTouch && fieldStat[x][y].stat == 1) {
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

    for (int pair = 0; pair < 24;) {
        for (int i = 1; i <= 8 && pair < 24; i++, pair++) {

            int firI, firJ;
            do {
                firI = qrand() % 8;
                firJ = qrand() % 3;
            } while (fieldStat[firI][firJ].type);
            fieldStat[firI][firJ].stat = 0;
            fieldStat[firI][firJ].type = i;

            int secI, secJ;
            do {
                secI = qrand() % 8;
                secJ = qrand() % 3 + 3;
            } while (fieldStat[secI][secJ].type);
            fieldStat[secI][secJ].stat = 0;
            fieldStat[secI][secJ].type = i;
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
