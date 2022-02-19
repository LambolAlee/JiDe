#ifndef FORMULARTABLEOFME_H
#define FORMULARTABLEOFME_H

#include "drugeditor.h"
#include "formular/formularmodel.h"

#include <QTableView>
#include <QKeyEvent>
#include <QAbstractItemDelegate>
#include <QMenu>

class QAction;

class FormularTableOfMe : public QTableView
{
    Q_OBJECT

signals:
    void focusInEditor();
    void drugCountChanged(int count);

public:
    FormularTableOfMe(QWidget *parent = nullptr);
    void setMenu();

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

    void commit(const QModelIndex &);
    void closeEditor_();
    void commitAndCloseEditor(const QModelIndex &);

    void openEditor(const QModelIndex &idx, QRect rect);
    void editPrevItem(const QModelIndex &index);
    void editNextItem(const QModelIndex &index, bool insertion = false);

    void insertRow(int row) { if (row < 0) return; model()->insertRow(row); }

    int drugCount() {
        FormularModel *fmodel = static_cast<FormularModel *>(model());
        return fmodel->drugCount();
    }
};

#endif // FORMULARTABLEOFME_H
