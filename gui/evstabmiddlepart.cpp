#include "evstabmiddlepart.h"

int EvsTabMiddlePart::getNumberOfEvs(){
    return evLabels.size();
}

void EvsTabMiddlePart::addEv(){
    QLabel * currentLabel = new QLabel;
    currentLabel->setText(QStringLiteral("EV%1").arg(evLabels.size()+1));
    evLabels.push_back(currentLabel);
    layout->addWidget(evLabels[evLabels.size()-1]);
}

void EvsTabMiddlePart::removeEv(){
    QLabel * currentLabel = evLabels[evLabels.size()-1];
    evLabels.remove(evLabels.size()-1);
    layout->removeWidget(currentLabel);
    delete currentLabel;
}


EvsTabMiddlePart::EvsTabMiddlePart(QWidget *parent)
    : QWidget(parent)
{
    layout = new QHBoxLayout;
    emptyLabel = new QLabel;
    emptyLabel->setText(tr(""));
    groupLabel = new QLabel;
    groupLabel->setText(tr("Group"));
    evLabels = QVector<QLabel*>();
    layout->addWidget(emptyLabel);
    layout->addWidget(groupLabel);
    this->setLayout(layout);
}
