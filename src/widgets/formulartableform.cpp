#include "formulartableform.h"
#include "ui_formulartableform.h"

#include "formular/formular.h"
#include "drugeditor.h"

FormularTableForm::FormularTableForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormularTableForm)
{
    ui->setupUi(this);
    ui->formularTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    initModel();
    initActions();

    ui->drugCountLabel->setText(QString::number(_model->drugCount()));
    connect(ui->addNewRowButton, &QPushButton::clicked, ui->actionAddRow, &QAction::triggered);
    connect(ui->deleteItemButton, &QPushButton::clicked, ui->actionDeleteItems, &QAction::triggered);
    connect(ui->deleteRowButton, &QPushButton::clicked, ui->actionDeleteRows, &QAction::triggered);
    connect(ui->tidyButton, &QPushButton::clicked, ui->actionTidy, &QAction::triggered);
}

FormularTableForm::~FormularTableForm()
{
    delete ui;
}

void FormularTableForm::initModel()
{
    QString f = "熟大黄 45g|土鳖虫 45g|水蛭 45g 后下|虻虫 45g|蛴螬 45g|干漆 45g|桃仁 45g|苦杏仁 45g|黄芩 45g|地黄 45g"/*|白芍 45g|甘草 45g"*/;
    Formular *ff = new Formular(f);
    _model = new FormularModel(ff, this);
    ui->formularTable->setModel(_model);
    connect(ui->formularTable, &FormularTableOfMe::drugCountChanged, this, [=](int count){ ui->drugCountLabel->setText(QString::number(count)); });
}

void FormularTableForm::initActions()
{
    QList<QAction *> actions;
    actions.append(ui->actionAddRow);
    actions.append(ui->actionDeleteItems);
    actions.append(ui->actionDeleteRows);
    actions.append(ui->actionTidy);
    ui->formularTable->addActions(actions);

    connect(ui->actionAddRow, &QAction::triggered, ui->formularTable, qOverload<>(&FormularTableOfMe::insertRow));
    connect(ui->actionDeleteItems, &QAction::triggered, ui->formularTable, &FormularTableOfMe::deleteItems);
    connect(ui->actionDeleteRows, &QAction::triggered, ui->formularTable, &FormularTableOfMe::deleteRows);
    connect(ui->actionTidy, &QAction::triggered, ui->formularTable, &FormularTableOfMe::tidy);
    ui->formularTable->setMenu();
}

void FormularTableForm::on_exportButton_clicked()
{
    //ui->formularTable->test();
}
