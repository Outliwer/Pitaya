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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OpenSceneGraph-3.6.1_lib_qt/lib/ -losg
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OpenSceneGraph-3.6.1_lib_qt/lib/ -losgd
else:unix: LIBS += -L$$PWD/../OpenSceneGraph-3.6.1_lib_qt/lib/ -losg

INCLUDEPATH += $$PWD/../OpenSceneGraph-3.6.1_lib_qt/include
DEPENDPATH += $$PWD/../OpenSceneGraph-3.6.1_lib_qt/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../osgQt_lib/lib/ -losgQt5
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../osgQt_lib/lib/ -losgQt5d
else:unix: LIBS += -L$$PWD/../osgQt_lib/lib/ -losgQt5

INCLUDEPATH += $$PWD/../osgQt_lib/include
DEPENDPATH += $$PWD/../osgQt_lib/include
