#include "dataholder.h"
#include <QFile>
#include <QTextStream>

DataHolder::DataHolder()
{

}

void DataHolder::ReadDataFromFile(const QString& filepath)
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QStringList strlist = in.readLine().split(',');
        if (strlist[0] == "f")
        {
            DataFeature df;
            for (int i = 1; i < strlist.length()-1; i++)
            {
                df.AddFeature(strlist[i].toInt());
            }
            df.SetClassId(strlist[strlist.length()-1].toInt());
            m_dataFeatures.append(df);
        }
        else if (strlist[0] == "c")
        {
            DataClass dc;
            dc.SetData(strlist[2]);
            dc.SetId(strlist[1].toInt());
            m_classes.append(dc);
        }
    }

    file.close();
}

void DataHolder::SaveDataToFile(const QString& filepath)
{
    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    for (int i = 0; i < m_dataFeatures.length(); i++)
    {
        QString str = "f,";
        int numOfFeatures = m_dataFeatures[i].GetNumOfFeatures();
        for (int j = 0; j < numOfFeatures; j++)
        {
            str += QString::number(m_dataFeatures[i].GetFeatureAt(j)) + ",";
        }
        str += QString::number(m_dataFeatures[i].GetClassId()) + "\n";
        file.write(str.toStdString().c_str(), str.length());
    }

    for (int i = 0; i < m_classes.length(); i++)
    {
        QString str = "c,";
        str += QString::number(m_classes[i].GetId());
        str += m_classes[i].GetData() + "\n";
        file.write(str.toStdString().c_str(), str.length());
    }

    file.close();
}

void DataHolder::AddDataFeature(const DataFeature& dataFeatures)
{
    m_dataFeatures.append(dataFeatures);
}

DataFeature DataHolder::GetDataFeatureAt(const int& index) const
{
    return m_dataFeatures[index];
}

DataClass DataHolder::GetClassAt(const int &index) const
{
    return m_classes[index];
}

DataClass DataHolder::GetClassById(const int &classId) const
{
    for (int i = 0; i < m_classes.length(); i++)
    {
        if (m_classes[i].GetId() == classId) return m_classes[i];
    }

    return DataClass();
}

int DataHolder::GetNumOfDataFeatures() const
{
    return m_dataFeatures.length();
}

int DataHolder::GetNumOfClasses() const
{
    return m_classes.length();
}

QList<DataFeature> DataHolder::GetDataFeaturesOfClass(const int& classId) const
{
    QList<DataFeature> dataFeatures;
    for (int i = 0; i < m_dataFeatures.length(); i++)
    {
        if(m_dataFeatures[i].GetClassId() == classId) dataFeatures.append(m_dataFeatures[i]);
    }
    return dataFeatures;
}

QList<int> DataHolder::GetClassesIds() const
{
    QList<int> classes;
    classes.append(m_dataFeatures[0].GetClassId());
    for (int i = 1; i < m_dataFeatures.length(); i++)
    {
        bool founded = false;
        for (int j = 0; j < classes.length(); j++)
        {
            if(classes[j] == m_dataFeatures[i].GetClassId())
            {
                founded = true;
                break;
            }
        }
        if(!founded) classes.append(m_dataFeatures[i].GetClassId());
    }
    return classes;
}
