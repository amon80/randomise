#include "contrasttabuppermiddlepart.h"

int ContrastTabMiddleUpperPart::getNumberOfFTests(){
    return fTestColumnsLabels->getNumberOfFTests();
}

int ContrastTabMiddleUpperPart::getNumberOfEvs(){
    return evsColumnsLabels->getNumberOfEvs();
}

void ContrastTabMiddleUpperPart::addOrRemoveEvs(int evsNumber){
    evsColumnsLabels->addOrRemoveEvs(evsNumber);
}

void ContrastTabMiddleUpperPart::addFTest(){
    fTestColumnsLabels->addFTest();
}

void ContrastTabMiddleUpperPart::removeFTest(){
    fTestColumnsLabels->removeFTest();
}

ContrastTabMiddleUpperPart::ContrastTabMiddleUpperPart(QWidget *parent)
    : QWidget(parent)
{
    layout = new QHBoxLayout;
    emptyLabel = new QLabel;
    contrastTitleLabel = new QLabel;
    contrastTitleLabel->setText("Title");
    evsColumnsLabels = new EvsColumnsLabels(this);
    fTestColumnsLabels = new FTestColumnsLabels(this);
    layout->addWidget(emptyLabel);
    layout->addWidget(contrastTitleLabel);
    layout->addWidget(evsColumnsLabels);
    layout->addWidget(fTestColumnsLabels);
    this->setLayout(layout);
}
