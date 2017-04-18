#include <QVBoxLayout>
#include "evstab.h"

void EvsTab::addSubject(){
    bottom->addRow();
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


void EvsTab::setFileName(const QString& filename){
    top->setFileName(filename);
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
    this->setLayout(layout);

    //Top part (Load file)
    top = new EvsTabTopPart(this);
    layout->addWidget(top);

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
    QObject::connect(this, SIGNAL(openVmp()), this->parentWidget(), SLOT(openVmp()));
    QObject::connect(this, SIGNAL(clearAll()), this->parentWidget(), SLOT(clearAll()));

}
