#include "panoball.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <osg/TexEnv>


PanoBallDataSet::PanoBallDataSet(string filePath)
{
    ifstream ifs(filePath);
    string ss;
    m_panoBalls.clear();
    while(ifs>>ss)
    {
        PanoBall panoball;
        panoball.PhotoID=ss;

        ifs>>ss;panoball.X=StringToFloat(ss);
        ifs>>ss;panoball.Z=StringToFloat(ss);
        ifs>>ss;panoball.Y=-StringToFloat(ss);
        ifs>>ss;panoball.Omega=StringToFloat(ss);
        ifs>>ss;panoball.Kappa=StringToFloat(ss);
        ifs>>ss;panoball.Phi=-StringToFloat(ss);
        m_panoBalls.push_back(panoball);
    }
    ifs.close();
}

PanoBallDataSet::~PanoBallDataSet()
{

}

//读数据文件，返回一个节点
osg::ref_ptr<osg::Group> PanoBallDataSet::ReadFile()
{
    osg::ref_ptr<osg::Group> root=new osg::Group();

    root->addChild(LocatePanoBall(m_panoBalls[0],false));
    for(int i=1;i<m_panoBalls.size();++i)
    {
        root->addChild(LocatePanoBall(m_panoBalls[i],false));
    }
    return root.get();
}



//字符串转数字
float PanoBallDataSet::StringToFloat(string ss)
{
    stringstream strStream;
    float res;
    strStream << ss;
    strStream >> res;
    return res;
}

//创建一个全景球
osg::ref_ptr<osg::Geode> PanoBallDataSet::CreatePanoBall(PanoBall panoball,bool flag)
{

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();

    if(flag)//指示是否绘制纹理
    {
        //新建一个半径为5的球体
        geode->addDrawable(new osg::ShapeDrawable(
                               new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), 5.0f)));

        //https://www.qxqzx.com/contents/507.html

        //获取图片路径
        string imageFilePath;
        imageFilePath="PNGdata/"+panoball.PhotoID;
        osg::ref_ptr<osg::Image> image=osgDB::readImageFile(imageFilePath);
        image->flipHorizontal();

        geode->getOrCreateStateSet()->setTextureAttributeAndModes(
                    0,new osg::Texture2D(image));
    }
    else
    {
        //新建一个小的白球体
        geode->addDrawable(new osg::ShapeDrawable(
                               new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f),0.5f)));
    }
    return geode;
}

//给全景球定位姿，返回的是矩阵变换节点
osg::ref_ptr<osg::MatrixTransform> PanoBallDataSet::LocatePanoBall(PanoBall panoball, bool flag)
{

    osg::ref_ptr<osg::MatrixTransform> mt=new osg::MatrixTransform();
    mt->setName(panoball.PhotoID);

    osg::Matrix m1,m2,m3;
    m1.makeTranslate(osg::Vec3(panoball.X,panoball.Y,panoball.Z));
//    m2.makeRotate(panoball.Omega,osg::X_AXIS,
//                 panoball.Phi,osg::Y_AXIS,
//                 panoball.Kappa,osg::Z_AXIS);
    //仅作用于z轴
    m2.makeRotate(panoball.Kappa,osg::Z_AXIS);
    //m2.makeRotate(panoball.Phi,osg::Z_AXIS);

//    m1.makeTranslate(osg::Vec3(panoball.X,-panoball.Z,panoball.Y));
//    m2.makeRotate(panoball.Omega,osg::X_AXIS,
//                 -panoball.Kappa,osg::Y_AXIS,
//                 panoball.Phi,osg::Z_AXIS);
//    m3.makeRotate(-90.0f,osg::X_AXIS);

    mt->setMatrix(m2*m1);//先旋转再平移！！！


    mt->addChild(CreatePanoBall(panoball,flag));

    return mt;
}

//用一个节点构造一个带贴图的节点
osg::ref_ptr<osg::Node> PanoBallDataSet::LocatePanoBall(
        osg::ref_ptr<osg::Node> node, bool flag)
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();

    if(flag)//指示是否绘制纹理
    {
        //新建一个半径为5的球体
        geode->addDrawable(new osg::ShapeDrawable(
                               new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), 5.0f)));


        //https://www.qxqzx.com/contents/507.html

        //获取图片路径
        string imageFilePath;
        imageFilePath="PNGdata/"+node->getParent(0)->getName();
        osg::ref_ptr<osg::Image> image=osgDB::readImageFile(imageFilePath);
        image->flipHorizontal();

        geode->getOrCreateStateSet()->setTextureAttributeAndModes(
                    0,new osg::Texture2D(image));
    }
    else
    {
        //新建一个小的白球体
        geode->addDrawable(new osg::ShapeDrawable(
                               new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f),0.5f)));
    }
    return geode;
}

//场景添加光源
osg::ref_ptr<osg::Group> PanoBallDataSet::CreateLight(osg::ref_ptr<osg::Node> node)
{
    osg::ref_ptr<osg::Group> lightRoot=new osg::Group();
    lightRoot->addChild(node);

    //开启光照
    osg::ref_ptr<osg::StateSet> stateset=new osg::StateSet();
    stateset=lightRoot->getOrCreateStateSet();
    stateset->setMode(GL_LIGHTING,osg::StateAttribute::ON);
    stateset->setMode(GL_LIGHT0,osg::StateAttribute::ON);

    //计算包围盒
    osg::BoundingSphere bs;
    node->computeBound();
    bs=node->getBound();

    //创建一个light对象
    osg::ref_ptr<osg::Light> light=new osg::Light();
    light->setLightNum(0);
    //设置方向
    light->setDirection(osg::Vec3(0.0f,0.0f,-1.0f));
    //设置位置
    light->setPosition(osg::Vec4(bs.center().x(),bs.center().y(),bs.center().z()+bs.radius(),1.0f));
    //设置环境光的颜色
    light->setAmbient(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
    //设置散射光的颜色
    light->setDiffuse(osg::Vec4(1.0f,1.0f,1.0f,1.0f));

    //设置恒衰减指数
    light->setConstantAttenuation(1.0f);
    //设置线性衰减指数
    light->setLinearAttenuation(0.0f);
    //设置二次方衰减指数
    light->setQuadraticAttenuation(0.0f);

    //创建光源
    osg::ref_ptr<osg::LightSource> lightSource=new osg::LightSource();
    lightSource->setLight(light.get());

    lightRoot->addChild(lightSource.get());

    return lightRoot.get();
}
