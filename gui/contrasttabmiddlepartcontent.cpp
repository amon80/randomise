#include "contrasttabmiddlepartcontent.h"

int ContrastTabMiddlePartContent::getContrast(int evNumber){
    return evsSpinBoxes->getContrast(evNumber);
}


void ContrastTabMiddlePartContent::addFTest(){
    fTestsCheckBoxes->addFTest();
}

void ContrastTabMiddlePartContent::removeFTest(){
    fTestsCheckBoxes->removeFTest();
}

void ContrastTabMiddlePartContent::addOrRemoveEvs(int evsNumber){
    int previousEvsNumber = evsSpinBoxes->getEvsNumber();
    int difference = evsNumber - previousEvsNumber;
    if(difference > 0){
        for(int i = 0; i < difference; i++)
            evsSpinBoxes->addEv();
    }else{
        difference = -difference;
        for(int i = 0; i < difference; i++)
            evsSpinBoxes->removeEv();
    }
}


ContrastTabMiddlePartContent::ContrastTabMiddlePartContent(QWidget *parent, int contrastNumber, int evsNumber, int fTestsNumber)
    : QWidget(parent)
{
    layout = new QHBoxLayout;
    contrastLabel = new QLabel;
    QString labelText = QStringLiteral("C%1").arg(contrastNumber);
    contrastLabel->setText(labelText);
    contrastTitleLineEdit = new QLineEdit;
    evsSpinBoxes = new EvsSpinBoxes(this, evsNumber);
    fTestsCheckBoxes = new FTestsCheckBoxes(this, fTestsNumber);
    layout->addWidget(contrastLabel);
    layout->addWidget(contrastTitleLineEdit);
    layout->addWidget(evsSpinBoxes);
    layout->addWidget(fTestsCheckBoxes);
    this->setLayout(layout);
}
