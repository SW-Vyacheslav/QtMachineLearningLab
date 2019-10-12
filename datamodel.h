#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractTableModel>
#include "dataholder.h"

class DataModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    DataModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation = Qt::Horizontal, int role = Qt::DisplayRole) const override;

    DataHolder GetDataHolder() const;

private:
    DataHolder* m_dataHolder;
};

#endif // DATAMODEL_H
