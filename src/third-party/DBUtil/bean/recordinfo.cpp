#include "recordinfo.h"
#include "dao/patientdao.h"


bool RecordInfo::isReexam()
{
    return _id != _parent_record;
}

QString RecordInfo::debug()
{
    return QString("Record(id: %1, parent_record: %2, clinic_date: %3)").arg(
                QString::number(_id), QString::number(_parent_record), _clinic_date.toString());
}

const QString RecordInfoGroup::title() const
{
    QList<QDate> dates;
    std::for_each(cbegin(), cend(), [&dates](const RecordInfo &info){ dates << info.getClinicDate(); });
    auto minAndMax = std::minmax_element(dates.cbegin(), dates.cend());
    return (*minAndMax.first).toString("yyyy.MM.dd") + " - " + (*minAndMax.second).toString("yyyy.MM.dd");
}

const QString RecordInfoGroup::patientName() const
{
    if (isEmpty())
        return QString();
    else
        return PatientDao::instance().findNameById(first().getPatientId());
}
