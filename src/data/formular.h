#ifndef FORMULAR_H
#define FORMULAR_H

#include <QList>
#include <QModelIndex>

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
    //QModelIndex toModelIndex(int i) const;

    inline int toListIndex(const QModelIndex &idx) { return 4*idx.row() + idx.column(); }
    inline int count() { return _formular.count(); }

private:
    QList<Drug> _formular;
};

#endif // FORMULAR_H
