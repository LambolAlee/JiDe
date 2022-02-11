#ifndef PATIENTDAO_H
#define PATIENTDAO_H

#include <QVariantMap>

#include "bean/patient.h"

class PatientDao
{
public:
    static Patient findByPatientId(int id);
private:
    static Patient mapToPatient(const QVariantMap &rowMap);
};

#endif // PATIENTDAO_H
