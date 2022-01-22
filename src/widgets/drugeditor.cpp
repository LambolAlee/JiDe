#include "drugeditor.h"
#include "ui_drugeditor.h"
#include "formulartableofme.h"

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
    _widgetsNames.append(ui->drugNameLE->objectName());
    _widgets.append(ui->weightLE);
    _widgetsNames.append(ui->weightLE->objectName());

    FormularTableOfMe *table = static_cast<FormularTableOfMe *>(parent);
    connect(table, &FormularTableOfMe::focusInEditor, this, &DrugEditor::handleFocusInEditor);
}

DrugEditor::~DrugEditor()
{
    delete ui;
}

void DrugEditor::handleFocusInEditor()
{
    ui->drugNameLE->setFocus();
    ui->drugNameLE->selectAll();
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
    if (drug.isEmpty()) return;
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
    QString name = ui->drugNameLE->text().trimmed();
    if (name.isEmpty()) return Drug();

    Drug drug;
    drug.append(name);
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
        auto key = keyEvent->key();
        if(key == Qt::Key_Tab) {
            if (!nextFocus())
                emit editNextPrevItem(QAbstractItemDelegate::EditNextItem);
            return true;
        } else if (key == Qt::Key_Backtab) {
            if (!prevFocus())
                emit editNextPrevItem(QAbstractItemDelegate::EditPreviousItem);
            return true;
        } else if (key == Qt::Key_Return) {
            emit editNextWithInsertion();
            return true;
        }
    } else if (event->type() == QEvent::FocusIn && _widgetsNames.contains(obj->objectName())) {
        _focusIndex = _widgetsNames.indexOf(obj->objectName());
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
