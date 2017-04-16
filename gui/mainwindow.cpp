#include "mainwindow.h"
#include "contrasttab.h"
#include "evstab.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent)
{
   tabs = new QTabWidget;
   //TODO: will be taken from the command line, otherwise 1
   tabs->addTab(new EvsTab(this, 3), tr("EVs"));
   tabs->addTab(new ContrastTab(this), tr("Contrasts &&& F-tests"));
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
