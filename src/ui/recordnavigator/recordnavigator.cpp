#include "recordnavigator.h"
#include "ui_recordnavigator.h"

#include "recordnavigator/recordsortfilterproxymodel.h"


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
    //ui->treeView->header()->setSectionResizeMode(QHeaderView::Stretch);
    connect(&_controller, &NavigationController::dataUpdated, this, [=]{ ui->treeView->resizeColumnToContents(0); });
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
    if (index.parent().isValid())
        return;

    auto &&proxyIndex = index.siblingAtColumn(0);
    auto &&sourceIndex = _proxyModel->mapToSource(index);
    auto *item = _controller.item(sourceIndex.row());
    if (item->hasChildren()) {
        if (ui->treeView->isExpanded(proxyIndex)) ui->treeView->collapse(proxyIndex);
        else ui->treeView->expand(proxyIndex);
    }
}
