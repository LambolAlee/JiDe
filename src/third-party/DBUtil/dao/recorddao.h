#ifndef RECORDDAO_H
#define RECORDDAO_H

#include <QObject>
#include <QVariantMap>

#include "util/Singleton.h"
#include "bean/record.h"

class RecordDao
{
public:
    static Record findByRecordId(int id);
    static RecordTree findByPatientId(int id);

private:
    static Record mapToRecord(const QVariantMap &rowMap);
    static RecordTree mapToRecordTree(const QList<Record> &records);

};

#endif // RECORDDAO_H
