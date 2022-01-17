#ifndef FORMULARTABLEOFME_H
#define FORMULARTABLEOFME_H

#include <QTableView>
#include <QKeyEvent>

class FormularTableOfMe : public QTableView
{
    Q_OBJECT
public:
    FormularTableOfMe(QWidget *parent = nullptr);

    void setItemDelegate(QAbstractItemDelegate *delegate);
};

#endif // FORMULARTABLEOFME_H
