QT += core xml sql

CONFIG += c++20

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/bean/User.h \
    $$PWD/bean/patient.h \
    $$PWD/bean/record.h \
    $$PWD/dao/UserDao.h \
    $$PWD/dao/patientdao.h \
    $$PWD/dao/recorddao.h \
    $$PWD/db/ConnectionPool.h \
    $$PWD/db/DBUtil.h \
    $$PWD/db/sqls.h \
    $$PWD/util/Config.h \
    $$PWD/util/Json.h \
    $$PWD/util/Singleton.h

SOURCES += \
    $$PWD/bean/User.cpp \
    $$PWD/bean/patient.cpp \
    $$PWD/bean/record.cpp \
    $$PWD/dao/UserDao.cpp \
    $$PWD/dao/patientdao.cpp \
    $$PWD/dao/recorddao.cpp \
    $$PWD/db/ConnectionPool.cpp \
    $$PWD/db/DBUtil.cpp \
    $$PWD/db/sqls.cpp \
    $$PWD/util/Config.cpp \
    $$PWD/util/Json.cpp \

