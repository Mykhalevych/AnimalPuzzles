#include "mwidget.h"
#include "ppsettings.h"
#include "pplocale.h"
#include "glogo.h"
#include "gmenumain.h"
#include "ggamescreen.h"

//-------------------------------------------------------------
MWidget::MWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    gSettings->initScreen(qApp->desktop()->width(), qApp->desktop()->height());

    gSettings->loadGameData();
    gSettings->prepareGameData();

    // Set settings for screen
    setBackgroundBrush(QBrush(Qt::black));
    setRenderHint(QPainter::SmoothPixmapTransform);
//    setRenderHint(QPainter::Antialiasing);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
#ifdef TRANSLATE
    scale(gSettings->gameScreen.coefScreen, gSettings->gameScreen.coefScreen);
#else
    scale(gSettings->gameScreen.coefWidth, gSettings->gameScreen.coefHeight);
#endif

    mainScene = new QGraphicsScene(this);
    mainScene->clear();
    setScene(mainScene);
    setRenderHint(QPainter::SmoothPixmapTransform);
//    setRenderHint(QPainter::Antialiasing);

    initScreens();

#ifdef Q_OS_WIN
    this->setFixedSize(QSize(gSettings->gameScreen.screenWidth, gSettings->gameScreen.screenHeight));
#endif

    gTimer = new QTimer;
    connect(gTimer, SIGNAL(timeout()), SLOT(slotUpdateGame()));
    gTimer->start(10);
}

//-------------------------------------------------------------
MWidget::~MWidget()
{
    gTimer->stop();
    delete gTimer;
}

//-------------------------------------------------------------
void MWidget::initScreens() {
    screens.clear();

    addScene(new GLogo(QString("Logo"), mainScene));
    addScene(new GMenuMain(QString("Menu"), mainScene));
    addScene(new GGameScreen(QString("Game"), mainScene));

    curentScreen = screens.begin();
    (*curentScreen)->setActive();
    (*curentScreen)->initScene();

    gSettings->statusGame = clPPSettings::stLogo;
}

//-------------------------------------------------------------
void MWidget::addScene(clPPBaseScene *_scene) {
    connect(_scene, SIGNAL(signalNextScreen(QString)), SLOT(slotNextScreen(QString)));
    connect(_scene, SIGNAL(signalPrevScreen(QString)), SLOT(slotPrevScreen(QString)));
    connect(_scene, SIGNAL(signalExitGame(QString)), SLOT(slotExitGame(QString)));

    screens.push_back(_scene);
}

//-------------------------------------------------------------
void MWidget::slotUpdateGame() {
    gSettings->updateTimer();

    (*curentScreen)->updateScene();

    gSettings->updateMouse();
}

//-------------------------------------------------------------
void MWidget::slotNextScreen(QString _name) {
    (*curentScreen)->setActive(false);
    if (_name == "Logo") {
        clPPBaseScene *sc = (*curentScreen);
        (*curentScreen) = 0;
        delete sc;

        gSettings->statusGame = clPPSettings::stMenu;
    }
    else if (_name == "Menu") {
        gSettings->statusGame = clPPSettings::stGame;
    }
    else {
        (*curentScreen)->setActive();
        return;
    }

    curentScreen++;
    (*curentScreen)->setActive();
    (*curentScreen)->initScene();
}

//-------------------------------------------------------------
void MWidget::slotPrevScreen(QString _name) {
    if (_name == "Logo") {
        close();
    }
    else if (_name == "Menu") {
        close();
    }
    else {
        (*curentScreen)->setActive(false);

        gSettings->statusGame = clPPSettings::stMenu;

        curentScreen--;
        (*curentScreen)->setActive();
        (*curentScreen)->initScene();
    }
}

//-------------------------------------------------------------
void MWidget::slotExitGame(QString _name) {
    qDebug() << _name;
    if (_name == "Logo") {
        close();
    }
    else if (_name == "Menu") {
        close();
    }
    else {
        slotPrevScreen(_name);
    }
}

//-------------------------------------------------------------
void MWidget::keyPressEvent(QKeyEvent *ke) {
    if (ke->key() == Qt::Key_Back) {
        (*curentScreen)->goToPrevScreen();
    }
}

