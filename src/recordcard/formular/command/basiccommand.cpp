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
    _drugs = new QList<Drug>();
    for (auto &&idx: indexs)
        _drugs->append(idx.data(Qt::EditRole).value<Drug>());
}

DeleteDrug::~DeleteDrug()
{
    _drugs->clear();
    delete _drugs;
    _drugs = nullptr;
}

void DeleteDrug::undo()
{
    for (int i=0; i < _l.size(); ++i) {
        _model->setData(_l.at(i), _drugs->at(i));
    }
    _model->view()->updateDrugCount();
}

void DeleteDrug::redo()
{
    _model->clearItems(_l);
    _model->view()->updateDrugCount();
}
