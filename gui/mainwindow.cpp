#include "mainwindow.h"
#include "statisticalmap4d.h"
#include "multyrowarray.h"
#include "mystat.h"
#include "randomise.h"
#include "Eigen/Dense"
#include <QFileDialog>

inline QString withoutExtension(const QString & fileName) {
    return fileName.left(fileName.lastIndexOf("."));
}

void MainWindow::collectDataAndFire(){
    //Initializing 4D map of data

    int dimX = vmp.getDimX();
    int dimY = vmp.getDimY();
    int dimZ = vmp.getDimZ();
    int dim = dimX * dimY * dimZ;
    int num_of_maps = vmp.getNrMaps();
    StatisticalMap4D Y(dimX, dimY, dimZ, num_of_maps);

    //Filling the initialized 4D map
    for(int v = 0; v < dim; v++){
        for (int i = 0; i < num_of_maps; i++){
            float value = vmp[i][v];
            Y[v](i) = value;
        }
    }

    //Collect options from the optionTab (useTfce, desired inference level, maxnumber of permutations, EE or ISE or both)
    Options options = optionsTab->getOptions();

    //Collect data(design matrix, groups) from the evsTab
    int numEvs = evsTab->getNumEvs();
    if(numEvs == 0)
        return;
    Eigen::MatrixXd M = Eigen::MatrixXd::Zero(num_of_maps, numEvs);
    //Filling the design matrix
    for(int i = 0; i < num_of_maps; i++){
        for(int j = 0; j < numEvs; j++){
            M(i,j) = evsTab->getEv(i,j);
        }
    }

    //Collect data(contrasts, ftests, and their names) from the contrastTab
    int numContrast = contrastTab->getNumberOfContrasts();
    if(numContrast == 0)
        return;
    std::vector<Eigen::MatrixXd> C(numContrast);
    for(int i = 0; i < numContrast; i++){
        C[i] = Eigen::MatrixXd::Zero(numEvs,1);
    }

    for(int i = 0; i < numContrast; i++){
        for(int j = 0; j < numEvs; j++){
            C[i](j,0) = contrastTab->getContrast(i,j);
        }
    }

    std::vector<std::string> contrastNames = std::vector<std::string>(numContrast);
    for(int i = 0; i < numContrast; i++){
        QString currentContrastName = contrastTab->getContrastName(i);
        if(currentContrastName == "")
            contrastNames[i] = "Contrast " + std::to_string(i+1);
        else
            contrastNames[i] = currentContrastName.toStdString();
    }

    //TODO: Get Ftests

    //Initializing multyrow array
    //TODO: It should be deduced from the evsTab
    //this is just a stub to test stuff
    MultyRowArray a(num_of_maps, 2);
    //Filling first row
    for(int i = 0; i < num_of_maps; i++)
        a[0][i] = 1;

    this->setCursor(Qt::WaitCursor);
    //Fire Randomise
    std::vector<RandomiseResult> r = randomise(Y, M, C, a, FStatistic, options.useTfce, options.EE, options.ISE, options.numPermutation, options.alpha);

    //Save results in VMP (one or more), only tmaps for now
    vmp.removeAllSubMaps();

    int n = r.size();
    for(int i = 0; i < n; i++){
        vmp.addSubMap();
        vmp.getSubHeader(i).NameOfMap = contrastNames[i];
        vmp.getSubHeader(i).ThreshMin = r[i].criticalThreshold;
        MinMaxStructure m = r[i].originalStatistic.findMinMax();
        vmp.getSubHeader(i).ThreshMax = m.max;
        vmp.getSubHeader(i).df1 = num_of_maps-1;
        vmp.getSubHeader(i).MapType = t;
        vmp.getSubHeader(i).ClusterSize = 0;
        vmp.getSubHeader(i).UseClusterSize = 0;
        //vmp.getSubHeader(i).NrOfStatVoxels = ???;
        for(int j = 0; j < dim; j++){
            vmp[i][j] = r[i].originalStatistic[j];
        }
    }
    QString outputPath = withoutExtension(filepath) + "RandomiseResult.vmp";
    vmp.writevmp(outputPath.toStdString().c_str());
    this->setCursor(Qt::ArrowCursor);

    //Close Dialog
    //MainWindow::close();
}

void MainWindow::closeWindow(){
    MainWindow::close();
}

void MainWindow::addOrRemoveEvs(int evsNumber){
    evsTab->addOrRemoveEvs(evsNumber);
    contrastTab->addOrRemoveEvs(evsNumber);
}

void MainWindow::openVmp(){
    filepath = QFileDialog::getOpenFileName(this, tr("Open vmp"), QDir::home().absolutePath(), tr("vmp Files (*.vmp)"));
    if(filepath == "")
        return;
    fileTab->setFileName(filepath);
    vmp.readvmp(filepath.toStdString().c_str());
    int n_subjects = vmp.getNrMaps();
    for(int i = 0; i < n_subjects; i++){
        evsTab->addSubject();
    }
}

void MainWindow::clearAll(){
    filepath = "";
    fileTab->setFileName("");
    evsTab->removeAllSubjects();
    vmp = MyVmp();
}

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent)
{
   tabs = new QTabWidget;
   fileTab = new FileTab(this);
   evsTab = new EvsTab(this);
   contrastTab = new ContrastTab(this);
   optionsTab = new OptionsTab(this);
   tabs->addTab(fileTab, tr("Input"));
   tabs->addTab(evsTab, tr("EVs"));
   tabs->addTab(contrastTab, tr("Contrasts &&& F-tests"));
   tabs->addTab(optionsTab, tr("Options"));

   buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

   QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(collectDataAndFire()));
   QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(closeWindow()));

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
