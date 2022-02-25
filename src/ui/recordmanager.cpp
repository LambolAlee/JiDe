#include "recordmanager.h"
#include "ui_recordmanager.h"

#include "recordcard/formular/ui/formulartablecard.h"
#include "patientinfodock.h"


RecordManager::RecordManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RecordManager)
{
    ui->setupUi(this);
    FormularTableCard *form = new FormularTableCard(this);
    setCentralWidget(form);
    ui->patientDock->setWidget(new PatientInfoDock(this));
}

RecordManager::~RecordManager()
{
    delete ui;
}

QMenuBar *RecordManager::menuBar()
{
    return ui->menuBar;
}
