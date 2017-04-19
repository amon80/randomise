#include <QVBoxLayout>
#include "evstab.h"

int EvsTab::getEv(int row, int col){
    return bottom->getEvs(row, col);
}

int EvsTab::getNumEvs(){
    return middle->getNumberOfEvs();
}

void EvsTab::addSubject(){
    bottom->addRow(middle->getNumberOfEvs());
}

void EvsTab::removeSubject(){
    bottom->removeRow();
}

void EvsTab::removeAllSubjects(){
    int n = bottom->getNRows();
    for(int i = 0; i < n; i++){
        bottom->removeRow();
    }
}

void EvsTab::addOrRemoveEvs(int evNumber){
    int oldEvNumber = middle->getNumberOfEvs();
    int difference = evNumber - oldEvNumber;
    if(difference > 0){
        for(int i = 0; i < difference; i++){
            middle->addEv();
            bottom->addEv();
        }
    }else{
        difference = -difference;
        for(int i = 0; i < difference; i++){
            middle->removeEv();
            bottom->removeEv();
        }
    }
}

EvsTab::EvsTab(QWidget *parent)
    : QWidget(parent)
{
    //Main layout
    QVBoxLayout * layout = new QVBoxLayout;
    this->setLayout(layout);;

    //Top part (EV spinbox)
    upperMiddle = new EvsTabUpperMiddlePart(this);
    layout->addWidget(upperMiddle);

    //Middle part (EV labels)
    middle = new EvsTabMiddlePart(this);
    layout->addWidget(middle);

    //Bottom part (Design Matrix)
    bottom = new EvsTabBottomPart(this);
    //for tests
    //bottom->addRow();
    layout->addWidget(bottom);

    //Propagating the signals received from the bottom layer to to upper layer
    QObject::connect(this, SIGNAL(valueChanged(int)), this->parentWidget(), SLOT(addOrRemoveEvs(int)));

}
