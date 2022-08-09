#include "patientinfodock.h"
#include "ui_patientinfodock.h"

#include "dao/patientdao.h"

#include <QHBoxLayout>
#include <QPushButton>


PatientInfoDock::PatientInfoDock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientInfoDock)
{
    ui->setupUi(this);
    ui->sexGroup->setId(ui->femaleRB, 0);
    ui->sexGroup->setId(ui->maleRB, 1);
    for (auto &v: PatientConst::Ethnicity)
        ui->ethnicCB->addItem(v, PatientConst::Ethnicity.key(v));
    ui->ethnicCB->model()->sort(0);
    ui->stackedWidget->setCurrentIndex(0);
    createEditButtons();
    connectSignalsWithSlots();
}

PatientInfoDock::~PatientInfoDock()
{
    delete ui;
}

void PatientInfoDock::connectSignalsWithSlots()
{
    connect(ui->resetNameBtn, &QToolButton::clicked, this, [=]{reset(ui->nameLE, "patient_name");});
    connect(ui->resetCareerBtn, &QToolButton::clicked, this, [=]{reset(ui->careerLE, "career");});
    connect(ui->resetNpBtn, &QToolButton::clicked, this, [=]{reset(ui->nativePlaceLE, "native_place");});
    connect(ui->resetBpBtn, &QToolButton::clicked, this, [=]{reset(ui->birthPlaceLE, "birth_place");});

    connect(ui->nameLE, &QLineEdit::textChanged, this, [=](const QString &text){triggerUndoButton(ui->resetNameBtn, "patient_name", text);});
    connect(ui->careerLE, &QLineEdit::textChanged, this, [=](const QString &text){triggerUndoButton(ui->resetCareerBtn, "career", text);});
    connect(ui->nativePlaceLE, &QLineEdit::textChanged, this, [=](const QString &text){triggerUndoButton(ui->resetNpBtn, "native_place", text);});
    connect(ui->birthPlaceLE, &QLineEdit::textChanged, this, [=](const QString &text){triggerUndoButton(ui->resetBpBtn, "birth_place", text);});

    connect(ui->sexGroup, &QButtonGroup::idToggled, this, &PatientInfoDock::triggerUndoButtonForSex);
    connect(ui->ethnicCB, &QComboBox::currentIndexChanged, this, &PatientInfoDock::triggerUndoButtonForEthnicity);

    connect(_editButton, &QPushButton::clicked, this, &PatientInfoDock::editButton_clicked);

    connect(_saveButton, &QPushButton::clicked, this, &PatientInfoDock::saveChanges);
    connect(_discardButton, &QPushButton::clicked, this, &PatientInfoDock::discardChanges);
}

void PatientInfoDock::createEditButtons()
{
    _editButton = new QPushButton("edit", this);
    _editButton->setFixedWidth(50);
    ui->showPageGridLayout->addWidget(_editButton, 0,0 , Qt::AlignRight);

    _discardButton = new QPushButton("discard", this);
    _discardButton->setFixedWidth(50);
    ui->editPageGridLayout->addWidget(_discardButton, 0,0 , Qt::AlignLeft);

    _saveButton = new QPushButton("save", this);
    _saveButton->setFixedWidth(50);
    ui->editPageGridLayout->addWidget(_saveButton, 0,0 , Qt::AlignRight);
}

void PatientInfoDock::saveChanges()
{
    if (_patient->isEmpty()) return;
    PatientDao::instance().update(_patient);
    for (auto &&btn: ui->allToolButtons->buttons()) {
        btn->setEnabled(false);
    }
    backToShow();
}

void PatientInfoDock::discardChanges()
{
    backToShow();
    if (_patient->isEmpty()) return;
}

void PatientInfoDock::setById(int id)
{
    _patient = PatientDao::instance().findByPatientId(id);
    updateShowArea();
}

void PatientInfoDock::updateEditArea()
{
    ui->nameLE->setText(_patient->getPatientName());
    ui->sexGroup->button(_patient->getSex())->setChecked(true);
    ui->ethnicCB->setCurrentText(PatientConst::toString(PatientConst::ToEthnicity, _patient->getEthnicity()));
    ui->careerLE->setText(_patient->getCareer());
    ui->birthPlaceLE->setText(_patient->getBirthPlace());
    ui->nativePlaceLE->setText(_patient->getNativePlace());
}

void PatientInfoDock::updateShowArea()
{
    ui->nameLabel->setText(_patient->getPatientName());
    ui->sexLabel->setText(PatientConst::toString(PatientConst::ToSex, _patient->getSex()));
    ui->ethnicLabel->setText(PatientConst::toString(PatientConst::ToEthnicity, _patient->getEthnicity()));
    ui->careerLabel->setText(_patient->getCareer());
    ui->birthPlaceLabel->setText(_patient->getBirthPlace());
    ui->nativePlaceLabel->setText(_patient->getNativePlace());
}

void PatientInfoDock::backToShow()
{
    ui->stackedWidget->setCurrentIndex(0);
    updateShowArea();
}

void PatientInfoDock::editButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    updateEditArea();
}

void PatientInfoDock::triggerUndoButton(QToolButton *toolBtn, const char *propertyName, const QVariant &value) {
    if (value == _patient->property(propertyName)) {
        toolBtn->setEnabled(false);
        _patient->remove(propertyName);
    } else {
        toolBtn->setEnabled(true);
        _patient->insert(propertyName, value);
    }
}

void PatientInfoDock::triggerUndoButtonForSex(int id, bool bl)
{
    if (!bl) return;
    triggerUndoButton(ui->resetSexBtn, "sex", id);
}

void PatientInfoDock::triggerUndoButtonForEthnicity(int index)
{
    int currentIndex = ui->ethnicCB->itemData(index).toInt();
    triggerUndoButton(ui->resetEthnicBtn, "ethnicity", currentIndex);
}

void PatientInfoDock::reset(QLineEdit *lineEdit, const char *propertyName)
{
    lineEdit->setText(_patient->property(propertyName).toString());
}

void PatientInfoDock::on_resetSexBtn_clicked()
{
    ui->sexGroup->button(_patient->getSex())->setChecked(true);
}

void PatientInfoDock::on_resetEthnicBtn_clicked()
{
    ui->ethnicCB->setCurrentText(PatientConst::toString(PatientConst::ToEthnicity, _patient->getEthnicity()));
}

QSize PatientInfoDock::sizeHint() const
{
    return QSize(260, 0);
}
