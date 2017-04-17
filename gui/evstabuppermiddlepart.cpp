#include "evstabuppermiddlepart.h"

EvsTabUpperMiddlePart::EvsTabUpperMiddlePart(QWidget *parent) :
    QWidget(parent)
{
    layout = new QHBoxLayout;
    evLabel = new QLabel;
    evLabel->setText("Number of EVs");
    evNumberSpinBox = new QSpinBox;
    evNumberSpinBox->setMinimum(0);
    evNumberSpinBox->setValue(0);
    layout->addWidget(evLabel);
    layout->addWidget(evNumberSpinBox);
    QObject::connect(evNumberSpinBox, SIGNAL(valueChanged(int)), this->parentWidget(), SIGNAL(valueChanged(int)));
    this->setLayout(layout);
}
