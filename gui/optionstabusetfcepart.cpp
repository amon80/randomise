#include "optionstabusetfcepart.h"

bool OptionsTabUseTfcePart::getUseTfce(){
    return useTfceCheckBox->isChecked();
}

bool OptionsTabUseTfcePart::getEE(){
    return EECheckBox->isChecked();
}

bool OptionsTabUseTfcePart::getISE(){
    return ISECheckBox->isChecked();
}

OptionsTabUseTfcePart::OptionsTabUseTfcePart(QWidget *parent)
    : QWidget(parent)
{
    layout = new QHBoxLayout;
    useTfceCheckBox = new QCheckBox(tr("Use Tfce"), this);
    EECheckBox = new QCheckBox(tr("Exchangeable Errors (EE)"), this);
    EECheckBox->setChecked(true);
    ISECheckBox = new QCheckBox(tr("Indipendent and Simmetric Errors (ISE)"), this);
    layout->addWidget(useTfceCheckBox);
    layout->addWidget(EECheckBox);
    layout->addWidget(ISECheckBox);
    this->setLayout(layout);
}
