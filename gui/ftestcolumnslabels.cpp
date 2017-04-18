#include "ftestcolumnslabels.h"
#include <QString>

void FTestColumnsLabels::addFTest(){
    QLabel * currentLabel = new QLabel;
    QString labelText = QStringLiteral("F%1").arg(fTestsLabels.size()+1);
    currentLabel->setText(labelText);
    fTestsLabels.push_back(currentLabel);
    layout->addWidget(currentLabel);
}

void FTestColumnsLabels::removeFTest(){
    QLabel * currentLabel = fTestsLabels[fTestsLabels.size()-1];
    fTestsLabels.remove(fTestsLabels.size()-1);
    layout->removeWidget(currentLabel);
    delete currentLabel;
}

int FTestColumnsLabels::getNumberOfFTests(){
    return fTestsLabels.size();
}

FTestColumnsLabels::FTestColumnsLabels(QWidget *parent)
    : QWidget(parent)
{
    layout = new QHBoxLayout;
    fTestsLabels = QVector<QLabel*>();
    this->setLayout(layout);
}
