#include "bottomcontent.h"
#include <QLabel>
#include <QString>

BottomContent::BottomContent(QWidget *parent, int inputnumber, int evnumber)
    : QWidget(parent)
{
    evs = QVector<QSpinBox*>(evnumber);
    for(int i = 0; i < evnumber; i++)
        evs[i] = new QSpinBox;
    layout = new QHBoxLayout;
    QLabel * inputlabel = new QLabel(this);
    QString lblText = QStringLiteral("Input %1").arg(inputnumber);
    inputlabel->setText(lblText);
    groupSpinBox = new QSpinBox(this);
    groupSpinBox->setMinimum(1);
    layout->addWidget(inputlabel);
    layout->addWidget(groupSpinBox);
    for(int i = 0; i < evnumber; i++)
        layout->addWidget(evs[i]);
    this->setLayout(layout);
}

void BottomContent::addEv(){
    QSpinBox * toAdd = new QSpinBox;
    evs.push_back(toAdd);
    layout->addWidget(toAdd);
}

void BottomContent::removeEv(){
    int index = evs.size()-1;
    QSpinBox * toRemove = evs[index];
    evs.remove(index);
    layout->removeWidget(toRemove);
    delete toRemove;
}
