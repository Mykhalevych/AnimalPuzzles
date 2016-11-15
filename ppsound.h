#ifndef PPSOUND_H
#define PPSOUND_H

#include <QObject>
#include <QtMultimedia>

#define FILEBEPPER ""
//-------------------------------------------------------------

class clPPSound : public QObject {

    Q_OBJECT

private:
    QMediaPlayer *musicPlayer;
    QSound *musicBeepper;

public:
    clPPSound(QObject *parent = 0);
    ~clPPSound();

    // Media methods
    enum enBeppers {bpPress, bpRelease, bpSwipe, bpGameOver};
    void playerPlay();
    void playerStop();
    void playerPause();
    bool playerCheckStop();
    void playerSetMedia(QMediaContent &media);
    void beepSound(enBeppers beep);
    void beepPlay(QString fileName = "");
    void beepStop();

};

//-------------------------------------------------------------
extern clPPSound* gSound;

#endif // PPSOUND_H
