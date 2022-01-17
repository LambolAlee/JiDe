#include "formulartableform.h"
#include "ui_formulartableform.h"

#include "data/formular.h"
#include "drugeditor.h"
#include "data/drugdelegate.h"

FormularTableForm::FormularTableForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormularTableForm)
{
    ui->setupUi(this);
    ui->formularTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //QString f = "麻黄 15g 后下|桂枝 12g|杏仁 9g|甘草 9g";
    QString f = "熟大黄 45g|土鳖虫 45g|水蛭 45g 后下|虻虫 45g|蛴螬 45g|干漆 45g|桃仁 45g|苦杏仁 45g|黄芩 45g|地黄 45g|白芍 45g|甘草 45g";
    Formular *ff = new Formular(f);
    ff->get();
    _model = new FormularModel(ff, this);
    ui->formularTable->setModel(_model);
    DrugDelegate *d = new DrugDelegate(ui->formularTable);
    ui->formularTable->setItemDelegate(d);
}

FormularTableForm::~FormularTableForm()
{
    delete ui;
}
