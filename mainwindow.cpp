#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QMenuBar>
#include <QMenu>

#include <QMessageBox>

#include <QDockWidget>
#include <QTextEdit>

#include <QToolBar>
#include <QStatusBar>
#include <QMouseEvent>
#include <QLabel>
#include <QPoint>
#include <QSize>

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

    QDockWidget *dock=new QDockWidget(tr("ProjectManager"),this);
    dock->setFeatures(QDockWidget::DockWidgetMovable);
    dock->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea);
    QTextEdit *te1=new QTextEdit();
    te1->setText(tr("ProjectManager"));
    dock->setWidget(te1);
    addDockWidget(Qt::LeftDockWidgetArea,dock);

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::CreateMenu()
{
    QMenuBar* pMenuBar = ui->menuBar;   // 菜单栏

    //　File菜单
    QMenu* File = new QMenu("File");
    QAction* New = new QAction(QIcon(QPixmap(":/img/new.png")), "New");
    File->addAction(New);
    QAction* Open = new QAction(QIcon(QPixmap(":/img/open.png")), "Open");
    File->addAction(Open);
    QAction* Save = new QAction(QIcon(QPixmap(":/img/save.png")), "Save");
    File->addAction(Save);
    QAction* SaveAs = new QAction(QIcon(QPixmap(":/img/saveas.png")), "SaveAs");
    File->addAction(SaveAs);
    QAction* Exit = new QAction(QIcon(QPixmap(":/img/exit.png")), "Exit");
    File->addAction(Exit);
    pMenuBar->addMenu(File);

    QObject::connect(New, SIGNAL(triggered(bool)), this, SLOT(New()));
    QObject::connect(Open, SIGNAL(triggered(bool)), this, SLOT(Open()));
    QObject::connect(Save, SIGNAL(triggered(bool)), this, SLOT(Save()));
    QObject::connect(SaveAs, SIGNAL(triggered(bool)), this, SLOT(SaveAs()));
    QObject::connect(Exit, SIGNAL(triggered(bool)), this, SLOT(close()));

    //Edit菜单
    QMenu* Edit = new QMenu("Edit");
    QAction* Undo = new QAction(QIcon(QPixmap(":/img/undo.png")), "Undo");
    Edit->addAction(Undo);
    QAction* Redo = new QAction(QIcon(QPixmap(":/img/redo.png")), "Redo");
    Edit->addAction(Redo);
    pMenuBar->addMenu(Edit);

    QObject::connect(Undo, SIGNAL(triggered(bool)), this, SLOT(Undo()));
    QObject::connect(Redo, SIGNAL(triggered(bool)), this, SLOT(Redo()));

    //View菜单
    QMenu* View = new QMenu("View");
    QAction* ProjectManager = new QAction(QIcon(QPixmap(":/img/ProjectManager.png")), "ProjectManager");
    View->addAction(ProjectManager);
    QAction* StatusBar = new QAction(QIcon(QPixmap(":/img/statusbar.png")), "StatusBar");
    View->addAction(StatusBar);
    QAction* Attribution = new QAction(QIcon(QPixmap(":/img/attribution.png")), "Attribution");
    View->addAction(Attribution);
    pMenuBar->addMenu(View);

    QObject::connect(ProjectManager, SIGNAL(triggered(bool)), this, SLOT(ProjectManager()));
    QObject::connect(StatusBar, SIGNAL(triggered(bool)), this, SLOT(StatusBar()));
    QObject::connect(Attribution, SIGNAL(triggered(bool)), this, SLOT(Attribution()));

    //generate菜单
    QMenu* Generate = new QMenu("Generate");
    QAction* Cloudmodel = new QAction(QIcon(QPixmap(":/img/cloudmodel.png")), "Three-site cloud model");
    Generate->addAction(Cloudmodel);
    QAction* OSGimg = new QAction(QIcon(QPixmap(":/img/OSGimg.png")), "OSGimg");
    Generate->addAction(OSGimg);
    pMenuBar->addMenu(Generate);

    QObject::connect(Cloudmodel, SIGNAL(triggered(bool)), this, SLOT(Cloudmodel()));
    QObject::connect(OSGimg, SIGNAL(triggered(bool)), this, SLOT(OSGimg()));

    //tool菜单
    QMenu* Tool = new QMenu("Tool");
    QAction* AerialTriangulation  = new QAction(QIcon(QPixmap(":/img/aerialtriangulation.png")), "Aerial triangulation");
    Tool->addAction(AerialTriangulation);
    QAction* Distance = new QAction(QIcon(QPixmap(":/img/distance.png")), "Distance between two points");
    Tool->addAction(Distance);
    QAction* Options = new QAction(QIcon(QPixmap(":/img/options.png")), "Options");
    Tool->addAction(Options);
    pMenuBar->addMenu(Tool);

    QObject::connect(AerialTriangulation, SIGNAL(triggered(bool)), this, SLOT(AerialTriangulation()));
    QObject::connect(Distance, SIGNAL(triggered(bool)), this, SLOT(Distance()));
    QObject::connect(Options, SIGNAL(triggered(bool)), this, SLOT(Options()));

    //check菜单
    QMenu* Check = new QMenu("Check");
    QAction* Panoramicimg  = new QAction(QIcon(QPixmap(":/img/Panoramicimage.png")), " Panoramic image");
    Check->addAction(Panoramicimg);
    QAction* Report = new QAction(QIcon(QPixmap(":/img/aerialtriangulation.png")), "Aerial triangulation report");
    Check->addAction(Report);
    QAction* DistanceReport = new QAction(QIcon(QPixmap(":/img/distance.png")), "Two-points distance report");
    Check->addAction(DistanceReport);
    pMenuBar->addMenu(Check);

    QObject::connect(Panoramicimg, SIGNAL(triggered(bool)), this, SLOT(Panoramicimg()));
    QObject::connect(Report, SIGNAL(triggered(bool)), this, SLOT(Report()));
    QObject::connect(DistanceReport, SIGNAL(triggered(bool)), this, SLOT(DistanceReport()));


    //help菜单
    QMenu* Help = new QMenu("Help");
    QAction* SeeHelp  = new QAction(QIcon(QPixmap(":/img/seehelp.png")), "See help");
    Help->addAction(SeeHelp);
    QAction* SendFeedback = new QAction(QIcon(QPixmap(":/img/sendfeedback.png")), "Send feedback");
    Help->addAction(SendFeedback);
    QAction* TechnicalSupport = new QAction(QIcon(QPixmap(":/img/technicalsupport.png")), "Technical support");
    Help->addAction(TechnicalSupport);
    pMenuBar->addMenu(Help);

    QObject::connect(SeeHelp, SIGNAL(triggered(bool)), this, SLOT(SeeHelp()));
    QObject::connect(SendFeedback, SIGNAL(triggered(bool)), this, SLOT(SendFeedback()));
    QObject::connect(TechnicalSupport, SIGNAL(triggered(bool)), this, SLOT(TechnicalSupport()));


}


