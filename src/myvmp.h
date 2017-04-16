#ifndef MYVMP_H
#define MYVMP_H

#include <vector>
#include <string>

struct fdrentry{
    float q;
    float crit_std;
    float crit_conservative;
};

struct vmp_header{
    std::string NameOfMap;			// 101 chars

    int   MapType;

    float ThreshMin;
    float ThreshMax;
    int   IncludeValuesGreaterThreshMax; // "1" (default) -> shows map values greater max threshold, "0" excludes values greater max threshold
    int   ClusterSize;
    int   UseClusterSize;
    int   df1;
    int   df2;
    int   NrOfStatVoxels;		// number of voxels with a calculated map value (!= 0.0) - used for multiple comparisons correction
    int   ShowPosOrNegOrBoth;   // 1 -> show pos values, 2 -> show neg values, 3 -> show pos and neg valeus

    int   NrOfCrossCorrLags;	// use value only if MapType "3" (cross-correlation or relative contribution map)
    int   CrossCorrMinLag;      // use value only if MapType "3"
    int   CrossCorrMaxLag;		// use value only if MapType "3"
    int   ShowCorrelations;		// use value only if MapType "3", if "1" shows correlation value, if "0" shows lag value in overlayed map

    int   ColorPosMin;
    int   ColorPosMax;
    int   ColorNegMin;
    int   ColorNegMax;
    int   UseMapColor;

    int SizeOfFdrTable;
    std::vector<fdrentry> FdrTable;
    int FdrTableIndex;

    std::string LUTFileName;

    float TransparentColorFactor;

    std::vector<float> TimeCourse;			// defined only if "(NrOfTimePoints > 0)", otherwise NULL ptr
    std::vector<float> ComponentParams;		// defined only if "(NrOfComponentParams > 0)", otherwise NULL ptr

    int   OverlayMap;			// get/set whether this component is shown
};

class MyVmp
{
public:
    MyVmp();
    void readvmp(const char * filename);
private:
    //header
    int   NrOfMaps;
    std::string FileName;

    int   NrOfTimePoints;
    int   NrOfMapParams;
    int   ShowParamsFrom;			// per default, all params are shown
    int   ShowParamsTo;				// per default, all params are shown (this can be restricted for display, all params always saved in "ParamsMatrix.txt" file)

    int   UseForICFingerprintFrom; // this is only relevant for ICA-related native resolution VMPs
    int   UseForICFingerprintTo;   // this is only relevant for ICA-related native resolution VMPs

    std::string VTCFileName;			// 261 chars reserved (empty C string ("") if not provided)
    std::string ProtocolFileName;		// 261 chars reserved (emtpy C string ("") if not provided)
    std::string VOIFileName;			// 261 chars reserved (empty C string ("") if not provided)

    int   XStart;  // do NOT change right now: if these 6 values are changed, you MUST also change the allocated memory of this and all other maps !
    int   XEnd;
    int   YStart;
    int   YEnd;
    int   ZStart;
    int   ZEnd;
    int   Resolution; // usually "3" (native resolution of many VTC data sets, but can be also "2" or "1")

    int magic_number;
    int version_number;
    int doctype;

    int dimX;
    int dimY;
    int dimZ;

    std::vector<std::string> NamesOfComponentParameters;

    //subheaders
    std::vector<vmp_header> subHeaders;

    //actualdata
    std::vector<std::vector<float>> data;
};

#endif // MYVMP_H
