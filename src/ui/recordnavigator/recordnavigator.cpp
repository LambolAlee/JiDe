#include "recordnavigator.h"
#include "ui_recordnavigator.h"

RecordNavigator::RecordNavigator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordNavigator)
{
    ui->setupUi(this);
    ui->naviGridLayout->addWidget(&_view);
}

RecordNavigator::~RecordNavigator()
{
    delete ui;
}

void RecordNavigator::loadRecordsById(int id)
{
    _view.loadRecordsById(id);
}
