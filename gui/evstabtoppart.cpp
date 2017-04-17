#include "evstabtoppart.h"

void EvsTabTopPart::setFileName(const QString& fileName){
    fileLabel->setText(fileName);
}


EvsTabTopPart::EvsTabTopPart(QWidget *parent)
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
    QObject::connect(loadFileButton, SIGNAL(clicked(bool)), this->parentWidget(), SLOT(openVmp()));
    QObject::connect(clearButton, SIGNAL(clicked(bool)), this->parentWidget(), SLOT(clearAll()));
}
