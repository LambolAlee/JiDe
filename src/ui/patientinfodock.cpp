#include "patientinfodock.h"
#include "ui_patientinfodock.h"

PatientInfoDock::PatientInfoDock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientInfoDock)
{
    ui->setupUi(this);
}

PatientInfoDock::~PatientInfoDock()
{
    delete ui;
}

void PatientInfoDock::on_returnBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void PatientInfoDock::on_editButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

