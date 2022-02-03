#ifndef EXAMINEWIDGET_H
#define EXAMINEWIDGET_H

#include <QWidget>

namespace Ui {
class ExamineWidget;
}

class ExamineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExamineWidget(QWidget *parent = nullptr);
    ~ExamineWidget();

private:
    Ui::ExamineWidget *ui;
};

#endif // EXAMINEWIDGET_H
