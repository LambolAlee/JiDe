#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H

#include <QStandardItemModel>

#include "dao/recordinfodao.h"


class NavigationController : public QStandardItemModel
{
    Q_OBJECT

signals:
    void dataUpdated();

public:
    enum ItemType {
        Parent,
        Child,
    };
    NavigationController();

    QStandardItemModel *model() { return this; }
    void loadRecordsById(int id);

private:
    ClassifiedRecords _recordMap;

    void resetModel();

    void arrangeChildrenOf(const RecordInfoGroup &group, QStandardItem *parent);
};

#endif // NAVIGATIONCONTROLLER_H
