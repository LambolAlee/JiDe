#ifndef FORMULAR_H
#define FORMULAR_H

#include <QList>
#include <QModelIndex>
#include <QPair>

using Drug = QList<QString>;

class Formular
{
public:
    explicit Formular();
    explicit Formular(const QString &);

    void set(const QString &);
    void set(const QList<Drug> &);
    void get();

    Drug getDrug(int index);
    Drug getDrug(int row, int column);
    Drug getDrug(const QModelIndex &);
    void setDrug(const QModelIndex &, const Drug &);
    void setDrug(QString);

    inline int toListIndex(int row, int column) { return 4*row + column; }
    inline int toListIndex(const QModelIndex &idx) { return toListIndex(idx.row(), idx.column()); }
    inline int toListIndex(QPair<int, int> pos) { return toListIndex(pos.first, pos.second); }
    int count();
    inline int formattedCount() const { return _formular.count(); }

    QPair<int, int> toRowCol(int i) const;

    bool insertRows(int row, int count);
    bool removeRows(int row, int count);
    bool clearItems(const QModelIndexList &indexs);
    void insertData(QPair<int, int> pos, const QList<Drug> &, const QList<QPair<int,int>> &posList);
    bool clearItem(const QModelIndex &);

    void tidy();

    static Drug toDrug(const QString &);
    inline static QString toString(const Drug &drug) { return drug.join(" "); }

private:
    QList<Drug> _formular;

    void completeDrug();
};

#endif // FORMULAR_H
