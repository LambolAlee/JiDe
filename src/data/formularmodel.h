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

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private:
    Formular *_formular;
};

#endif // FORMULARMODEL_H
