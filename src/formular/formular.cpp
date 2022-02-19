#include "formular.h"

#include <QDebug>

Formular::Formular()
    : QList<Drug>()
{
}

Formular::Formular(const QString &formularStr)
    : QList<Drug>()
{
    QList<QString> formularList = formularStr.split("|");
    for (const QString &drugStr: formularList) {
        append(Formular::toDrug(drugStr));
    }
    completeDrug();
}

void Formular::get()
{
    qDebug() << this;
}

Drug Formular::getDrug(const QModelIndex &idx)
{
    int i = toListIndex(idx);
    return at(i);
}

void Formular::setDrug(const QModelIndex &idx, const Drug &drug)
{
    int i = toListIndex(idx);
    replace(i, drug);
}

int Formular::exactCount()
{
    return std::count_if(cbegin(), cend(), [](const Drug &drug){ return !drug.isEmpty(); });
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
    insert(startPos, 4*count, Drug());
    return true;
}

bool Formular::removeRows(int row, int count)
{
    int startPos = 4*row;
    remove(startPos, 4*count);
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

    std::for_each(drugList.cbegin(), drugList.cend(), [=](const Drug &drug){ removeOne(drug); });
    std::for_each(drugList.crbegin(), drugList.crend(), [=](const Drug &drug){ insert(fin_target, drug); });
}

bool Formular::clearItem(const QModelIndex &index)
{
    int i = toListIndex(index);
    replace(i, Drug());
    return true;
}

void Formular::tidy()
{
    QList<Drug>::const_iterator it = std::remove(begin(), end(), Drug());
    erase(it, end());
    completeDrug();
}

Drug Formular::toDrug(const QString &str)
{
    if (str.isEmpty()) return Drug();
    else return str.split(" ");
}

void Formular::completeDrug()
{
    int remainder = count() % 4;
    int completions = (4-remainder) % 4;
    insert(size(), completions, Drug());
}
