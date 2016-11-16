#ifndef GSTRUCTURES_H
#define GSTRUCTURES_H

//#include <QtGlobal>

//-----------------------------------------------------------------------
struct structGameSettings {
    bool soundOn;
    bool musicOn;
    int lang;
};

//-----------------------------------------------------------------------
struct structGameData {
    int level;
    int points;
    int dataLevels;
};

//-Mouse parameters------------------------------------------------------
struct structMouse {
    bool mouseCurState; // Текущее состояние кнопки - true нажата
    bool mousePrevState; // Предыдущее состояние кнопки
    bool mouseDblClic; // Признак двойного нажатия
    int mouseX; // Координата X курсора мыши, в пикселях
    int mouseY; // Координата Y курсора мыши, в пикселях
    int pointX; // Координата X курсора мыши, где встал на экран
    int pointY; // Координата Y курсора мыши, где встал на экран
    int minX; // Для определения свайпа по горизонтали
    int minY; // Для определения свайпа по вертикали
    int maxX; // Для определения свайпа по горизонтали
    int maxY; // Для определения свайпа по вертикали
};

//-Data timer------------------------------------------------------------
struct structTime {
    qint64 cTime; // Current Time
    qint64 pTime; // Previus time
    qint64 dTime; // Time delta
    qint64 fps; // FPS
};

//-Screen size & scale coefficients-------------------------------------
struct structScreen {
    float origWidth; // Original screen width (960px LANDSCAPE) (600px PORTRAIT)
    float origHeight; // Original screen height (600px LANDSCAPE) (960px PORTRAIT)
    float screenWidth; // Current screen/window width
    float screenHeight; // Current screen/window height
    float coefWidth; // Width scale coefficient
    float coefHeight; // Height scale coefficient
    float coefScreen; // Common scale coefficient

    float shiftX; // Смещения по горизонтали
    float shiftY; // Смещения по вертикали
};
//-Fonts structure-------------------------------------------------------
struct structFonts {
    QFont* fntArial;
    QFont* fntSegoe;
};
//-----------------------------------------------------------------------

#endif // GSTRUCTURES_H
