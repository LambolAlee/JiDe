#include "formulartableview.h"

#include "../command/basiccommand.h"

#include <QCursor>
#include <QHeaderView>
#include <QMenu>
#include <QKeyEvent>


FormularTableView::FormularTableView(QWidget *parent)
    : QTableView(parent)
{
    connect(this, &FormularTableView::doubleClicked, this, &FormularTableView::editItem);
    connect(this, &FormularTableView::focusInEditor, &_editor, &DrugEditor::focusInEditor);
    connect(&_editor, &DrugEditor::editNextWithInsertion, this, [=]{
        finish(_editingIndex, QAbstractItemDelegate::EditNextItem, true);
    });
    connect(&_editor, &DrugEditor::editNextPrevItem, this, [=](QAbstractItemDelegate::EndEditHint hint){
        finish(_editingIndex, hint);
    });
}

void FormularTableView::setMenu()
{
    QList<QAction *> acs = actions();
    _menu = new QMenu(this);
    _menu->addActions(acs);
    _addRow = acs.at(0);
    _deleteItems = acs.at(1);
    _deleteRows = acs.at(2);
}

void FormularTableView::setModel(QAbstractItemModel *model)
{
    _fmodel = static_cast<FormularModel *>(model);
    _fmodel->setView(this);
    return QTableView::setModel(model);
}

void FormularTableView::keyPressEvent(QKeyEvent *event)
{
    auto key = event->key();
    if (key == Qt::Key_F2) {
        emit doubleClicked(currentIndex());
    } else if (key == Qt::Key_Backspace || key == Qt::Key_Delete) {
        deleteItems();
    }
    return QTableView::keyPressEvent(event);
}

void FormularTableView::contextMenuEvent(QContextMenuEvent *event)
{
    QModelIndexList ilist = selectedIndexes();
    if (ilist.isEmpty()) {
        _addRow->setDisabled(true);
        _deleteItems->setDisabled(true);
        _deleteRows->setDisabled(true);
    }
    if (ilist.count() == 1) {
        _addRow->setEnabled(true);
        _deleteItems->setEnabled(true);
        _deleteRows->setEnabled(true);
    }
    _menu->exec(event->globalPos());
}

void FormularTableView::currentChanged(const QModelIndex &idxNow, const QModelIndex &idxPrev)
{
    if (_state == FormularTableView::EditingState && idxNow != _editingIndex) {
        _state = FormularTableView::NoState;
        commit(_editingIndex);
    }
    return QTableView::currentChanged(idxNow, idxPrev);
}

void FormularTableView::updateDrugCount()
{
    emit drugCountChanged(_fmodel->drugCount());
}

void FormularTableView::deleteItems()
{
    auto *cmd = new DeleteDrug(_fmodel, selectedIndexes());
    emit operateWith(cmd);
}

void FormularTableView::deleteRows()
{
    auto *cmd = new DeleteRows(_fmodel, selectedIndexes());
    emit operateWith(cmd);
}

void FormularTableView::tidy()
{
    auto *cmd = new TidyCommand(_fmodel);
    emit operateWith(cmd);
}

void FormularTableView::editPrevItem(const QModelIndex &index)
{
    int column = index.column();
    if (column -1 < 0) column = _fmodel->columnCount()-1; else --column;
    int row = index.row();
    if (column == _fmodel->columnCount()-1) { // column == columnCount-1 means it has reached the beginning of the current row
        if (row == 0) row = model()->rowCount()-1;
        else --row;
    }
    QModelIndex idx = index.sibling(row, column);
    setCurrentIndex(idx);
    editItem(idx);
}

void FormularTableView::editNextItem(const QModelIndex &index, bool insertion)
{
    int rowCount = _fmodel->rowCount();
    int columnCount = _fmodel->columnCount();
    int column = (index.column() + 1) % columnCount;

    int row = index.row();
    if (!column) { // column == 0 means it has reached the end of the current row
        if (row == rowCount-1) {
            if (insertion) { insertRow(row); row = rowCount; }
            else row = 0;
        } else ++row;
    }
    QModelIndex idx = _fmodel->index(row, column);
    setCurrentIndex(idx);
    editItem(idx);
}

void FormularTableView::insertRow(int row)
{
    auto *cmd = new AddNewRow(_fmodel, row);
    emit operateWith(cmd);
}

void FormularTableView::finish(const QModelIndex &index, QAbstractItemDelegate::EndEditHint hint, bool insertion)
{
    switch (hint) {
    case QAbstractItemDelegate::EditNextItem: {
        commitAndCloseEditor(index);
        editNextItem(index, insertion);
        break;
    }
    case QAbstractItemDelegate::EditPreviousItem: {
        commitAndCloseEditor(index);
        editPrevItem(index);
        break;
    }
    case QAbstractItemDelegate::NoHint:
        closeEditor_();
        break;
    default:
        break;
    }
    emit drugCountChanged(_fmodel->drugCount());
}

// =====================================Editor related code here========================================== //
void FormularTableView::openEditor(const QModelIndex &idx, QRect rect)
{
    _editor.fitViewItemHeight(rect.height());
    _editor.setFixedWidth(rect.width());
    _editor.move(mapToGlobal(QPoint(rect.x() + verticalHeader()->width(), rect.y())));
    _editor.setDrug(idx.model()->data(idx, Qt::EditRole).value<Drug>());
    _editor.show();
    _editor.activateWindow(); // use this to enable chinese imput on windows which have windowflag Qt::Popup
}

void FormularTableView::editItem(const QModelIndex &idx)
{
    QRect rect = visualRect(idx);
    _state = FormularTableView::EditingState;
    _editingIndex = idx;
    openEditor(idx, rect);

    emit focusInEditor();
}

void FormularTableView::commit(const QModelIndex &index)
{
    Drug old = index.data(Qt::EditRole).value<Drug>();
    auto *cmd = new UpdateDrug(_fmodel, index, _editor.submitDrug(), old);
    emit operateWith(cmd);
}

void FormularTableView::closeEditor_()
{
    _state = FormularTableView::NoState;
    _editor.close();
}

void FormularTableView::commitAndCloseEditor(const QModelIndex &index)
{
    commit(index);
    closeEditor_();
}
