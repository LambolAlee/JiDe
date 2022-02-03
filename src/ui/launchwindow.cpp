#include "launchwindow.h"
#include "ui_launchwindow.h"
#include "basicinfodockwidget.h"

#include <QSizePolicy>

LaunchWindow::LaunchWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LaunchWindow)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 13);
    ui->splitter->setStretchFactor(1, 17);
    QWidget *widget = new QWidget(this);
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->toolBar->insertWidget(ui->actionSave, widget);
    ui->toolBar->insertSeparator(ui->actionSave);
}

LaunchWindow::~LaunchWindow()
{
    delete ui;
}
