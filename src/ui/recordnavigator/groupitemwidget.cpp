#include "groupitemwidget.h"
#include "ui_groupitemwidget.h"

GroupItemWidget::GroupItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupItemWidget)
{
    ui->setupUi(this);
    ui->foldButton->setIcon(QIcon(":/icon/fold.svg"));
}

GroupItemWidget::GroupItemWidget(const RecordGroup &group, QWidget *parent)
    : GroupItemWidget(parent)
{
    _group = group;
    ui->spanLabel->setText(group.title());
    ui->countLabel->setText(QString::number(group.count()));
    ui->nameLabel->setText(group.patientName());
}

GroupItemWidget::~GroupItemWidget()
{
    delete ui;
}
