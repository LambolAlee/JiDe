#include "patientinfodock.h"
#include "ui_patientinfodock.h"

PatientInfoDock::PatientInfoDock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientInfoDock)
{
    ui->setupUi(this);
    ui->sexGroup->setId(ui->femaleRB, 0);
    ui->sexGroup->setId(ui->maleRB, 1);
    for (auto &&k: PatientConst::Ethnicity.keys())
        ui->ethnicCB->addItem(PatientConst::Ethnicity.value(k), k);
    ui->ethnicCB->model()->sort(0);
    connect(ui->resetNameBtn, &QToolButton::clicked, ui->nameLE, &QLineEdit::undo);
    connect(ui->resetCareerBtn, &QToolButton::clicked, ui->careerLE, &QLineEdit::undo);
    //qDebug() << findChildren<QToolButton*>();
}

PatientInfoDock::~PatientInfoDock()
{
    delete ui;
}

void PatientInfoDock::setById(int id)
{
    _info.setById(id);
    updateShowArea();
}

void PatientInfoDock::updateEditArea()
{
    ui->nameLE->setText(_info.name());
    ui->sexGroup->button(_info.sex())->setChecked(true);
    ui->ethnicCB->setCurrentText(PatientConst::toString(PatientConst::ToEthnicity, _info.ethnicity()));
    ui->careerLE->setText(_info.career());
    ui->birthPlaceLE->setText(_info.birthPlace());
    ui->nativePlaceLE->setText(_info.nativePlace());
}

void PatientInfoDock::updateShowArea()
{
    ui->nameLabel->setText(_info.name());
    ui->sexLabel->setText(PatientConst::toString(PatientConst::ToSex, _info.sex()));
    ui->ethnicLabel->setText(PatientConst::toString(PatientConst::ToEthnicity, _info.ethnicity()));
    ui->careerLabel->setText(_info.career());
    ui->birthPlaceLabel->setText(_info.birthPlace());
    ui->nativePlaceLabel->setText(_info.nativePlace());
}

void PatientInfoDock::on_returnBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    updateShowArea();
}

void PatientInfoDock::on_editButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    updateEditArea();
}

void PatientInfoDock::on_nameLE_textEdited(const QString &changedText)
{
    if (changedText == _info.name()) {
        ui->resetNameBtn->setEnabled(false);
    } else ui->resetNameBtn->setEnabled(true);
}
