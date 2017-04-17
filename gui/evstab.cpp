#include <QVBoxLayout>
#include <QFileDialog>
#include "evstab.h"

void EvsTab::openVmp(){
    QString filepath = QFileDialog::getOpenFileName(this, tr("Open Vmp"), "/home/marco", tr("Vmp Files (*.vmp)"));
    top->setFileName(filepath);
    //TODO
}

void EvsTab::clearAll(){
    top->setFileName("");
    //TODO
}

void EvsTab::addOrRemoveEvs(int evNumber){
    //First, take the number of previous ev
    //can be taken by labels or design matrix
    //equivalentely
    int oldEvNumber = middle->getNumberOfEvs();
    int difference = evNumber - oldEvNumber;
    if(difference > 0){
        //Case #1: Adding EV
        for(int i = 0; i < difference; i++){
            middle->addEv();
            bottom->addEv();
        }
    }else{
        //Case #2: Removing EV
        difference = -difference;
        for(int i = 0; i < difference; i++){
            middle->removeEv();
            bottom->removeEv();
        }
    }
    //Either case, signal should be propagated to main window, so contrast tab can be fixed
    //TODO
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

}
