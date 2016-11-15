#ifndef PPLOCALE_H
#define PPLOCALE_H


#include <QString>
#include <QMap>

#define LOC_DEBUG_

class clPPLocale {

private:
    QMap <QString,  QMap <int, QString> > strDepot;

    QString& checkStringForSystemLiterals(QString &str);

public:
    clPPLocale();
    clPPLocale(QString lang);

    void loadLocale(QString lang);

    QString getLocaleString(QString strModule, int nStr, QString strDefault);
};

extern clPPLocale* gLocale;

#endif // MYLOCALE_H
