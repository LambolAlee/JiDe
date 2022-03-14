#include "recordinfodao.h"
#include "db/sqls.h"
#include "db/DBUtil.h"
#include "global.h"

RecordInfoDao::RecordInfoDao() {}

RecordInfoDao::~RecordInfoDao() {}

RecordInfo RecordInfoDao::mapToRecord(const QVariantMap &rowMap)
{
    RecordInfo record;
    record.setId(rowMap.value("id").toInt());
    record.setPatientId(rowMap.value("patient_id").toInt());
    record.setParentRecord(rowMap.value("parent_record").toInt());
    record.setClinicDate(rowMap.value("clinic_date").toDate());
    record.setAge(rowMap.value("age").toInt());
    record.setDoctorName(rowMap.value("doctor_name").toString());
    record.setDoctorId(rowMap.value("doctor_id").toInt());
    record.setPlace(rowMap.value("place").toString());
    record.setDisplayName(rowMap.value("display_name").toString());

    return record;
}

ClassifiedRecords RecordInfoDao::findByPatientId(int id)
{
    QString sql = Sqls::instance().getSql(DaoNameSpace::RecordInfo, "findByPatientId").arg(QString::number(id));
    RecordInfoSet records = DBUtil::selectBeans(mapToRecord, sql);
    return classify(records);
}

ClassifiedRecords RecordInfoDao::classify(RecordInfoSet records)
{
    QMap<int, RecordInfoGroup> map;
    for (auto &&record: records) {
        if (record.isReexam()) {
            auto group = map.value(record.getParentRecord());
            group << record;
            map.insert(record.getParentRecord(), group);
        } else {
            auto group = map.value(record.getId());
            group.prepend(record);
            map.insert(record.getId(), group);
        }
    }
    return map;
}
