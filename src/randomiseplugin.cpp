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
#include <Eigen/Dense>


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

        //Initializing 4D map of data
        StatisticalMap4D Y(dim, num_of_maps);

        //Filling the initialized 4D map
        for(int v = 0; v < dim; v++){
            for (int i = 0; i < num_of_maps; i++){
                vv = qxGetNRVMPOfCurrentVMR(i, &vmp_header);
                float value = vv[v];
                Y[v](i) = value;
            }
        }

        //Initializing the design matrix
        //NOTE: GUI controls can be made in the future
        Eigen::MatrixXd M(num_of_maps, 2);
        //Filling the design matrix
        for(int i = 0; i < num_of_maps; i++){
            M(i,0) = 1;
            M(i,1) = i+1*10;
        }

        //Initializing the contrast
        //NOTE: GUI controls can be made in the future
        Eigen::MatrixXd C1(2,1);
        //Filling the contrasts
        C1(0,0) = 1;
        C1(1,0) = 0;

        //Initializing multyrow array
        //NOTE: GUI controls can be made in the future
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
        //NOTE: 1 permutation is set to test F statistic correctness
        RandomiseResult r = randomise(Y, M, C1, multyRowArray, FStatistic, false, true, 1);

        //Finished permutations! Now let's show the results
        qxDeleteNRVMPsOfCurrentVMR();
        qxCreateNRVMPsForCurrentVMR(1, 0, 0, NULL);
        qxGetNRVMPsOfCurrentVMR(&vmps_header);
        num_of_maps = vmps_header.NrOfMaps;
        qxGetNRVMPsOfCurrentVMR(&vmps_header);
        vv = qxGetNRVMPOfCurrentVMR(0, &vmp_header);
        for(int i = 0; i < dim; i++)
            vv[i] = r.originalStatistic[i];
        //TODO: threshold with p-values
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
static const char *PluginDescription = "This plugin implements the randomise tecnique.<br>";

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


