#include "examinewidget.h"
#include "ui_examinewidget.h"

ExamineWidget::ExamineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamineWidget)
{
    ui->setupUi(this);
}

ExamineWidget::~ExamineWidget()
{
    delete ui;
}
