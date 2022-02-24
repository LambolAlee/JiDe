#include "launchwindow.h"
#include "ui_launchwindow.h"

#include "recordcard/formular/ui/formulartablecard.h"


LaunchWindow::LaunchWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LaunchWindow)
{
    ui->setupUi(this);
    FormularTableCard *form = new FormularTableCard(this);
    setCentralWidget(form);
}

LaunchWindow::~LaunchWindow()
{
    delete ui;
}

QMenuBar *LaunchWindow::menuBar()
{
    return ui->menuBar;
}
