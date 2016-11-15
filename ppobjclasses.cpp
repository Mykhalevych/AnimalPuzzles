#include "ppobjclasses.h"

//-------------------------------------------------------------
clPPButton::clPPButton(QRect _pos, QPixmap *_source, QRect _off, QRect _on, QRect* _unEnabled) :
    clicked(false) {

    pos = _pos;

    initButton();

//    QPainter painter;
    painter.begin(imgOff);
//    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.drawPixmap(QPoint(0, 0), *_source, _off);
    painter.end();

    painter.begin(imgOn);
//    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.drawPixmap(QPoint(0, 0), *_source, _on);
    painter.end();

    if (_unEnabled) {
        imgUnEnabled = new QPixmap(pos.size());
        imgUnEnabled->fill(Qt::transparent);
        painter.begin(imgUnEnabled);
//        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter.drawPixmap(QPoint(0, 0), *_source, *_unEnabled);
        painter.end();
    }
}

//-------------------------------------------------------------
clPPButton::clPPButton(QRect _pos, QPixmap *_sourceOff, QPixmap *_sourceOn, QPixmap *_sourceUnEnabled) :
    clicked(false) {

    pos = _pos;

    initButton();

//    QPainter painter;
    painter.begin(imgOff);
//    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.drawPixmap(0, 0, *_sourceOff);
    painter.end();

    painter.begin(imgOn);
//    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.drawPixmap(0, 0, *_sourceOn);
    painter.end();

    if (_sourceUnEnabled) {
        imgUnEnabled = new QPixmap(pos.size());
        painter.begin(imgUnEnabled);
//        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter.drawPixmap(QPoint(0, 0), *_sourceUnEnabled);
        painter.end();
    }
}

//-------------------------------------------------------------
clPPButton::~clPPButton() {
    delete imgOff;
    delete imgOn;

    if (imgTxt) {
        delete imgTxt;
    }

    if (imgUnEnabled) {
        delete imgUnEnabled;
    }

    item = 0;
//    if (item) {
//        delete item;
//        item = 0;
//    }
}

//-------------------------------------------------------------
void clPPButton::initButton() {
    imgOff = new QPixmap(pos.size());
    imgOn = new QPixmap(pos.size());
    imgOff->fill(QColor(0, 0, 0, 0));
    imgOn->fill(QColor(0, 0, 0, 0));

    item = 0;
    imgTxt = 0;
    imgUnEnabled = 0;
    enabled = true;
}

//-------------------------------------------------------------
bool clPPButton::checkClick(QPoint &mousePos) const {
    if (!enabled) return false;

    if (pos.contains(mousePos)) {
        return true;
    }

    return false;
}

//-------------------------------------------------------------
bool clPPButton::checkClick(int &x, int &y) const {
    QPoint mousePos = QPoint(x, y);

    return checkClick(mousePos);
}

//-------------------------------------------------------------
bool clPPButton::updateButton(QPoint &mousePos, bool _clicked) {
    if (!enabled) return clicked;

    if (pos.contains(mousePos) && !clicked && _clicked) {
        clicked = true;
        setImage();
    }
    else if (clicked && (!pos.contains(mousePos) || !_clicked)) {
        clicked = false;
        setImage();
    }

    return clicked;
}

//-------------------------------------------------------------
bool clPPButton::updateButton(int &x, int &y, bool _clicked) {
    QPoint mousePos = QPoint(x, y);

    return updateButton(mousePos, _clicked);
}

//-------------------------------------------------------------
void clPPButton::setText(QString txt, int flags, QColor color, QFont &font) {
//    QPainter painter;

    text = txt;
    if (imgTxt) {
        delete imgTxt;
        imgTxt = 0;
    }

    imgTxt = new QPixmap(pos.size());
    imgTxt->fill(Qt::transparent);

    painter.begin(imgTxt);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setFont(font);
    painter.setPen(color);
    painter.drawText(QRect(QPoint(0, 0), pos.size()), flags, txt);
    painter.end();

    setImage();
}

//-------------------------------------------------------------
void clPPButton::operator =(QGraphicsPixmapItem* _item) {
    item = _item;
    item->setPos(pos.topLeft());
    setImage();
}

//-------------------------------------------------------------
void clPPButton::setImage() {
    if (item) {
        QPixmap img(pos.size());
        img.fill(Qt::transparent);
        painter.begin(&img);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter.setBrush(QColor(128, 128, 128, 196));

        if (!enabled && imgUnEnabled) {
            painter.drawPixmap(0, 0, *imgUnEnabled);
        }
        else if (clicked) {
            painter.drawPixmap(0, 0, *imgOn);
        }
        else {
            painter.drawPixmap(0, 0, *imgOff);
        }

        if (imgTxt) {
            painter.drawPixmap(0, 0, *imgTxt);
        }

        painter.end();
        item->setPixmap(img);
    }
}

