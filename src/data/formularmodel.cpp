#include "formularmodel.h"
#include "widgets/drugeditor.h"

FormularModel::FormularModel(Formular *formular, QObject *parent)
    : QAbstractTableModel(parent)
    , _formular(formular)
{
}

FormularModel::~FormularModel()
{
    delete _formular;
}

Qt::ItemFlags FormularModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags fs = QAbstractTableModel::flags(index);

    return fs | Qt::ItemIsEditable;
}

int FormularModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return (_formular->count() +3) / 4;
}

int FormularModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 4;
}

QVariant FormularModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole) {
        Drug drug = _formular->getDrug(index);
        return drug.join(" ");
    } else if (role == Qt::EditRole) {
        return _formular->getDrug(index);
    } else if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }
    else
        return QVariant();
}

bool FormularModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (role == Qt::EditRole) {
        _formular->setDrug(index, value.value<Drug>());
        emit dataChanged(index, index, QList<int>(Qt::DisplayRole));
    }
    return true;
}
