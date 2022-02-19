#include "launchwindow.h"
#include "ui_launchwindow.h"

#include "widgets/formulartableform.h"


LaunchWindow::LaunchWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LaunchWindow)
{
    ui->setupUi(this);
    FormularTableForm *form = new FormularTableForm(this);
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
