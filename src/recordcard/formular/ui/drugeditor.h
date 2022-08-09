#ifndef DRUGEDITOR_H
#define DRUGEDITOR_H

#include <QWidget>
#include <QAbstractItemDelegate>

#include "../formular.h"


class QEvent;

namespace Ui {
class DrugEditor;
}

class DrugEditor : public QWidget
{
    Q_OBJECT

signals:
    void editNextPrevItem(QAbstractItemDelegate::EndEditHint);
    void editNextWithInsertion();

public:
    explicit DrugEditor(QWidget *parent = nullptr);
    ~DrugEditor();

    void setDrug(const Drug &);
    void fitViewItemHeight(int);
    Drug submitDrug();
    void focusInEditor();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Ui::DrugEditor *ui;
    void setDropShadow();

    void setDrugName(const QString &);
    void setDrugWeight(QString &&);
    void setDrugUsage(const QString &);
};

#endif // DRUGEDITOR_H
