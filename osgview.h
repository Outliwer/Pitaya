#include "drawtwoball.h"
#include "pickhandler.h"

#ifndef OSGVIEW_H
#define OSGVIEW_H

osgQt::GraphicsWindowQt* createGraphicsWindow( int x, int y, int w, int h )
{
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowDecoration = false;
    traits->x = x;
    traits->y = y;
    traits->width = w;
    traits->height = h;
    traits->doubleBuffer = true;

    return new osgQt::GraphicsWindowQt(traits.get());
}

class ViewerWidget : public QWidget
{
public:
    ViewerWidget( osgQt::GraphicsWindowQt* gw, osg::Node* scene )
    : QWidget()
    {
        const osg::GraphicsContext::Traits* traits = gw->getTraits();
        PickHandler* p=new PickHandler();
        osg::Camera* camera = _viewer.getCamera();
        camera->setGraphicsContext( gw );
        camera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );
        camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
        camera->setProjectionMatrixAsPerspective(
            30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f );

        _viewer.setSceneData( scene );
        _viewer.addEventHandler( new osgViewer::StatsHandler );
        _viewer.setCameraManipulator( new osgGA::TrackballManipulator );
        _viewer.setThreadingModel( osgViewer::Viewer::SingleThreaded );

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget( gw->getGLWidget() );
        setLayout( layout );

        connect( &_timer, SIGNAL(timeout()), this, SLOT(update()) );
        _timer.start( 40 );
    }

protected:
    virtual void paintEvent( QPaintEvent* event )
    { _viewer.frame(); }

    osgViewer::Viewer _viewer;
    QTimer _timer;
};

#endif // OSGVIEW_H
