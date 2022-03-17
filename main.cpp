#include "ui/recordmanager.h"
#include "ui/framelesswindow.h"
#include "ui/titlemenubar.h"
#include "util/util.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#ifdef Q_OS_MAC
#include <QStyleFactory>
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("lambol");
    a.setApplicationName("JiDe");
    a.setApplicationDisplayName(QObject::tr("JiDe"));

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "RecMed_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    Util::loadStyleSheet(":/stylesheet/style.qss");

    RecordManager w;

#ifdef Q_OS_MAC
    a.setStyle(QStyleFactory::create("Fusion"));
    Util::loadStyleSheet(":/stylesheet/font-mac.qss");
    w.show();

#elif defined Q_OS_WIN
    Util::loadStyleSheet(":/stylesheet/font-win.qss");
    TitleMenuBar *tb = new TitleMenuBar(w.menuBar(), &w);
    CFramelessWindow *fw = new CFramelessWindow;
    fw->makeFrameless(&w, tb, tb->title());
    tb->setParentWidget(fw);
    fw->show();

#endif

    return a.exec();
}
