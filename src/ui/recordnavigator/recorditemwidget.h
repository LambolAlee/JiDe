#ifndef RECORDITEMWIDGET_H
#define RECORDITEMWIDGET_H

#include <QWidget>

namespace Ui {
class RecordItemWidget;
}

class RecordItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RecordItemWidget(QWidget *parent = nullptr);
    ~RecordItemWidget();

private:
    Ui::RecordItemWidget *ui;
};

#endif // RECORDITEMWIDGET_H
