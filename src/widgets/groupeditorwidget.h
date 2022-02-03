#ifndef GROUPEDITORWIDGET_H
#define GROUPEDITORWIDGET_H

#include <QWidget>

namespace Ui {
class GroupEditorWidget;
}

class GroupEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GroupEditorWidget(QWidget *parent = nullptr);
    ~GroupEditorWidget();

private:
    Ui::GroupEditorWidget *ui;
};

#endif // GROUPEDITORWIDGET_H
