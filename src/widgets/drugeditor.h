#ifndef DRUGEDITOR_H
#define DRUGEDITOR_H

#include <QWidget>
#include <QEvent>

#include "data/formular.h"

namespace Ui {
class DrugEditor;
}

class DrugEditor : public QWidget
{
    Q_OBJECT

signals:
    void editNextPrevItem(QWidget* editor, bool next);

public:
    explicit DrugEditor(QWidget *parent = nullptr);
    ~DrugEditor();

    void setDrug(const Drug &);
    void setDrugName(const QString &);
    void setDrugWeight(const QString &, const QString &);
    void setDrugUsage(const QString &);
    void fitViewItemHeight(int);
    Drug submitDrug();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Ui::DrugEditor *ui;
    void setDropShadow();
    int _focusIndex = 0;
    QWidgetList _widgets;

    bool nextFocus();
    bool prevFocus();
    void focusAndSelectAllInLineEdit();
};

#endif // DRUGEDITOR_H
