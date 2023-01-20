QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    application.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    application.h \
    colorpalette.h \
    mainwindow.h \
    structs.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui
    
TRANSLATIONS += i18n/hellocomputer_de.ts \
                i18n/hellocomputer_en.ts

win32: LIBS += -luser32
unix|linux {
CONFIG += no_keywords
QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += glibmm-2.4 giomm-2.4
LIBS += -lglibmm-2.4 -lgiomm-2.4
}

RC_ICONS = res/hellocomputer.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    hellocomputer.qrc
