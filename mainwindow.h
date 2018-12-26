#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDomDocument>
#include "./tools/xml/filetree.h"
namespace Ui {
class MainWindow;
}
QT_BEGIN_NAMESPACE
class QTreeWidget;
class QPlainTextEdit;
class QTreeWidgetItem;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void loadDirectory(const QString &directory);
private:
    Ui::MainWindow *ui;
    QWidget *pResultWidget;
    QWidget *pViewWidget;
    QTabWidget *pTabWidget;
    QTreeWidget *pTreeView;
    QMenuBar* pMenuBar;
    QToolBar* pToolBar;
    QStatusBar* pStatusBar;
    QPlainTextEdit *textEdit;
    QString curFile;
    const QXmlNamePool  m_namePool;
    const FileTree      m_fileTree;
    QXmlNodeModelIndex  m_fileNode;

protected:
    void CreateMenu();
    void CreateToolBar();
    void CreateStatusBar();
    void CreateCamera();
    void CreateTableView();
    void CreateTreeView();
    void listDom(QDomElement& docElem, QTreeWidgetItem* pItem);
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
    void removeSubTab(int index);
};

#endif // MAINWINDOW_H