void MainWindow::CreateToolBar()
{
    // 获取到ToolBar
    QToolBar* pToolBar = ui->mainToolBar;

    // Action
    QAction* Undo= new QAction(QIcon(QPixmap(":/img/undo.png")),"Undo");;
    QAction* Redo = new QAction(QIcon(QPixmap(":/img/redo.png")),"Redo");
    QAction* New = new QAction(QIcon(QPixmap(":/img/new.png")),"New");
    QAction* Open = new QAction(QIcon(QPixmap(":/img/open.png")),"Open");
    QAction* Save = new QAction(QIcon(QPixmap(":/img/save.png")),"Save");
    QAction* SaveAs = new QAction(QIcon(QPixmap(":/img/saveas.png")),"SaveAs");
    QAction* Cloudmodel = new QAction(QIcon(QPixmap(":/img/cloudmodel.png")),"Genarate three-site cloud model");
    QAction* OSGimg = new QAction(QIcon(QPixmap(":/img/OSGimg.png")),"Generate OSGimg");

    // 将Action添加至ToolBar中
    pToolBar->addAction(Undo);
    pToolBar->addAction(Redo);
    pToolBar->addAction(New);
    pToolBar->addAction(Open);
    pToolBar->addAction(Save);
    pToolBar->addAction(SaveAs);
    pToolBar->addAction(Cloudmodel);
    pToolBar->addAction(OSGimg);

    // 将Action与槽函数关联
    QObject::connect(Undo, SIGNAL(triggered(bool)), this, SLOT(Undo()));
    QObject::connect(Redo, SIGNAL(triggered(bool)), this, SLOT(Redo()));
    QObject::connect(New, SIGNAL(triggered(bool)), this, SLOT(New()));
    QObject::connect(Open, SIGNAL(triggered(bool)), this, SLOT(Open()));
    QObject::connect(Save, SIGNAL(triggered(bool)), this, SLOT(Save()));
    QObject::connect(SaveAs, SIGNAL(triggered(bool)), this, SLOT(SavaAs()));
    QObject::connect(Cloudmodel, SIGNAL(triggered(bool)), this, SLOT(Cloudmodel()));
    QObject::connect(OSGimg, SIGNAL(triggered(bool)), this, SLOT(OSGimg()));

}

void MainWindow::CreateStatusBar()
{
    QStatusBar* pStatusBar = ui->statusBar;
    pStatusBar->showMessage(tr("status"));

}



void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // 鼠标事件包含了全局坐标与本地坐标，在此只需要本地坐标即可
    QPointF pt = event->localPos();
    // 将坐标点格式化
    QString strShow = QString("Location:  X:%1 Y:%2").arg(pt.x()).arg(pt.y());
    // 在SatusBar中实时显示
    ui->statusBar->showMessage(strShow);
}

void MainWindow::New()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::Open()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::Save()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::SaveAs()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::Undo()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::Redo()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::ProjectManager()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::StatusBar()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::Attribution()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::Cloudmodel()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::OSGimg()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::AerialTriangulation()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::Distance()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::Options()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::Panoramicimg()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::Report()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::DistanceReport()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::SeeHelp()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::SendFeedback()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

void MainWindow::TechnicalSupport()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.exec();
}

