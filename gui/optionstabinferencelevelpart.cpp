#include "optionstabinferencelevelpart.h"

float OptionsTabInferenceLevelPart::getInferenceLevel(){
    return inferenceLevelSpinBox->value();
}


OptionsTabInferenceLevelPart::OptionsTabInferenceLevelPart(QWidget *parent)
    : QWidget(parent)
{
    layout = new QHBoxLayout;
    inferenceLevelLabel = new QLabel;
    inferenceLevelLabel->setText(tr("Desired inference level:"));
    inferenceLevelSpinBox = new QDoubleSpinBox;
    inferenceLevelSpinBox->setMinimum(0);
    inferenceLevelSpinBox->setMaximum(1);
    inferenceLevelSpinBox->setValue(0.05);
    inferenceLevelSpinBox->setSingleStep(0.01);
    layout->addWidget(inferenceLevelLabel);
    layout->addWidget(inferenceLevelSpinBox);
    this->setLayout(layout);
}
