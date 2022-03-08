#include "record.h"
#include "dao/patientdao.h"


bool Record::isReexam()
{
    return _id != _parent_record;
}

QString Record::debug()
{
    return QString("Record(id: %1, parent_record: %2, clinic_date: %3)").arg(
                QString::number(_id), QString::number(_parent_record), _clinic_date.toString());
}

const QString RecordGroup::title() const
{
    QList<QDate> dates;
    std::for_each(cbegin(), cend(), [&dates](const Record &record){ dates << record.getClinicDate(); });
    auto minAndMax = std::minmax_element(dates.cbegin(), dates.cend());
    return (*minAndMax.first).toString() + "-" + (*minAndMax.second).toString();
}

const QString RecordGroup::patientName() const
{
    if (isEmpty())
        return QString();
    else
        return PatientDao::instance().findNameById(first().getId());
}
