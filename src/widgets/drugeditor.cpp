#include "drugeditor.h"
#include "ui_drugeditor.h"

#include <QGraphicsEffect>
#include <QKeyEvent>
#include <QFocusEvent>

DrugEditor::DrugEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrugEditor)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("DrugEditor{background:#f0f0f0;}");

    setDropShadow();
    ui->drugNameLE->installEventFilter(this);
    ui->weightLE->installEventFilter(this);
    ui->unitCB->installEventFilter(this);
    ui->usageCB->installEventFilter(this);

    _widgets.append(ui->drugNameLE);
    _widgets.append(ui->weightLE);
//    _widgets.append(ui->unitCB);
//    _widgets.append(ui->usageCB);

    setFocusProxy(ui->drugNameLE);
}

DrugEditor::~DrugEditor()
{
    delete ui;
}

void DrugEditor::setDropShadow()
{
    QGraphicsDropShadowEffect *e = new QGraphicsDropShadowEffect(this);
    e->setColor(QColor(63, 63, 63, 30));
    e->setBlurRadius(20);
    e->setXOffset(3);
    e->setYOffset(3);
    setGraphicsEffect(e);
}

void DrugEditor::setDrug(const Drug &drug)
{
    setDrugName(drug.at(0));
    QString weight_and_unit = drug[1];
    QString unit = weight_and_unit.at(weight_and_unit.size()-1);
    QString weight = weight_and_unit.remove(unit);
    setDrugWeight(weight, unit);
    if (drug.count() == 3)
        setDrugUsage(drug.at(2));
}

void DrugEditor::setDrugName(const QString &name)
{
    ui->drugNameLE->setText(name);
}

void DrugEditor::setDrugWeight(const QString &weight, const QString &unit)
{
    ui->weightLE->setText(weight);
    ui->unitCB->setCurrentText(unit);
}

void DrugEditor::setDrugUsage(const QString &usage)
{
    ui->usageCB->setCurrentText(usage);
}

void DrugEditor::fitViewItemHeight(int height)
{
    for (int i=0; i < ui->drugLayout->count(); ++i) {
        QWidget *w = ui->drugLayout->itemAt(i)->widget();
        w->setFixedHeight(height);
    }
}

Drug DrugEditor::submitDrug()
{
    Drug drug;
    drug.append(ui->drugNameLE->text());
    drug.append(ui->weightLE->text() + ui->unitCB->currentText());
    QString usage = ui->usageCB->currentText();
    if (usage != "无")
        drug.append(usage);
    return drug;
}

bool DrugEditor::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Tab) {
            if (!nextFocus())
                emit editNextPrevItem(this, true);
            return true;
        } else if (keyEvent->key() == Qt::Key_Backtab) {
            if (!prevFocus())
                emit editNextPrevItem(this, false);
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void DrugEditor::focusAndSelectAllInLineEdit()
{
    auto *l = static_cast<QLineEdit *>(_widgets.at(_focusIndex));
    l->selectAll();
    l->setFocus();
}

bool DrugEditor::nextFocus()
{
    if (_focusIndex)
        return false;
    _focusIndex = _focusIndex + 1;
    focusAndSelectAllInLineEdit();
    return true;
}

bool DrugEditor::prevFocus()
{
    if (!_focusIndex)
        return false;
    _focusIndex = _focusIndex - 1;
    focusAndSelectAllInLineEdit();
    return true;
}
