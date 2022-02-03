#ifndef INFORECORDWIDGET_H
#define INFORECORDWIDGET_H

#include <QWidget>

namespace Ui {
class InfoRecordWidget;
}

class InfoRecordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InfoRecordWidget(QWidget *parent = nullptr);
    ~InfoRecordWidget();

private:
    Ui::InfoRecordWidget *ui;
};

#endif // INFORECORDWIDGET_H
