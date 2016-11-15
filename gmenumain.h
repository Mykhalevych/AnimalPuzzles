#ifndef GMENUMAIN_H
#define GMENUMAIN_H

#include "ppbasescene.h"
#include "ppobjclasses.h"

class GMenuMain : public clPPBaseScene {
    Q_OBJECT

private:

    GMenuMain(QGraphicsScene *_scene = 0, QWidget *_parent = 0);

    clPPButton *btnStart;
    clPPButton *btnExit;

    QPixmap *pxmpTiles;

    QVector<clPPGroupButton*> btnLevel;
    QVector<clPPGroupButton*> btnLang;

public:
    GMenuMain(QString _name, QGraphicsScene *_scene = 0, QWidget *_parent = 0);
    ~GMenuMain();

    void initScene();

public slots:
    void updateScene();

private:
    void checkMouse();
};

#endif // GMENUMAIN_H
