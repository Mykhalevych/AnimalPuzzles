#include "glevel01.h"
#include "pplocale.h"
#include "ppsettings.h"
#include <QPainter>
#include <QDebug>

GLevel01::GLevel01(QGraphicsItem *parent) : clItemBase(parent) {

    pxmpTiles = new QPixmap(":/data/textures/games/lvl01/Tiles.png");

    dashes << 6 << 6 << 0 << 0;
    timerDashes = 0;

    rectBarrel = QRect(211, 60, 225, 400);
    rect5l = QRect(436, 140, 176, 320);
    rect3l = QRect(613, 220, 133, 240);

    beginLevel();
}

//-------------------------------------------------------------
GLevel01::~GLevel01() {

}

//-------------------------------------------------------------
void GLevel01::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->fillRect(boundingRect(), Qt::transparent);

    makeProgress();

    gSettings->drawText(painter, gLocale->getLocaleString("GameScreen", 10, "Level "), gSettings->setFontSettings(*gSettings->gameFonts.fntArial, 14, true), QRect(20, 10, 920, 40), Qt::yellow);
    painter->setPen(Qt::blue);
    painter->setBrush(Qt::blue);
    painter->drawRect(QRect(231, 180, 185, 250)); // Cask
    painter->drawRect(QRect(450, 430 - (38.0 * cur5l), 146, 38.0 * cur5l)); // 5L
    painter->drawRect(QRect(625, 430 - (130.0 * cur3l / 3.0), 108, 130.0 * cur3l / 3.0)); // 3L
    painter->drawPixmap(214, 60, *pxmpTiles);

    QString txt = (leftMoves || !win) ? gLocale->getLocaleString("GameScreen", 8, "Left moves - %1").arg(leftMoves) : gLocale->getLocaleString("GameScreen", 9, "You win! Go next!");
    gSettings->drawText(painter, gLocale->getLocaleString("GameScreen", 5, "Cask"), gSettings->setFontSettings(*gSettings->gameFonts.fntArial, 20, true), QRect(232, 180, 184, 250), Qt::yellow);
    gSettings->drawText(painter, gLocale->getLocaleString("GameScreen", 6, "5L"), gSettings->setFontSettings(*gSettings->gameFonts.fntArial, 16, true), QRect(450, 240, 146, 190), Qt::yellow);
    gSettings->drawText(painter, gLocale->getLocaleString("GameScreen", 7, "3L"), gSettings->setFontSettings(*gSettings->gameFonts.fntArial, 16, true), QRect(625, 300, 108, 130), Qt::yellow);
    gSettings->drawText(painter, txt, gSettings->setFontSettings(*gSettings->gameFonts.fntArial, 16, true), QRect(20, 460, 920, 40),  (leftMoves || win) ? Qt::yellow : Qt::red);

    QPen linePen(Qt::yellow, 2.0);
    painter->setPen(linePen);
    for (int i = 0; i <= 190; i += 38) {
        painter->drawLine(450, 431 - i, 465, 431 - i);
    }
    for (int i = 0; i <= 3; i++) {
        painter->drawLine(625, 431 - (130.0 * i / 3.0), 640, 431 - (130.0 * i / 3.0));
    }

    timerDashes += gSettings->gameTime.dTime;
    if (timerDashes >= 250) {
        qreal tmp = dashes[0];
        dashes[0] = dashes[2];
        dashes[2] = tmp;

        do {
            timerDashes -= 250;
        } while (timerDashes >= 250);
    }

    penChoise.setDashPattern(dashes);
    penChoise.setColor(Qt::gray);
    painter->setBrush(Qt::transparent);
    painter->setPen(penChoise);
    switch (curTouch) {
        case 1:
            painter->drawRect(211, 60, 225, 400);
            break;

        case 2:
            painter->drawRect(436, 140, 176, 320);
            break;

        case 3:
            painter->drawRect(613, 220, 133, 240);
            break;
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//-------------------------------------------------------------
bool GLevel01::checkMouse(int mX, int mY, bool mStatCur, bool mStatPrev) {

    if (win || !leftMoves) clItemBase::checkMouse(mX, mY, mStatCur, mStatPrev);

    if (mStatCur && !mStatPrev) {
        if (rectBarrel.contains(mX, mY)) {
            switch (curTouch) {
                case 0:
                    curTouch = 1;
                    break;
                case 1:
                    curTouch = 0;
                    break;
                case 2:
                    if (curProgress == stNoProgress && cur5l > 0.0) {
                        curProgress = st5lToBarrel;
                        leftMoves -= (leftMoves > 0) ? 1 : 0;
                        curTouch = 0;
                    }
                    break;
                case 3:
                    if (curProgress == stNoProgress && cur3l > 0.0) {
                        curProgress = st3lToBarrel;
                        leftMoves -= (leftMoves > 0) ? 1 : 0;
                        curTouch = 0;
                    }
                    break;
            }
        }
        else if (rect5l.contains(mX, mY)) {
            switch (curTouch) {
                case 0:
                    curTouch = 2;
                    break;
                case 1:
                    if (curProgress == stNoProgress && cur5l < 5.0) {
                        curProgress = stBarrelTo5l;
                        leftMoves -= (leftMoves > 0) ? 1 : 0;
                        curTouch = 0;
                    }
                    break;
                case 2:
                    curTouch = 0;
                    break;
                case 3:
                    if (curProgress == stNoProgress && cur5l < 5.0 && cur3l > 0.0) {
                        curProgress = st3lTo5l;
                        if (leftMoves && static_cast<int>(cur5l + cur3l) == 4) {
                            win = true;
                        }
                        leftMoves -= (leftMoves > 0) ? 1 : 0;
                        curTouch = 0;
                    }
                    break;
            }
        }
        else if (rect3l.contains(mX, mY)) {
            switch (curTouch) {
                case 0:
                    curTouch = 3;
                    break;
                case 1:
                    if (curProgress == stNoProgress && cur3l < 3.0) {
                        curProgress = stBarrelTo3l;
                        leftMoves -= (leftMoves > 0) ? 1 : 0;
                        curTouch = 0;
                    }
                    break;
                case 2:
                    if (curProgress == stNoProgress && cur3l < 3.0 && cur5l > 0.0) {
                        curProgress = st5lTo3l;
                        if (leftMoves && static_cast<int>(cur5l - (3.0 - cur3l)) == 4) {
                            win = true;
                        }
                        leftMoves -= (leftMoves > 0) ? 1 : 0;
                        curTouch = 0;
                    }
                    break;
                case 3:
                    curTouch = 0;
                    break;
            }
        }
    }

    return clItemBase::checkMouse(mX, mY, mStatCur, mStatPrev);
}

//-------------------------------------------------------------
void GLevel01::beginLevel() {

    cur3l = cur5l = curTouch = stat = 0;
    leftMoves = 6;
    curTouch = 0;
    curProgress = stNoProgress;
}

//-------------------------------------------------------------
void GLevel01::makeProgress() {
    float progress = static_cast<float>(gSettings->gameTime.dTime) / 500.0;

    switch (curProgress) {
        case stBarrelTo3l:
            cur3l += progress;
            if (cur3l >= 3.0) {
                cur3l = 3.0;
                curProgress = stNoProgress;
            }
            break;
        case st5lTo3l:
            cur3l += progress;
            cur5l -= progress;
            if (cur3l >= 3.0) {
                cur5l += cur3l - 3.0;
                cur5l = static_cast<int>(cur5l + 0.5);
                cur3l = 3.0;
                curProgress = stNoProgress;
                qDebug() << cur5l;
            }
            else if (cur5l <= 0.0) {
                cur3l += cur5l;
                cur3l = static_cast<int>(cur3l + 0.5);
                cur5l = 0.0;
                qDebug() << cur3l;
                curProgress = stNoProgress;
            }
            break;
        case stBarrelTo5l:
            cur5l += progress;
            if (cur5l >= 5.0) {
                cur5l = 5.0;
                curProgress = stNoProgress;
            }
            break;
        case st3lTo5l:
            cur5l += progress;
            cur3l -= progress;
            if (cur5l >= 5.0) {
                cur3l += cur5l - 5.0;
                cur3l = static_cast<int>(cur3l + 0.5);
                cur5l = 5.0;
                qDebug() << cur3l;
                curProgress = stNoProgress;
            }
            else if (cur3l <= 0.0) {
                cur5l += cur3l;
                cur5l = static_cast<int>(cur5l + 0.5);
                cur3l = 0.0;
                qDebug() << cur5l;
                curProgress = stNoProgress;
            }
            break;
        case st5lToBarrel:
            cur5l -= progress;
            if (cur5l <= 0.0) {
                cur5l = 0.0;
                curProgress = stNoProgress;
            }
            break;
        case st3lToBarrel:
            cur3l -= progress;
            if (cur3l <= 0.0) {
                cur3l = 0.0;
                curProgress = stNoProgress;
            }
            break;

        default:
            break;
    }
}

//-------------------------------------------------------------
