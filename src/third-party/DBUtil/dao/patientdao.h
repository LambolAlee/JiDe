#ifndef PATIENTDAO_H
#define PATIENTDAO_H

#include <QCache>

#include "bean/patient/patient.h"
#include "util/Singleton.h"

class PatientDao
{
    SINGLETON(PatientDao)

public:
    Patient *findByPatientId(int id);
    Patient *findByPatientIndex(const QString &patient_name, int sex, int flag);
    QString findNameById(int id);
    int insert(Patient *patient);
    bool update(Patient *patient);
    bool deletePatient(int id);

private:
    QCache<int, Patient> _patientCache;
    QCache<QString, int> _indexCache;

    static Patient *mapToPatient(const QVariantMap &rowMap);

    QString buildIndex(Patient *patient);
    QString buildIndex(const QString &patient_name, int sex, int flag);

    QStringList findIndexById(int id);

// --------------------------------------Cache Operation-----------------------------------------------
    void insertIntoCache(Patient *patient);
    void insertIntoCache(const QString &idxKey, Patient *patient);
    void removeFromCache(const QString &idxKey, int id);
    void updateCache(const QString &oldKey, Patient *patient);
};
#endif // PATIENTDAO_H
