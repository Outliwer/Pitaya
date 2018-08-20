#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


protected:
    void CreateMenu();
    void CreateToolBar();
    void CreateStatusBar();
    void CreateCamera();



    virtual void mouseMoveEvent(QMouseEvent *event);

signals:
    void sigTest(QString fileName);

protected slots:

    void New();
    void Open();
    void Save();
    void SaveAs();
    void Undo();
    void Redo();
    void ProjectManager();
    void StatusBar();
    void Attribution();
    void Cloudmodel();
    void OSGimg();
    void AerialTriangulation();
    void Distance();
    void Options();
    void Panoramicimg();
    void Report();
    void DistanceReport();
    void SeeHelp();
    void SendFeedback();
    void TechnicalSupport();
    void readFile(QString fileName);
    void emitSig()
    {
        emit sigTest("fileName");
    }


};

#endif // MAINWINDOW_H
