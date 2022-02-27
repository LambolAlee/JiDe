#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <QDate>


class Patient
{
public:
    int id;
    QString patient_name;
    int sex;
    int flag;
    QDate birthday;
    int ethnicity;
    QString native_place;
    QString birth_place;
    QString career;
};

#endif // PATIENT_H
