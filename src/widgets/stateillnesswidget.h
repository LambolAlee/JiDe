#ifndef STATEILLNESSWIDGET_H
#define STATEILLNESSWIDGET_H

#include <QWidget>

namespace Ui {
class StateIllnessWidget;
}

class StateIllnessWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StateIllnessWidget(QWidget *parent = nullptr);
    ~StateIllnessWidget();

private:
    Ui::StateIllnessWidget *ui;
};

#endif // STATEILLNESSWIDGET_H
