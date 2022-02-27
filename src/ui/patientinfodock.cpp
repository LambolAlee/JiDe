#include "patientinfodock.h"
#include "ui_patientinfodock.h"

PatientInfoDock::PatientInfoDock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientInfoDock)
{
    ui->setupUi(this);
    ui->sexGroup->setId(ui->femaleRB, 0);
    ui->sexGroup->setId(ui->maleRB, 1);
    connect(ui->resetNameBtn, &QToolButton::clicked, this, [=]{ ui->nameLE->undo(); });
}

PatientInfoDock::~PatientInfoDock()
{
    delete ui;
}

void PatientInfoDock::setById(int id)
{
    _info.setById(id);
    updateUi();
}

void PatientInfoDock::updateUi()
{
    ui->nameLE->setText(_info.name());
    ui->sexGroup->button(_info.sex())->setChecked(true);
}

void PatientInfoDock::on_returnBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void PatientInfoDock::on_editButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void PatientInfoDock::on_nameLE_textEdited(const QString &arg1)
{
    qDebug() << arg1;
    if (arg1 == _info.name()) {
        ui->resetNameBtn->setEnabled(false);
    } else ui->resetNameBtn->setEnabled(true);
}
