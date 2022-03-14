#include "navigationcontroller.h"


NavigationController::NavigationController()
{
}

void NavigationController::loadRecordsById(int id)
{
    _recordMap = RecordInfoDao::instance().findByPatientId(id);
    resetModel();
}

void NavigationController::resetModel()
{
    beginResetModel();
    auto root = invisibleRootItem();
    for (auto &&group: _recordMap) {
        auto *parentItem = new QStandardItem(group.first().getDisplayName());
        if (group.size() > 1) {
            parentItem->setData(Parent, Qt::UserRole);
            parentItem->setData(QVariant::fromValue<RecordInfoGroup>(group), Qt::UserRole +1);
            parentItem->appendRows(getChildrenOf(group));
        } else {
            parentItem->setData(Child, Qt::UserRole);
            parentItem->setData(QVariant::fromValue<RecordInfo>(group.first()), Qt::UserRole +1);
        }
        root->appendRow(parentItem);
    }
    endResetModel();
    emit dataUpdated();
}

const QList<QStandardItem *> NavigationController::getChildrenOf(const RecordInfoGroup &group)
{
    QList<QStandardItem *> children;
    std::for_each(group.begin(), group.end(), [&children](const RecordInfo &info){
        auto *item = new QStandardItem(info.getDisplayName());
        item->setData(Child, Qt::UserRole);
        item->setData(QVariant::fromValue<RecordInfo>(info), Qt::UserRole +1);
        children << item;
    });
    return children;
}
