#ifndef FORMULAR_H
#define FORMULAR_H

#include <QList>
#include <QModelIndex>
#include <QPair>

using Drug = QList<QString>;
using DrugLayout = QList<qint8>;

class Formular : private QList<Drug>
{
public:
    explicit Formular();
    explicit Formular(const QString &);

    void get();

    Drug getDrug(int index);
    Drug getDrug(int row, int column);
    Drug getDrug(const QModelIndex &);
    void setDrug(const QModelIndex &, const Drug &);
    void setDrug(QString);

    int toListIndex(int row, int column) { return columnCount*row + column; }
    int toListIndex(const QModelIndex &idx) { return toListIndex(idx.row(), idx.column()); }
    int toListIndex(QPair<int, int> pos) { return toListIndex(pos.first, pos.second); }
    int exactCount();
    int formattedCount() const { return count(); }

    QPair<int, int> toRowCol(int i) const;

    bool insertRows(int row, int count);
    bool removeRows(int row, int count);
    bool clearItems(const QModelIndexList &indexs);
    void insertData(QPair<int, int> pos, const QList<Drug> &, const QList<QPair<int,int>> &posList);
    bool clearItem(const QModelIndex &);

    void tidy();
    bool needTidy();

    static Drug toDrug(const QString &);
    static QString toString(const Drug &drug) { return drug.join(" "); }

    DrugLayout layout();
    void completeWithLayout(const DrugLayout &layout);

private:
    static const int columnCount = 4;
    void completeDrug();
    int completions();
};

#endif // FORMULAR_H
