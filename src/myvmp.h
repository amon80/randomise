#ifndef MYVMP_H
#define MYVMP_H

#include <vector>
#include <string>

//TODO:Add all kinds of map
enum MapTypeEnum{
    beta = 15, t = 1
};

struct fdrentry{
    float q;
    float crit_std;
    float crit_conservative;
};

struct vmp_header{
    std::string NameOfMap;			// 101 chars

    MapTypeEnum MapType;

    float ThreshMin;
    float ThreshMax;
    int IncludeValuesGreaterThreshMax; // "1" (default) -> shows map values greater max threshold, "0" excludes values greater max threshold
    int ClusterSize;
    int UseClusterSize;
    int df1;
    int df2;
    int NrOfStatVoxels;		// number of voxels with a calculated map value (!= 0.0) - used for multiple comparisons correction
    int ShowPosOrNegOrBoth;   // 1 -> show pos values, 2 -> show neg values, 3 -> show pos and neg valeus

    int NrOfCrossCorrLags;	// use value only if MapType "3" (cross-correlation or relative contribution map)
    int CrossCorrMinLag;      // use value only if MapType "3"
    int CrossCorrMaxLag;		// use value only if MapType "3"
    int ShowCorrelations;		// use value only if MapType "3", if "1" shows correlation value, if "0" shows lag value in overlayed map

    int RedPositiveMinValue;
    int GreenPositiveMinValue;
    int YellowPositiveMinValue;

    int RedPositiveMaxValue;
    int GreenPositiveMaxValue;
    int YellowPositiveMaxValue;

    int RedNegativeMinValue;
    int GreenNegativeMinValue;
    int YellowNegativeMinValue;

    int RedNegativeMaxValue;
    int GreenNegativeMaxValue;
    int YellowNegativeMaxValue;

    int UseMapColor;

    int SizeOfFdrTable;
    std::vector<fdrentry> FdrTable;
    int FdrTableIndex;

    std::string LUTFileName;
    std::vector<float> TimeCourse;

    float TransparentColorFactor;

    int   OverlayMap;			// get/set whether this component is shown
};

class MyVmp
{
public:
    MyVmp();
    void readvmp(const char * filename);
    void writevmp(const char * filename);
    int getNrMaps();
    int getDimX();
    int getDimY();
    int getDimZ();
    std::vector<float>& operator[](const std::size_t idx);
    void removeSubMap(int index);
    void removeAllSubMaps();
private:
    //header
    int NrOfMaps;
    std::string FileName;

    int NrOfTimePoints;
    int NrOfMapParams;
    int ShowParamsFrom;
    int ShowParamsTo;

    int UseForICFingerprintFrom;
    int UseForICFingerprintTo;

    std::string VTCFileName;
    std::string ProtocolFileName;
    std::string VOIFileName;

    int XStart;
    int XEnd;
    int YStart;
    int YEnd;
    int ZStart;
    int ZEnd;
    int Resolution;

    int magic_number;
    int version_number;
    int doctype;

    int dimX;
    int dimY;
    int dimZ;

    std::vector<std::string> NamesOfComponentParameters;

    std::vector<float> ComponentParams;		// defined only if "(NrOfComponentParams > 0)", otherwise NULL ptr

    //subheaders
    std::vector<vmp_header> subHeaders;

    //actualdata
    std::vector<std::vector<float>> data;
};

#endif // MYVMP_H
