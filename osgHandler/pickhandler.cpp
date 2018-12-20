#pragma once

#include "pickhandler.h"


PickHandler::PickHandler()
{
    _mx=0.0f;
    _my=0.0f;
}

PickHandler::~PickHandler()
{

}

bool PickHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{

    //把view换成viewer试试
    osgViewer::Viewer* view=dynamic_cast<osgViewer::Viewer*>(&aa);
    if(!view)
        return false;

    switch(ea.getEventType())
    {
    //鼠标按下
    case(osgGA::GUIEventAdapter::PUSH):
    {
        //更新鼠标位置
        _mx=ea.getX();
        _my=ea.getY();
        break;
    }
    //鼠标释放
    case(osgGA::GUIEventAdapter::RELEASE):
    {
        if(_mx==ea.getX() && _my==ea.getY())
        {
            pick(view,ea.getX(),ea.getY());//执行对象选取
        }
        break;
    }
    default:
        break;
    }

    view=NULL;
    delete view;
    return false;
}

//对象选取事情处理器
void PickHandler::pick(osgViewer::Viewer* view, float x, float y)
{
    osg::ref_ptr<osg::Node> node=new osg::Node();
    osg::ref_ptr<osg::Group> parent=new osg::Group();
    //创建一个线段交集检测函数
    osgUtil::LineSegmentIntersector::Intersections intersections;

    if(view->computeIntersections(x,y,intersections))
    {
        osgUtil::LineSegmentIntersector::Intersection intersection=*intersections.begin();
        osg::NodePath& nodePath=intersection.nodePath;

        //得到选择的物体
        node=(nodePath.size()>=1)?nodePath[nodePath.size()-1]:0;
        parent=(nodePath.size()>=2)?dynamic_cast<osg::Group*>(nodePath[nodePath.size()-2]):0;

    }
    else
    {
        return;
    }
    //如果被选中，用带贴图的、有光照的节点替换这个节点，并把视点移动到该全景球的中心
    if(parent.get()&&node.get())
    {
        osg::ref_ptr<osg::MatrixTransform> parentAsMt=dynamic_cast<osg::MatrixTransform*>
                (parent.get());
        if(parentAsMt)
        {
            if(lastNode)
                lastNode->getParent(0)->replaceChild(
                            lastNode.get(),PanoBallDataSet::LocatePanoBall(lastNode,false));

            osg::ref_ptr<osg::Group> replaceNode=PanoBallDataSet::CreateLight(
                        PanoBallDataSet::LocatePanoBall(node));
//            osg::ref_ptr<osg::Node> replaceNode=
//                        PanoBallDataSet::LocatePanoBall(node);

            //把原始的白球节点换成有贴图的节点
            parent->replaceChild(node.get(),replaceNode);//都是矩阵变换节点的子节点
            lastNode=replaceNode.get();

            osg::ref_ptr<osgGA::TrackballManipulator> ballMani=
                    dynamic_cast<osgGA::TrackballManipulator*>(view->getCameraManipulator());
//            if(lastMatrixd.ptr()!=NULL)
//                ballMani->setByInverseMatrix(lastMatrixd);

            ballMani->setByInverseMatrix(view->getCamera()->getViewMatrix());

            ballMani->setDistance(3);
            ballMani->setCenter(parent->getBound().center());//设置操作器的中心
        }
    }
}

