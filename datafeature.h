#ifndef DATA_H
#define DATA_H

#include <QList>

class DataFeature
{
public:
    DataFeature();

    void AddFeature(const int& feature);
    void SetClassId(const int& classId);

    int GetFeatureAt(const int& index) const;
    int GetClassId() const;
    int GetNumOfFeatures() const;

    bool operator==(const DataFeature& features) const;

private:
    int m_classId;
    QList<int> m_features;
};

#endif // DATA_H
