### `osg`控件的显示

* 对于实现一个`osg`嵌入到`qt`中的应用，开始便是在`qt`中加载可以显示`osg`图像的应用

* 首先是`QWidget`类，对于`qt`而言，该类是所有`Widget`部件的基类，因此定义一个`osg`的控件就应该从继承`QWidget`类开始（这里设置为`ViewerWidget`类）：

  ```c++
  class ViewerWidget : public QWidget{
  public:
      ViewerWidget( osgQt::GraphicsWindowQt* gw, osg::Node* scene )
      : QWidget(){
      
      }
  protected:
      virtual void paintEvent( QPaintEvent* event )
      {
          _viewer.frame();
      }
      osgViewer::Viewer _viewer;
      QTimer _timer;
  public:
      void addPickHandle()
      {
          _viewer.addEventHandler(new PickHandler());
      }
  };
  ```

* 在`ViewerWidget`类中使用`Viewer`对象、`QTimer`对象、`paintEvent`方法、`addPickHandle`方法

  * `Viewer`对象设置各种方法

    ```c++
    osg::Camera *camera=_viewer.getCamera();
            camera->setGraphicsContext( gw );
            camera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );
            camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
            camera->setProjectionMatrixAsPerspective(
                30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f );
    
            _viewer.addEventHandler( new osgViewer::StatsHandler );
            _viewer.setSceneData(scene);
            _viewer.setCameraManipulator( new osgGA::TrackballManipulator );
            _viewer.setThreadingModel( osgViewer::Viewer::SingleThreaded );
    ```

  * `QTimer`对象作为定时器和相关函数联系

    ```C++
    connect( &_timer, SIGNAL(timeout()), this, SLOT(update()) );
            _timer.start( 40 );
    ```

  * `paintEvent`方法使用`osg`的`frame()`函数

  * `addPickHandle`方法即绑定对象选取事件处理器

* 在`ViewerWidget`类的构造函数里面有`GraphicsWindowQt`对象和`Node`对象

  * 其中`GraphicsWindowQt`对象是包含一个与`osg`的渲染操作的图形上下文相关的`qt`小部件

    * 在`layout`加入该组件

      ```c++
      QVBoxLayout* layout = new QVBoxLayout;
              layout->addWidget( gw->getGLWidget() );
              setLayout( layout );
      ```

    * 而关于`GraphicsWindowQt`对象参数的设置

      * 通过`createGraphicsWindow`方法

        ```C++
        osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
            traits->windowDecoration = false;
            traits->x = x;
            traits->y = y;
            traits->width = w;
            traits->height = h;
            traits->doubleBuffer = true;
        
            return new osgQt::GraphicsWindowQt(traits.get());
        ```

      * 其中`Traits`类：用于定义基本窗体的参数

  * `Node`对象则是读取数据中已经存在的模型

* 在定义完这些类以后即可运行

  ```C++
  osg::ref_ptr<osgQt::GraphicsWindowQt> gw= createGraphicsWindow( 50, 50, 640, 480 );
  osg::ref_ptr<osg::Node> scene=osgDB::readNodeFile("cow.osg");
  ViewerWidget* widget = new ViewerWidget(gw, scene);
  widget->setGeometry( 100, 100, 800, 600 );
  this->setCentralWidget(widget);
  ```

* 相关文件：
  * [`osgview.h`](../osgView/osgview.h)
  * [`mainwindows.cpp`](../mainwindows.cpp)

