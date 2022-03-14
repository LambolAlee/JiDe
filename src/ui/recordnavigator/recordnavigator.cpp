#include "recordnavigator.h"
#include "ui_recordnavigator.h"

RecordNavigator::RecordNavigator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordNavigator)
{
    ui->setupUi(this);
    ui->treeView->setModel(_controller.model());
    ui->treeView->setHeaderHidden(true);
    connect(ui->treeView, &QTreeView::clicked, this, &RecordNavigator::clickToExpand);
}

RecordNavigator::~RecordNavigator()
{
    delete ui;
}

void RecordNavigator::loadRecordsById(int id)
{
    _controller.loadRecordsById(id);
}

void RecordNavigator::clickToExpand(const QModelIndex &index)
{
    auto *item = _controller.itemFromIndex(index);
    if (item->hasChildren()) {
        if (ui->treeView->isExpanded(index)) ui->treeView->collapse(index);
        else ui->treeView->expand(index);
    }
}
