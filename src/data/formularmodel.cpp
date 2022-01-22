#include "formularmodel.h"
#include "widgets/drugeditor.h"

#include <QMimeData>
#include <QIODevice>

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
    if (!index.isValid())
        return Qt::ItemIsDropEnabled | fs;
    else
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | fs;
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
        //qDebug() << index;
        Drug drug = _formular->getDrug(index);
        return Formular::toString(drug);
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

bool FormularModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row+count-1);
    bool res = _formular->insertRows(row, count);
    endInsertRows();
    return res;
}

bool FormularModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count-1);
    bool res = _formular->removeRows(row, count);
    endRemoveRows();
    return res;
}

Qt::DropActions FormularModel::supportedDropActions() const
{
    return Qt::MoveAction | Qt::CopyAction;
}

QStringList FormularModel::mimeTypes() const
{
    QStringList types;
    types << "application/vnd.text.list" << "application/vnd.pos.list";
    return types;
}

QMimeData *FormularModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData;
    QByteArray encodedData;
    QByteArray encodedPos;
    QDataStream posStream(&encodedPos, QIODevice::WriteOnly);
    QDataStream stream(&encodedData, QIODevice::WriteOnly);
    for (const QModelIndex &index: indexes) {
        if (index.isValid()) {
            stream << data(index).toString();
            posStream << QPair<int,int>(index.row(), index.column());
        }
    }
    mimeData->setData("application/vnd.text.list", encodedData);
    mimeData->setData("application/vnd.pos.list", encodedPos);

    return mimeData;
}

bool FormularModel::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(action);

    if (!(data->hasFormat("application/vnd.text.list") && data->hasFormat("application/vnd.pos.list")))
        return false;
    if (row == rowCount())
        return false;
    if (parent.isValid() || row+column >= 0)
        return true;
    else
        return false;
}

bool FormularModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (!canDropMimeData(data, action, row, column, parent))
        return false;

    if (action == Qt::IgnoreAction)
        return true;

    QPair<int, int> pos;
    if (parent.isValid()) {
        pos.first = parent.row();
        pos.second = parent.column();
    } else {
        pos.first = row;
        pos.second = column;
    }

    QByteArray encodedData = data->data("application/vnd.text.list");
    QByteArray encodedPos = data->data("application/vnd.pos.list");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QDataStream posStream(&encodedPos, QIODevice::ReadOnly);
    QList<QPair<int,int>> posList;
    QList<Drug> drugList;
    //QList<QModelIndex> indexes;

    while (!stream.atEnd()) {
        QString text; QPair<int,int> pos;
        stream >> text; posStream >> pos;
        drugList << Formular::toDrug(text);
        posList << pos;
    }
    ////////////////////////////////////////////////////////////
    _formular->insertData(pos, drugList, posList);
    ///////////////////////////////////////////////////////////

    return true;
}

bool FormularModel::clearItems(const QModelIndexList &indexs)
{
    if (indexs.isEmpty()) return false;
    bool res = _formular->clearItems(indexs);
    emit dataChanged(indexs.constFirst(), indexs.constLast(), QList<int>(Qt::DisplayRole));
    return res;
}

void FormularModel::tidy()
{
    beginResetModel();
    _formular->tidy();
    endResetModel();
}
