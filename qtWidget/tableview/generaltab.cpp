#include "generaltab.h"
#include <QtWidgets>

GeneralTab::GeneralTab(QWidget *parent)
    : QWidget(parent)
{
    QLabel *fileNameLabel = new QLabel(tr("File Name:"));
    QLabel *pathLabel = new QLabel(tr("Path:"));
    QLabel *sizeLabel = new QLabel(tr("Size:"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fileNameLabel);
    mainLayout->addWidget(pathLabel);
    mainLayout->addWidget(sizeLabel);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}
