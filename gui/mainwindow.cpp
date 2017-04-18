#include "mainwindow.h"
#include <QFileDialog>

void MainWindow::addOrRemoveEvs(int evsNumber){
    evsTab->addOrRemoveEvs(evsNumber);
    contrastTab->addOrRemoveEvs(evsNumber);
}

void MainWindow::openVmp(){
    QString filepath = QFileDialog::getOpenFileName(this, tr("Open vmp"), QDir::home().absolutePath(), tr("vmp Files (*.vmp)"));
    evsTab->setFileName(filepath);
    vmp.readvmp(filepath.toStdString().c_str());
    int n_subjects = vmp.getNrSubjects();
    for(int i = 0; i < n_subjects; i++){
        evsTab->addSubject();
    }
}

void MainWindow::clearAll(){
    evsTab->setFileName("");
    evsTab->removeAllSubjects();
    vmp = MyVmp();
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

   mainLayout = new QVBoxLayout;
   mainLayout->addWidget(tabs);
   mainLayout->addWidget(buttonBox);
   setLayout(mainLayout);
   setWindowTitle(tr("Randomise GUI"));

   vmp = MyVmp();
}

MainWindow::~MainWindow()
{
}
