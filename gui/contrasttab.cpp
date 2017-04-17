#include "contrasttab.h"

void ContrastTab::addOrRemoveEvs(int evsNumber){
    //TODO
}

ContrastTab::ContrastTab(QWidget *parent) :
    QWidget(parent)
{
    //Main layout
    QVBoxLayout * layout = new QVBoxLayout;
    this->setLayout(layout);

    //Top part (Contrasts & F-tests)
    top = new ContrastTabTopPart(this);
    layout->addWidget(top);

    //Upper-middle part: labels
    uppermiddle = new ContrastTabMiddleUpperPart(this);
    layout->addWidget(uppermiddle);

    //Middle part: contrasts and Ftests
    //TODO
}
