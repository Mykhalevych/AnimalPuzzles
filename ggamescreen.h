#ifndef GGAMESCREEN_H
#define GGAMESCREEN_H

#include "ppbasescene.h"
#include "ppobjclasses.h"
#include "gitembase.h"

class GGameScreen : public clPPBaseScene {
    Q_OBJECT

private:
    GGameScreen(QGraphicsScene *_scene = 0, QWidget *_parent = 0);

    clPPButton *btnNext;
    clPPButton *btnRefresh;
    clPPButton *btnBack;

    clItemBase * mainItem;

    QPixmap *pxmpTiles;

public:
    GGameScreen(QString _name, QGraphicsScene *_scene = 0, QWidget *_parent = 0);
    ~GGameScreen();

    void initScene();

public slots:
    void updateScene();

private:
    void checkMouse();
    void setMainItem();
};

#endif // GGAMESCREEN_H
