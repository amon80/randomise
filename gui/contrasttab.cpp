#include "contrasttab.h"

int ContrastTab::getNumberOfEvs(){
    return uppermiddle->getNumberOfEvs();
}

int ContrastTab::getNumberOfFTests(){
    return uppermiddle->getNumberOfFTests();
}

int ContrastTab::getNumberOfContrasts(){
    return middle->getNumberOfContrasts();
}

int ContrastTab::getContrast(int contrastNumber, int evNumber){
    return middle->getContrast(contrastNumber, evNumber);
}


void ContrastTab::ftestsValueChanged(int ftestsNumber){
    int previousFTests = uppermiddle->getNumberOfFTests();
    int difference = ftestsNumber - previousFTests;
    if(difference > 0){
        for(int i = 0; i < difference; i++){
            uppermiddle->addFTest();
            middle->addFTest();
        }
    }else{
        difference = -difference;
        for(int i = 0; i < difference; i++){
            uppermiddle->removeFTest();
            middle->removeFTest();
        }
    }
}

void ContrastTab::contrastsValueChanged(int contrastValue){
    int previousContrast = middle->getNumberOfContrasts();
    int difference = contrastValue - previousContrast;
    if(difference > 0){
        for(int i = 0; i < difference; i++){
            int evs = getNumberOfEvs();
            int fTests = getNumberOfFTests();
            middle->addContrast(evs, fTests);
        }
    }else{
        difference = -difference;
        for(int i = 0; i < difference; i++){
            middle->removeContrast();
        }
    }
}

void ContrastTab::addOrRemoveEvs(int evsNumber){
    uppermiddle->addOrRemoveEvs(evsNumber);
    middle->addOrRemoveEvs(evsNumber);
}

ContrastTab::ContrastTab(QWidget *parent) :
    QWidget(parent)
{
    //Main layout
    QVBoxLayout * layout = new QVBoxLayout;
    this->setLayout(layout);

    //Top part (Contrasts & F-tests spin boxes)
    top = new ContrastTabTopPart(this);
    layout->addWidget(top);

    //Upper-middle part: labels
    uppermiddle = new ContrastTabMiddleUpperPart(this);
    layout->addWidget(uppermiddle);

    //Middle part: contrasts spin boxes and Ftests checkboxes
    middle = new ContrastTabMiddlePart(this);
    layout->addWidget(middle);
}
