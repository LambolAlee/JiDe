#ifndef RECORD_H
#define RECORD_H

#include <QVariantMap>
#include <QDate>
#include <QList>

#include "common.h"


class Record : public QVariantMap
{
    AccessMethod(Int, id, Id)
    AccessMethod(Int, patient_id, PatientId)
    AccessMethod(Int, parent_record, ParentRecord)
    AccessMethod(Date, clinic_date, ClinicDate)
    AccessMethod(Int, age, Age)
    AccessMethod(String, doctor_name, DoctorName)
    AccessMethod(Int, doctor_id, DoctorId)
    AccessMethod(String, place, Place)

    int _id;
    int _patient_id;
    int _parent_record;
    QDate _clinic_date;
    int _age;
    QString _doctor_name;
    int _doctor_id;
    QString _place;

public:
    bool isReexam();
    QString debug(); // not provided for user will remove later
};

class RecordGroup : public QList<Record>
{
public:

};

using Records = QList<Record>;
using ClassifiedRecords = QMap<int, RecordGroup>;

#endif // RECORD_H
