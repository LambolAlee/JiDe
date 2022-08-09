#include "recordcardframe.h"
#include "ui_recordcardframe.h"

#include "statepanel.h"
#include "recordcardbody.h"

#include <QAction>
#include <QUndoCommand>


RecordCardFrame::RecordCardFrame(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RecordCardFrame)
{
    ui->setupUi(this);
    _statePanel = new StatePanel(this);
    _typeLabel = new QPushButton(this);
    _typeLabel->setIcon(QIcon(":/icon/typelabel.svg"));
    _typeLabel->setProperty("class", "TypeLabel");
    delete ui->cardTitleLayout->replaceWidget(ui->labelWidget, _typeLabel);
    delete ui->cardTitleLayout->replaceWidget(ui->statePanelWidget, _statePanel);

    connect(_statePanel, &StatePanel::submit, this, &RecordCardFrame::submit);
    connect(_statePanel, &StatePanel::cancel, this, &RecordCardFrame::cancel);
}

RecordCardFrame::~RecordCardFrame()
{
    delete ui;
}

void RecordCardFrame::initUndoSystem()
{
    auto *stack = _body->undoStack();

    auto *redo = stack->createRedoAction(this);
    redo->setIcon(QIcon(":/icon/redo.svg"));
    addRedoAction(redo);
    auto *undo = stack->createUndoAction(this);
    undo->setIcon(QIcon(":/icon/undo.svg"));
    addUndoAction(undo);

    connect(stack, &QUndoStack::cleanChanged, _statePanel, &StatePanel::updateState);
}

void RecordCardFrame::setBody(RecordCardBody *w)
{
    auto *_ = layout()->replaceWidget(ui->centralWidget, w, Qt::FindDirectChildrenOnly);
    if (_) {
        delete _;
        _body = w;
    }
}

void RecordCardFrame::setText(const QString &text)
{
    _typeLabel->setText(text);
}

void RecordCardFrame::setTitle(const QString &title)
{
    ui->titleLabel->setText(title);
}

const QString RecordCardFrame::title() const
{
    return ui->titleLabel->text();
}

void RecordCardFrame::addRedoAction(QAction *action)
{
    _statePanel->addRedoAction(action);
}

void RecordCardFrame::addUndoAction(QAction *action)
{
    _statePanel->addUndoAction(action);
}

void RecordCardFrame::submit()
{
    _body->undoStack()->clear();
}

void RecordCardFrame::cancel()
{
    auto *stack = _body->undoStack();
    while (stack->canUndo())
        stack->undo();
}
