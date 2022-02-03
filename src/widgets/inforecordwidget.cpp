#include "inforecordwidget.h"
#include "ui_inforecordwidget.h"

InfoRecordWidget::InfoRecordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoRecordWidget)
{
    ui->setupUi(this);
}

InfoRecordWidget::~InfoRecordWidget()
{
    delete ui;
}
