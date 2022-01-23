#include "formulartableofme.h"
#include "drugeditor.h"


#include <QCursor>


FormularTableOfMe::FormularTableOfMe(QWidget *parent)
    : QTableView(parent)
{
    connect(this, &FormularTableOfMe::doubleClicked, this, &FormularTableOfMe::editItem); // enter and dblclick work -> edit
    connect(this, &FormularTableOfMe::clicked, this, &FormularTableOfMe::cancelEdit);
}

void FormularTableOfMe::setMenu()
{
    QList<QAction *> acs = actions();
    _menu = new QMenu(this);
    _menu->addActions(acs);
    _addRow = acs.at(0);
    _deleteItems = acs.at(1);
    _deleteRows = acs.at(2);
}

void FormularTableOfMe::keyPressEvent(QKeyEvent *event)
{
    auto key = event->key();
    if (key == Qt::Key_F2) {
        emit doubleClicked(currentIndex());
    } else if (key == Qt::Key_Escape && _state == FormularTableOfMe::EditingState) {
        finish(_editingIndex);
    } else if (key == Qt::Key_Backspace || key == Qt::Key_Delete) {
        deleteItems();
    }
    return QTableView::keyPressEvent(event);
}

void FormularTableOfMe::contextMenuEvent(QContextMenuEvent *event)
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

void FormularTableOfMe::deleteItems()
{
    FormularModel *fmodel = static_cast<FormularModel *>(model());
    fmodel->clearItems(selectedIndexes());
    qDebug() << fmodel->drugCount();
    emit drugCountChanged(fmodel->drugCount());
}

void FormularTableOfMe::deleteRows()
{
    int previous = -1;
    auto sList = selectedIndexes();
    if (sList.isEmpty()) return;
    std::for_each(sList.crbegin(), sList.crend(), [&](const QModelIndex &index) {
        if (index.row() == previous) return;
        previous = index.row();
        model()->removeRow(previous);
    });
    emit drugCountChanged(drugCount());
}

void FormularTableOfMe::tidy()
{
    FormularModel *fmodel = static_cast<FormularModel *>(model());
    fmodel->tidy();
}

void FormularTableOfMe::cancelEdit(const QModelIndex &index)
{
    if (_state == FormularTableOfMe::EditingState && index != _editingIndex) {
        commitAndCloseEditor(_editingIndex);
    }
}

void FormularTableOfMe::editPrevItem(const QModelIndex &index)
{
    int column = index.column();
    int row = index.row();
    if (column == 0) {
        if (row == 0) row = model()->rowCount()-1;
        else row -= 1;
        column = 3;
    } else column -= 1;
    QModelIndex idx = index.sibling(row, column);
    setCurrentIndex(idx);
    editItem(idx);
}

void FormularTableOfMe::editNextItem(const QModelIndex &index, bool insertion)
{
    int arow, row, acolumn, column;
    arow = row = index.row(); acolumn = column = index.column();

    if (column == 3) {
        arow += 1;
        if (row == model()->rowCount()-1) {
            if (insertion) insertRow(row);
            else arow = 0;
        }
        acolumn = 0;
    } else acolumn += 1;
    QModelIndex idx = model()->index(arow, acolumn);
    setCurrentIndex(idx);
    editItem(idx);
}

void FormularTableOfMe::finish(const QModelIndex &index, QAbstractItemDelegate::EndEditHint hint, bool insertion)
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
        safeCloseEditor(index);
        break;
    default:
        break;
    }
    emit drugCountChanged(drugCount());
}

void FormularTableOfMe::initEditor(const QModelIndex &idx, QRect rect)
{
    _editor = new DrugEditor(this);
    int height = _editor->height();
    _editor->setGeometry(rect);
    _editor->fitViewItemHeight(rect.height());
    _editor->setFixedHeight(height);
    _editor->setDrug(idx.model()->data(idx, Qt::EditRole).value<Drug>());
    connect(_editor, &DrugEditor::editNextPrevItem, this, [=](QAbstractItemDelegate::EndEditHint hint){
        finish(_editingIndex, hint);
    });
    connect(_editor, &DrugEditor::editNextWithInsertion, this, [=]{
        finish(_editingIndex, QAbstractItemDelegate::EditNextItem, true);
    });
}

void FormularTableOfMe::editItem(const QModelIndex &idx)
{
    QRect rect = visualRect(idx);
    _state = FormularTableOfMe::EditingState;
    _editingIndex = idx;
    initEditor(idx, rect);

    setIndexWidget(idx, _editor);
    emit focusInEditor();
}

void FormularTableOfMe::commit(const QModelIndex &index)
{
    model()->setData(index, _editor->submitDrug());
}

void FormularTableOfMe::safeCloseEditor(const QModelIndex &index)
{
    startCloseEditor();
    _state = FormularTableOfMe::NoState;
    setIndexWidget(index, nullptr);
    _editor->close();
    _editor->deleteLater();
    _editor = nullptr;
    endCloseEditor();
}

void FormularTableOfMe::commitAndCloseEditor(const QModelIndex &index)
{
    commit(index);
    safeCloseEditor(index);
}
