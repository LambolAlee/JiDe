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
        _formular.append(Formular::toDrug(drugStr));
    }
    completeDrug();
}

void Formular::get()
{
    qDebug() << _formular;
}

Drug Formular::getDrug(const QModelIndex &idx)
{
    int i = toListIndex(idx);
    return _formular.at(i);
}

void Formular::setDrug(const QModelIndex &idx, const Drug &drug)
{
    int i = toListIndex(idx);
    _formular.replace(i, drug);
}

QPair<int, int> Formular::toRowCol(int i) const
{
    int row, column;
    row = i / 4;
    column = i % 4;
    return QPair<int, int>(row, column);
}

bool Formular::insertRows(int row, int count)
{
    int startPos = 4*(row+1);
    _formular.insert(startPos, 4*count, Drug());
    get();
    return true;
}

bool Formular::removeRows(int row, int count)
{
    int startPos = 4*row;
    _formular.remove(startPos, 4*count);
    return true;
}

bool Formular::clearItems(const QModelIndexList &indexs)
{
    std::for_each(indexs.begin(), indexs.end(), [this](const QModelIndex &idx){ clearItem(idx); });
    return true;
}

void Formular::insertData(QPair<int, int> pos, const QList<Drug> &drugList, const QList<QPair<int,int>> &posList)
{
    int target = toListIndex(pos);
    QList<int> indexes;
    std::for_each(posList.cbegin(), posList.cend(), [&](const QPair<int,int> &p){ indexes << toListIndex(p.first, p.second); });
    indexes << target;

    std::sort(indexes.begin(), indexes.end());
    int sub = indexes.indexOf(target);
    int fin_target = target - sub;

    std::for_each(drugList.cbegin(), drugList.cend(), [=](const Drug &drug){ _formular.removeOne(drug); });
    std::for_each(drugList.crbegin(), drugList.crend(), [=](const Drug &drug){ _formular.insert(fin_target, drug); });
}

bool Formular::clearItem(const QModelIndex &index)
{
    int i = toListIndex(index);
    _formular[i].clear();
    return true;
}

void Formular::tidy()
{
    QList<Drug>::const_iterator it = std::remove(_formular.begin(), _formular.end(), Drug());
    _formular.erase(it, _formular.end());
    completeDrug();
}

Drug Formular::toDrug(const QString &str)
{
    if (str.isEmpty()) return Drug();
    else return str.split(" ");
}

void Formular::completeDrug()
{
    int remainder = _formular.count() % 4;
    int completions = (4-remainder) % 4;
    _formular.insert(_formular.size(), completions, Drug());
}
