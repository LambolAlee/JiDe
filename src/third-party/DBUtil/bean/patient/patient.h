#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <QDate>
#include <QVariantMap>

#include "patientconst.h"
#include "../common.h"


class Patient : public QObject, public QVariantMap
{
    Q_OBJECT

    PropertyWithAccess(int, Int, id, Id)
    PropertyWithAccess(QString, String, patient_name, PatientName)
    PropertyWithAccess(int, Int, sex, Sex)
    PropertyWithAccess(int, Int, flag, Flag)
    PropertyWithAccess(QDate, Date, birthday, Birthday)
    PropertyWithAccess(int, Int, ethnicity, Ethnicity)
    PropertyWithAccess(QString, String, native_place, NativePlace)
    PropertyWithAccess(QString, String, birth_place, BirthPlace)
    PropertyWithAccess(QString, String, career, Career)

    int _id;
    QString _patient_name;
    int _sex;
    int _flag;
    QDate _birthday;
    int _ethnicity;
    QString _native_place;
    QString _birth_place;
    QString _career;

public:
    const QString save();
};

#endif // PATIENT_H
