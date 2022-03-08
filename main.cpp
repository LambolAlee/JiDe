#include "ui/recordmanager.h"
#include "ui/framelesswindow.h"
#include "ui/titlemenubar.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#ifdef Q_OS_MAC
#include <QStyleFactory>
#endif

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

    RecordManager w;

#ifdef Q_OS_MAC
    a.setStyle(QStyleFactory::create("Fusion"));
    w.show();

#elif Q_OS_WIN
    TitleMenuBar *tb = new TitleMenuBar(w.menuBar(), &w);
    CFramelessWindow *fw = new CFramelessWindow;
    fw->makeFrameless(&w, tb, tb->title());
    tb->setParentWidget(fw);
    fw->show();

#endif

    return a.exec();
}
