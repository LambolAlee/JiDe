#include "recordtreeview.h"

RecordTreeView::RecordTreeView(QWidget *parent)
    : QTreeView(parent)
{
    setModel(_controller.model());
    setHeaderHidden(true);
    setIndentation(0);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(&_controller, &NavigationController::dataUpdated, this, &RecordTreeView::updateIndexWidget);
}

void RecordTreeView::loadRecordsById(int id)
{
    _controller.loadRecordsById(id);
}

void RecordTreeView::updateIndexWidget()
{

}
