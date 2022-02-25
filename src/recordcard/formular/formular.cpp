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
    row = i / columnCount;
    column = i % columnCount;
    return QPair<int, int>(row, column);
}

bool Formular::insertRows(int row, int count)
{
    int startPos = columnCount*(row+1);
    insert(startPos, columnCount*count, Drug());
    return true;
}

bool Formular::removeRows(int row, int count)
{
    int startPos = columnCount*row;
    remove(startPos, columnCount*count);
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
    removeAll(Drug());
    completeDrug();
}

bool Formular::needTidy()
{
    int blank = count(Drug());
    if (blank < columnCount) return false;
    else return true;
}

Drug Formular::toDrug(const QString &str)
{
    if (str.isEmpty()) return Drug();
    else return str.split(" ");
}

void Formular::completeWithLayout(const DrugLayout &layout)
{
    for (int i=0; i < layout.size(); ++i) {
        if (layout.at(i)) continue;
        insert(i, Drug());
    }
}

DrugLayout Formular::layout()
{
    DrugLayout layout;
    for (auto &&drug: *this) {
        if (drug.isEmpty()) layout << 0;
        else layout << 1;
    }
    return layout.mid(0, layout.size()-completions()-2);
}

int Formular::completions()
{
    int remainder = count() % columnCount;
    int comp = (4-remainder) % columnCount;
    return comp;
}

void Formular::completeDrug()
{
    int comp = completions();
    insert(size(), comp, Drug());
}
