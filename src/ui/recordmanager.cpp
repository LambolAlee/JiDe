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
    auto *pinfo = new PatientInfoDock(this);
    pinfo->setById(1);
    ui->patientDock->setWidget(pinfo);
}

RecordManager::~RecordManager()
{
    delete ui;
}

QMenuBar *RecordManager::menuBar()
{
    return ui->menuBar;
}
