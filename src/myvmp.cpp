#include "myvmp.h"
#include "binaryio.h"
#include <fstream>

MyVmp::MyVmp()
{

}

void MyVmp::removeSubMap(int index){
    NrOfMaps--;
    subHeaders.erase(subHeaders.begin()+index);
    data.erase(data.begin()+index);
}

void MyVmp::writevmp(const char * filename){

    //Opening file in write only binary mode
    std::ofstream output(filename, std::ios::binary);

    write_uint32(output, magic_number);
    write_uint16(output, version_number);
    write_uint16(output, doctype);

    write_uint32(output, NrOfMaps);
    write_uint32(output, NrOfTimePoints);
    write_uint32(output, NrOfMapParams);

    write_uint32(output, ShowParamsFrom);
    write_uint32(output, ShowParamsTo);

    write_uint32(output, UseForICFingerprintFrom);
    write_uint32(output, UseForICFingerprintTo);

    write_uint32(output, XStart);
    write_uint32(output, XEnd);
    write_uint32(output, YStart);
    write_uint32(output, YEnd);
    write_uint32(output, ZStart);
    write_uint32(output, ZEnd);

    write_uint32(output, Resolution);

    write_uint32(output, dimX);
    write_uint32(output, dimY);
    write_uint32(output, dimZ);

    //Names: vtc, prt, voi
    write_zstring(output, VTCFileName);
    write_zstring(output, ProtocolFileName);
    write_zstring(output, VOIFileName);

    for(int i = 0; i < NrOfMaps; i++){
        write_uint32(output, subHeaders[i].MapType);
        write_float(output, subHeaders[i].ThreshMin);
        write_float(output, subHeaders[i].ThreshMax);

        write_zstring(output, subHeaders[i].NameOfMap);

        write_uint32(output, subHeaders[i].color1);
        write_uint32(output, subHeaders[i].color2);
        write_uint32(output, subHeaders[i].color3);

        write_uint8(output, subHeaders[i].UseMapColor);
        write_zstring(output, subHeaders[i].LUTFileName);
        write_float(output, subHeaders[i].TransparentColorFactor);

        if(subHeaders[i].MapType == 3){
            write_uint32(output, subHeaders[i].NrOfCrossCorrLags);
            write_uint32(output, subHeaders[i].CrossCorrMinLag);
            write_uint32(output, subHeaders[i].CrossCorrMaxLag);
            write_uint32(output, subHeaders[i].ShowCorrelations);
        }

        write_uint32(output, subHeaders[i].ClusterSize);
        write_uint8(output, subHeaders[i].UseClusterSize);

        write_uint32(output, subHeaders[i].IncludeValuesGreaterThreshMax);
        write_uint32(output, subHeaders[i].df1);
        write_uint32(output, subHeaders[i].df2);
        write_uint8(output, subHeaders[i].ShowPosOrNegOrBoth);

        write_uint32(output, subHeaders[i].NrOfStatVoxels);

        write_uint32(output, subHeaders[i].SizeOfFdrTable);
        for(int j = 0; j < subHeaders[i].SizeOfFdrTable; j++){
            write_float(output, subHeaders[i].FdrTable[j].q);
            write_float(output, subHeaders[i].FdrTable[j].crit_std);
            write_float(output, subHeaders[i].FdrTable[j].crit_conservative);
        }
        write_uint32(output, subHeaders[i].FdrTableIndex);
    }

    if(NrOfTimePoints > 0){
        for(int i = 0; i < NrOfMaps; i++){
            for(int j = 0; j < NrOfTimePoints; j++){
                write_float(output, subHeaders[i].TimeCourse[j]);
            }
        }
    }
    if(NrOfMapParams > 0){
        NamesOfComponentParameters = std::vector<std::string>(NrOfMapParams);
        ComponentParams = std::vector<float>(NrOfMapParams);
        for(int i = 0; i < NrOfMapParams; i++){
            write_zstring(output, NamesOfComponentParameters[i]);
            write_float(output, ComponentParams[i]);
        }
    }

    for(int i = 0; i < NrOfMaps; i++){
        for(int zindex = 0; zindex < dimZ; zindex++){
            for(int yindex = 0; yindex < dimY; yindex++){
                for(int xindex = 0; xindex < dimX; xindex++){
                    write_float(output, data[i][zindex*dimX*dimY + yindex+dimX +zindex]);
                }
            }
        }
    }

    output.close();
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

        //NOTE: Just to make it work
        subHeaders[i].color1 = read_uint32(input);
        subHeaders[i].color2 = read_uint32(input);
        subHeaders[i].color3 = read_uint32(input);

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
        NamesOfComponentParameters = std::vector<std::string>(NrOfMapParams);
        ComponentParams = std::vector<float>(NrOfMapParams);
        for(int i = 0; i < NrOfMapParams; i++){
            NamesOfComponentParameters[i] = read_string(input);
            ComponentParams[i] = read_float(input);
        }
    }

    dimX = (XEnd - XStart) / Resolution;
    dimY = (YEnd - YStart) / Resolution;
    dimZ = (ZEnd - ZStart) / Resolution;

    data = std::vector<std::vector<float>>(NrOfMaps);
    for(int i = 0; i < NrOfMaps; i++){
        data[i] = std::vector<float>(dimX*dimY*dimZ);
        for(int zindex = 0; zindex < dimZ; zindex++){
            for(int yindex = 0; yindex < dimY; yindex++){
                for(int xindex = 0; xindex < dimX; xindex++){
                    data[i][zindex*dimX*dimY + yindex+dimX +zindex] = read_float(input);
                }
            }
        }
    }

    input.close();
}

int MyVmp::getNrMaps(){
    return NrOfMaps;
}

