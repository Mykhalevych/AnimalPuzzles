#include <QApplication>

#include "mwidget.h"
#include "pplocale.h"
#include "ppobjclasses.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("ppDevGroup");
    QCoreApplication::setApplicationName(GAMENAME);

    gSettings->loadSettings();

    // Для локализации необходимо определить язык
    QString locale = QLocale::system().name().mid(0, 2).toUpper();
    if (!gSettings->gameSettings.lang) {
        if (locale == "UK") {
            gSettings->gameSettings.lang = 3;
        }
        else if (locale == "RU") { // Проверка языка
            gSettings->gameSettings.lang = 2;
        }
        else {
            gSettings->gameSettings.lang = 1;
            locale = "EN"; // Устанавливаем английский если язык не русский и не украинский
        }
        gSettings->saveGameData();
    }
    else {
        locale = (gSettings->gameSettings.lang == 1) ? "EN" : (gSettings->gameSettings.lang == 2) ? "RU" : "UK";
    }

//    locale = "EN"; // Язык для теста
    gLocale->loadLocale(locale);

    MWidget w;
    w.show();

    return a.exec();
}
