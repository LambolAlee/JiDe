#include "patientinfodock.h"
#include "ui_patientinfodock.h"

#include <QHBoxLayout>

PatientInfoDock::PatientInfoDock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientInfoDock)
{
    ui->setupUi(this);
    ui->sexGroup->setId(ui->femaleRB, 0);
    ui->sexGroup->setId(ui->maleRB, 1);
    for (auto &&k: PatientConst::Ethnicity.keys()) {
        ui->ethnicCB->addItem(PatientConst::Ethnicity.value(k), k);
    }
    ui->ethnicCB->model()->sort(0);
    createNavigateBar();
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

    connect(ui->sexGroup, &QButtonGroup::idToggled, this, &PatientInfoDock::triggerUndoButtonForButtonGroup);
    connect(ui->ethnicCB, &QComboBox::currentTextChanged, this, [=](const QString &text){triggerUndoButton(ui->resetEthnicBtn, "ethnicity", text);});

    connect(_returnButton, &QPushButton::clicked, this, &PatientInfoDock::returnButton_clicked);
    connect(_editButton, &QPushButton::clicked, this, &PatientInfoDock::editButton_clicked);
}

void PatientInfoDock::createNavigateBar()
{
    _editButton = new QPushButton("edit", this);
    _editButton->setFixedWidth(50);
    ui->showPageGridLayout->addWidget(_editButton, 0,1 , Qt::AlignRight);

    _returnButton = new QPushButton("return", this);
    _returnButton->setFixedWidth(50);
    ui->editPageLayout->addWidget(_returnButton, 0,0 , Qt::AlignLeft);
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

void PatientInfoDock::returnButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    updateShowArea();
}

void PatientInfoDock::editButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    updateEditArea();
}

void PatientInfoDock::triggerUndoButton(QToolButton *toolBtn, const char *propertyName, const QString &changedText)
{
    QString comp;
    if (propertyName == QStringLiteral("ethnicity")) {
        comp = PatientConst::toString(PatientConst::ToEthnicity, _patient->property(propertyName).toInt());
    } else {
        comp = _patient->property(propertyName).toString();
    }
    if (changedText == comp) {
        toolBtn->setEnabled(false);
    } else {
        toolBtn->setEnabled(true);
    }
}

void PatientInfoDock::triggerUndoButtonForButtonGroup(int id, bool bl)
{
    if (!bl) return;
    if (id == _patient->property("sex")) {
        ui->resetSexBtn->setEnabled(false);
    } else {
        ui->resetSexBtn->setEnabled(true);
    }
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
    return QSize(260, 400);
}
