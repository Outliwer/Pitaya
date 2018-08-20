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

//#include "pickhandler.h"
//#include <osg/PositionAttitudeTransform>
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


//    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
//    PickHandler* p=new PickHandler();
//    viewer->addEventHandler(p);
//    osg::ref_ptr<osg::Group> root=new osg::Group();

//    //读取模型
//    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("cow.osg");

//    //创建位置变换位置节点pat2
//    osg::ref_ptr<osg::PositionAttitudeTransform> pat2=new osg::PositionAttitudeTransform();
//    pat2->setPosition(osg::Vec3(10.0f,0.0f,0.0f));
//    pat2->addChild(node.get());

//    root->addChild(node.get());
//    root->addChild(pat2.get());

//    printf_s("X:%lf,Y:%lf,Z:%lf\n\n",node->getBound().center().x(),
//             node->getBound().center().y(),
//             node->getBound().center().z());
//    printf_s("X:%lf,Y:%lf,Z:%lf",pat2->getBound().center().x(),
//             pat2->getBound().center().y(),
//             pat2->getBound().center().z());

//    viewer->setUpViewInWindow(100,100,800,600);

//    //优化场景数据
//    osgUtil::Optimizer op;
//    op.optimize(root.get());

//    viewer->setSceneData(root.get());
//    viewer->realize();
//    viewer->run();

//    return 0;
}
