#include "optionstab.h"

Options OptionsTab::getOptions(){
    Options toReturn;
    toReturn.numPermutation = numberPermutationPart->getNumPermutation();
    toReturn.alpha = inferenceLevelPart->getInferenceLevel();
    toReturn.useTfce = useTfcePart->getUseTfce();
    toReturn.EE = useTfcePart->getEE();
    toReturn.ISE = useTfcePart->getISE();
    return toReturn;
}


OptionsTab::OptionsTab(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout;
    numberPermutationPart = new OptionsTabNumberPermutationPart(this);
    inferenceLevelPart = new OptionsTabInferenceLevelPart(this);
    useTfcePart = new OptionsTabUseTfcePart(this);
    layout->addWidget(numberPermutationPart);
    layout->addWidget(inferenceLevelPart);
    layout->addWidget(useTfcePart);
    this->setLayout(layout);
}
