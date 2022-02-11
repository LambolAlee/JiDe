#include "patientdao.h"
#include "db/DBUtil.h"
#include "db/sqls.h"

const char * const SQL_NAMESPACE_PATIENT = "Patient";

Patient PatientDao::mapToPatient(const QVariantMap &rowMap)
{
    Patient patient;
    patient.id = rowMap.value("id").toInt();
    patient.patient_name = rowMap.value("patient_name").toString();
    patient.sex = rowMap.value("sex").toBool();
    patient.flag = rowMap.value("flag").toInt();
    patient.birthday = rowMap.value("birthday").toDate();
    patient.ethnicity = rowMap.value("ethnicity").toInt();
    patient.native_place = rowMap.value("native_place").toString();
    patient.birth_place = rowMap.value("birth_place").toString();
    patient.career = rowMap.value("career").toString();
    return patient;
}

Patient PatientDao::findByPatientId(int id)
{
    QString sql = Sqls::instance().getSql(SQL_NAMESPACE_PATIENT, "findByPatientId").arg(id);
    return DBUtil::selectBean(mapToPatient, sql);
}
