#include "basicinfodockwidget.h"
#include "ui_basicinfodockwidget.h"

BasicInfoDockWidget::BasicInfoDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::BasicInfoDockWidget)
{
    ui->setupUi(this);
}

BasicInfoDockWidget::~BasicInfoDockWidget()
{
    delete ui;
}
