#include "sidebar.h"
#include "ui_sidebar.h"

SideBar::SideBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideBar)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground);
}

SideBar::~SideBar()
{
    delete ui;
}
