#include <QSettings>
#include <QDebug>

#include "ppsettings.h"
#include "pplocale.h"

//-------------------------------------------------------------
clPPSettings *gSettings = new clPPSettings;

//-------------------------------------------------------------
clPPSettings::clPPSettings() {

    clock = new QElapsedTimer;
    clock->start();
    gameTime.cTime = 0;
    updateTimer();
}

//-------------------------------------------------------------
clPPSettings::~clPPSettings() {

}

//-------------------------------------------------------------
void clPPSettings::loadSettings() {
    gameSettings.soundOn = getSetting("Settings/Sound", true).toBool();
    gameSettings.musicOn = getSetting("Settings/Music", true).toBool();
    gameSettings.lang = getSetting("Settings/Lang", 0).toInt();
}

//-------------------------------------------------------------
void clPPSettings::saveSettings() const {
    setSetting("Settings/Sound", gameSettings.soundOn);
    setSetting("Settings/Music", gameSettings.musicOn);
    setSetting("Settings/Lang", gameSettings.lang);
}

//-------------------------------------------------------------
void clPPSettings::loadGameData() {
    gameData.level = getSetting("Data/level", 1).toInt();
    gameData.points = getSetting("Data/points", 1).toUInt();
    gameData.dataLevels = getSetting("Data/dataLevels", 1).toUInt();
}

//-------------------------------------------------------------
void clPPSettings::saveGameData() const {
    setSetting("Data/level", gameData.level);
    setSetting("Data/points", gameData.points);
//    setSetting("Data/dataLevels", gameData.dataLevels);
}

//-------------------------------------------------------------
void clPPSettings::setSetting(const QString &key, const QVariant &value) const {
    static QSettings settings("ppDevGroup", GAMENAME);

    settings.setValue(key, value);
}

//-------------------------------------------------------------
QVariant clPPSettings::getSetting(const QString &key, const QVariant &defaultValue) const {
    static QSettings settings("ppDevGroup", GAMENAME);

    QVariant val = settings.value(key, defaultValue);
    return val;
}

//-------------------------------------------------------------
void clPPSettings::prepareGameData() {
    // Load fonts and other
    gameFonts.fntArial = loadFont(":/data/font/arial.ttf");
    gameFonts.fntSegoe = loadFont(":/data/font/segoeprb.ttf");
}

//-------------------------------------------------------------
void clPPSettings::updateMouse() {
    gameMouse.mousePrevState = gameMouse.mouseCurState;
}

void clPPSettings::updateTimer() {
    gameTime.pTime = gameTime.cTime;
    gameTime.cTime = clock->elapsed();
    gameTime.dTime = gameTime.cTime - gameTime.pTime;

    if (gameTime.dTime) {
        gameTime.fps = 1000 / gameTime.dTime;
    }
    else {
        gameTime.fps = 1000;
    }
}

//-------------------------------------------------------------
void clPPSettings::restartTimer() {
    clock->restart();
    gameTime.cTime = 0;
    updateTimer();
}

//-------------------------------------------------------------
void clPPSettings::initScreen(const float dscWidth, const float dscHeigh) {
    float debugW = 1.f;
    float debugH = 1.f;

    float myWidth = 960.f;
    float myHeight = 600.f;

    gameScreen.shiftX = 0;
    gameScreen.shiftY = 0;

#ifdef PORTRAIT
    gameScreen.origWidth = myHeight.f;
    gameScreen.origHeight = 960.f;

#ifdef Q_OS_WIN
    debugW = 0.45f;
    debugH = 0.45f;
#endif

    // Определения размеров экрана для портретной оринтации
    if (dscHeigh > dscWidth) {
        gameScreen.screenHeight = dscHeigh;
        gameScreen.screenWidth = dscWidth;
    }
    else {
        gameScreen.screenWidth = dscHeigh * debugW;
        gameScreen.screenHeight = dscWidth * debugH;
    }
//        gameScreen.screenWidth = myHeight;
//        gameScreen.screenHeight = myWidth;
#endif

#ifdef LANDSCAPE
    gameScreen.origWidth = myWidth;
    gameScreen.origHeight = myHeight;

#ifdef Q_OS_WIN
    debugW = 0.65f;
    debugH = 0.65f;
#endif

        // Определения размеров экрана для альбомной оринтации
        if (dscHeigh > dscWidth) {
            gameScreen.screenHeight = dscWidth;
            gameScreen.screenWidth = dscHeigh;
        }
        else {
            gameScreen.screenWidth = dscWidth * debugW;
            gameScreen.screenHeight = dscHeigh * debugH;
        }
//        gameScreen.screenWidth = myWidth;
//        gameScreen.screenHeight = myHeight;
#endif

    gameScreen.coefWidth = gameScreen.screenWidth / gameScreen.origWidth;
    gameScreen.coefHeight = gameScreen.screenHeight / gameScreen.origHeight;

    if (gameScreen.coefWidth < gameScreen.coefHeight) {
        gameScreen.coefScreen = gameScreen.coefWidth;
        gameScreen.shiftY = (gameScreen.screenHeight - (gameScreen.origHeight * gameScreen.coefWidth)) / 2;
    }
    else {
        gameScreen.coefScreen = gameScreen.coefHeight;
        gameScreen.shiftX = (gameScreen.screenWidth - (gameScreen.origWidth * gameScreen.coefHeight)) / 2;
    }
}

//-------------------------------------------------------------
QFont* clPPSettings::loadFont(QString path) {
    int id = QFontDatabase::addApplicationFont(path);
    return new QFont(QFontDatabase::applicationFontFamilies(id).at(0), 36);
}

//-------------------------------------------------------------
QFont& clPPSettings::setFontSettings(QFont &font, int size, bool bold, bool italic, bool underline) {
//    font.setPointSize(size);
    font.setPixelSize(size);
    font.setBold(bold);
    font.setItalic(italic);
    font.setUnderline(underline);

    return font;
}

//-------------------------------------------------------------
void clPPSettings::drawText(QPainter *painter, QString str, QFont &fnt, QRect rect, QColor pen, int flags) {
    QPixmap img(rect.size());
    QPainter paint;

    img.fill(QColor(255, 0, 0, 0));
    paint.begin(&img);
    paint.setRenderHint(QPainter::TextAntialiasing, true);
    paint.setPen(pen);
    paint.setFont(fnt);
    paint.drawText(QRect(QPoint(0, 0), rect.size()), flags, str);
    paint.end();

    painter->drawPixmap(rect.topLeft(), img);
}

//-------------------------------------------------------------