//-------------------------------------------------------------
void MWidget::mousePressEvent(QMouseEvent *me) {
#ifdef TRANSLATE
    gSettings->gameMouse.mouseX = (me->x() - gSettings->gameScreen.shiftX) / gSettings->gameScreen.coefScreen;
    gSettings->gameMouse.mouseY = (me->y() - gSettings->gameScreen.shiftY) / gSettings->gameScreen.coefScreen;
#else
    gSettings->gameMouse.mouseX = me->x() / gSettings->gameScreen.coefWidth;
    gSettings->gameMouse.mouseY = me->y() / gSettings->gameScreen.coefHeight;
#endif

    gSettings->gameMouse.pointX = gSettings->gameMouse.minX =
            gSettings->gameMouse.maxX = gSettings->gameMouse.mouseX;
    gSettings->gameMouse.pointY = gSettings->gameMouse.minY =
            gSettings->gameMouse.maxY = gSettings->gameMouse.mouseY;

    gSettings->gameMouse.mouseCurState = true;
}

//-------------------------------------------------------------
void MWidget::mouseMoveEvent(QMouseEvent *me) {
#ifdef TRANSLATE
    gSettings->gameMouse.mouseX = (me->x() - gSettings->gameScreen.shiftX) / gSettings->gameScreen.coefScreen;
    gSettings->gameMouse.mouseY = (me->y() - gSettings->gameScreen.shiftY) / gSettings->gameScreen.coefScreen;
#else
    gSettings->gameMouse.mouseX = me->x() / gSettings->gameScreen.coefWidth;
    gSettings->gameMouse.mouseY = me->y() / gSettings->gameScreen.coefHeight;
#endif

    if (gSettings->gameMouse.maxX < gSettings->gameMouse.mouseX) {
        gSettings->gameMouse.maxX = gSettings->gameMouse.mouseX;
    }
    if (gSettings->gameMouse.minX > gSettings->gameMouse.mouseX) {
        gSettings->gameMouse.minX = gSettings->gameMouse.mouseX;
    }

    if (gSettings->gameMouse.maxY < gSettings->gameMouse.mouseY) {
        gSettings->gameMouse.maxY = gSettings->gameMouse.mouseY;
    }
    if (gSettings->gameMouse.minY > gSettings->gameMouse.mouseY) {
        gSettings->gameMouse.minY = gSettings->gameMouse.mouseY;
    }
}

//-------------------------------------------------------------
void MWidget::mouseReleaseEvent(QMouseEvent *me) {
#ifdef TRANSLATE
    gSettings->gameMouse.mouseX = (me->x() - gSettings->gameScreen.shiftX) / gSettings->gameScreen.coefScreen;
    gSettings->gameMouse.mouseY = (me->y() - gSettings->gameScreen.shiftY) / gSettings->gameScreen.coefScreen;
#else
    gSettings->gameMouse.mouseX = me->x() / gSettings->gameScreen.coefWidth;
    gSettings->gameMouse.mouseY = me->y() / gSettings->gameScreen.coefHeight;
#endif

    gSettings->gameMouse.mouseCurState = false;
    gSettings->gameMouse.mouseDblClic = false;
}

//-------------------------------------------------------------
void MWidget::mouseDoubleClickEvent(QMouseEvent *me) {
#ifdef TRANSLATE
    gSettings->gameMouse.mouseX = (me->x() - gSettings->gameScreen.shiftX) / gSettings->gameScreen.coefScreen;
    gSettings->gameMouse.mouseY = (me->y() - gSettings->gameScreen.shiftY) / gSettings->gameScreen.coefScreen;
#else
    gSettings->gameMouse.mouseX = me->x() / gSettings->gameScreen.coefWidth;
    gSettings->gameMouse.mouseY = me->y() / gSettings->gameScreen.coefHeight;
#endif

    gSettings->gameMouse.pointX = gSettings->gameMouse.minX =
            gSettings->gameMouse.maxX = gSettings->gameMouse.mouseX;
    gSettings->gameMouse.pointY = gSettings->gameMouse.minY =
            gSettings->gameMouse.maxY = gSettings->gameMouse.mouseY;

    gSettings->gameMouse.mouseCurState = true;
    gSettings->gameMouse.mouseDblClic = true;
}

//-------------------------------------------------------------
void MWidget::closeEvent(QCloseEvent *ce) {
    // Обязательные действия при закрытии окна
    return;
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Binary Master",
                                                               gLocale->getLocaleString(QString("Main"), 1, QString("Do you want exit from game?")),
                                                               QMessageBox::No | QMessageBox::Yes,
                                                               QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        ce->setAccepted(false);
    }
}

//-------------------------------------------------------------
void MWidget::customEvent(QEvent *pe) {


    Q_UNUSED(pe);
}

//-------------------------------------------------------------
