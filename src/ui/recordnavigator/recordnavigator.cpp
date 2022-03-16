#include "recordnavigator.h"
#include "ui_recordnavigator.h"

RecordNavigator::RecordNavigator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordNavigator),
    _proxyModel(new RecordSortFilterProxyModel)
{
    ui->setupUi(this);
    _proxyModel->setSourceModel(_controller.model());
    _proxyModel->sort(0);
    ui->treeView->setModel(_proxyModel);
    ui->treeView->setHeaderHidden(true);
    connect(ui->treeView, &QTreeView::clicked, this, &RecordNavigator::clickToExpand);
}

RecordNavigator::~RecordNavigator()
{
    delete ui;
    delete _proxyModel;
}

void RecordNavigator::loadRecordsById(int id)
{
    _controller.loadRecordsById(id);
}

void RecordNavigator::clickToExpand(const QModelIndex &index)
{
    auto *item = _controller.itemFromIndex(_proxyModel->mapToSource(index));
    if (item->hasChildren()) {
        if (ui->treeView->isExpanded(index)) ui->treeView->collapse(index);
        else ui->treeView->expand(index);
    }
}
