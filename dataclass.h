#ifndef CLASSHOLDER_H
#define CLASSHOLDER_H

#include <QString>

class DataClass
{
public:
    DataClass();

    void SetId(const int& id);
    int GetId() const;
    QString GetData() const;
    void SetData(const QString& data);

private:
    int m_id;
    QString m_data;
};

#endif // CLASSHOLDER_H
