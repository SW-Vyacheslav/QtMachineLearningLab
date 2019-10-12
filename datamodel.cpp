#include "datamodel.h"

DataModel::DataModel(QObject* parent) : QAbstractTableModel(parent)
{
    m_dataHolder = new DataHolder();
    m_dataHolder->ReadDataFromFile("C:\\Users\\Vuacheslav\\Desktop\\QtMachineLearningLab\\data.csv");
}

int DataModel::rowCount(const QModelIndex &) const
{
    return m_dataHolder->GetNumOfDataFeatures();
}

int DataModel::columnCount(const QModelIndex &) const
{
    return m_dataHolder->GetDataFeatureAt(0).GetNumOfFeatures() + 1;
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        DataFeature df = m_dataHolder->GetDataFeatureAt(index.row());
        if(index.column() < columnCount() - 1) return QString::number(df.GetFeatureAt(index.column()));
        else return m_dataHolder->GetClassById(df.GetClassId()).GetData();
    }
    return QVariant();
}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return QString("f1");
            case 1:
                return QString("f2");
            case 2:
                return QString("Class");
            default:
                return QVariant();
            }
        }
    }

    return QVariant();
}

DataHolder DataModel::GetDataHolder() const
{
    return *m_dataHolder;
}
