QT += xml sql

CONFIG += c++20

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/bean/common.h \
    $$PWD/bean/patient/patient.h \
    $$PWD/bean/patient/patientconst.h \
    $$PWD/bean/record.h \
    $$PWD/dao/patientdao.h \
    $$PWD/dao/recorddao.h \
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
    $$PWD/bean/record.cpp \
    $$PWD/dao/patientdao.cpp \
    $$PWD/dao/recorddao.cpp \
    $$PWD/db/ConnectionPool.cpp \
    $$PWD/db/DBUtil.cpp \
    $$PWD/db/sqls.cpp \
    $$PWD/util/Config.cpp \
    $$PWD/util/Json.cpp \

