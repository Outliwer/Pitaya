### `osg`控件与原生`qt`控件的联合使用

* 在[上文](./chapter1.md)中介绍了`osg`控件的显示，这里介绍一下怎么和当前的`qt`的原生控件结合使用

* 对于一个`qt`应用来说会存在一个`ui`界面，也就是常用的`mainwindow`，而对于和`qt`的原生控件的使用上无明显差别，因为`ViewerWidget`是`QWidget`的子类，直接按照`QWidget`对象进行调用即可

  ```c++
  MainWindow::MainWindow(QWidget *parent) :
      QMainWindow(parent),
      ui(new Ui::MainWindow)
  {
      ui->setupUi(this);
      this->resize( QSize( 800, 600 ));
      // 鼠标追踪
      this->setMouseTracking(true);
      ui->centralWidget->setMouseTracking(true);
  
      CreateMenu();
      CreateToolBar();
      CreateStatusBar();
  
      osg::ref_ptr<osgQt::GraphicsWindowQt>gw = createGraphicsWindow( 50, 50, 640, 480 );
      osg::ref_ptr<osg::Node> scene=osgDB::readNodeFile("cow.osg");
      ViewerWidget* widget = new ViewerWidget(gw, scene);
      widget->setGeometry( 100, 100, 800, 600 );
      this->setCentralWidget(widget);
  }
  ```

