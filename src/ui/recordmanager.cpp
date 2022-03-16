#include "recordmanager.h"
#include "ui_recordmanager.h"

#include "recordcard/formular/ui/formulartablecard.h"
#include "patientinfodock.h"
#include "recordnavigator/recordnavigator.h"
#include "recordeditorarea.h"
#include "recorddocument.h"

RecordManager::RecordManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RecordManager)
{
    ui->setupUi(this);
    // test to see the previewing   -- start
    auto *editor = new RecordEditorArea(this);
    auto *doc = new RecordDocument;
    FormularTableCard *form1 = new FormularTableCard;
    FormularTableCard *form2 = new FormularTableCard;
    doc->addCard(form1);
    doc->addCard(form2);
    editor->addSubWindow(doc, Qt::FramelessWindowHint);
    setCentralWidget(editor);
    // test to see the previewing   -- end

    auto *pinfo = new PatientInfoDock(this);
    pinfo->setById(1);
    ui->patientDock->setWidget(pinfo);

    auto *navi = new RecordNavigator(this);
    navi->loadRecordsById(1);
    ui->recordDock->setWidget(navi);
}

RecordManager::~RecordManager()
{
    delete ui;
}

QMenuBar *RecordManager::menuBar()
{
    return ui->menuBar;
}
