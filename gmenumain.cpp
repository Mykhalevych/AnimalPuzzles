#include "gmenumain.h"
#include "ppsettings.h"
#include "pplocale.h"
#include "ppsound.h"

//-------------------------------------------------------------
GMenuMain::GMenuMain(QGraphicsScene *_scene, QWidget *_parent)
    : clPPBaseScene(_scene, _parent) {

}

//-------------------------------------------------------------
GMenuMain::GMenuMain(QString _name, QGraphicsScene *_scene, QWidget *_parent)
    : clPPBaseScene(_name, _scene, _parent) {


    btnStart = 0;
    btnExit = 0;

    pxmpTiles = new QPixmap(":/data/textures/common/Tiles.png");
}

//-------------------------------------------------------------
GMenuMain::~GMenuMain() {
    delete pxmpTiles;

    delete btnStart;
    delete btnExit;
}

//-------------------------------------------------------------
void GMenuMain::initScene() {
    QString strMainText = gLocale->getLocaleString("MainMenu", 4, "Hello gamer!");

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

    if (!btnStart) {
        btnStart = new clPPButton(QRect(793, 520, 147, 60), pxmpTiles, QRect(0, 0, 147, 60), QRect(0, 60, 147, 60));
    }
    btnStart->operator =(scene->addPixmap(*btnStart->imgOff));
    btnStart->setText(gLocale->getLocaleString("MainMenu", 1, QString("Start")), Qt::AlignCenter, Qt::yellow, gSettings->setFontSettings(*gSettings->gameFonts.fntSegoe, 18, false));

    if (!btnExit) {
        btnExit = new clPPButton(QRect(20, 520, 147, 60), pxmpTiles, QRect(0, 0, 147, 60), QRect(0, 60, 147, 60));
    }
    btnExit->operator =(scene->addPixmap(*btnExit->imgOff));
    btnExit->setText(gLocale->getLocaleString("MainMenu", 3, QString("Exit")), Qt::AlignCenter, Qt::yellow, gSettings->setFontSettings(*gSettings->gameFonts.fntSegoe, 18, false));

    QPixmap imgTxt(QSize(gSettings->gameScreen.origWidth - 40, 150));
    imgTxt.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&imgTxt);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
//    painter.setRenderHint(QPainter::Antialiasing, true);
    gSettings->drawText(&painter, strMainText, gSettings->setFontSettings(*gSettings->gameFonts.fntSegoe, 22, true), imgTxt.rect(), QColor(255, 255, 0, 255), Qt::AlignVCenter | Qt::AlignJustify | Qt::TextWordWrap);
    painter.end();

    scene->addPixmap(imgTxt)->setPos(20, 20);

    // Draw level buttons
    if (btnLevel.size()) {
        for (int i = 0; i < btnLevel.size(); i++) {
            delete btnLevel[i];
        }
        btnLevel.clear();
        clPPGroupButton::clearGroup(1);
    }
    for (int nBut = 0; nBut < 16; nBut++) {
        QRect rectBtn = QRect(nBut * 80 - ((nBut / 8) * 80 * 8) + 176, (nBut / 8) * 64 + 300, 48, 48);
        int group = (gSettings->gameData.dataLevels & (1 << nBut)) ? 1 : 0;
        clPPGroupButton *btn = new clPPGroupButton(rectBtn, pxmpTiles, QRect((group > 0) ? 0 : 96, 180, 48, 48), QRect((group > 0) ? 48 : 96, 180, 48, 48), 0, group);
        if (group) {
            btn->setText(QString("%1").arg((nBut + 1)), Qt::AlignCenter, Qt::yellow, gSettings->setFontSettings(*gSettings->gameFonts.fntArial, 18, true));
        }
        *btn = scene->addPixmap(*btn->imgOff);

        btnLevel.push_back(btn);
    }

    // Draw lang buttons
    if (btnLang.size()) {
        for (int i = 0; i < btnLang.size(); i++) {
            delete btnLang[i];
        }
        btnLang.clear();
        clPPGroupButton::clearGroup(2);
    }
    for (int nBut = 0; nBut < 3; nBut++) {
        QRect rectBtn = QRect(nBut * 48 + 416, 530, 32, 32);
        clPPGroupButton *btn = new clPPGroupButton(rectBtn, pxmpTiles, QRect(0, 228, 34, 34), QRect(34, 228, 34, 34), 0, 2);
        QString txtLang = (nBut == 0) ? "EN" : (nBut == 1) ? "RU" : "UA";
        btn->setText(txtLang, Qt::AlignCenter, Qt::white, gSettings->setFontSettings(*gSettings->gameFonts.fntArial, 14));

        *btn = scene->addPixmap(*btn->imgOff);

        btnLang.push_back(btn);
        if (nBut == gSettings->gameSettings.lang - 1) {
            clPPGroupButton::clickGroup(2, QPoint(rectBtn.left() + 16, rectBtn.top() + 16));
        }
    }
}

//-------------------------------------------------------------
void GMenuMain::updateScene() {
    if (!active) return;

    checkMouse();
}

//-------------------------------------------------------------
void  GMenuMain::checkMouse() {

    btnStart->updateButton(gSettings->gameMouse.mouseX, gSettings->gameMouse.mouseY, gSettings->gameMouse.mouseCurState);
    btnExit->updateButton(gSettings->gameMouse.mouseX, gSettings->gameMouse.mouseY, gSettings->gameMouse.mouseCurState);

    if (!gSettings->gameMouse.mouseCurState && gSettings->gameMouse.mousePrevState) {
        if (btnStart->checkClick(gSettings->gameMouse.mouseX, gSettings->gameMouse.mouseY)) {
            gSettings->gameData.level = clPPGroupButton::getCklickedIdGroup(1);
            goToNextScreen();
        }
        else if (btnExit->checkClick(gSettings->gameMouse.mouseX, gSettings->gameMouse.mouseY)) {
            exitGame();
        }
    }
    else if (gSettings->gameMouse.mouseCurState && !gSettings->gameMouse.mousePrevState) {
        if (clPPGroupButton::clickGroup(1, QPoint(gSettings->gameMouse.mouseX, gSettings->gameMouse.mouseY))) {
            if (gSettings->gameMouse.mouseDblClic) {
                gSettings->gameData.level = clPPGroupButton::getCklickedIdGroup(1);
                goToNextScreen();
            }
        }
        if (clPPGroupButton::clickGroup(2, QPoint(gSettings->gameMouse.mouseX, gSettings->gameMouse.mouseY))) {
            gSettings->gameSettings.lang = clPPGroupButton::getCklickedIdGroup(2);
            gSettings->saveSettings();
            QString locale = (gSettings->gameSettings.lang == 1) ? "EN" : (gSettings->gameSettings.lang == 2) ? "RU" : "UK";
            gLocale->loadLocale(locale);
            initScene();
        }
    }
}

//-------------------------------------------------------------
