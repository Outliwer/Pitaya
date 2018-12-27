#pragma once

#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QDockWidget>
#include <QTextEdit>
#include <QTextBrowser>
#include <QDebug>
#include <QTextStream>
#include <QToolBar>
#include <QStatusBar>
#include <QMouseEvent>
#include <QLabel>
#include <QPoint>
#include <QSize>
#include <QVector>
#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtXmlPatterns>
#include "libs.h"
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Viewer>
#include <osgQt/GraphicsWindowQt>
#include <QVBoxLayout>

#include <QFileDialog>

#include "./osgView/osgview.h"
#include "./qtWidget/treeview/treemodel.h"
#include "./osgWidget/panoBall/panoball.h"
#include "./osgHandler/pickhandler.h"
#include "./qtWidget/tableview/generaltab.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_fileTree(m_namePool),textEdit(new QPlainTextEdit)
{
    ui->setupUi(this);
    this->resize( QSize( 1200, 900 ));
    this->setWindowState(Qt::WindowMinimized);
    ui->splitter->setStretchFactor(0, 3);
    ui->splitter->setStretchFactor(1, 14);
    // 鼠标追踪
    //this->setMouseTracking(true);
    //ui->centralWidget->setMouseTracking(true);

    CreateMenu();
    CreateToolBar();
    CreateStatusBar();
    CreateTreeView();
    CreateTableView();

}

MainWindow::~MainWindow()
{

    delete ui;
}



void MainWindow::CreateTableView()
{
    pTabWidget = ui->tabWidget;
    m_pictureBox = new PictureBox();
    pTabWidget->addTab(new GeneralTab(), tr("Introduction"));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    pTabWidget->setTabsClosable(true);
    connect(pTabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));
}

void MainWindow::CreateTreeView()
{
    /*
    QStringList headers;
    headers << tr("Title");
    QFile file("./defaultTree.txt");
    file.open(QIODevice::ReadOnly);
    TreeModel *model = new TreeModel(headers, file.readAll());
    file.close();
    pTreeView->setModel(model);
    for (int column = 0; column < model->columnCount(); ++column)
        pTreeView->resizeColumnToContents(column);
    */
    pTreeWidget = ui->treeWidget;
    pTreeWidget->setColumnCount(1);
    QFile file("./defaultTree.txt");
    if(file.open(QIODevice::ReadOnly)){
        QDomDocument dom("WCM");
        if (dom.setContent(&file)){
            ui->treeWidget->clear();
            QDomElement docElem = dom.documentElement();
            listDom(docElem, NULL);
        }
    }
    file.close();
    connect(pTreeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)), this,SLOT(checkself(QTreeWidgetItem* ,int)));//检测点击事件，信号槽机制
    connect(pTreeWidget,SIGNAL(customContextMenuRequested(const QPoint&)), this,SLOT(popMenu(const QPoint&)));//检测鼠标右键
}

void MainWindow::listDom(QDomElement& docElem, QTreeWidgetItem* pItem){
    QDomNode node = docElem.firstChild();
    if(node.toElement().isNull()){
        pItem->setText (0,docElem.attribute("fileName"));
        pItem->setText (1,docElem.attribute("filePath"));
        pItem->setText (2,docElem.attribute("suffix"));
    }
    while(!node.isNull()){
        QDomElement element = node.toElement(); // try to convert the node to an element.
        if( !element.isNull() ){
            QTreeWidgetItem *item;
            if( pItem ){
                item = new QTreeWidgetItem(pItem);
            } else {
                item = new QTreeWidgetItem(ui->treeWidget);
            }
            // TODO:设置图标
            item->setText(0, element.attribute("fileName"));
            item->setText(1, element.attribute("filePath"));
            listDom(element, item);
            if( pItem ){
                pItem->addChild(item);
            } else {
                ui->treeWidget->addTopLevelItem(item);
            }
        }
        node = node.nextSibling();
    }
    return;
}

