#include "ppbasescene.h"

//-------------------------------------------------------------
clPPBaseScene::clPPBaseScene(QGraphicsScene *_scene, QWidget *_parent) :
    QObject(0), scene(_scene), parent(_parent) {

    active = false;
}

//-------------------------------------------------------------
clPPBaseScene::clPPBaseScene(QString _name, QGraphicsScene *_scene, QWidget *_parent) :
    QObject(0), scene(_scene), parent(_parent) {

    active = false;
    screenName = _name;
}

//-------------------------------------------------------------
clPPBaseScene::~clPPBaseScene() {

}

//-------------------------------------------------------------
void clPPBaseScene::setScene(QGraphicsScene *_scene) {
    scene = _scene;
}

//-------------------------------------------------------------
void clPPBaseScene::setActive(bool _active) {
    active = _active;
}

//-------------------------------------------------------------
void clPPBaseScene::freeScreen() {
    scene = 0;
    active = false;
}

//-------------------------------------------------------------
void clPPBaseScene::goToNextScreen() {
    emit(signalNextScreen(screenName));
}

//-------------------------------------------------------------
void clPPBaseScene::goToPrevScreen() {
    emit(signalPrevScreen(screenName));
}

//-------------------------------------------------------------
void clPPBaseScene::exitGame() {
    emit(signalExitGame(screenName));
}

//-------------------------------------------------------------
