#include "filetabtoppart.h"

void FileTabTopPart::setFileName(const QString& fileName){
    fileLabel->setText(fileName);
}


FileTabTopPart::FileTabTopPart(QWidget *parent)
    : QWidget(parent)
{
    layout = new QHBoxLayout;
    fileLabel = new QLabel;
    fileLabel->setText("");
    loadFileButton = new QPushButton;
    loadFileButton->setText(tr("Load VMP"));
    clearButton = new QPushButton;
    clearButton->setText(tr("Clear"));
    layout->addWidget(fileLabel);
    layout->addWidget(loadFileButton);
    layout->addWidget(clearButton);
    this->setLayout(layout);
    QObject::connect(loadFileButton, SIGNAL(clicked(bool)), this->parentWidget(), SIGNAL(openVmp()));
    QObject::connect(clearButton, SIGNAL(clicked(bool)), this->parentWidget(), SIGNAL(clearAll()));
}
