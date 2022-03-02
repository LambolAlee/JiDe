#include "patient.h"

const QString Patient::save()
{
    QStringList updateString;
    auto item = constBegin();
    QByteArray propertyName;
    while (item != constEnd()) {
        propertyName = item.key().toLatin1();
        setProperty(propertyName.constData(), item.value());
        updateString << QString("%1='%2'").arg(item.key(), item.value().toString());
        ++item;
    }
    clear();
    return updateString.join(", ");
}
