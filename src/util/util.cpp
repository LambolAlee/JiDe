#include "util.h"

#include <QFile>
#include <QApplication>

void Util::loadStyleSheet(const QString &path)
{
    QFile file(path);
    if (file.open(QFile::ReadOnly)) {
        QString style = QLatin1String(file.readAll());
        QString loaded = qApp->styleSheet();
        qApp->setStyleSheet(loaded.append(style));
        file.close();
    }
    else {
        qDebug() << QObject::tr("==> Style Loader: load stylesheet failed: %1 with error string: \n%2").arg(path, file.errorString());
    }
}

void Util::dumpStructure(const QObject *obj, int spaceCount) {
    qDebug() << QString("%1%2 : %3")
                .arg("", spaceCount)
                .arg(obj->metaObject()->className())
                .arg(obj->objectName());

    QObjectList list = obj->children();

    foreach (QObject * child, list) {
        dumpStructure(child, spaceCount + 4);
    }
}
