QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
TARGET = RecMed

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
    #CONFIG -= app_bundle
    QMAKE_INFO_PLIST = Info.plist
    QMAKE_POST_LINK += cp -r $$PWD/src/third-party/DBUtil/bin/.recmed $$OUT_PWD/$${TARGET}.app/Contents/MacOS
}

SOURCES += \
    main.cpp \
    src/recordnavigator/navigationcontroller.cpp \
    src/recordnavigator/recordsortfilterproxymodel.cpp \
    src/ui/patientinfodock.cpp \
    src/ui/recordeditorarea.cpp \
    src/ui/recordmanager.cpp \
    src/ui/recordnavigator/recordnavigator.cpp \
    src/ui/titlemenubar.cpp \
    src/util/flowlayout.cpp \
    src/util/util.cpp

HEADERS += \
    src/recordnavigator/navigationcontroller.h \
    src/recordnavigator/recordsortfilterproxymodel.h \
    src/ui/patientinfodock.h \
    src/ui/recordeditorarea.h \
    src/ui/recordmanager.h \
    src/ui/recordnavigator/recordnavigator.h \
    src/ui/titlemenubar.h \
    src/util/flowlayout.h \
    src/util/util.h

FORMS += \
    src/ui/patientinfodock.ui \
    src/ui/recordmanager.ui \
    src/ui/recordnavigator/recordnavigator.ui \
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
