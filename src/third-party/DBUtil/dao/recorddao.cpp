#include "recorddao.h"
#include "db/sqls.h"
#include "db/DBUtil.h"

const char * const SQL_NAMESPACE_RECORD = "Record";


Record RecordDao::mapToRecord(const QVariantMap &rowMap)
{
    Record record;
    record.id = rowMap.value("id").toInt();
    record.patient_id = rowMap.value("patient_id").toInt();
    record.is_reexam = rowMap.value("is_reexam").toBool();
    record.parent_record = rowMap.value("parent_record").toInt();
    record.clinic_date = rowMap.value("clinic_date").toDate();
    record.age = rowMap.value("age").toInt();
    record.doctor_name = rowMap.value("doctor_name").toString();
    record.doctor_id = rowMap.value("doctor_id").toInt();
    record.place = rowMap.value("place").toString();

    return record;
}

RecordTree RecordDao::mapToRecordTree(const QList<Record> &records)
{
    RecordTree tree;
    for (const Record &record: records) {
        ChildRecord child = tree.value(record.parent_record);
        if (record.parent_record == record.id)
            child.prepend(record);
        else
            child.append(record);
        tree.insert(record.parent_record, child);
    }
    return tree;
}

Record RecordDao::findByRecordId(int id)
{
    QString sql = Sqls::instance().getSql(SQL_NAMESPACE_RECORD, "findByRecordId").arg(id);
    return DBUtil::selectBean(mapToRecord, sql);
}

RecordTree RecordDao::findByPatientId(int id)
{
    QString sql = Sqls::instance().getSql(SQL_NAMESPACE_RECORD, "findByPatientId").arg(id);
    auto records = DBUtil::selectBeans(mapToRecord, sql);
    return mapToRecordTree(records);
}
