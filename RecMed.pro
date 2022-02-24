QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/src

include(src/third-party/DBUtil/DBUtil.pri)
include(src/recordcard/recordcard.pri)

win32 {
    LIBS += -lDwmapi -luser32
}

SOURCES += \
    main.cpp \
    src/ui/launchwindow.cpp \
    src/ui/examinewidget.cpp \
    src/ui/groupeditorwidget.cpp \
    src/ui/framelesswindow.cpp \
    src/ui/titlemenubar.cpp

HEADERS += \
    src/ui/launchwindow.h \
    src/ui/examinewidget.h \
    src/ui/groupeditorwidget.h \
    src/ui/framelesswindow.h \
    src/ui/titlemenubar.h

FORMS += \
    src/ui/launchwindow.ui \
    src/ui/examinewidget.ui \
    src/ui/groupeditorwidget.ui \
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
