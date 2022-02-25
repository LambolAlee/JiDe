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

// ======================================Add New Row Command===============================================
class AddNewRow : public BasicCommand
{
public:
    AddNewRow(FormularModel *model, int row);
    void undo() override;
    void redo() override;

private:
    int _row;
};

// =====================================Update Drug Command================================================
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

// ======================================Delete Drug Command================================================
class DeleteDrug: public BasicCommand
{
public:
    DeleteDrug(FormularModel *model, const QModelIndexList &indexs);
    void undo() override;
    void redo() override;

private:
    QModelIndexList _l;
    QList<Drug> _drugs;
};

// =======================================Tidy Command=====================================================
class TidyCommand: public BasicCommand
{
public:
    TidyCommand(FormularModel *model);
    void undo() override;
    void redo() override;

private:
    DrugLayout _layout;
};

// =======================================Delete Drug Rows Command=========================================
class DeleteRows: public BasicCommand
{
public:
    DeleteRows(FormularModel *model, const QModelIndexList &list);
    void undo() override;
    void redo() override;

private:
    QMap<int, QList<Drug>> _modifier;
};

#endif // BASICCOMMAND_H
