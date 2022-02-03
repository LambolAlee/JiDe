#ifndef BASICINFODOCKWIDGET_H
#define BASICINFODOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class BasicInfoDockWidget;
}

class BasicInfoDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit BasicInfoDockWidget(QWidget *parent = nullptr);
    ~BasicInfoDockWidget();

private:
    Ui::BasicInfoDockWidget *ui;
};

#endif // BASICINFODOCKWIDGET_H
