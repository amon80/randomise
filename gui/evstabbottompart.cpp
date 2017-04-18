#include "evstabbottompart.h"

int EvsTabBottomPart::getNRows(){
    return rows.size();
}

void EvsTabBottomPart::addEv(){
    int nrows = rows.size();
    for(int i = 0; i < nrows; i++){
        rows[i]->addEv();
    }
}

void EvsTabBottomPart::removeEv(){
    int nrows = rows.size();
    for(int i = 0; i < nrows; i++){
        rows[i]->removeEv();
    }
}

void EvsTabBottomPart::addRow(){
    EvsTabBottomContent * newRow = new EvsTabBottomContent(this, QString::number(rows.size()+1));
    rows.push_back(newRow);
    layout->addWidget(newRow);
}

void EvsTabBottomPart::removeRow(){
    EvsTabBottomContent * rowToEliminate = rows[rows.size()-1];
    rows.remove(rows.size()-1);
    layout->removeWidget(rowToEliminate);
    delete rowToEliminate;
}

EvsTabBottomPart::EvsTabBottomPart(QWidget *parent)
    : QWidget(parent)
{
    rows = QVector<EvsTabBottomContent*>();
    layout = new QVBoxLayout;
    this->setLayout(layout);
}
