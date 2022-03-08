#include "recorditemwidget.h"
#include "ui_recorditemwidget.h"

RecordItemWidget::RecordItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordItemWidget)
{
    ui->setupUi(this);
}

RecordItemWidget::~RecordItemWidget()
{
    delete ui;
}
