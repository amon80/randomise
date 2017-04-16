#include "myvmp.h"
#include "binaryio.h"
#include <fstream>

MyVmp::MyVmp()
{

}

void MyVmp::readvmp(const char * filename){

    //Opening file in read only binary mode
    std::ifstream input(filename, std::ios::binary);

    magic_number = read_uint32(input);
    version_number = read_uint16(input);
    doctype = read_uint16(input);

    NrOfMaps = read_uint32(input);
    NrOfTimePoints = read_uint32(input);
    NrOfMapParams = read_uint32(input);

    ShowParamsFrom = read_uint32(input);
    ShowParamsTo = read_uint32(input);

    UseForICFingerprintFrom = read_uint32(input);
    UseForICFingerprintTo = read_uint32(input);

    XStart = read_uint32(input);
    XEnd = read_uint32(input);
    YStart = read_uint32(input);
    YEnd = read_uint32(input);
    ZStart = read_uint32(input);
    ZEnd = read_uint32(input);

    Resolution = read_uint32(input);

    //dims are not stored since they're computed at runtime
    dimX = read_uint32(input);
    dimY = read_uint32(input);
    dimZ = read_uint32(input);

    //Names: vtc, prt, voi
    VTCFileName = read_string(input);
    ProtocolFileName = read_string(input);
    VOIFileName = read_string(input);

    subHeaders = std::vector<vmp_header>(NrOfMaps);

    for(int i = 0; i < NrOfMaps; i++){
        subHeaders[i].MapType = read_uint32(input);
        subHeaders[i].ThreshMin = read_float(input);
        subHeaders[i].ThreshMax = read_float(input);

        subHeaders[i].NameOfMap = read_string(input);

        //NOTE:This shouldn't be a permanent solution
        //3 bytes colors. There are 4 of them, so
        //skip them we read 12 bytes.
        read_uint32(input);
        read_uint32(input);
        read_uint32(input);

        subHeaders[i].UseMapColor = read_uint8(input);
        subHeaders[i].LUTFileName = read_string(input);
        subHeaders[i].TransparentColorFactor = read_float(input);

        if(subHeaders[i].MapType == 3){
            subHeaders[i].NrOfCrossCorrLags = read_uint32(input);
            subHeaders[i].CrossCorrMinLag = read_uint32(input);
            subHeaders[i].CrossCorrMaxLag = read_uint32(input);
            subHeaders[i].ShowCorrelations = read_uint32(input);
        }

        subHeaders[i].ClusterSize = read_uint32(input);
        subHeaders[i].UseClusterSize = read_uint8(input);

        subHeaders[i].IncludeValuesGreaterThreshMax = read_uint32(input);
        subHeaders[i].df1 = read_uint32(input);
        subHeaders[i].df2 = read_uint32(input);
        subHeaders[i].ShowPosOrNegOrBoth = read_uint8(input);

        subHeaders[i].NrOfStatVoxels = read_uint32(input);

        subHeaders[i].SizeOfFdrTable = read_uint32(input);
        subHeaders[i].FdrTable = std::vector<fdrentry>(subHeaders[i].SizeOfFdrTable);
        for(int j = 0; j < subHeaders[i].SizeOfFdrTable; j++){
            subHeaders[i].FdrTable[j].q = read_float(input);
            subHeaders[i].FdrTable[j].crit_std = read_float(input);
            subHeaders[i].FdrTable[j].crit_conservative = read_float(input);
        }
        subHeaders[i].FdrTableIndex = read_uint32(input);
    }

    if(NrOfTimePoints > 0){
        for(int i = 0; i < NrOfMaps; i++){
            subHeaders[i].TimeCourse = std::vector<float>(NrOfTimePoints);
            for(int j = 0; j < NrOfTimePoints; j++){
                subHeaders[i].TimeCourse[j] = read_float(input);
            }
        }
    }
    if(NrOfMapParams > 0){
        //TODO
        for(int i = 0; i < NrOfMapParams; i++){

        }
    }


    input.close();
}
