#include "basiccommand.h"
#include "../ui/formulartableview.h"


BasicCommand::BasicCommand(FormularModel *model)
    : QUndoCommand()
{
    _model = model;
}

// ======================================Add New Row Command===============================================
AddNewRow::AddNewRow(FormularModel *model, int row)
    : BasicCommand(model)
{
    if (row < 0) {
        setObsolete(true);
        return;
    }
    _row = row;
    setText(QString("Add new row to pos: %1").arg(row));
}

void AddNewRow::undo()
{
    _model->removeRow(_row+1);
}

void AddNewRow::redo()
{
    _model->insertRow(_row);
}

// =====================================Update Drug Command================================================
UpdateDrug::UpdateDrug(FormularModel *model, const QModelIndex &index, const Drug &newDrug, const Drug &oldDrug)
    : BasicCommand(model)
{
    if (oldDrug == newDrug) {
        setObsolete(true);
        return;
    }
    _index = index;
    _data.first = newDrug;
    _data.second = oldDrug;
    setText(QString("Update Drug %1 with %2").arg(newDrug.join(" "), oldDrug.join(" ")));
}

void UpdateDrug::undo()
{
    _model->setData(_index, _data.second);
    if (_data.second.isEmpty())
        _model->view()->updateDrugCount();
}

void UpdateDrug::redo()
{
    _model->setData(_index, _data.first);
    if (_data.second.isEmpty())
        _model->view()->updateDrugCount();
}

// ======================================Delete Drug Command================================================
DeleteDrug::DeleteDrug(FormularModel *model, const QModelIndexList &indexs)
    : BasicCommand(model)
{
    if (indexs.isEmpty()) {
        setObsolete(true);
        return;
    }
    _l = indexs;
    for (auto &&idx: indexs)
        _drugs.append(idx.data(Qt::EditRole).value<Drug>());
}

void DeleteDrug::undo()
{
    for (int i=0; i < _l.size(); ++i) {
        _model->setData(_l.at(i), _drugs.at(i));
    }
    _model->view()->updateDrugCount();
}

void DeleteDrug::redo()
{
    _model->clearItems(_l);
    _model->view()->updateDrugCount();
}

// =======================================Tidy Command=====================================================
TidyCommand::TidyCommand(FormularModel *model)
    : BasicCommand(model)
{
    if (!_model->needTidy())
        setObsolete(true);
}

void TidyCommand::undo()
{
    _model->refillWith(_layout);
}

void TidyCommand::redo()
{
    _layout = _model->layout();
    _model->tidy();
}

// =======================================Delete Drug Rows Command=========================================
DeleteRows::DeleteRows(FormularModel *model, const QModelIndexList &list)
    : BasicCommand(model)
{
    if (list.isEmpty()) {
        setObsolete(true);
        return;
    }
    int previous = -1;
    for (auto &&i: list) {
        if (i.row() == previous) continue;
        previous = i.row();
        _modifier.insert(previous, _model->getDrugsInRow(previous));
    }
}

void DeleteRows::undo()
{
    std::for_each(_modifier.constKeyValueBegin(), _modifier.constKeyValueEnd(), [=](auto pair){
        _model->insertRow(pair.first-1); // the inserRows method in FormularModel inserts new rows after the specific `row`
        _model->setRowDrugs(pair.first, pair.second);
    });
    _model->view()->updateDrugCount();
}

void DeleteRows::redo()
{
    auto iList = _modifier.keys();
    std::for_each(iList.crbegin(), iList.crend(), [=](int row){ _model->removeRow(row); });
    _model->view()->updateDrugCount();
}
