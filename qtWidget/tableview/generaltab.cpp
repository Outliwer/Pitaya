#include "generaltab.h"
#include <QtWidgets>

GeneralTab::GeneralTab(QWidget *parent)
    : QWidget(parent)
{
    QLabel *fileNameLabel = new QLabel(tr("open a directory"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fileNameLabel);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}
