QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cellform.cpp \
    createprojectform.cpp \
    inputparametersform.cpp \
    letterform.cpp \
    main.cpp \
    mainwindow.cpp \
    turingclass.cpp

HEADERS += \
    cellform.h \
    createprojectform.h \
    inputparametersform.h \
    letterform.h \
    mainwindow.h \
    turingclass.h

FORMS += \
    cellform.ui \
    createprojectform.ui \
    inputparametersform.ui \
    letterform.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