//-------------------------------------------------------------
void clPPButton::setEnabled(bool _enabled) {
    enabled = _enabled;
    setImage();
}

//-------------------------------------------------------------
bool clPPButton::isEnabled() const {
    return enabled;
}
//-------------------------------------------------------------
//-------------------------------------------------------------
QMap<size_t, QVector<clPPGroupButton*> > clPPGroupButton::mapContainer;
bool clPPGroupButton::first = true;
//-------------------------------------------------------------
clPPGroupButton::clPPGroupButton(QRect _pos, QPixmap *_source, QRect _off, QRect _on, QRect* _unEnabled, size_t _group) :
    clPPButton(_pos, _source, _off, _on, _unEnabled) {

    initButton(_group);
}

//-------------------------------------------------------------
clPPGroupButton::clPPGroupButton(QRect _pos, QPixmap *_sourceOff, QPixmap *_sourceOn, QPixmap *_sourceUnEnabled, size_t _group) :
    clPPButton(_pos, _sourceOff, _sourceOn, _sourceUnEnabled) {

    initButton(_group);
}

//-------------------------------------------------------------
clPPGroupButton::~clPPGroupButton() {

}

//-------------------------------------------------------------
void clPPGroupButton::initButton(size_t _group) {
    myGroup = 0;

    if (first) {
        first = false;
        mapContainer.clear();
    }

    if (_group) {
        setGroup(_group);
    }
}

//-------------------------------------------------------------
bool clPPGroupButton::updateButton(QPoint &mousePos, bool _clicked) {
    if (!enabled) return clicked;

    if (pos.contains(mousePos) && _clicked) {
        if (!clicked) {
            if (myGroup) {
                size_t mySize = mapContainer[myGroup].size();
                for (size_t l = 0; l < mySize; l++) {
                    if (mapContainer[myGroup][l] != this && mapContainer[myGroup][l]->clicked) {
                        mapContainer[myGroup][l]->clicked = false;
                        mapContainer[myGroup][l]->setImage();
                    }
                }
            }
            clicked = true;
            setImage();
        }
        else if (!myGroup) {
            clicked = false;
            setImage();
        }
    }

    return clicked;
}

//-------------------------------------------------------------
void clPPGroupButton::setGroup(size_t _group) {
    if(myGroup) {
        size_t mySize = mapContainer[_group].size();
        for (size_t l = 0; l < mySize; l++) {
            if (mapContainer[_group][l] == this) {
                mapContainer[_group].remove(l);
                break;
            }
        }
        if (clicked && mySize > 1) {
            mapContainer[_group][0]->clicked = true;
            mapContainer[_group][0]->setImage();
        }
    }

    myGroup = _group;
    if (myGroup) {
        mapContainer[myGroup].push_back(this);
        if (mapContainer[myGroup].size() == 1) {
            clicked = true;
        }
    }

    setImage();
}

//-------------------------------------------------------------
bool clPPGroupButton::clickGroup(size_t _group, QPoint mousePos) {
    bool res = false;
    size_t mySize = mapContainer[_group].size();
    for (size_t l = 0; l < mySize; l++) {
        if (mapContainer[_group][l]->checkClick(mousePos)) {
            mapContainer[_group][l]->updateButton(mousePos, true);
            res = true;
        }
    }

    return res;
}

//-------------------------------------------------------------
void clPPGroupButton::checkAllGroup(QPoint mousePos) {
    QMap<size_t, QVector<clPPGroupButton*> >::iterator it = mapContainer.begin();

    while (it != mapContainer.end()) {
        clickGroup(it.key(), mousePos);
        ++it;
    }
}

//-------------------------------------------------------------
void clPPGroupButton::clearGroup(size_t _group) {
    mapContainer[_group].clear();
}

//-------------------------------------------------------------
void clPPGroupButton::operator =(QGraphicsPixmapItem* _item) {
    clPPButton::operator =(_item);
}

//-------------------------------------------------------------
size_t clPPGroupButton::getCklickedIdGroup(size_t _group) {
    if (mapContainer.find(_group) != mapContainer.end()) {
        size_t mySize = mapContainer[_group].size();
        for (size_t id = 0; id < mySize; id++) {
            if (mapContainer[_group][id]->clicked) {
                return (id + 1);
            }
        }
    }

    return 1;
}
//-------------------------------------------------------------
