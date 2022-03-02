#include "patientdao.h"
#include "db/DBUtil.h"
#include "db/sqls.h"


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
    if (_userCache.contains(id)) {
        return _userCache.object(id);
    }

    QString sql = Sqls::instance().getSql(SQL_NAMESPACE_PATIENT, "findByPatientId").arg(id);
    Patient *patient = DBUtil::selectBean(mapToPatient, sql);
    insertIntoCache(buildIndex(patient), patient);
    return patient; // fix later
    /*patientdao.cpp:40:5: Use of memory after it is freed [clang-analyzer-cplusplus.NewDelete]*/
}

Patient *PatientDao::findByPatientIndex(const QString &patient_name, int sex, int flag)
{
    QString idxKey = buildIndex(patient_name, sex, flag);
    if (_indexCache.contains(idxKey)) {
        auto *key = _indexCache.object(idxKey);
        return _userCache.object(*key);
    }

    QString sql = Sqls::instance().getSql(SQL_NAMESPACE_PATIENT, "findByPatientIndex")
                                    .arg(patient_name, QString::number(sex), QString::number(flag));
    Patient *patient = DBUtil::selectBean(mapToPatient, sql);
    insertIntoCache(idxKey, patient);
    return patient; // fix later
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
        insertIntoCache(buildIndex(patient), patient);
    }
    return newId;
}

bool PatientDao::update(Patient *patient)
{
    QString updateString = patient->save();
    QString sql = Sqls::instance().getSql(SQL_NAMESPACE_PATIENT, "update").arg(updateString, QString::number(patient->getId()));
    bool res = DBUtil::update(sql);
    if (res) {

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
    return QString("%1%2%3").arg(p->getPatientName(), QString::number(p->getSex()), QString::number(p->getFlag()));
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
    auto *idptr = new int(patient->getId());
    _userCache.insert(patient->getId(), patient);
    _indexCache.insert(idxKey, idptr);
}

void PatientDao::removeFromCache(const QString &idxKey, int id)
{
    _userCache.remove(id);
    _indexCache.remove(idxKey);
}
