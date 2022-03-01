#include "patientdao.h"
#include "db/DBUtil.h"
#include "db/sqls.h"

const char * const SQL_NAMESPACE_PATIENT = "Patient";


PatientDao::~PatientDao()
{
    _userCache.clear();
    _indexCache.clear();
}

PatientDao::PatientDao()
{
}

Patient *PatientDao::mapToPatient(const QVariantMap &rowMap)
{
    Patient *patient = new Patient;
    patient->id = rowMap.value("id").toInt();
    patient->patient_name = rowMap.value("patient_name").toString();
    patient->sex = rowMap.value("sex").toBool();
    patient->flag = rowMap.value("flag").toInt();
    patient->birthday = rowMap.value("birthday").toDate();
    patient->ethnicity = rowMap.value("ethnicity").toInt();
    patient->native_place = rowMap.value("native_place").toString();
    patient->birth_place = rowMap.value("birth_place").toString();
    patient->career = rowMap.value("career").toString();
    return patient;
}

Patient PatientDao::findByPatientId(int id)
{
    if (_userCache.contains(id)) {
        return *_userCache.object(id);
    }

    QString sql = Sqls::instance().getSql(SQL_NAMESPACE_PATIENT, "findByPatientId").arg(id);
    Patient *patient = DBUtil::selectBean(mapToPatient, sql);
    insertIntoCache(buildIndex(*patient), patient);
    return *patient;
}

Patient PatientDao::findByPatientIndex(const QString &patient_name, int sex, int flag)
{
    QString idxKey = buildIndex(patient_name, sex, flag);
    if (_indexCache.contains(idxKey)) {
        auto *key = _indexCache.object(idxKey);
        return *_userCache.object(*key);
    }

    QString sql = Sqls::instance().getSql(SQL_NAMESPACE_PATIENT, "findByPatientIndex")
                                    .arg(patient_name, QString::number(sex), QString::number(flag));
    Patient *patient = DBUtil::selectBean(mapToPatient, sql);
    insertIntoCache(idxKey, patient);
    return *patient;
}

int PatientDao::insert(Patient *patient)
{
    QVariantMap params;
    params["patient_name"] = patient->patient_name;
    params["sex"] = patient->sex;
    params["flag"] = patient->flag;
    params["birthday"] = patient->birthday.toString();
    params["ethnicity"] = patient->ethnicity;
    params["native_place"] = patient->native_place;
    params["birth_place"] = patient->birth_place;
    params["career"] = patient->career;

    int newId = DBUtil::insert(Sqls::instance().getSql(SQL_NAMESPACE_PATIENT, "insert"), params);
    if (newId != -1) {
        insertIntoCache(buildIndex(*patient), patient);
    }
    return newId;
}

bool PatientDao::update(Patient *patient)
{
    QVariantMap params;
    params["patient_name"] = patient->patient_name;
    params["sex"] = patient->sex;
    params["flag"] = patient->flag;
    params["birthday"] = patient->birthday.toString();
    params["ethnicity"] = patient->ethnicity;
    params["native_place"] = patient->native_place;
    params["birth_place"] = patient->birth_place;
    params["career"] = patient->career;

    bool res = DBUtil::update(Sqls::instance().getSql(SQL_NAMESPACE_PATIENT, "update"), params);
    if (res) {
        insertIntoCache(buildIndex(*patient), patient);
    }
    return res;
}

bool PatientDao::deletePatient(int id)
{
    QString key = QString::number(id);
    QStringList indexes = findIndexById(id);
    QString sql = Sqls::instance().getSql(SQL_NAMESPACE_PATIENT, "delete").arg(key);
    bool res = DBUtil::delete_(sql);
    if (res) {
        removeFromCache(indexes.join(""), id);
    }
    return res;
}

QString PatientDao::buildIndex(const Patient &p)
{
    return QString("%1%2%3").arg(p.patient_name, QString::number(p.sex), QString::number(p.flag));
}

QString PatientDao::buildIndex(const QString &patient_name, int sex, int flag)
{
    return QString("%1%2%3").arg(patient_name, QString::number(sex), QString::number(flag));
}

QStringList PatientDao::findIndexById(int id)
{
    QString sql = Sqls::instance().getSql(SQL_NAMESPACE_PATIENT, "findIndexById").arg(QString::number(id));
    return DBUtil::selectStrings(sql);
}

// --------------------------------------Cache Operation-----------------------------------------------
void PatientDao::insertIntoCache(const QString &idxKey, Patient *patient)
{
    _userCache.insert(patient->id, patient);
    auto *idptr = new int(patient->id);
    _indexCache.insert(idxKey, idptr);
}

void PatientDao::removeFromCache(const QString &idxKey, int id)
{
    _userCache.remove(id);
    _indexCache.remove(idxKey);
}
