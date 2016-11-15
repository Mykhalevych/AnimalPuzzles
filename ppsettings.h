#ifndef PPSETTINGS_H
#define PPSETTINGS_H

#include <QPainter>
#include <QFontDatabase>
#include <QElapsedTimer>
#include <QVariant>

#include "gstructures.h"

//DEFINES------------------------------------------------------
#define GAMENAME "AnimalPuzzles"

#define LANDSCAPE
//#define PORTRAIT

#define TRANSLATE

#define MULTITOUCH

#define DEBUG
//-------------------------------------------------------------

class clPPSettings {

private:
    // Таймер для синхронизации
    QElapsedTimer *clock;

public:
    enum enGameSatus {stLogo, stMenu, stGame, stPause, stExit} statusGame;

    clPPSettings();
    ~clPPSettings();

    structGameSettings gameSettings;
    structGameData gameData;

    structScreen gameScreen;

    structMouse gameMouse;
    structTime gameTime;

    structFonts gameFonts;

    // Методы сохранения и загрузки настроек игры
    void loadSettings();
    void saveSettings() const;

    void loadGameData();
    void saveGameData() const;

    void updateMouse();
    void updateTimer();
    void restartTimer();

    void initScreen(const float dscWidth = 960.f, const float dscHeigh = 600.f);

    void prepareGameData();

    // Fonts function;
    QFont* loadFont(QString path);
    QFont& setFontSettings(QFont &font, int size = 12, bool bold = false, bool italic = false, bool underline = false);

    void drawText(QPainter* painter, QString str, QFont& fnt, QRect rect, QColor pen, int flags = Qt::AlignCenter);

private:
    // Методы для сохранения и получения различных установок
    void setSetting(const QString &key, const QVariant &value) const;
    QVariant getSetting(const QString &key, const QVariant &defaultValue) const;
};

extern clPPSettings *gSettings;

#endif // GSETTINGS_H
