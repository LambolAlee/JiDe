QT += xml sql

CONFIG += c++20

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/bean/common.h \
    $$PWD/bean/patient/patient.h \
    $$PWD/bean/patient/patientconst.h \
    $$PWD/bean/recordinfo.h \
    $$PWD/dao/global.h \
    $$PWD/dao/patientdao.h \
    $$PWD/dao/recordattrdao.h \
    $$PWD/dao/recordinfodao.h \
    $$PWD/db/ConnectionPool.h \
    $$PWD/db/DBUtil.h \
    $$PWD/db/sqls.h \
    $$PWD/util/Config.h \
    $$PWD/util/Json.h \
    $$PWD/util/Singleton.h

SOURCES += \
    $$PWD/bean/common.cpp \
    $$PWD/bean/patient/patient.cpp \
    $$PWD/bean/patient/patientconst.cpp \
    $$PWD/bean/recordinfo.cpp \
    $$PWD/dao/patientdao.cpp \
    $$PWD/dao/recordattrdao.cpp \
    $$PWD/dao/recordinfodao.cpp \
    $$PWD/db/ConnectionPool.cpp \
    $$PWD/db/DBUtil.cpp \
    $$PWD/db/sqls.cpp \
    $$PWD/util/Config.cpp \
    $$PWD/util/Json.cpp \

