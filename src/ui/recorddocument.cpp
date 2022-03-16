#include "recorddocument.h"
#include "ui_recorddocument.h"

#include "recordcard/recordcardframe.h"

RecordDocument::RecordDocument(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RecordDocument)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->listView->setModel(&_model);
    ui->listView->setSpacing(10);
    ui->listView->setAutoScroll(false);
}

RecordDocument::~RecordDocument()
{
    delete ui;
}

void RecordDocument::addCard(RecordCardFrame *frame)
{
    frame->setParent(this);
    QStandardItem *item = new QStandardItem;
    item->setSizeHint(frame->size());
    //item->setData(QVariant::fromValue<RecordCardFrame *>(frame));
    _model.appendRow(item);
    auto idx = _model.indexFromItem(item);
    ui->listView->setIndexWidget(idx, frame);
}

void RecordDocument::showEvent(QShowEvent *event)
{
    showMaximized();
    return QMainWindow::showEvent(event);
}

void RecordDocument::updateIndexWdiget()
{
    for (int row=0; row < _model.rowCount(); ++row) {
        auto idx = _model.index(row, 0);
        if (ui->listView->indexWidget(idx)) continue;
    }
}
