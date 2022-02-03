#include "diagnosiswidget.h"
#include "ui_diagnosiswidget.h"

DiagnosisWidget::DiagnosisWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiagnosisWidget)
{
    ui->setupUi(this);
}

DiagnosisWidget::~DiagnosisWidget()
{
    delete ui;
}
