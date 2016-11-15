#include "ppsound.h"
#include "ppsettings.h"

//-------------------------------------------------------------
clPPSound *gSound = new clPPSound;

//-------------------------------------------------------------
clPPSound::clPPSound(QObject *parent) : QObject(parent) {
    musicPlayer = new QMediaPlayer;
    musicPlayer->setVolume(100);

    // Load title music
//    musicPlayer->setMedia(QUrl(QStringLiteral("qrc:///data/audio/title.mp3")));

    musicBeepper = new QSound(FILEBEPPER);
    musicBeepper->setLoops(-1);
}

//-------------------------------------------------------------
clPPSound::~clPPSound() {
    musicPlayer->stop();

    delete musicPlayer;
    delete musicBeepper;
}

// Player
//-------------------------------------------------------------
void clPPSound::playerPlay() {
    if (gSettings->gameSettings.musicOn) {
        musicPlayer->play();
    }
}

//-------------------------------------------------------------
void clPPSound::playerStop() {
    musicPlayer->stop();
}

//-------------------------------------------------------------
void clPPSound::playerPause() {
    musicPlayer->pause();
}

//-------------------------------------------------------------
bool clPPSound::playerCheckStop() {
    return musicPlayer->state() == QMediaPlayer::StoppedState || musicPlayer->state() == QMediaPlayer::PausedState;
}

//-------------------------------------------------------------
void clPPSound::playerSetMedia(QMediaContent &media) {
    musicPlayer->setMedia(media);
}

//-------------------------------------------------------------

// Beepper
//-------------------------------------------------------------
void clPPSound::beepSound(enBeppers beep) {
    if (!gSettings->gameSettings.soundOn) return;

    switch (beep) {
    case bpPress:
//        musicBeepper->play(":/data/audio/click.wav");
        break;

    case bpRelease:
//        musicBeepper->play(":/data/audio/click.wav");
        break;

    case bpSwipe:
//        musicBeepper->play(":/data/audio/swipe.wav");
        break;

    case bpGameOver:
//        musicBeepper->play(":/data/audio/gameover.wav");
        break;
    }
}

//-------------------------------------------------------------
void clPPSound::beepPlay(QString fileName) {
    if (fileName.isEmpty()) {
        musicBeepper->play();
    }
    else {
        musicBeepper->play(fileName);
    }
}

//-------------------------------------------------------------
void clPPSound::beepStop() {
    musicBeepper->stop();
}

//-------------------------------------------------------------
