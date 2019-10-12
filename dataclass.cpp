#include "dataclass.h"

DataClass::DataClass()
{

}

void DataClass::SetId(const int &id)
{
    m_id = id;
}

int DataClass::GetId() const
{
    return m_id;
}

QString DataClass::GetData() const
{
    return m_data;
}

void DataClass::SetData(const QString &data)
{
    m_data = data;
}
