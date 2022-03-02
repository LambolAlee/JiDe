#ifndef PATIENTINFO_H
#define PATIENTINFO_H

#include <QObject>

#include "dao/patientdao.h"
#include "patient/patientconst.h"

class PatientInfo : public QObject
{
    Q_OBJECT

public:
    PatientInfo(QObject *parent = nullptr);
    PatientInfo(int id, QObject *parent = nullptr);
    PatientInfo(const QString patient_name, int sex, int flag = 0, QObject *parent = nullptr);

    void setById(int id);
    void setByIndex(const QString patient_name, int sex, int flag);

    QString name() const { return _patient.patient_name; }
    int sex() const { return _patient.sex; }
    QDate birthday() const { return _patient.birthday; }
    int ethnicity() const { return _patient.ethnicity; }
    QString career() const { return _patient.career; }
    QString birthPlace() const { return _patient.birth_place; }
    QString nativePlace() const { return _patient.native_place; }

private:
    Patient _patient;
};

#endif // PATIENTINFO_H
