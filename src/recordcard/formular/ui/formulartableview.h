#ifndef FORMULARTABLEVIEW_H
#define FORMULARTABLEVIEW_H

#include "drugeditor.h"

#include <QTableView>
#include <QAbstractItemDelegate>

class QUndoCommand;
class FormularModel;


class FormularTableView : public QTableView
{
    Q_OBJECT

signals:
    void focusInEditor();
    void drugCountChanged(int count);
    void operateWith(QUndoCommand *cmd);

public:
    FormularTableView(QWidget *parent = nullptr);
    void setMenu();
    void setModel(QAbstractItemModel *model) override;
    FormularModel *model() { return _fmodel; }

    void updateDrugCount();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
    void currentChanged(const QModelIndex &idxNow, const QModelIndex &) override;

public slots:
    void insertRow() { insertRow(currentIndex().row()); }
    void deleteItems();
    void deleteRows();
    void tidy();

private slots:
    void finish(const QModelIndex &, QAbstractItemDelegate::EndEditHint hint = QAbstractItemDelegate::NoHint, bool insertion = false);
    void editItem(const QModelIndex &);

private:
    DrugEditor _editor;
    QModelIndex _editingIndex;
    QTableView::State _state;
    QMenu *_menu;
    QAction *_addRow, *_deleteItems, *_deleteRows;
    FormularModel *_fmodel;

    void commit(const QModelIndex &);
    void closeEditor_();
    void commitAndCloseEditor(const QModelIndex &);

    void openEditor(const QModelIndex &idx, QRect rect);
    void editPrevItem(const QModelIndex &index);
    void editNextItem(const QModelIndex &index, bool insertion = false);

    void insertRow(int row);
};

#endif // FORMULARTABLEVIEW_H
