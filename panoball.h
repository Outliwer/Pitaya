#ifndef PANOBALL_H
#define PANOBALL_H
#endif // PANOBALL_H

#pragma once

#include "libs.h"

#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osgGA/NodeTrackerManipulator>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

#include<vector>

using namespace std;

//表示一个全景球
struct  PanoBall
{
    string PhotoID;
    float X, Y, Z, Omega, Phi, Kappa;
};

//表示全景球的数据集
class PanoBallDataSet
{
public:
    PanoBallDataSet(string filePath);
    ~PanoBallDataSet();
    float StringToFloat(string ss);
    osg::ref_ptr<osg::Group >ReadFile();

    vector<PanoBall> m_panoBalls;//储存全景球的数据集

    static osg::ref_ptr<osg::Geode> CreatePanoBall(PanoBall panoball,bool flag=true);//创建一个全景球
    static osg::ref_ptr<osg::MatrixTransform> LocatePanoBall(PanoBall panoball,bool flag=true);//给全景球定位姿
    static osg::ref_ptr<osg::Node> LocatePanoBall(osg::ref_ptr<osg::Node> node, bool flag=true);

    static osg::ref_ptr<osg::Group> CreateLight(osg::ref_ptr<osg::Node> node);//给相应的节点添加光照
};


