#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H

#include <QStandardItemModel>

#include "dao/recorddao.h"


class NavigationController : public QStandardItemModel
{
signals:
    void dataUpdated();

public:
    NavigationController();

    QStandardItemModel *model() { return this; }
    void loadRecordsById(int id);

private:
    ClassifiedRecords _recordMap;

    void resetModel();

    const QList<QStandardItem *> getChildrenOf(const RecordGroup &group);
};

#endif // NAVIGATIONCONTROLLER_H
