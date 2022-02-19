QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/src

include(src/third-party/DBUtil/DBUtil.pri)

win32 {
    LIBS += -lDwmapi -luser32
}

SOURCES += \
    main.cpp \
    src/formular/formular.cpp \
    src/formular/formularmodel.cpp \
    src/ui/launchwindow.cpp \
    src/widgets/drugeditor.cpp \
    src/widgets/examinewidget.cpp \
    src/widgets/formulartableform.cpp \
    src/widgets/formulartableofme.cpp \
    src/widgets/groupeditorwidget.cpp \
    src/ui/framelesswindow.cpp \
    src/widgets/titlemenubar.cpp

HEADERS += \
    src/formular/formular.h \
    src/formular/formularmodel.h \
    src/ui/launchwindow.h \
    src/widgets/drugeditor.h \
    src/widgets/examinewidget.h \
    src/widgets/formulartableform.h \
    src/widgets/formulartableofme.h \
    src/widgets/groupeditorwidget.h \
    src/ui/framelesswindow.h \
    src/widgets/titlemenubar.h

FORMS += \
    src/ui/launchwindow.ui \
    src/widgets/drugeditor.ui \
    src/widgets/examinewidget.ui \
    src/widgets/formulartableform.ui \
    src/widgets/groupeditorwidget.ui \
    src/widgets/titlemenubar.ui

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
