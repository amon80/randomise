// RandomisePlugin.cpp : Defines the initialization routines for the DLL.
//

#include "randomiseplugin.h"

#if defined(OS_WIN32)
#include <windows.h>
#include <malloc.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "permutationtree.h"
#include "matrices.h"
#include "mystat.h"
#include "randomise.h"
#include "Eigen/Dense"


// constructor of your plugin class
//
RandomisePlugin::RandomisePlugin()
{
}

// destructor of your plugin class
//
RandomisePlugin::~RandomisePlugin()
{
}

bool RandomisePlugin::initPlugin() // this function is called in GUI plugins once after class has been created - not called in pure computational plugins
{
	// This function call and check of return value is necessary to check whether access to QX works

	int ret = InitQXAccess();

	// Never continue, if the "InitQXAccess" function fails
	//
	if(!ret)
		return false;

	// Test whether the used QX version is new enough to support the commands used in your plugin
	//
	int Major, Minor, SubMinor;
	qxGetVersionOfBrainVoyagerQX(&Major, &Minor, &SubMinor);

	// We require v1.4.8
	if( !checkVersionGreaterEqualVersion(Major, Minor, SubMinor, 2, 1, 0) )
	{
		// we can use message box since this was available with the first QX version with plugin support (v1.3.8)
		qxMessageBox("Can not execute this plugin - BrainVoyager QX version 2.1 or higher required.");
		return false;
	}

	return true;
}

// THE MOST IMPORTANT EXPORTED FUNCTION
//
bool RandomisePlugin::execute()
{
    float * vv = NULL;
    struct VMR_Header vmr_header;
    struct NR_VMPs_Header vmps_header;
    struct NR_VMP_Header vmp_header;
    int dim;

    char buffer[100];


    if (!qxGetMainHeaderOfCurrentVMR(&vmr_header)){
        qxLogText("Plugin>  Problem Get resolution voxel");
        return false;
    }

    if (qxGetNRVMPsOfCurrentVMR(&vmps_header) != NULL) {
        //Getting VMR dimension
        int dimX = (vmps_header.XEnd - vmps_header.XStart) / vmps_header.Resolution;
        int dimY = (vmps_header.YEnd - vmps_header.YStart) / vmps_header.Resolution;
        int dimZ = (vmps_header.ZEnd - vmps_header.ZStart) / vmps_header.Resolution;
        dim = dimX*dimY*dimZ;

        //Getting number of vmps
        int num_of_maps = vmps_header.NrOfMaps;

        //Getting desired significance level
        //NOTE: This should be asked to the user, so GUI controls are need in the future

        //TODO: if there are few maps (i.e. low degrees of freedom),
        //variance can be pooled together
        //by smoothing the maps with a gaussian kernel of 5mm

        //Initializing 4D map of data
        StatisticalMap4D Y(dimX, dimY, dimZ, num_of_maps);

        //Filling the initialized 4D map
        for(int v = 0; v < dim; v++){
            for (int i = 0; i < num_of_maps; i++){
                vv = qxGetNRVMPOfCurrentVMR(i, &vmp_header);
                float value = vv[v];
                Y[v](i) = value;
            }
        }

        //Initializing the design matrix
        //No nuisance effect for this tests
        //NOTE: GUI controls can be made in the future
        Eigen::MatrixXd M(num_of_maps, 1);
        //Filling the design matrix
        for(int i = 0; i < num_of_maps; i++){
            M(i,0) = 1;
        }

        //Initializing the contrast
        //NOTE: GUI controls can be made in the future
        std::vector<Eigen::MatrixXd> C(1);
        C[0] = Eigen::MatrixXd::Zero(1,1);
        C[0](0,0) = 1;

        //Initializing multyrow array
        //NOTE: GUI controls can be made in the future
        //And maybe also a class since the last row is always the same
        std::vector<std::vector<int>> multyRowArray(2);
        for(int i = 0; i < 2; i++)
            multyRowArray[i] = std::vector<int>(num_of_maps);
        //Filling first row
        for(int i = 0; i < num_of_maps; i++)
            multyRowArray[0][i] = 1;
        //Filling second row
        for(int i = 0; i < num_of_maps; i++)
            multyRowArray[1][i] = i+1;

        //Go with the math!
        //DEBUG NOTE: set to 1 permutation is set to test F/T statistic correctness

        float alpha = qxGetFloatInput("Enter desired alpha inference level:", 0.05, 0.01, 0.05);

        int J = qxGetIntegerInput("How many permutations would you like to perform maximum?", 10000, 0, 50000);

        int useTfceInt = qxYesNoMessageBox("Do you want to use TFCE?");
        bool useTfce = false;
        if(useTfceInt)
            useTfce = true;

        //Setting values hardcoded for this small example
        bool EE = false;
        bool ISE = true;

        qxShowBusyCursor();
        std::vector<RandomiseResult> r = randomise(Y, M, C, multyRowArray, TStatistic, useTfce, EE, ISE, J);
        qxStopBusyCursor();

        int perforemdPermutations = r[0].maxDistribution.size();

        sprintf(buffer, "Maximal distribution");
        qxLogText(buffer);
        for(int i = 0; i < perforemdPermutations; i++){
            sprintf(buffer, "%d - %f", i, r[0].maxDistribution[i]);
            qxLogText(buffer);
        }
        int criticalThresholdIndex = (int) floor(alpha*perforemdPermutations) + 1;
        sprintf(buffer, "Critical Threshold index for %f inference level: %d", alpha, criticalThresholdIndex);
        qxLogText(buffer);
        float criticalThreshold = r[0].maxDistribution[criticalThresholdIndex];
        sprintf(buffer, "Critical threshold for %f inference level: %f", alpha, criticalThreshold);
        qxLogText(buffer);

		float min, max, range;
		r.originalStatistic.findMinMax(min, max, range);

        //Finished permutations! Now let's show the results
        qxDeleteNRVMPsOfCurrentVMR();
        qxCreateNRVMPsForCurrentVMR(3, 0, 0, NULL);
        qxGetNRVMPsOfCurrentVMR(&vmps_header);
        vv = qxGetNRVMPOfCurrentVMR(0, &vmp_header);
        strcpy(vmp_header.NameOfMap, "Mean effect");
        vmp_header.MapType = 1;
		vmp_header.df1 = num_of_maps - 1;
        vmp_header.OverlayMap = 1;
        vmp_header.ThreshMin = criticalThreshold;
        float min, max, range;
        r[0].originalStatistic.findMinMax(min, max,range);
        vmp_header.ThreshMin = criticalThreshold;        
        vmp_header.ThreshMax = max;
        for(int i = 0; i < dim; i++)
            vv[i] = r[0].originalStatistic[i];
        qxSetNRVMPParametersOfCurrentVMR(0, &vmp_header);
        vv = qxGetNRVMPOfCurrentVMR(1, &vmp_header);
        strcpy(vmp_header.NameOfMap, "Uncorrected p-values");
        //this has little since since it's not a tmap
        vmp_header.MapType = 1;
        //showing only positives since pvalues are between 0 and 1
        vmp_header.ShowPosOrNegOrBoth = 1;
        vmp_header.OverlayMap = 0;
        vmp_header.ThreshMin = 0;
        vmp_header.ThreshMax = alpha;
        for(int i = 0; i < dim; i++)
            vv[i] = r[0].uncorrected[i];
        qxSetNRVMPParametersOfCurrentVMR(1, &vmp_header);
        vv = qxGetNRVMPOfCurrentVMR(2, &vmp_header);
        strcpy(vmp_header.NameOfMap, "Corrected p-values");
        //this has little since since it's not a tmap
        vmp_header.MapType = 1;
        //showing only positives since pvalues are between 0 and 1
        vmp_header.ShowPosOrNegOrBoth = 1;
        vmp_header.OverlayMap = 0;
        vmp_header.ThreshMin = 0;
        vmp_header.ThreshMax = alpha;
        for(int i = 0; i < dim; i++)
            vv[i] = r[0].corrected[i];
        qxSetNRVMPParametersOfCurrentVMR(2, &vmp_header);
    }
    else{
        qxLogText("Plugin>  VMP not found");
        return false;
    }

	// To make the change visible, update the active window in QX
	qxUpdateActiveWindow();

    qxLogText("Plugin>  Randomise Plugin completed!\n");
	return true;
}


