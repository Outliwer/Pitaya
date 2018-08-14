#-------------------------------------------------
#
# Project created by QtCreator 2016-08-15T07:12:54
#
#-------------------------------------------------

QT += core
QT -= gui
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = menuToolbarStatusBar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    panoball.cpp \
    pickhandler.cpp

HEADERS  += mainwindow.h \
    libs.h \
    osgview.h \
    panoball.h \
    pickhandler.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

DISTFILES += \
    img/redo.png


win32: LIBS += -LC:/OSG/OpenSceneGraph-3.6.1_lib_qt/lib/ -lOpenThreadsd

INCLUDEPATH += C:/OSG/OpenSceneGraph-3.6.1_lib_qt/include
DEPENDPATH += C:/OSG/OpenSceneGraph-3.6.1_lib_qt/include
