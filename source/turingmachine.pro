QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gui/sub_widgets/managerprojectform.cpp \
    main.cpp \
    core/turingclass.cpp \
    gui/mainwindow.cpp \
    gui/sub_widgets/createprojectform.cpp \
    gui/sub_widgets/inputparametersform.cpp \
    gui/sub_widgets/input_frames/cellform.cpp \
    gui/sub_widgets/input_frames/letterform.cpp \
    gui/sub_widgets/workingmachineform.cpp \
    gui/sub_widgets/scene.cpp \
    project/jsonparserclass.cpp \
    project/projectfileclass.cpp

HEADERS += \
    core/Action.h \
    core/turingclass.h \
    gui/mainwindow.h \
    gui/sub_widgets/createprojectform.h \
    gui/sub_widgets/inputparametersform.h \
    gui/sub_widgets/input_frames/cellform.h \
    gui/sub_widgets/input_frames/letterform.h \
    gui/sub_widgets/managerprojectform.h \
    gui/sub_widgets/workingmachineform.h \
    gui/sub_widgets/scene.h \
    project/jsonparserclass.h \
    project/projectfileclass.h

FORMS += \
    gui/mainwindow.ui \
    gui/sub_widgets/createprojectform.ui \
    gui/sub_widgets/inputparametersform.ui \
    gui/sub_widgets/input_frames/cellform.ui \
    gui/sub_widgets/input_frames/letterform.ui \
    gui/sub_widgets/managerprojectform.ui \
    gui/sub_widgets/workingmachineform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
