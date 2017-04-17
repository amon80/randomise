#include "evscolumnslabels.h"

void EvsColumnsLabels::addOrRemoveEvs(int evNumber){
    int previousSize = evsLabels.size();
    int difference = evNumber - previousSize;
    if(difference > 0){
        for(int i = 0; i < difference; i++){
            QLabel * currentLabel = new QLabel;
            currentLabel->setText(QStringLiteral("EV%1").arg(evsLabels.size()+1));
            evsLabels.push_back(currentLabel);
            layout->addWidget(currentLabel);
        }
    }else{
        difference = -difference;
        for(int i = 0; i < difference; i++){
            QLabel * currentLabel = evsLabels[evsLabels.size()-1];
            evsLabels.remove(evsLabels.size()-1);
            layout->removeWidget(currentLabel);
            delete currentLabel;
        }
    }
}


EvsColumnsLabels::EvsColumnsLabels(QWidget *parent)
    : QWidget(parent)
{
    layout = new QHBoxLayout;
    evsLabels = QVector<QLabel*>();
    this->setLayout(layout);
}
