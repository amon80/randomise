#include "filetab.h"

void FileTab::setFileName(const QString& filename){
    top->setFileName(filename);
}

FileTab::FileTab(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout;
    top = new FileTabTopPart(this);
    layout->addWidget(top);
    this->setLayout(layout);
    QObject::connect(this, SIGNAL(openVmp()), this->parentWidget(), SLOT(openVmp()));
    QObject::connect(this, SIGNAL(clearAll()), this->parentWidget(), SLOT(clearAll()));
}
