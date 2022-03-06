#include "recordtreeview.h"

RecordTreeView::RecordTreeView(QWidget *parent)
    : QTreeView(parent)
{
    setModel(_controller.model());
    setHeaderHidden(true);
}

void RecordTreeView::loadRecordsById(int id)
{
    _controller.loadRecordsById(id);
}
