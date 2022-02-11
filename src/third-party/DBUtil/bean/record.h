#ifndef RECORD_H
#define RECORD_H

#include <QVariantMap>
#include <QDate>
#include <QList>
#include <QMap>


class Record
{
public:    
    int id;
    int patient_id;
    bool is_reexam;
    int parent_record;
    QDate clinic_date;
    int age;
    QString doctor_name;
    int doctor_id;
    QString place;
};

typedef QList<Record> ChildRecord;
typedef QMap<int, ChildRecord> RecordTree;

#endif // RECORD_H
