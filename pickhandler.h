#ifndef PICKHANDLER_H
#define PICKHANDLER_H
#endif // PICKHANDLER_H

#pragma once

#include "panoball.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

#include <osg/MatrixTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgFX/Scribe>

#include <osgGA/GUIEventHandler>

#include <osgUtil/Optimizer>

#include <iostream>

#include <osgGA/TrackballManipulator>
#include <osgGA/CameraManipulator>
#include <osgGA/NodeTrackerManipulator>


//对象选取事件处理器
class PickHandler:public osgGA::GUIEventHandler
{
public:
    PickHandler();
    ~PickHandler();

    bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
    void pick(osgViewer::Viewer* view, float x, float y);
    //鼠标位置
    float _mx;
    float _my;

    osg::ref_ptr<osg::Node> lastNode;//上一个被选中的节点
    osg::Matrixd lastMatrixd;//上一次的位姿矩阵
};

