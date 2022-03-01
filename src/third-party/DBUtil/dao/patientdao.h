#ifndef PATIENTDAO_H
#define PATIENTDAO_H

#include <QVariantMap>
#include <QCache>

#include "bean/patient.h"
#include "util/Singleton.h"

class PatientDao
{
    SINGLETON(PatientDao)

public:
    Patient findByPatientId(int id);
    Patient findByPatientIndex(const QString &patient_name, int sex, int flag);
    int insert(Patient *patient);
    bool update(Patient *patient);
    bool deletePatient(int id);

private:
    QCache<int, Patient> _userCache;
    QCache<QString, int> _indexCache;

    static Patient *mapToPatient(const QVariantMap &rowMap);

    QString buildIndex(const Patient &patient);
    QString buildIndex(const QString &patient_name, int sex, int flag);

    QStringList findIndexById(int id);

// --------------------------------------Cache Operation-----------------------------------------------
    void insertIntoCache(const QString &idxKey, Patient *p);
    void removeFromCache(const QString &idxKey, int id);
};
#endif // PATIENTDAO_H
