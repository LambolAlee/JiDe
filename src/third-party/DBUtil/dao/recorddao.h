#ifndef RECORDDAO_H
#define RECORDDAO_H

#include <QObject>
#include <QVariantMap>

#include "util/Singleton.h"
#include "bean/record.h"

class RecordDao
{
    SINGLETON(RecordDao)

public:
    ClassifiedRecords findByPatientId(int id);

private:
    static constexpr const char * const SQL_NAMESPACE_RECORD = "Record";
    static Record mapToRecord(const QVariantMap &rowMap);
    static ClassifiedRecords classify(Records records);

};

#endif // RECORDDAO_H
