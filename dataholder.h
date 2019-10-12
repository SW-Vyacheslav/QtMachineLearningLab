#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include <QString>
#include <QList>
#include "datafeature.h"
#include "dataclass.h"

class DataHolder
{
public:
    DataHolder();

    void ReadDataFromFile(const QString& filepath);
    void SaveDataToFile(const QString& filepath);

    void AddDataFeature(const DataFeature& dataFeatures);

    int GetNumOfDataFeatures() const;
    int GetNumOfClasses() const;
    DataFeature GetDataFeatureAt(const int& index) const;
    DataClass GetClassAt(const int& index) const;
    DataClass GetClassById(const int& classId) const;
    QList<DataFeature> GetDataFeaturesOfClass(const int& classId) const;
    QList<int> GetClassesIds() const;

private:
    QList<DataFeature> m_dataFeatures;
    QList<DataClass> m_classes;
};

#endif // DATAHOLDER_H
