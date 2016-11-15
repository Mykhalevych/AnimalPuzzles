#include "ggamescreen.h"
#include "ppsettings.h"
#include "pplocale.h"
#include "ppsound.h"
#include "glevel01.h"
#include "glevel02.h"

//-------------------------------------------------------------
GGameScreen::GGameScreen(QGraphicsScene *_scene, QWidget *_parent) :
    clPPBaseScene(_scene, _parent) {

    mainItem = 0;
}

//-------------------------------------------------------------
GGameScreen::GGameScreen(QString _name, QGraphicsScene *_scene, QWidget *_parent) :
    clPPBaseScene(_name, _scene, _parent) {

    mainItem = 0;

    pxmpTiles = new QPixmap(":/data/textures/common/Tiles.png");
}

//-------------------------------------------------------------
GGameScreen::~GGameScreen() {
    delete btnNext;
    delete btnBack;

    if (mainItem) {
        delete mainItem;
    }
}

//-------------------------------------------------------------
void GGameScreen::initScene() {
    scene->clear();

#ifdef PORTRAIT
    QPixmap *pxmpBackGround = new QPixmap(600, 960); // Loading menu background
#else
//    QPixmap *pxmpBackGround = new QPixmap(960, 600); // Loading menu background
    QPixmap *pxmpBackGround = new QPixmap(":/data/textures/common/background.png"); // Loading menu background
#endif
//    pxmpBackGround->fill(QColor(0, 255, 128, 255));

    scene->addPixmap(*pxmpBackGround);
    delete pxmpBackGround;

    btnNext = new clPPButton(QRect(793, 520, 147, 60), pxmpTiles, QRect(0, 0, 147, 60), QRect(0, 60, 147, 60), new QRect(0, 120, 147, 60));
    btnNext->setText(gLocale->getLocaleString("GameScreen", 1, QString("Next")), Qt::AlignCenter, Qt::yellow, gSettings->setFontSettings(*gSettings->gameFonts.fntSegoe, 18, false));
    btnNext->operator =(scene->addPixmap(*btnNext->imgOff));
    btnNext->setEnabled(false);

    btnRefresh = new clPPButton(QRect(406, 520, 147, 60), pxmpTiles, QRect(0, 0, 147, 60), QRect(0, 60, 147, 60));
    btnRefresh->setText(gLocale->getLocaleString("GameScreen", 2, QString("Try again")), Qt::AlignCenter, Qt::yellow, gSettings->setFontSettings(*gSettings->gameFonts.fntSegoe, 18, false));
    btnRefresh->operator =(scene->addPixmap(*btnRefresh->imgOff));

    btnBack = new clPPButton(QRect(20, 520, 147, 60), pxmpTiles, QRect(0, 0, 147, 60), QRect(0, 60, 147, 60));
    btnBack->setText(gLocale->getLocaleString("GameScreen", 3, QString("Back")), Qt::AlignCenter, Qt::yellow, gSettings->setFontSettings(*gSettings->gameFonts.fntSegoe, 18, false));
    btnBack->operator =(scene->addPixmap(*btnBack->imgOff));

    setMainItem();

//    QPixmap pxmpLevelTxt(gSettings->gameScreen.origWidth, 30);
//    QPainter painter;
//    pxmpLevelTxt.fill(Qt::transparent);
//    painter.begin(&pxmpLevelTxt);
//    painter.setPen(Qt::yellow);
//    gSettings->drawText(&painter, gLocale->getLocaleString("GameScreen", 4, QString("Level %1")).arg(gSettings->gameData.level), gSettings->setFontSettings(*gSettings->gameFonts.fntSegoe, 24, true), pxmpLevelTxt.rect(), Qt::yellow);
//    painter.end();
//    scene->addPixmap(pxmpLevelTxt);
}

//-------------------------------------------------------------
void GGameScreen::updateScene() {
    if (!active) return;

    if (mainItem) {
        mainItem->updateLevel();
        if (mainItem->isWin() && !btnNext->isEnabled()) {
            btnNext->setEnabled();
            gSettings->gameData.dataLevels |= 1 << gSettings->gameData.level;
            gSettings->saveGameData();
        }
    }

    checkMouse();
}

//-------------------------------------------------------------
void  GGameScreen::checkMouse() {
    btnNext->updateButton(gSettings->gameMouse.mouseX, gSettings->gameMouse.mouseY, gSettings->gameMouse.mouseCurState);
    btnRefresh->updateButton(gSettings->gameMouse.mouseX, gSettings->gameMouse.mouseY, gSettings->gameMouse.mouseCurState);
    btnBack->updateButton(gSettings->gameMouse.mouseX, gSettings->gameMouse.mouseY, gSettings->gameMouse.mouseCurState);

    if (!gSettings->gameMouse.mouseCurState && gSettings->gameMouse.mousePrevState) {
        if (btnRefresh->checkClick(gSettings->gameMouse.mouseX, gSettings->gameMouse.mouseY) && mainItem) {
            mainItem->repeat();
        }
        else if (btnBack->checkClick(gSettings->gameMouse.mouseX, gSettings->gameMouse.mouseY)) {
            mainItem = 0;
            goToPrevScreen();
        }
        else if (btnNext->isEnabled() && btnNext->checkClick(gSettings->gameMouse.mouseX, gSettings->gameMouse.mouseY)) {
            if (gSettings->gameData.level < 16) {
                gSettings->gameData.level++;
                setMainItem();
                btnNext->setEnabled(false);
            }
        }
    }
    else if (gSettings->gameMouse.mouseCurState && !gSettings->gameMouse.mousePrevState) {
    }
}

//-------------------------------------------------------------
void GGameScreen::setMainItem() {
    if (mainItem) {
        scene->removeItem(mainItem);
        delete mainItem;
        mainItem = 0;
    }

    switch (gSettings->gameData.level) {
        case 1:
            scene->addItem(mainItem = new GLevel01);
            break;

        case 2:
            scene->addItem(mainItem = new GLevel02);
            break;
    }

    if (mainItem) {
        mainItem->setPos(0, 0);
    }
}
