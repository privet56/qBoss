#-------------------------------------------------
#
# Project created by QtCreator 2017-11-20T12:59:54
#
#-------------------------------------------------

QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qboss
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    tabbrowser.cpp \
    tabsettings.cpp \
    util/anibutton.cpp \
    util/cfg.cpp \
    util/emitter.cpp \
    util/f.cpp \
    util/logger.cpp \
    util/logwnd.cpp \
    util/str.cpp \
    util/tray.cpp \
    util/w.cpp \
    util/anilabel.cpp \
    controls/anioklabel.cpp \
    controllers/appservercontroller.cpp

HEADERS += \
        mainwindow.h \
    tabbrowser.h \
    tabsettings.h \
    res.rc \
    resource.h \
    util/anibutton.h \
    util/cfg.h \
    util/emitter.h \
    util/f.h \
    util/logger.h \
    util/logwnd.h \
    util/str.h \
    util/tray.h \
    util/w.h \
    util/anilabel.h \
    controls/anioklabel.h \
    controllers/appservercontroller.h

HEADERS  += resource.h

FORMS += \
        mainwindow.ui \
    tabbrowser.ui \
    tabsettings.ui

RESOURCES += \
    res.qrc

DISTFILES += \
    res/styles.css \
    ico.ico

DISTFILES += ico.ico

RC_FILE = res.rc
