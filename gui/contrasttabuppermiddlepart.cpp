#include "contrasttabuppermiddlepart.h"

void ContrastTabMiddleUpperPart::addOrRemoveEvs(int evsNumber){
    evsColumnsLabels->addOrRemoveEvs(evsNumber);
}


ContrastTabMiddleUpperPart::ContrastTabMiddleUpperPart(QWidget *parent)
    : QWidget(parent)
{
    layout = new QHBoxLayout;
    emptyLabel = new QLabel;
    contrastTitle = new QLabel;
    contrastTitle->setText("Title");
    evsColumnsLabels = new EvsColumnsLabels(this);
    fTestColumnsLabels = new FTestColumnsLabels(this);
    layout->addWidget(emptyLabel);
    layout->addWidget(contrastTitle);
    layout->addWidget(evsColumnsLabels);
    layout->addWidget(fTestColumnsLabels);
    this->setLayout(layout);
}
