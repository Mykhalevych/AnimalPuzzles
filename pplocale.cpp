#include "pplocale.h"

#include <QFile>
#include <QIODevice>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include <QDebug>

clPPLocale *gLocale = new clPPLocale;

//-------------------------------------------------------------
clPPLocale::clPPLocale() {
    strDepot.clear();
}

//-------------------------------------------------------------
clPPLocale::clPPLocale(QString lang) {
    loadLocale(lang);
}

//-------------------------------------------------------------
QString& clPPLocale::checkStringForSystemLiterals(QString &str) {
    for (int pos = 0; pos < str.length() - 1; pos++) {
        if (str.mid(pos, 2) == "\\n") {
            str[pos] = '\n';
            str.remove(pos + 1, 1);
        }
        else if (str.mid(pos, 2) == "\\r") {
            str[pos] = '\r';
            str.remove(pos + 1, 1);
        }
        else if (str.mid(pos, 2) == "\\t") {
            str[pos] = '\t';
            str.remove(pos + 1, 1);
        }
    }

    return str;
}

//-------------------------------------------------------------
QString clPPLocale::getLocaleString(QString strModule, int nStr, QString strDefault) {
    if (strDepot.find(strModule) == strDepot.end()) {
        return strDefault;
    }
    else {
        if (strDepot[strModule].find(nStr) == strDepot[strModule].end()) {
            return strDefault;
        }
    }

    return strDepot[strModule][nStr];
}

//-------------------------------------------------------------
void clPPLocale::loadLocale(QString lang) {
    QFile fileJson(":/data/locale/locale.json");

    if (!fileJson.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open locale file.");
        return;
    }

    QJsonParseError jsErr;

    QJsonDocument jsDoc = QJsonDocument::fromJson(fileJson.readAll(), &jsErr);
    fileJson.close();

    if (jsErr.error) {
        qDebug() << jsErr.error << jsErr.errorString();
        return;
    }

    strDepot.clear();

    QJsonObject jsObjMain = jsDoc.object();
    QJsonObject::iterator itMain = jsObjMain.begin();

    while (itMain != jsObjMain.end()) {
        QString strKeyMain = itMain.key();

#ifdef LOC_DEBUG
        qDebug() << "Main - " << strKeyMain;
#endif

        QJsonObject jsObjInn = jsObjMain[strKeyMain].toObject();
        QJsonObject::iterator itInn = jsObjInn.begin();

        while (itInn != jsObjInn.end()) {
            QString strKeyInn = itInn.key();


            QJsonObject jsObjLang = jsObjInn[strKeyInn].toObject();

            strDepot[strKeyMain][strKeyInn.toInt()] = jsObjLang[lang].toString(); //checkStringForSystemLiterals(str);

#ifdef LOC_DEBUG
            qDebug() << "Inner - " << strKeyInn;

            QJsonObject::iterator itLang = jsObjLang.begin();

            qDebug() << "strLang - " << str;

            while (itLang != jsObjLang.end()) {
                QString strKeyLang = itLang.key();

                qDebug() << "Lang - " << strKeyLang;

                itLang++;
            }

#endif
            itInn++;
        }

        itMain++;
    }
}

//-------------------------------------------------------------
