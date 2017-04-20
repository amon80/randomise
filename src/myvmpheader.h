#ifndef MYVMPHEADER_H
#define MYVMPHEADER_H

#include <string>
#include <vector>

struct fdrentry{
    float q;
    float crit_std;
    float crit_conservative;
};

enum MapTypeEnum{
    beta = 15, t = 1
};

class MyVmpHeader
{
public:
    MyVmpHeader(int nTimePoints = 0);

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

    int   OverlayMap;
};

#endif // MYVMPHEADER_H
