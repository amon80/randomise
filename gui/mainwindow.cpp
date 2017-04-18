#include "mainwindow.h"
#include <QVBoxLayout>

void MainWindow::addOrRemoveEvs(int evsNumber){
    evsTab->addOrRemoveEvs(evsNumber);
    contrastTab->addOrRemoveEvs(evsNumber);
}


MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent)
{
   tabs = new QTabWidget;
   evsTab = new EvsTab(this);
   contrastTab = new ContrastTab(this);
   tabs->addTab(evsTab, tr("EVs"));
   tabs->addTab(contrastTab, tr("Contrasts &&& F-tests"));
   buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

   //TODO: Ok button will collect data and fire randomise
   connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
   connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

   QVBoxLayout * mainLayout = new QVBoxLayout;
   mainLayout->addWidget(tabs);
   mainLayout->addWidget(buttonBox);
   setLayout(mainLayout);
   setWindowTitle(tr("Randomise GUI"));
}

MainWindow::~MainWindow()
{
}
