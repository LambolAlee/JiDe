#include "statepanel.h"
#include "ui_statepanel.h"


StatePanel::StatePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatePanel)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground);
    ui->panel->hide();
    _led = new LEDButton(this);
    ui->gridLayout->addWidget(_led, 0,0);
    ui->gridLayout->setAlignment(_led, Qt::AlignRight);

    connect(ui->submitButton, &QToolButton::clicked, this, &StatePanel::submit);
    connect(ui->cancelButton, &QToolButton::clicked, this, &StatePanel::cancel);
}

StatePanel::~StatePanel()
{
    delete ui;
}

void StatePanel::addRedoAction(QAction *action)
{
    ui->redoButton->setDefaultAction(action);
}

void StatePanel::addUndoAction(QAction *action)
{
    ui->undoButton->setDefaultAction(action);
}

void StatePanel::updateState(bool clean)
{
    _led->updateState(clean);
    ui->submitButton->setEnabled(!clean);
    ui->cancelButton->setEnabled(!clean);
}

void StatePanel::enterEvent(QEnterEvent *ev)
{
    if (!_led->isChecked()) {
        ui->panel->setVisible(true);
        _led->updateChecked(true);
    }
    return QWidget::enterEvent(ev);
}

void StatePanel::leaveEvent(QEvent *ev)
{
    if (!_led->isChecked()) {
        ui->panel->setVisible(false);
        _led->updateChecked(false);
    }
    return QWidget::leaveEvent(ev);
}
