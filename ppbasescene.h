#ifndef PPBASESCENE_H
#define PPBASESCENE_H

#include <QtWidgets>

class clPPBaseScene : public QObject {

    Q_OBJECT

protected:
    QGraphicsScene *scene;

    QWidget *parent;

    virtual void exitGame();

public:

    clPPBaseScene(QGraphicsScene *_scene = 0, QWidget *_parent = 0);
    clPPBaseScene(QString _name, QGraphicsScene *_scene = 0, QWidget *_parent = 0);
    virtual ~clPPBaseScene();

    virtual void initScene() = 0;
    virtual void setActive(bool _active = true);

    virtual void setScene(QGraphicsScene *_scene);
    virtual void freeScreen();

    QString screenName;

    bool active;

    virtual void goToNextScreen();
    virtual void goToPrevScreen();

signals:
    void signalNextScreen(QString _name);
    void signalPrevScreen(QString _name);
    void signalExitGame(QString _name);

public slots:
    virtual void updateScene() = 0;
};

#endif // PPBASESCENE_H
