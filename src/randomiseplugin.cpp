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
#include "multyrowarray.h"
#include "matrices.h"
#include "mystat.h"
#include "randomise.h"
#include "Eigen/Dense"

#include "connectivity3d6.h"
#include "connectivity3d18.h"
#include "connectivity3d26.h"

#include <future>
#include <chrono>

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

    if (!qxGetMainHeaderOfCurrentVMR(&vmr_header)){
        qxLogText("Plugin>  Problem Get resolution voxel.");
        return false;
    }

    if (!qxGetNRVMPsOfCurrentVMR(&vmps_header)){
        qxLogText("Plugin> No vmp loaded, exiting.");
        return false;
    }
    num_of_maps = vmps_header.NrOfMaps;
    if(!num_of_maps){
        qxLogText("Plugin> For this plugin, you need a vmp with more than one map. Read the docs. Exiting.");
        return false;
    }

	return true;
}

// THE MOST IMPORTANT EXPORTED FUNCTION
//
bool RandomisePlugin::execute()
{
    char task_name[100];
    qxGetStringParameter("Command", task_name);

    if(!strcmp(task_name, "GetNumOfMaps")){
        qxSetIntParameter("NumOfMaps", num_of_maps);
        return true;
    }else if(!strcmp(task_name, "Execute")){
        int maxPermutations = qxGetIntParameter("MaxPermutations");
        int useEEInt = qxGetIntParameter("EE");
        int useISEInt = qxGetIntParameter("ISE");
        int useTfceInt = qxGetIntParameter("UseTfce");
        float alpha = qxGetFloatParameter("Alpha");

        int numberContrasts = qxGetIntParameter("NumberOfContrasts");
        int numberRegressors = qxGetIntParameter("NumberOfRegressors");
        int numberFTests = qxGetIntParameter("NumberOfFTests");
        int numberGroupLayers = qxGetIntParameter("NumberOfGroupLayers");

        int refreshingTimeSeconds = qxGetIntParameter("RefreshingTime");

        float dh = 0.1;
        float H = 2.0;
        float E = 0.5;
        Connectivity3D * Conn = nullptr;

        char buffer[100];

        bool useTfce = false;
        if(useTfceInt){
            useTfce = true;
            dh = qxGetFloatParameter("dh");
            H = qxGetFloatParameter("H");
            E = qxGetFloatParameter("E");
            qxGetStringParameter("C", buffer);
            if(!strcmp(buffer, "6 connectivity")){
                Conn = new Connectivity3D6();
            }else if(!strcmp(buffer, "18 connectivity")){
                Conn = new Connectivity3D18();
            }else{
                Conn = new Connectivity3D26();
            }
        }
        bool EE = false;
        if(useEEInt)
            EE = true;

        bool ISE = false;
        if(useISEInt)
            ISE = true;

        float * vv = NULL;
        struct NR_VMP_Header vmp_header;
        int dim;

        char variableName[100];

        //Getting VMR dimension
        int dimX = (vmps_header.XEnd - vmps_header.XStart) / vmps_header.Resolution;
        int dimY = (vmps_header.YEnd - vmps_header.YStart) / vmps_header.Resolution;
        int dimZ = (vmps_header.ZEnd - vmps_header.ZStart) / vmps_header.Resolution;
        dim = dimX*dimY*dimZ;

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
        Eigen::MatrixXd M(num_of_maps, numberRegressors);
        //Filling the design matrix
        for(int i = 0; i < num_of_maps; i++){
            for(int j = 0; j < numberRegressors; j++){
                sprintf(variableName, "DesignMatrix%d%d",i,j);
                qxGetStringParameter(variableName, buffer);
                M(i,j) = atof(buffer);

            }
        }

        int total_contrasts = numberContrasts + numberFTests;
        //Initializing the contrasts and the ftests
        std::vector<Eigen::MatrixXd> C(total_contrasts);
        for(int i = 0; i < numberContrasts; i++){
            C[i] = Eigen::MatrixXd::Zero(numberRegressors,1);
        }
        for(int i = numberContrasts; i < total_contrasts; i++){
            C[i] = Eigen::MatrixXd::Zero(numberRegressors,numberContrasts);
        }
        //Filling contrasts and ftests
        for(int i = 0; i < numberContrasts; i++){
            for(int j = 0; j < numberRegressors; j++){
                sprintf(variableName, "ContrastMatrix%d%d",i,j);
                qxGetStringParameter(variableName, buffer);
                C[i](j,0) = atof(buffer);
            }
        }
        for(int i = numberContrasts; i < total_contrasts; i++){
            int k = i - numberContrasts;
            for(int j = 0; j < numberContrasts; j++){
                sprintf(variableName, "FTestMatrix%d%d",k,j);
                qxGetStringParameter(variableName, buffer);
                float useContrastJ = atof(buffer);
                for(int r = 0; r < numberRegressors; r++){
                    C[i](r,j) = useContrastJ*C[j](r,0);
                }
            }
        }

        //Initializing multyrow array
        MultyRowArray a(num_of_maps,1+numberGroupLayers);
        for(int j = 0; j < numberGroupLayers; j++){
            for(int i = 0; i < num_of_maps; i++){
                sprintf(variableName, "GroupMatrix%d%d",i,j);
                qxGetStringParameter(variableName, buffer);
                a[j][i] = atoi(buffer);
            }
        }

        //Declaring function pointer for statistic, and getting its value from ui
        float (*pivotal)(Eigen::VectorXd&, Eigen::VectorXd&, Eigen::MatrixXd&, Eigen::MatrixXd&, Eigen::MatrixXd&, Eigen::MatrixXd&, Eigen::MatrixXd&, int, std::vector<int>&) = nullptr;
        qxGetStringParameter("Statistic", buffer);
        if(!strcmp(buffer, "F")){
            pivotal = FStatistic;
        }else if(!strcmp(buffer, "G")){
            pivotal = GStatistic;
        }

        //Declaring integer to pass by reference for logging use
        int performed_perm = 0;
        int total_perm = 0;
        int contrast = 0;

        //Go with the math (asynchronosly)
        qxShowBusyCursor();
        std::chrono::milliseconds span (1000 * refreshingTimeSeconds);
        auto randomise_lambda = [&Y, &M, &C, &a, &pivotal, &useTfce, &E, &H, &dh, &Conn, &EE, &ISE, &maxPermutations, &alpha, &performed_perm, &total_perm, &contrast]
        {
            return randomise(Y, M, C, a, pivotal, useTfce, E, H, dh, Conn, EE, ISE, maxPermutations, alpha, &performed_perm, &total_perm, &contrast);
        };
        auto fut = std::async(std::launch::async, randomise_lambda);
        while (true){
            auto waiting_result = fut.wait_for(span);
            if(waiting_result==std::future_status::ready){
                qxLogText("Finished!");
                break;
            }
            else if(waiting_result==std::future_status::timeout){
                sprintf(buffer, "Contrast %d - Executed %d/%d permutations", contrast, performed_perm, total_perm);
                qxLogText(buffer);
            }
        }
        qxStopBusyCursor();

        std::vector<RandomiseResult> r = fut.get();

		//Arrange the results in a vmp
        int n = C.size();
		int total_vmp = n * 3;

        qxDeleteNRVMPsOfCurrentVMR();
        qxCreateNRVMPsForCurrentVMR(total_vmp, 0, 0, NULL);
        qxGetNRVMPsOfCurrentVMR(&vmps_header);
        int j = 0;
        for(int i = 0; i < n; i++){
            int performedPermutations = r[i].performedPermutations;
            float criticalThreshold;

            if(performedPermutations > 0){
                criticalThreshold = r[i].criticalThreshold;
                sprintf(buffer, "Contrast %d - Critical threshold for %f inference level: %f", i, alpha, criticalThreshold);
                qxLogText(buffer);
            }

			//Filling submap with original statistic for contrast i
            MinMaxStructure m = r[i].originalStatistic.findMinMax();
            float min = m.min;
            float max = m.max;

            vv = qxGetNRVMPOfCurrentVMR(j, &vmp_header);
            sprintf(buffer, "Contrast %d", i);
            strcpy(vmp_header.NameOfMap, buffer);
            vmp_header.df1 = num_of_maps - 1;
            vmp_header.OverlayMap = 0;
            if(performedPermutations > 0)
                vmp_header.ThreshMin = criticalThreshold;
            else
                vmp_header.ThreshMin = min;
            vmp_header.ThreshMax = max;
            for(int k = 0; k < dim; k++)
                vv[k] = r[i].originalStatistic[k];
            qxSetNRVMPParametersOfCurrentVMR(j++, &vmp_header);

			//Filling submap with negated uncorrected pvalues for contrast i
			vv = qxGetNRVMPOfCurrentVMR(j, &vmp_header);
            sprintf(buffer, "Contrast %d - Uncorrected 1-pvalues", i);
			strcpy(vmp_header.NameOfMap, buffer);
			vmp_header.OverlayMap = 0;
			vmp_header.ThreshMin = 1-alpha;
			vmp_header.ThreshMax = 1;
			for (int k = 0; k < dim; k++)
				vv[k] = 1 - r[i].uncorrected[k];
            vmp_header.ShowPosOrNegOrBoth = 1;
			qxSetNRVMPParametersOfCurrentVMR(j++, &vmp_header);

			//Filling submap with negated FWER corrected pvalues for contrast i
			vv = qxGetNRVMPOfCurrentVMR(j, &vmp_header);
            sprintf(buffer, "Contrast %d - FWER corrected 1-pvalues", i);
			strcpy(vmp_header.NameOfMap, buffer);
			vmp_header.OverlayMap = 0;
			vmp_header.ThreshMin = 1 - alpha;
			vmp_header.ThreshMax = 1;
			for (int k = 0; k < dim; k++)
				vv[k] = 1 - r[i].corrected[k];
            vmp_header.ShowPosOrNegOrBoth = 1;
			qxSetNRVMPParametersOfCurrentVMR(j++, &vmp_header);
        }

        // To make the change visible, update the active window in QX
        qxUpdateActiveWindow();

        qxLogText("Plugin>  Randomise Plugin completed!");
        return true;
    }
    qxLogText("Plugin>  Plugin received unknown command, exiting.");
    return false;
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
static const char *PluginDescription = "This plugin implements the permutation inference for the GLM.<br>";

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
    return "randomise.js";
}



