#include "evstab.h"
#include "bottomcontent.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>

void EvsTab::addOrRemoveEV(int evSpinBoxValue){
    //add EV
    if(evSpinBoxValue > this->evnumber){
        int difference = evSpinBoxValue - this->evnumber;
        for(int j = 0; j < difference; j++){
            QLabel * currentLabel = new QLabel;
            QString currentLabelText = QStringLiteral("EV%1").arg(this->evnumber+j+1);
            currentLabel->setText(currentLabelText);
            evLabels.push_back(currentLabel);
            middleLayout->addWidget(currentLabel);
            for(int i = 0; i < num_of_subjects; i++)
                rows[i]->addEv();
        }
    }
    //remove EV
    else{
        int difference = this->evnumber - evSpinBoxValue;
        for(int j = 0; j < difference; j++){
            QLabel * toRemove = evLabels[this->evnumber-1-j];
            middleLayout->removeWidget(toRemove);
            evLabels.remove(this->evnumber-1-j);
            delete toRemove;
            for(int i = 0; i < num_of_subjects; i++)
                rows[i]->removeEv();
        }
    }
    this->evnumber = evSpinBoxValue;
}

void EvsTab::openvmp(){
    QString filename = QFileDialog::getOpenFileName(this, tr("Open VMP"), "/home/marco", tr("VMP Files (*.vmp)"));
    //TODO: actual reading here
    fileEdit->setText(filename);
}

EvsTab::EvsTab(QWidget *parent, int num_of_subjects)
    : QWidget(parent),
      num_of_subjects(num_of_subjects)
{
    //Main layout
    QVBoxLayout * layout = new QVBoxLayout;
    this->setLayout(layout);

    //Top part (Load file)
    QWidget * topFile = new QWidget(this);
    QHBoxLayout * topFileLayout = new QHBoxLayout;
    fileEdit = new QLineEdit;
    fileEdit->setReadOnly(true);
    fileEdit->setPlaceholderText(tr("Loaded file name will appear here."));
    QPushButton * loadFile = new QPushButton;
    loadFile->setText(tr("Load VMP"));
    topFileLayout->addWidget(fileEdit);
    topFileLayout->addWidget(loadFile);
    topFile->setLayout(topFileLayout);
    layout->addWidget(topFile);

    //Top part (EVs)
    QWidget * top = new QWidget(this);
    QHBoxLayout * topLayout = new QHBoxLayout;
    QLabel * evlabel = new QLabel;
    evlabel->setText("Number of EVs");
    evnumber = 1;
    evnumberSpinbox = new QSpinBox;
    evnumberSpinbox->setMinimum(1);
    evnumberSpinbox->setValue(1);
    topLayout->addWidget(evlabel);
    topLayout->addWidget(evnumberSpinbox);
    top->setLayout(topLayout);
    layout->addWidget(top);

    //Middle part
    labelRow = new QWidget(this);
    middleLayout = new QHBoxLayout;
    QLabel * inputLabel = new QLabel;
    inputLabel->setText(tr("Inputs"));
    middleLayout->addWidget(inputLabel);
    QLabel * groupLabel = new QLabel;
    groupLabel->setText(tr("Group"));
    middleLayout->addWidget(groupLabel);
    evLabels = QVector<QLabel*>(evnumberSpinbox->value());
    for(int i = 0; i < evnumberSpinbox->value(); i++){
        QLabel * currentLabel = new QLabel;
        QString currentLabelText = QStringLiteral("EV%1").arg(i+1);
        currentLabel->setText(currentLabelText);
        evLabels[i] = currentLabel;
        middleLayout->addWidget(currentLabel);
    }
    labelRow->setLayout(middleLayout);
    layout->addWidget(labelRow);

    //Bottom part
    QWidget * bottom = new QWidget(this);
    QVBoxLayout * bottomLayout = new QVBoxLayout;
    rows = QVector<BottomContent*>(num_of_subjects);
    for(int i = 0; i < num_of_subjects; i++){
        rows[i] = new BottomContent(this, i+1, evnumberSpinbox->value());
        bottomLayout->addWidget(rows[i]);
    }
    bottom->setLayout(bottomLayout);
    layout->addWidget(bottom);

    //connecting
    QObject::connect(evnumberSpinbox, SIGNAL(valueChanged(int)),
                     this,  SLOT(addOrRemoveEV(int)));
    QObject::connect(loadFile, SIGNAL(clicked(bool)), this, SLOT(openvmp()));

}