void MainWindow::checkself(QTreeWidgetItem* ,int){
    //qDebug() << "open on";
    QTreeWidgetItem* curItem=pTreeWidget->currentItem();  //获取当前被点击的节点
    if(curItem==NULL)return;
    QString filePath = curItem->text(1);
    QString fileName = curItem->text(0);
    QString fileSuffix = curItem->text(3);
    if (fileSuffix.compare("png") || fileSuffix.compare("jpg")){
        if (pQImage.load(filePath)){
            m_pictureBox->setImage(pQImage);
            m_pictureBox->setMode(PictureBox::PB_MODE::FIX_SIZE_CENTRED);
            pTabWidget->addTab(m_pictureBox, tr("read file %1.").arg(QDir::toNativeSeparators(fileName)));
            ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
        }
    } else {
        QFile file(filePath);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("Application"),
                                 tr("Cannot read file %1:\n%2.")
                                 .arg(QDir::toNativeSeparators(fileName), file.errorString()));
            return;
        }
        QTextStream in(&file);
        in.setCodec("UTF-8");
        #ifndef QT_NO_CURSOR
        QApplication::setOverrideCursor(Qt::WaitCursor);
        #endif
        textEdit->setPlainText(in.readAll());
        #ifndef QT_NO_CURSOR
        QApplication::restoreOverrideCursor();
        #endif
        pTabWidget->addTab(textEdit, tr("read file %1.").arg(QDir::toNativeSeparators(fileName)));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    }
}

void MainWindow::popMenu(const QPoint&){
    //qDebug() << "right on";
    QTreeWidgetItem* curItem=pTreeWidget->currentItem();  //获取当前被点击的节点
    if(curItem==NULL)return;           //这种情况是右键的位置不在treeItem的范围内，即在空白位置右击
    QString wellName = curItem->text(0);
    if(wellName != "wells"){
        QAction deleteWell(QString::fromLocal8Bit("&删除文件"),this);//删除井
        QAction reNameWell(QString ::fromLocal8Bit("&重命名文件"),this);//重命名井
        //在界面上删除该item
        connect(&deleteWell, SIGNAL(triggered()), this, SLOT(deleteItem()));
        connect(&reNameWell,SIGNAL(triggered()),this,SLOT(renameWell()));
        QMenu menu(ui->treeWidget);
        menu.addAction(&deleteWell);
        menu.addAction(&reNameWell);
        menu.exec(QCursor::pos());  //在当前鼠标位置显示
    }
}

void MainWindow::deleteItem(){
    /*
    root->removeChild(treeWidget->currentItem());
    if(myW != NULL){
        myW->setParent(NULL);
        ui.verticalLayout_4->removeWidget(myW);
    }
    //删除井数据文件
    QString dirPath = "../Data1/";
    dirPath.append(treeWidget->currentItem()->text(0));
    dirPath.append("/");
    DeleteDirectory(dirPath);
    */
}

void MainWindow::renameWell(){
    /*
    preName = treeWidget->currentItem()->text(0);
    prePath = "../Data1/";
    prePath.append(preName);
    ui.treeWidget->editItem(ui.treeWidget->currentItem());
    //t通过监控itemChanged事件来确定修改后的名字！！！！
    connect(treeWidget,SIGNAL(itemChanged( QTreeWidgetItem *,int )),this,SLOT(nameChanged(QTreeWidgetItem*  )));
    */
}

void MainWindow::DeleteDirectory(const QString &path){
    /*
    if (path.isEmpty())
            return false;
    QDir dir(path);
    if(!dir.exists())
        return true;
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList){
        if (fi.isFile())
            fi.dir().remove(fi.fileName());
        else
            DeleteDirectory(fi.absoluteFilePath());
    }
    return dir.rmpath(dir.absolutePath());
    */
}

void MainWindow::nameChanged(QTreeWidgetItem* item){
    /*
    //先重命名文件夹
    QString newName = treeWidget->currentItem()->text(0);
    QString newPath = "../Data1/";
    newPath.append(newName);
    QFile::rename(prePath,newPath);
    prePath = newPath.append("/");
    prePath.append(preName);
    prePath.append(".txt");
    //重命名井眼轨迹处理后的文件
    newPath.append("/");
    newPath.append(newName);
    newPath.append(".txt");
    QFile::rename(prePath,newPath);
    */
}

void MainWindow::CreateCamera(){

}

void MainWindow::CreateMenu()
{

    /*
    //增加初始选择的菜单项
    QDockWidget *dock=new QDockWidget(tr("DemoProject"),this);
    dock->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dock->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea);
    QPushButton *button= new QPushButton();
    QString strText = QStringLiteral("示例Demo，用于展示OSG最基本图像");
    button->setText(strText);
    dock->setWidget(button);

    addDockWidget(Qt::LeftDockWidgetArea,dock);
    */

    pMenuBar = ui->menuBar;   // 菜单栏
    //　File菜单
    QMenu* File = new QMenu("File");
//    QAction* New = new QAction(QIcon(QPixmap(":/img/new.png")), "New");
//    File->addAction(New);
    QAction* Open = new QAction(QIcon(QPixmap(":/img/open.png")), "Open");
    File->addAction(Open);
    QAction* Save = new QAction(QIcon(QPixmap(":/img/save.png")), "Save");
    File->addAction(Save);
    QAction* SaveAs = new QAction(QIcon(QPixmap(":/img/saveas.png")), "SaveAs");
    File->addAction(SaveAs);
    QAction* Exit = new QAction(QIcon(QPixmap(":/img/exit.png")), "Exit");
    File->addAction(Exit);
    pMenuBar->addMenu(File);

//    QObject::connect(New, SIGNAL(triggered(bool)), this, SLOT(New()));
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
    pToolBar = ui->mainToolBar;

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
    QObject::connect(SaveAs, SIGNAL(triggered(bool)), this, SLOT(SaveAs()));
    QObject::connect(Cloudmodel, SIGNAL(triggered(bool)), this, SLOT(Cloudmodel()));
    QObject::connect(OSGimg, SIGNAL(triggered(bool)), this, SLOT(OSGimg()));

}

