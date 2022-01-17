#include "formular.h"

#include <QDebug>

Formular::Formular()
{
}

Formular::Formular(const QString &formularStr)
{
    set(formularStr);
}

void Formular::set(const QString &formularStr)
{
    QList<QString> formularList = formularStr.split("|");
    for (const QString &drugStr: formularList) {
        Drug drug = drugStr.split(" ");
        _formular.append(drug);
    }
}

void Formular::get()
{
    qDebug() << _formular;
}

Drug Formular::getDrug(const QModelIndex &idx)
{
    int i = toListIndex(idx);
    if (i < _formular.count())
        return _formular.at(i);
    else
        return Drug();
}

void Formular::setDrug(const QModelIndex &idx, const Drug &drug)
{
    int i = toListIndex(idx);
    _formular.replace(i, drug);
}
