#ifndef RECORDNAVIGATOR_H
#define RECORDNAVIGATOR_H

#include <QWidget>

#include "recordnavigator/navigationcontroller.h"


class RecordSortFilterProxyModel;

namespace Ui {
class RecordNavigator;
}

class RecordNavigator : public QWidget
{
    Q_OBJECT

public:
    explicit RecordNavigator(QWidget *parent = nullptr);
    ~RecordNavigator();

    void loadRecordsById(int id);

private:
    Ui::RecordNavigator *ui;
    NavigationController _controller;
    RecordSortFilterProxyModel *_proxyModel;

    void clickToExpand(const QModelIndex &index);
};

#endif // RECORDNAVIGATOR_H
