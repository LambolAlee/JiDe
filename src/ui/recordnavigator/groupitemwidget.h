#ifndef GROUPITEMWIDGET_H
#define GROUPITEMWIDGET_H

#include <QWidget>

#include "bean/record.h"

namespace Ui {
class GroupItemWidget;
}

class GroupItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GroupItemWidget(QWidget *parent = nullptr);
    GroupItemWidget(const RecordGroup &group, QWidget *parent = nullptr);
    ~GroupItemWidget();

private:
    Ui::GroupItemWidget *ui;
    RecordGroup _group;
};

#endif // GROUPITEMWIDGET_H
