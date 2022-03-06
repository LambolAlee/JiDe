#ifndef RECORDNAVIGATOR_H
#define RECORDNAVIGATOR_H

#include <QWidget>

#include "recordtreeview.h"


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
    RecordTreeView _view;
};

#endif // RECORDNAVIGATOR_H
