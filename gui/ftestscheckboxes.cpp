#include "ftestscheckboxes.h"

void FTestsCheckBoxes::addFTest(){
    QCheckBox * currentCheckBox = new QCheckBox;
    checkBoxes.push_back(currentCheckBox);
    layout->addWidget(currentCheckBox);
}

void FTestsCheckBoxes::removeFTest(){
    QCheckBox * currentCheckBox = checkBoxes[checkBoxes.size()-1];
    checkBoxes.remove(checkBoxes.size()-1);
    layout->removeWidget(currentCheckBox);
    delete currentCheckBox;
}

FTestsCheckBoxes::FTestsCheckBoxes(QWidget *parent, int fTestsNumber)
    : QWidget(parent)
{
    layout = new QHBoxLayout;
    checkBoxes = QVector<QCheckBox*>();\
    for(int i = 0; i < fTestsNumber; i++){
        addFTest();
    }
    this->setLayout(layout);
}
