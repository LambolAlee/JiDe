#include "patientdao.h"
#include "db/DBUtil.h"
#include "db/sqls.h"


PatientDao::PatientDao() {}

PatientDao::~PatientDao()
{
    _patientCache.clear();
    _indexCache.clear();
}

Patient *PatientDao::mapToPatient(const QVariantMap &rowMap)
{
    Patient *patient = new Patient;
    patient->setId(rowMap.value("id").toInt());
    patient->setPatientName(rowMap.value("patient_name").toString());
    patient->setSex(rowMap.value("sex").toBool());
    patient->setFlag(rowMap.value("flag").toInt());
    patient->setBirthday(rowMap.value("birthday").toDate());
    patient->setEthnicity(rowMap.value("ethnicity").toInt());
    patient->setNativePlace(rowMap.value("native_place").toString());
    patient->setBirthPlace(rowMap.value("birth_place").toString());
    patient->setCareer(rowMap.value("career").toString());
    return patient;
}

Patient *PatientDao::findByPatientId(int id)
{
    if (!_patientCache.contains(id)) {
        QString sql = Sqls::instance().getSql(SQL_NAMESPACE_PATIENT, "findByPatientId").arg(id);
        Patient *patient = DBUtil::selectBean(mapToPatient, sql);
        insertIntoCache(patient);
    }
    return _patientCache.object(id);
}

Patient *PatientDao::findByPatientIndex(const QString &patient_name, int sex, int flag)
{
    QString idxKey = buildIndex(patient_name, sex, flag);
    if (!_indexCache.contains(idxKey)) {
        QString sql = Sqls::instance().getSql(SQL_NAMESPACE_PATIENT, "findByPatientIndex")
                                        .arg(patient_name, QString::number(sex), QString::number(flag));
        Patient *patient = DBUtil::selectBean(mapToPatient, sql);
        insertIntoCache(idxKey, patient);
    }
    auto *key = _indexCache.object(idxKey);
    return _patientCache.object(*key);
}

QString PatientDao::findNameById(int id)    // usually used in record infomation query
{
    if (_patientCache.contains(id))
        return _patientCache.object(id)->getPatientName();
    QString sql = Sqls::instance().getSql(SQL_NAMESPACE_PATIENT, "findNameById").arg(QString::number(id));
    return DBUtil::selectString(sql);
}

int PatientDao::insert(Patient *patient)
{
    QVariantMap params;
    params["patient_name"] = patient->getPatientName();
    params["sex"] = patient->getSex();
    params["flag"] = patient->getFlag();
    params["birthday"] = patient->getBirthday().toString();
    params["ethnicity"] = patient->getEthnicity();
    params["native_place"] = patient->getNativePlace();
    params["birth_place"] = patient->getBirthPlace();
    params["career"] = patient->getCareer();

    int newId = DBUtil::insert(Sqls::instance().getSql(SQL_NAMESPACE_PATIENT, "insert"), params);
    if (newId != -1) {
        insertIntoCache(patient);
    }
    return newId;
}

bool PatientDao::update(Patient *patient)
{
    QString oldKey = buildIndex(patient);
    QString updateString = patient->save();
    QString sql = Sqls::instance().getSql(SQL_NAMESPACE_PATIENT, "update").arg(updateString, QString::number(patient->getId()));
    bool res = DBUtil::update(sql);
    if (res) {
        updateCache(oldKey, patient);
    }
    return res;
}

bool PatientDao::deletePatient(int id)
{
    QStringList indexes = findIndexById(id);
    QString sql = Sqls::instance().getSql(SQL_NAMESPACE_PATIENT, "delete").arg(QString::number(id));
    bool res = DBUtil::delete_(sql);
    if (res) {
        removeFromCache(indexes.join(""), id);
    }
    return res;
}

QString PatientDao::buildIndex(Patient *p)
{
    return p->getPatientName() + QString::number(p->getSex()) + QString::number(p->getFlag());
}

QString PatientDao::buildIndex(const QString &patient_name, int sex, int flag)
{
    return patient_name + QString::number(sex) + QString::number(flag);
}

QStringList PatientDao::findIndexById(int id)
{
    QString sql = Sqls::instance().getSql(SQL_NAMESPACE_PATIENT, "findIndexById").arg(QString::number(id));
    return DBUtil::selectStrings(sql);
}

// --------------------------------------Cache Operation-----------------------------------------------
void PatientDao::insertIntoCache(const QString &idxKey, Patient *patient)
{
    auto *idptr = new int(patient->getId());
    _patientCache.insert(patient->getId(), patient);
    _indexCache.insert(idxKey, idptr);
}

void PatientDao::insertIntoCache(Patient *patient)
{
    QString idxKey = buildIndex(patient);
    insertIntoCache(idxKey, patient);
}

void PatientDao::removeFromCache(const QString &idxKey, int id)
{
    _patientCache.remove(id);
    _indexCache.remove(idxKey);
}

void PatientDao::updateCache(const QString &oldKey, Patient *patient)
{
    _indexCache.remove(oldKey);

    QString idxKey = buildIndex(patient);
    auto *idptr = new int(patient->getId());
    _indexCache.insert(idxKey, idptr);
}
