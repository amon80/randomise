#include "contrasttabuppermiddlepart.h"

ContrastTabMiddleUpperPart::ContrastTabMiddleUpperPart(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout * middleTopLayout = new QHBoxLayout;
    QLabel * contrastNumberUpperLabel = new QLabel;
    contrastNumberUpperLabel->setText("Contrast");
    QLabel * contrastTitleUpperLabel = new QLabel;
    contrastTitleUpperLabel->setText("Title");
    middleTopLayout->addWidget(contrastNumberUpperLabel);
    middleTopLayout->addWidget(contrastTitleUpperLabel);
    this->setLayout(middleTopLayout);
}
