QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/src

include(src/third-party/DBUtil/DBUtil.pri)
include(src/recordcard/recordcard.pri)

win32{
    LIBS += -lDwmapi -luser32
    SOURCES += src/ui/framelesswindow.cpp
    HEADERS += src/ui/framelesswindow.h
}

macx{
    CONFIG -= app_bundle
}

SOURCES += \
    main.cpp \
    src/patient/patientconst.cpp \
    src/patient/patientinfo.cpp \
    src/ui/examinewidget.cpp \
    src/ui/groupeditorwidget.cpp \
    src/ui/patientinfodock.cpp \
    src/ui/recordeditorarea.cpp \
    src/ui/recordmanager.cpp \
    src/ui/titlemenubar.cpp

HEADERS += \
    src/patient/patientconst.h \
    src/patient/patientinfo.h \
    src/ui/examinewidget.h \
    src/ui/groupeditorwidget.h \
    src/ui/patientinfodock.h \
    src/ui/recordeditorarea.h \
    src/ui/recordmanager.h \
    src/ui/titlemenubar.h

FORMS += \
    src/ui/examinewidget.ui \
    src/ui/groupeditorwidget.ui \
    src/ui/patientinfodock.ui \
    src/ui/recordmanager.ui \
    src/ui/titlemenubar.ui

TRANSLATIONS += \
    translations/RecMed_zh_CN.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
