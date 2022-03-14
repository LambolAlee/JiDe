#ifndef RECORDATTRDAO_H
#define RECORDATTRDAO_H

#include "util/Singleton.h"


class RecordAttrDao
{
    SINGLETON(RecordAttrDao)

public:
    QString fetchRecordDescription(int id);
};

#endif // RECORDATTRDAO_H
