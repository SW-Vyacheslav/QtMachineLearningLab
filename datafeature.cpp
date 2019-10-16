#include "datafeature.h"

DataFeature::DataFeature()
{

}

void DataFeature::AddFeature(const int& feature)
{
    m_features.append(feature);
}

void DataFeature::SetClassId(const int& classId)
{
    m_classId = classId;
}

int DataFeature::GetFeatureAt(const int& index) const
{
    return m_features[index];
}

int DataFeature::GetClassId() const
{
    return m_classId;
}

int DataFeature::GetNumOfFeatures() const
{
    return m_features.length();
}

bool DataFeature::operator==(const DataFeature &features) const
{
    return features.m_features == m_features;
}
