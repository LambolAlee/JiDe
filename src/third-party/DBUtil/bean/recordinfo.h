#ifndef RECORDINFO_H
#define RECORDINFO_H

#include <QVariantMap>
#include <QDate>
#include <QList>

#include "common.h"


class RecordInfo : public QVariantMap
{
    AccessMethod(Int, id, Id)
    AccessMethod(Int, patient_id, PatientId)
    AccessMethod(Int, parent_record, ParentRecord)
    AccessMethod(Date, clinic_date, ClinicDate)
    AccessMethod(Int, age, Age)
    AccessMethod(String, doctor_name, DoctorName)
    AccessMethod(Int, doctor_id, DoctorId)
    AccessMethod(String, place, Place)
    AccessMethod(String, display_name, DisplayName)

    int _id;
    int _patient_id;
    int _parent_record;
    QDate _clinic_date;
    int _age;
    QString _doctor_name;
    int _doctor_id;
    QString _place;
    QString _display_name;

public:
    using QVariantMap::QVariantMap;
    bool isReexam();
    QString title() const;
    QString debug(); // not provided for user will remove later
};

class RecordInfoGroup : public QList<RecordInfo>
{
public:
    using QList<RecordInfo>::QList;
    const QString title() const;
    const QString patientName() const;
};

using RecordInfoSet = QList<RecordInfo>;
using ClassifiedRecords = QMap<int, RecordInfoGroup>;

#endif // RECORDINFO_H
