#ifndef PPOBJCLASSES_H
#define PPOBJCLASSES_H

#include <QRect>
#include <QFont>
#include <QString>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QPainter>

//-Class for button control------------------------------------
class clPPButton {

protected:
    QPainter painter;

    bool enabled;

public:
    bool clicked;

    QRect pos;

    QPixmap *imgOff;
    QPixmap *imgOn;
    QPixmap *imgUnEnabled;

    QPixmap *imgTxt;

    QGraphicsPixmapItem *item;

    QString text;

public:

    clPPButton(QRect _pos, QPixmap *_source, QRect _off, QRect _on, QRect* _unEnabled = 0);

    clPPButton(QRect _pos, QPixmap *_sourceOff, QPixmap *_sourceOn, QPixmap *_sourceUnEnabled = 0);

    virtual ~clPPButton();

    virtual bool updateButton(QPoint &mousePos, bool _clicked = false);
    virtual bool updateButton(int &x, int &y, bool _clicked = false);

    virtual bool checkClick(QPoint &mousePos) const;
    virtual bool checkClick(int &x, int &y) const;

    virtual void setText(QString txt, int flags, QColor color, QFont &font);

    virtual void operator =(QGraphicsPixmapItem* _item);

    virtual void setEnabled(bool _enabled = true);
    virtual bool isEnabled() const;

protected:
    virtual void initButton();
    virtual void setImage();
};

//-Class group button------------------------------------------
class clPPGroupButton : public clPPButton {
private:
    size_t myGroup;

    static QMap<size_t, QVector<clPPGroupButton*> > mapContainer;
    static bool first;

public:

    clPPGroupButton(QRect _pos, QPixmap *_source, QRect _off, QRect _on, QRect* _unEnabled = 0, size_t _group = 0);
    clPPGroupButton(QRect _pos, QPixmap *_sourceOff, QPixmap *_sourceOn, QPixmap *_sourceUnEnabled = 0, size_t _group = 0);

    virtual ~clPPGroupButton();

    virtual bool updateButton(QPoint &mousePos, bool _clicked = false);
//    bool updateBut();

    static bool clickGroup(size_t _group, QPoint mousePos);
    static void checkAllGroup(QPoint mousePos);
    static void clearGroup(size_t _group);
    static size_t getCklickedIdGroup(size_t _group);

    void setGroup(size_t _group);

    void operator =(QGraphicsPixmapItem* _item);

protected:
    void initButton(size_t _group);
};

#endif // PPOBJCLASSES_H
