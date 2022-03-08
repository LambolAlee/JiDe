#include "navitagsbar.h"
#include "ui_navitagsbar.h"

NaviTagsBar::NaviTagsBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NaviTagsBar)
{
    ui->setupUi(this);
}

NaviTagsBar::~NaviTagsBar()
{
    delete ui;
}