void MainWindow::CreateStatusBar()
{
    //QStatusBar* pStatusBar = ui->statusBar;
    //pStatusBar->showMessage(tr("status"));

}



void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

    // 鼠标事件包含了全局坐标与本地坐标，在此只需要本地坐标即可
    QPointF pt = event->localPos();
    ui->statusBar->showMessage(QString("The program is running normally"));
    /*
    // 将坐标点格式化
    QString strShow = QString("Location:  X:%1 Y:%2").arg(pt.x()).arg(pt.y());
    // 在SatusBar中实时显示
    ui->statusBar->showMessage(strShow);
    */
}

void MainWindow::New()
{
}



void MainWindow::Open()
{
    const QString directoryName = QFileDialog::getExistingDirectory(this);
    if (!directoryName.isEmpty())
        loadDirectory(directoryName);
}

void MainWindow::loadDirectory(const QString &directory)
{
    Q_ASSERT(QDir(directory).exists());
    m_fileNode = m_fileTree.nodeFor(directory);
    QXmlQuery query(m_namePool);
    query.bindVariable("fileTree", m_fileNode);
    query.setQuery(QUrl("qrc:/text/wholeTree.xq"));

    QByteArray output;
    QBuffer buffer(&output);
    buffer.open(QIODevice::WriteOnly);

    QXmlFormatter formatter(query, &buffer);
    query.evaluateTo(&formatter);
    //处理这一次打开文件的docTemp
    QFile fileTemp("./temp.txt");
    if (fileTemp.open(QIODevice::ReadWrite | QFile::Truncate)) {
        QTextStream out(&fileTemp);
        out << output;
    }
    QDomDocument docTemp;
    fileTemp.close();
    QFile fileTempRead("./temp.txt");
    if(!fileTempRead.open(QFile::ReadOnly))
            return;
    if(!docTemp.setContent(&fileTempRead)){
        fileTempRead.close();
        return;
    }
    fileTempRead.close();
    //在原有的基本项目增加新的项目
    QFile file("./defaultTree.txt");
    QDomDocument doc;
    if(!doc.setContent(&file)){
        file.close();
        return;
    }
    file.close();
    QDomElement root=doc.documentElement();
    QDomElement rootTemp=docTemp.documentElement();
    root.appendChild(rootTemp);
    if(file.open(QIODevice::ReadWrite | QFile::Truncate)){
        QTextStream out_stream(&file);
        doc.save(out_stream,4); //缩进4格
    }
    file.close();
    CreateTreeView();
}

/**
  * remove the tab in the tabWidget
  */
void MainWindow::removeSubTab(int index)
{
    pTabWidget->removeTab(index);
}

void MainWindow::readFile(QString fileName)
{
    qDebug() << "Can not open";
        printf("fileName");
        QTextBrowser*Browser=new QTextBrowser;
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly|QFile::Text))
        qDebug() << "Can not open";
        QTextStream in(&file);
        Browser->setText(in.readAll());
        Browser->show();
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
    //导入配置文件，txt文件（osgPNGdata.txt）
    QString fileName =
            QFileDialog::getOpenFileName(
                this, tr("open file"), "",  tr("TxtFile(*.txt);;AllFile(*.*)"));

    osg::ref_ptr<osgQt::GraphicsWindowQt> gw = createGraphicsWindow( 50, 50, 640, 480 );

    //导入文件后，设置场景的节点
    PanoBallDataSet *panoBallDS=new PanoBallDataSet(fileName.toStdString());
    osg::ref_ptr<osg::Group> scene=panoBallDS->ReadFile();


    ViewerWidget* widget = new ViewerWidget(gw, scene);
    //绑定点击事件
    widget->addPickHandle();

    widget->setGeometry( 100, 100, 800, 600 );
    pTabWidget->addTab(widget, tr("Result"));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
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
