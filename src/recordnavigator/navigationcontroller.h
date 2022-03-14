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
        Child,
        Parent,
    };
    NavigationController();

    QStandardItemModel *model() { return this; }
    void loadRecordsById(int id);

private:
    ClassifiedRecords _recordMap;

    void resetModel();

    const QList<QStandardItem *> getChildrenOf(const RecordInfoGroup &group);
};

#endif // NAVIGATIONCONTROLLER_H
