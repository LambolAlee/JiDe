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
    setWindowFlag(Qt::Popup);

    setDropShadow();

    ui->drugNameLE->installEventFilter(this);
    ui->weightLE->installEventFilter(this);

    connect(ui->drugNameLE, &QLineEdit::returnPressed, this, &DrugEditor::editNextWithInsertion);
    connect(ui->weightLE, &QLineEdit::returnPressed, this, &DrugEditor::editNextWithInsertion);
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
    setDrugName(drug.value(0));
    setDrugWeight(drug.value(1, "g"));
    setDrugUsage(drug.value(2, "无"));
}

void DrugEditor::setDrugName(const QString &name)
{
    ui->drugNameLE->setText(name);
}

void DrugEditor::setDrugWeight(QString &&weight_and_unit)
{
    QString unit = weight_and_unit.at(weight_and_unit.size()-1);
    QString weight = weight_and_unit.remove(unit);
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

void DrugEditor::focusInEditor()
{
    ui->drugNameLE->setFocus();
    ui->drugNameLE->selectAll();
}

bool DrugEditor::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Tab && obj->objectName() == QStringLiteral("weightLE")) {
            emit editNextPrevItem(QAbstractItemDelegate::EditNextItem);
            return true;
        } else if (keyEvent->key() == Qt::Key_Backtab && obj->objectName() == QStringLiteral("drugNameLE")) {
            emit editNextPrevItem(QAbstractItemDelegate::EditPreviousItem);
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}
