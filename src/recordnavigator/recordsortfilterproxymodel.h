#ifndef RECORDSORTFILTERPROXYMODEL_H
#define RECORDSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class RecordSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    explicit RecordSortFilterProxyModel(QObject *parent = nullptr);
};

#endif // RECORDSORTFILTERPROXYMODEL_H
