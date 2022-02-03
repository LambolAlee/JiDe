#ifndef DIAGNOSISWIDGET_H
#define DIAGNOSISWIDGET_H

#include <QWidget>

namespace Ui {
class DiagnosisWidget;
}

class DiagnosisWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DiagnosisWidget(QWidget *parent = nullptr);
    ~DiagnosisWidget();

private:
    Ui::DiagnosisWidget *ui;
};

#endif // DIAGNOSISWIDGET_H
