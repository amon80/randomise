#include "evsspinboxes.h"

int EvsSpinBoxes::getEvsNumber(){
    return spinBoxes.size();
}

void EvsSpinBoxes::addEv(){
    QSpinBox * currentSpinBox = new QSpinBox;
    currentSpinBox->setMinimum(0);
    spinBoxes.push_back(currentSpinBox);
    layout->addWidget(currentSpinBox);
}

void EvsSpinBoxes::removeEv(){
    QSpinBox * currentSpinBox = spinBoxes[spinBoxes.size()-1];
    spinBoxes.remove(spinBoxes.size()-1);
    layout->removeWidget(currentSpinBox);
    delete currentSpinBox;
}


EvsSpinBoxes::EvsSpinBoxes(QWidget *parent, int evsNumber)
    : QWidget(parent)
{
    layout = new QHBoxLayout;
    spinBoxes = QVector<QSpinBox*>();
    for(int i = 0; i < evsNumber; i++){
        addEv();
    }
    this->setLayout(layout);
}
