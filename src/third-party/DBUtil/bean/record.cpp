#include "record.h"


bool Record::isReexam()
{
    return _id != _parent_record;
}

QString Record::debug()
{
    return QString("Record(id: %1, parent_record: %2, clinic_date: %3)").arg(
                QString::number(_id), QString::number(_parent_record), _clinic_date.toString());
}
