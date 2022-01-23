#ifndef FORMULARTABLEOFME_H
#define FORMULARTABLEOFME_H

#include "drugeditor.h"
#include "data/formularmodel.h"

#include <QTableView>
#include <QKeyEvent>
#include <QAbstractItemDelegate>
#include <QMenu>
#include <QAction>

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

public slots:
    inline void insertRow() { insertRow(currentIndex().row()); }
    void deleteItems();
    void deleteRows();
    void tidy();

private slots:
    void finish(const QModelIndex &, QAbstractItemDelegate::EndEditHint hint = QAbstractItemDelegate::NoHint, bool insertion = false);
    void editItem(const QModelIndex &);

private:
    DrugEditor *_editor;
    QModelIndex _editingIndex;
    QTableView::State _state;
    QMenu *_menu;
    QAction *_addRow, *_deleteItems, *_deleteRows;

    void commit(const QModelIndex &);
    void safeCloseEditor(const QModelIndex &);
    void commitAndCloseEditor(const QModelIndex &);

    void cancelEdit(const QModelIndex &);
    inline void startCloseEditor() { setTabKeyNavigation(false); }
    inline void endCloseEditor() { setTabKeyNavigation(true); }
    void initEditor(const QModelIndex &idx, QRect rect);
    void editPrevItem(const QModelIndex &index);
    void editNextItem(const QModelIndex &index, bool insertion = false);

    inline void insertRow(int row) { if (row < 0) return; model()->insertRow(row); }

    inline int drugCount() {
        FormularModel *fmodel = static_cast<FormularModel *>(model());
        return fmodel->drugCount();
    }
};

#endif // FORMULARTABLEOFME_H
