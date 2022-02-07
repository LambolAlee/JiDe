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
}

LaunchWindow::~LaunchWindow()
{
    delete ui;
}
