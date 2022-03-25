#ifndef UTIL_H
#define UTIL_H

class QString;
class QObject;

namespace Util
{
    void loadStyleSheet(const QString &path);
    void dumpStructure(const QObject *obj, int spaceCount = 0);
}

#endif // UTIL_H
