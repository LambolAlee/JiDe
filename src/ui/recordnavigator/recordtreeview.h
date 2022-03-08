#ifndef RECORDTREEVIEW_H
#define RECORDTREEVIEW_H

#include <QTreeView>

#include "recordnavigator/navigationcontroller.h"


class RecordTreeView : public QTreeView
{
    Q_OBJECT
public:
    RecordTreeView(QWidget *parent = nullptr);

    void loadRecordsById(int id);

private:
    NavigationController _controller;

    void updateIndexWidget();
};

#endif // RECORDTREEVIEW_H
