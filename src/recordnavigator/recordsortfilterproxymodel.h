#ifndef RECORDSORTFILTERPROXYMODEL_H
#define RECORDSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class RecordSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit RecordSortFilterProxyModel(QObject *parent = nullptr);

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

#endif // RECORDSORTFILTERPROXYMODEL_H
