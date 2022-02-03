#include "lineeditwithextensibletextbox.h"
#include "ui_lineeditwithextensibletextbox.h"

LineEditWithExtensibleTextBox::LineEditWithExtensibleTextBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineEditWithExtensibleTextBox)
{
    ui->setupUi(this);
}

LineEditWithExtensibleTextBox::~LineEditWithExtensibleTextBox()
{
    delete ui;
}
