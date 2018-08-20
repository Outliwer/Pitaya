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
    drawtwoball.cpp \
    pickhandler.cpp \
    panoball.cpp

HEADERS  += mainwindow.h \
    libs.h \
    osgview.h \
    drawtwoball.h \
    pickhandler.h \
    panoball.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

DISTFILES += \
    img/redo.png


#win32: LIBS += -LC:/OSG/OpenSceneGraph-3.6.1_lib_qt/lib/ -lOpenThreadsd

#INCLUDEPATH += C:/OSG/OpenSceneGraph-3.6.1_lib_qt/include
#DEPENDPATH += C:/OSG/OpenSceneGraph-3.6.1_lib_qt/include



win32: LIBS += -Llib/ -lOpenThreadsd

INCLUDEPATH += include
DEPENDPATH += include