//
// C access functions (extern "C" in header)
//

// THIS FUNCTION CREATES YOUR PLUGIN CLASS
//
PLUGIN_ACCESS BVQXPluginInterface *createPlugin() 
{
	return new RandomisePlugin();
}

// return a name for your plugin
//
PLUGIN_ACCESS const char *getPluginName() 
{
    return "Randomise Plugin";
}

// returns a descriptive string for your plugin shown in the QX "Descriptions of Plugins" window
//   it is recommended to use a static C string to describe your plugin
//   (the potentially lengthy string needs then not be created repeatedly in successive calls)
//   Note that you may use simple HTML tags to format the string, such as <b></b>, <i></i> and <br>
//
static const char *PluginDescription = "This plugin implements the permutation tests for the GLM.<br>";

PLUGIN_ACCESS const char *getPluginDescription() 
{
	return PluginDescription;
}

// get credit for your work!
//
PLUGIN_ACCESS const char *getAuthor()
{
    return "<i>Marco Mecchia</i>";
}

// you may provide the name for a HTML file containing online help
//
PLUGIN_ACCESS const char *getHelpFile()
{
	return "";
}

// you may provide a version string ("Major.Minor") for (updated) releases of your plugins
//
PLUGIN_ACCESS const char *getPluginVersion()
{
	return "2.0";
}

// NEW: If you want to use GUI dialogs, return a GUI script file, if not, return empty C string
//
PLUGIN_ACCESS const char *getGUIScript()
{
	return "";
}



