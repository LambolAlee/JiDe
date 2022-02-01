QT += core xml sql

CONFIG += c++20

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/bean/User.h \
    $$PWD/dao/UserDao.h \
    $$PWD/db/ConnectionPool.h \
    $$PWD/db/DBUtil.h \
    $$PWD/db/sqls.h \
    $$PWD/util/Config.h \
    $$PWD/util/Json.h \
    $$PWD/util/Singleton.h

SOURCES += \
    $$PWD/bean/User.cpp \
    $$PWD/dao/UserDao.cpp \
    $$PWD/db/ConnectionPool.cpp \
    $$PWD/db/DBUtil.cpp \
    $$PWD/db/sqls.cpp \
    $$PWD/util/Config.cpp \
    $$PWD/util/Json.cpp \

