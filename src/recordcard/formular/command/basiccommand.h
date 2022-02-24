#ifndef BASICCOMMAND_H
#define BASICCOMMAND_H

#include "../formularmodel.h"

#include <QUndoCommand>
#include <QItemSelectionModel>


class BasicCommand: public QUndoCommand
{
public:
    BasicCommand(FormularModel *model);

protected:
    FormularModel *_model;
};

class AddNewRow : public BasicCommand
{
public:
    AddNewRow(FormularModel *model, int row);
    void undo() override;
    void redo() override;

private:
    int _row;
};

class UpdateDrug: public BasicCommand
{
public:
    UpdateDrug(FormularModel *model, const QModelIndex &index, const Drug &newDrug, const Drug &oldDrug);
    void undo() override;
    void redo() override;

private:
    QPersistentModelIndex _index;
    QPair<Drug, Drug> _data;
};

class DeleteDrug: public BasicCommand
{
public:
    DeleteDrug(FormularModel *model, const QModelIndexList &indexs);
    ~DeleteDrug();
    void undo() override;
    void redo() override;

private:
    QModelIndexList _l;
    QList<Drug> *_drugs;
};

#endif // BASICCOMMAND_H
