#include "drugdelegate.h"
#include "widgets/drugeditor.h"

DrugDelegate::DrugDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *DrugDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &,
                          const QModelIndex &) const
{
    DrugEditor *de = new DrugEditor(parent);
    connect(de, &DrugEditor::editNextPrevItem, this, &DrugDelegate::moveNextPrevItemWithEditor);
    return de;
}

void DrugDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    DrugEditor *de = static_cast<DrugEditor *>(editor);
    Drug d = index.model()->data(index, Qt::EditRole).value<Drug>();
    de->setDrug(d);
}

void DrugDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                  const QModelIndex &index) const
{
    DrugEditor *de = static_cast<DrugEditor *>(editor);
    Drug drug = de->submitDrug();
    model->setData(index, drug);
}

void DrugDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                          const QModelIndex &) const
{
    editor->setGeometry(option.rect);
    editor->setFixedHeight(60);
}

void DrugDelegate::moveNextPrevItemWithEditor(QWidget *editor, bool next)
{
    QAbstractItemDelegate::EndEditHint hint;
    hint = next ? QAbstractItemDelegate::EditNextItem : QAbstractItemDelegate::EditPreviousItem;
    emit commitData(editor);

    startMoveEditor();
    emit closeEditor(editor, hint);
    endMoveEditor();
}
