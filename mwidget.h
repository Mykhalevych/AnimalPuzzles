#ifndef MWIDGET_H
#define MWIDGET_H

#include "ppbasescene.h"
#include "ppsettings.h"


class MWidget : public QGraphicsView
{
    Q_OBJECT

private:
    QList <clPPBaseScene*> screens;
    QList <clPPBaseScene*>::iterator curentScreen;

    QTimer *gTimer;

    QGraphicsScene *mainScene;

protected:

    virtual void customEvent(QEvent *pe);

    virtual void closeEvent(QCloseEvent *ce);

    virtual void keyPressEvent(QKeyEvent *ke);

    virtual void mousePressEvent(QMouseEvent *me);
    virtual void mouseMoveEvent(QMouseEvent *me);
    virtual void mouseReleaseEvent(QMouseEvent *me);
    virtual void mouseDoubleClickEvent(QMouseEvent *me);

public:
    MWidget(QWidget *parent = 0);
    ~MWidget();

private:
    void initScreens();
    void addScene(clPPBaseScene *_scene);



public slots:
    void slotUpdateGame();
    void slotNextScreen(QString _name);
    void slotPrevScreen(QString _name);
    void slotExitGame(QString _name);
};

#endif // MWIDGET_H
