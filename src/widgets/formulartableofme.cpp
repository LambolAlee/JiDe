#include "formulartableofme.h"
#include "drugeditor.h"
#include "data/drugdelegate.h"

FormularTableOfMe::FormularTableOfMe(QWidget *parent)
    : QTableView(parent)
{
}

void FormularTableOfMe::setItemDelegate(QAbstractItemDelegate *delegate)
{
    DrugDelegate *d = static_cast<DrugDelegate *>(delegate);
    connect(d, &DrugDelegate::startOrEndEdit, this, &FormularTableOfMe::setTabKeyNavigation);
    QTableView::setItemDelegate(delegate);
}
