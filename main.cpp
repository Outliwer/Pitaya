#include "mainwindow.h"
#include <QApplication>

#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Viewer>
#include <osgQt/GraphicsWindowQt>
#include <QVBoxLayout>
#include "libs.h"
//#include "osgview.h"

//int main( int argc, char** argv )
//{
//    QApplication app( argc, argv );
//    osgQt::GraphicsWindowQt* gw = createGraphicsWindow( 50, 50, 640, 480 );
//    osg::Node* scene = osgDB::readNodeFile("cow.osg");

//    ViewerWidget* widget = new ViewerWidget(gw, scene);
//    widget->setGeometry( 100, 100, 800, 600 );
//    widget->show();
//    return app.exec();
//}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
