#include "groupeditorwidget.h"
#include "ui_groupeditorwidget.h"

GroupEditorWidget::GroupEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupEditorWidget)
{
    ui->setupUi(this);
}

GroupEditorWidget::~GroupEditorWidget()
{
    delete ui;
}
