#include "navigationcontroller.h"


NavigationController::NavigationController() {}

void NavigationController::loadRecordsById(int id)
{
    _recordMap = RecordInfoDao::instance().findByPatientId(id);
    resetModel();
}

void NavigationController::resetModel()
{
    auto root = invisibleRootItem();
    for (auto &&group: _recordMap) {
        auto titles = group.title();
        auto *parentItem = new QStandardItem(titles.first);
        auto *recordNameItem = new QStandardItem(titles.second);
        if (group.size() > 1) {
            parentItem->setData(Parent, Qt::UserRole);
            parentItem->setData(QVariant::fromValue<RecordInfoGroup>(group), Qt::UserRole +1);
            arrangeChildrenOf(group, parentItem);
        } else {
            parentItem->setData(Child, Qt::UserRole);
            parentItem->setData(QVariant::fromValue<RecordInfo>(group.first()), Qt::UserRole +1);
        }
        root->appendRow({parentItem, recordNameItem});
    }
    emit dataUpdated();
}

void NavigationController::arrangeChildrenOf(const RecordInfoGroup &group, QStandardItem *parent)
{
    for (auto &&info: group) {
        auto titles = info.title();
        auto *timeItem = new QStandardItem(titles.first);
        auto *recordNameItem = new QStandardItem(titles.second);
        timeItem->setData(Child, Qt::UserRole);
        timeItem->setData(QVariant::fromValue<RecordInfo>(info), Qt::UserRole +1);
        parent->appendRow({timeItem, recordNameItem});
    }
}
