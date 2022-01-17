#ifndef DRUGDELEGATE_H
#define DRUGDELEGATE_H

#include <QStyledItemDelegate>

class DrugDelegate : public QStyledItemDelegate
{
    Q_OBJECT

signals:
    void startOrEndEdit(bool allowTabNavigation);

public:
    DrugDelegate(QObject *parent = nullptr);

protected:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

private:
    void moveNextPrevItemWithEditor(QWidget *editor, bool next);
    inline void startMoveEditor() { emit startOrEndEdit(false); }
    inline void endMoveEditor() { emit startOrEndEdit(true); }
};

#endif // DRUGDELEGATE_H
