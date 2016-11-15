#include "glogo.h"

//-------------------------------------------------------------
GLogo::GLogo(QGraphicsScene *_scene, QWidget *_parent)
    : clPPBaseScene(_scene, _parent) {

}

//-------------------------------------------------------------
GLogo::GLogo(QString _name, QGraphicsScene *_scene, QWidget *_parent)
    : clPPBaseScene(_name, _scene, _parent) {

    timeLogo = 0;
}

//-------------------------------------------------------------
GLogo::~GLogo() {
    delete pxmpShadow;
}

//-------------------------------------------------------------
void GLogo::initScene() {
    scene->clear();

#ifdef PORTRAIT
    QPixmap *pxmpLogo = new QPixmap(600, 960); // Loading Logo picture
#else
    QPixmap *pxmpLogo = new QPixmap(960, 600); // Loading Logo picture
#endif
    pxmpLogo->fill(QColor(255, 160, 0, 255));

    scene->addPixmap(*pxmpLogo);
    delete pxmpLogo;

#ifdef PORTRAIT
    pxmpShadow = new QPixmap(600, 960);
#else
    pxmpShadow = new QPixmap(960, 600);
#endif
    pxmpShadow->fill(QColor(0, 0, 0, 255));
    gpiShadow = scene->addPixmap(*pxmpShadow);
}

//-------------------------------------------------------------
void GLogo::updateScene() {

    static int const interval = 1000;
    static int const timelogo = 2000;

    if (!timeLogo) { // First time
        timeLogo = gSettings->gameTime.cTime + 3000;
        iAlpha = 255;
        r = g = b = 0;
    }

    quint64 timer = gSettings->gameTime.cTime - timeLogo;

    if ( timer <= interval) {
        iAlpha = 255 - (gSettings->gameTime.cTime - timeLogo) / (interval / 250.0);
    }
    else if (timer <= timelogo + interval) {
        iAlpha = 0;
    }
    else {
        r = g = b = 255; // Go to white, comment if go to black

        if (timer > timelogo + 2 * interval + 500) {
            timeLogo = 0;
            goToNextScreen();
            return;
        }
        else if (timer <= timelogo + 2 * interval) {
            iAlpha = (timer - (timelogo  + interval)) / (interval / 250.0);
        }
        else {
            iAlpha = 255;
        }
    }

    pxmpShadow->fill(QColor(r, g, b, iAlpha));
    gpiShadow->setPixmap(*pxmpShadow);
}

//-------------------------------------------------------------
