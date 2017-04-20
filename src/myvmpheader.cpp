#include "myvmpheader.h"

MyVmpHeader::MyVmpHeader(int nTimePoints)
{
    NameOfMap = "";		// 101 chars

    MapType = t;

    ThreshMin = 2.0;
    ThreshMax = 10.0;
    IncludeValuesGreaterThreshMax = 1; // "1" (default) -> shows map values greater max threshold, "0" excludes values greater max threshold
    ClusterSize = 0;
    UseClusterSize = 0;
    df1 = 0;
    df2 = 0;
    NrOfStatVoxels = 0;		// number of voxels with a calculated map value (!= 0.0) - used for multiple comparisons correction
    ShowPosOrNegOrBoth = 3;   // 1 -> show pos values, 2 -> show neg values, 3 -> show pos and neg valeus

    NrOfCrossCorrLags = 0;	// use value only if MapType "3" (cross-correlation or relative contribution map)
    CrossCorrMinLag = 0;      // use value only if MapType "3"
    CrossCorrMaxLag = 0;		// use value only if MapType "3"
    ShowCorrelations = 0;		// use value only if MapType "3", if "1" shows correlation value, if "0" shows lag value in overlayed map

    RedPositiveMinValue = 0;
    GreenPositiveMinValue = 0;
    YellowPositiveMinValue = 100;

    RedPositiveMaxValue = 0;
    GreenPositiveMaxValue = 0;
    YellowPositiveMaxValue = 255;

    RedNegativeMinValue = 100;
    GreenNegativeMinValue = 100;
    YellowNegativeMinValue = 50;

    RedNegativeMaxValue = 200;
    GreenNegativeMaxValue = 200;
    YellowNegativeMaxValue = 100;

    UseMapColor = 0;

    SizeOfFdrTable = 0;
    std::vector<fdrentry> FdrTable = std::vector<fdrentry>(SizeOfFdrTable);
    FdrTableIndex = -1;

    LUTFileName = "<default>";
    TimeCourse = std::vector<float>(nTimePoints);

    TransparentColorFactor = 1.0;

    OverlayMap = 0;
}
