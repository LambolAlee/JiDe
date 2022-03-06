#include "navigationcontroller.h"


NavigationController::NavigationController()
{
}

void NavigationController::loadRecordsById(int id)
{
    _recordMap = RecordDao::instance().findByPatientId(id);
    resetModel();
}

void NavigationController::resetModel()
{
    beginResetModel();
    int i = 100;
    auto root = invisibleRootItem();
    for (auto &group: _recordMap) {
        QString text;
        auto *parentItem = new QStandardItem;

        if (group.size() == 1) {
            text = QString::number(group.constFirst().getId());
        }
        else {
            text = QString::number(i++);
            parentItem->appendRows(getChildrenOf(group));
        }
        parentItem->setText(text);
        root->appendRow(parentItem);
    }
    endResetModel();
}

const QList<QStandardItem *> NavigationController::getChildrenOf(const RecordGroup &group)
{
    QList<QStandardItem *> children;
    std::for_each(group.begin(), group.end(), [&children](const Record &record){
        auto *item = new QStandardItem(QString::number(record.getId()));
        item->setData(record);
        children << item;
    });
    return children;
}
