#include "recordsortfilterproxymodel.h"
#include "bean/recordinfo.h"

RecordSortFilterProxyModel::RecordSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{

}

bool RecordSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    auto leftRole = sourceModel()->data(left, Qt::UserRole);
    auto rightRole = sourceModel()->data(right, Qt::UserRole);
    if (leftRole != rightRole) {
        return leftRole.toInt() < rightRole.toInt();
    }
    auto leftData = sourceModel()->data(left, Qt::UserRole +1);
    auto rightData = sourceModel()->data(right, Qt::UserRole +1);
    if (leftData.canConvert<RecordInfoGroup>()) {
        QDate l = leftData.value<RecordInfoGroup>().first().getClinicDate();
        QDate r = rightData.value<RecordInfoGroup>().first().getClinicDate();
        return l < r;
    } else {
        QDate l = leftData.value<RecordInfo>().getClinicDate();
        QDate r = rightData.value<RecordInfo>().getClinicDate();
        return l < r;
    }
}
