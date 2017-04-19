#include "optionstabnumberpermutationpart.h"

int OptionsTabNumberPermutationPart::getNumPermutation(){
    return numberPermutationSpinBox->value();
}

OptionsTabNumberPermutationPart::OptionsTabNumberPermutationPart(QWidget *parent)
    : QWidget(parent)
{
    layout = new QHBoxLayout;
    numberPermutationLabel = new QLabel;
    numberPermutationLabel->setText(tr("Number of permutations:"));
    numberPermutationSpinBox = new QSpinBox;
    numberPermutationSpinBox->setMinimum(0);
    numberPermutationSpinBox->setMaximum(100000);
    numberPermutationSpinBox->setValue(2000);
    layout->addWidget(numberPermutationLabel);
    layout->addWidget(numberPermutationSpinBox);
    this->setLayout(layout);
}
