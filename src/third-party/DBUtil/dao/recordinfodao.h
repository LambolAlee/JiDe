#ifndef RECORDINFODAO_H
#define RECORDINFODAO_H

#include <QObject>
#include <QVariantMap>

#include "util/Singleton.h"
#include "bean/recordinfo.h"

class RecordInfoDao
{
    SINGLETON(RecordInfoDao)

public:
    ClassifiedRecords findByPatientId(int id);

private:
    static RecordInfo mapToRecord(const QVariantMap &rowMap);
    static ClassifiedRecords classify(RecordInfoSet records);
};

#endif // RECORDINFODAO_H
