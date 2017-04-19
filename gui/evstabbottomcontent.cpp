#include "evstabbottomcontent.h"

int EvsTabBottomContent::getCol(int col){
    return evs[col]->value();
}

EvsTabBottomContent::EvsTabBottomContent(QWidget *parent, QString labelText, int nEvs)
    : QWidget(parent)
{
    layout = new QHBoxLayout;
    inputLabel = new QLabel;
    inputLabel->setText(labelText);
    groupSpinBox = new QSpinBox(this);
    groupSpinBox->setMinimum(1);
    layout->addWidget(inputLabel);
    layout->addWidget(groupSpinBox);
    evs = QVector<QSpinBox*>();
    for(int i = 0; i < nEvs; i++){
        addEv();
    }
    this->setLayout(layout);
}

void EvsTabBottomContent::addEv(){
    QSpinBox * toAdd = new QSpinBox;
    evs.push_back(toAdd);
    layout->addWidget(toAdd);
}

void EvsTabBottomContent::removeEv(){
    int index = evs.size()-1;
    QSpinBox * toRemove = evs[index];
    evs.remove(index);
    layout->removeWidget(toRemove);
    delete toRemove;
}
