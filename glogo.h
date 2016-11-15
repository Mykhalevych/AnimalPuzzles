#ifndef GLOGO_H
#define GLOGO_H

#include "ppbasescene.h"
#include "ppsettings.h"

class GLogo : public clPPBaseScene {

    Q_OBJECT

private:
    QPixmap *pxmpShadow;

    int iAlpha;
    int r, g, b;
    qint64 timeLogo;

    QGraphicsPixmapItem *gpiShadow;

    QObject *parent;

    GLogo(QGraphicsScene *_scene = 0, QWidget *_parent = 0);

public:
    GLogo(QString _name, QGraphicsScene *_scene = 0, QWidget *_parent = 0);
    ~GLogo();

    void initScene();

public slots:
    void updateScene();
};

#endif // GLOGO_H
