#include "contrasttab.h"

void ContrastTab::addOrRemoveEvs(int evsNumber){
    uppermiddle->addOrRemoveEvs(evsNumber);
    //TODO:handle the contrasts
}

ContrastTab::ContrastTab(QWidget *parent) :
    QWidget(parent)
{
    //Main layout
    QVBoxLayout * layout = new QVBoxLayout;
    this->setLayout(layout);

    //Top part (Contrasts & F-tests spin boxes)
    top = new ContrastTabTopPart(this);
    layout->addWidget(top);

    //Upper-middle part: labels
    uppermiddle = new ContrastTabMiddleUpperPart(this);
    layout->addWidget(uppermiddle);

    //Middle part: contrasts and Ftests
    //TODO
}
