#include "recorddao.h"
#include "db/sqls.h"
#include "db/DBUtil.h"

RecordDao::RecordDao() {}

RecordDao::~RecordDao() {}

Record RecordDao::mapToRecord(const QVariantMap &rowMap)
{
    Record record;
    record.setId(rowMap.value("id").toInt());
    record.setPatientId(rowMap.value("patient_id").toInt());
    record.setParentRecord(rowMap.value("parent_record").toInt());
    record.setClinicDate(rowMap.value("clinic_date").toDate());
    record.setAge(rowMap.value("age").toInt());
    record.setDoctorName(rowMap.value("doctor_name").toString());
    record.setDoctorId(rowMap.value("doctor_id").toInt());
    record.setPlace(rowMap.value("place").toString());

    return record;
}

ClassifiedRecords RecordDao::findByPatientId(int id)
{
    QString sql = Sqls::instance().getSql(SQL_NAMESPACE_RECORD, "findByPatientId").arg(QString::number(id));
    Records records = DBUtil::selectBeans(mapToRecord, sql);
    return classify(records);
}

ClassifiedRecords RecordDao::classify(Records records)
{
    QMap<int, RecordGroup> map;
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
