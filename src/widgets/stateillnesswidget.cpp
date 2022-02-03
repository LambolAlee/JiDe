#include "stateillnesswidget.h"
#include "ui_stateillnesswidget.h"

StateIllnessWidget::StateIllnessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StateIllnessWidget)
{
    ui->setupUi(this);
}

StateIllnessWidget::~StateIllnessWidget()
{
    delete ui;
}
