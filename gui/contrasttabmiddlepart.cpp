#include "contrasttabmiddlepart.h"

void ContrastTabMiddlePart::addFTest(){
    int n = rows.size();
    for(int i = 0; i < n; i++){
        rows[i]->addFTest();
    }
}

void ContrastTabMiddlePart::removeFTest(){
    int n = rows.size();
    for(int i = 0; i < n; i++){
        rows[i]->removeFTest();
    }
}


int ContrastTabMiddlePart::getNumberOfContrasts(){
    return rows.size();
}

void ContrastTabMiddlePart::addContrast(int evsNumber, int fTestsNumber){
    ContrastTabMiddlePartContent * currentContrast = new ContrastTabMiddlePartContent(this, rows.size()+1, evsNumber, fTestsNumber);
    rows.push_back(currentContrast);
    layout->addWidget(currentContrast);
}

void ContrastTabMiddlePart::removeContrast(){
    ContrastTabMiddlePartContent * currentContrast = rows[rows.size()-1];
    rows.remove(rows.size()-1);
    layout->removeWidget(currentContrast);
    delete currentContrast;
}

void ContrastTabMiddlePart::addOrRemoveEvs(int evsNumber){
    int n = rows.size();
    for(int i = 0; i < n; i++){
        rows[i]->addOrRemoveEvs(evsNumber);
    }
}

ContrastTabMiddlePart::ContrastTabMiddlePart(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout;
    rows = QVector<ContrastTabMiddlePartContent*>();
    this->setLayout(layout);
}
