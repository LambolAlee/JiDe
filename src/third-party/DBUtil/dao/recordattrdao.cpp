#include "recordattrdao.h"
#include "global.h"
#include "db/DBUtil.h"
#include "db/sqls.h"

#include <QString>

RecordAttrDao::RecordAttrDao() {}
RecordAttrDao::~RecordAttrDao() {}

QString RecordAttrDao::fetchRecordDescription(int id)
{
    QString sql = Sqls::instance().getSql(DaoNameSpace::RecordAttr, "fetchRecordDescription").arg(QString::number(id));
    QString desc = DBUtil::selectString(sql);
    return desc;
}
