#include "patientinfo.h"


PatientInfo::PatientInfo(QObject *parent)
    : QObject{parent}
{

}

PatientInfo::PatientInfo(int id, QObject *parent)
    : PatientInfo(parent)
{
    setById(id);
}

PatientInfo::PatientInfo(const QString patient_name, int sex, int flag, QObject *parent)
    : PatientInfo(parent)
{
    setByIndex(patient_name, sex, flag);
}

void PatientInfo::setById(int id)
{
    _patient = PatientDao::instance().findByPatientId(id);
}

void PatientInfo::setByIndex(const QString patient_name, int sex, int flag)
{
    _patient = PatientDao::instance().findByPatientIndex(patient_name, sex, flag);
}
