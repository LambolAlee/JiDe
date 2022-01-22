#ifndef FORMULARMODEL_H
#define FORMULARMODEL_H

#include "data/formular.h"

#include <QAbstractTableModel>

class FormularModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit FormularModel(Formular *formular, QObject *parent = nullptr);
    ~FormularModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Qt::DropActions supportedDropActions() const override;

    QStringList mimeTypes() const override;

    QMimeData *mimeData(const QModelIndexList &indexes) const override;

    bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const override;

    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

    bool clearItems(const QModelIndexList &indexs);

    void tidy();

private:
    Formular *_formular;
};

#endif // FORMULARMODEL_H
