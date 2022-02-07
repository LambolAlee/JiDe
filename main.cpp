#include "ui/launchwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QResource>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "RecMed_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    qApp->setStyleSheet("file:///:/stylesheet/style.qss");

    LaunchWindow w;
    w.show();
    return a.exec();
}
