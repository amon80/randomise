#include "contrasttabtoppart.h"

ContrastTabTopPart::ContrastTabTopPart(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout;
    contrastSpinBox = new QSpinBox;
    ftestsSpinBox = new QSpinBox;
    contrastSpinBoxLabel = new QLabel;
    ftestsSpinBoxLabel = new QLabel;
    contrastSpinBoxLabel->setText(tr("Contrasts"));
    ftestsSpinBoxLabel->setText(tr("F-Tests"));
    contrastSpinBox->setMinimum(0);
    contrastSpinBox->setValue(0);
    ftestsSpinBox->setMinimum(0);
    ftestsSpinBox->setValue(0);
    layout->addWidget(contrastSpinBoxLabel);
    layout->addWidget(contrastSpinBox);
    layout->addWidget(ftestsSpinBoxLabel);
    layout->addWidget(ftestsSpinBox);
    this->setLayout(layout);
    QObject::connect(ftestsSpinBox, SIGNAL(valueChanged(int)), this->parentWidget(), SLOT(ftestsValueChanged(int)));
    QObject::connect(contrastSpinBox, SIGNAL(valueChanged(int)), this->parentWidget(), SLOT(contrastsValueChanged(int)));
}
