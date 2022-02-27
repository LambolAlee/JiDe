#ifndef PATIENTINFO_H
#define PATIENTINFO_H

#include <QObject>

#include "dao/patientdao.h"

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

private:
    Patient _patient;
};

#endif // PATIENTINFO_H
