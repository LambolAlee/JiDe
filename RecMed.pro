QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/src

SOURCES += \
    main.cpp \
    src/data/formular.cpp \
    src/data/formularmodel.cpp \
    src/ui/launchwindow.cpp \
    src/widgets/drugeditor.cpp \
    src/widgets/formulartableform.cpp \
    src/widgets/formulartableofme.cpp

HEADERS += \
    src/data/formular.h \
    src/data/formularmodel.h \
    src/ui/launchwindow.h \
    src/widgets/drugeditor.h \
    src/widgets/formulartableform.h \
    src/widgets/formulartableofme.h

FORMS += \
    src/ui/launchwindow.ui \
    src/widgets/drugeditor.ui \
    src/widgets/formulartableform.ui

TRANSLATIONS += \
    RecMed_zh_CN.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
