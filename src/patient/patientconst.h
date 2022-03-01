#ifndef PATIENTCONST_H
#define PATIENTCONST_H

#include <QMap>

namespace PatientConst
{
    extern QMap<int, QString> Sex;
    extern QMap<int, QString> Ethnicity;

    enum FieldType{ ToSex, ToEthnicity };

    QString toString(FieldType type, int k);
    int toIndex(FieldType type, const QString &v);
}

#endif // PATIENTCONST_H
