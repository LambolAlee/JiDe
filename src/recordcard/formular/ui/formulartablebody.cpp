#include "formulartablebody.h"
#include "ui_formulartablebody.h"

#include "drugeditor.h"

#include <QPushButton>

FormularTableBody::FormularTableBody(QWidget *parent) :
    RecordCardBody(parent),
    ui(new Ui::FormularTableBody)
{
    ui->setupUi(this);
    ui->formularTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    initModel();
    initActions();

    ui->drugCountLabel->setText(QString::number(_model->drugCount()));
    connect(ui->addNewRowButton, &QToolButton::clicked, ui->actionAddRow, &QAction::triggered);
    connect(ui->deleteItemButton, &QToolButton::clicked, ui->actionDeleteItems, &QAction::triggered);
    connect(ui->deleteRowButton, &QToolButton::clicked, ui->actionDeleteRows, &QAction::triggered);
    connect(ui->tidyButton, &QToolButton::clicked, ui->actionTidy, &QAction::triggered);
}

FormularTableBody::~FormularTableBody()
{
    delete ui;
}

void FormularTableBody::initModel()
{
    QString f = "熟大黄 45g|土鳖虫 45g|水蛭 45g 后下|虻虫 45g|蛴螬 45g|干漆 45g|桃仁 45g|苦杏仁 45g|黄芩 45g|地黄 45g"/*|白芍 45g|甘草 45g"*/;
    Formular *ff = new Formular(f);
    _model = new FormularModel(ff, this);
    ui->formularTable->setModel(_model);
    connect(ui->formularTable, &FormularTableView::drugCountChanged, this, [=](int count){ ui->drugCountLabel->setText(QString::number(count)); });
    connect(ui->formularTable, &FormularTableView::operateWith, undoStack(), &QUndoStack::push);
}

void FormularTableBody::initActions()
{
    QList<QAction *> actions;
    actions.append(ui->actionAddRow);
    actions.append(ui->actionDeleteItems);
    actions.append(ui->actionDeleteRows);
    actions.append(ui->actionTidy);
    ui->formularTable->addActions(actions);

    connect(ui->actionAddRow, &QAction::triggered, ui->formularTable, qOverload<>(&FormularTableView::insertRow));
    connect(ui->actionDeleteItems, &QAction::triggered, ui->formularTable, &FormularTableView::deleteItems);
    connect(ui->actionDeleteRows, &QAction::triggered, ui->formularTable, &FormularTableView::deleteRows);
    connect(ui->actionTidy, &QAction::triggered, ui->formularTable, &FormularTableView::tidy);
    ui->formularTable->setMenu();
}
