#include "myvmp.h"
#include "binaryio.h"
#include <fstream>

//NOTE: At least a map should be added before saving
MyVmp::MyVmp(int NrOfMaps, int NrOfTimePoints, int NrOfMapsParams)
{
    magic_number = MAGIC_NUMBER;
    version_number = VERSION_NUMBER;
    doctype = DOCTYPE;
    NrOfMaps = 0;
    NrOfTimePoints = NrOfTimePoints;
    NrOfMapParams = NrOfMapsParams;
    ShowParamsFrom = 0;
    ShowParamsTo = 0;
    UseForICFingerprintFrom = 0;
    UseForICFingerprintTo = 0;
    XStart = STARTX;
    XEnd = ENDX;
    YStart = STARTY;
    YEnd = ENDY;
    ZStart = STARTZ;
    ZEnd = ENDZ;
    Resolution = RESOLUTION;
    dimX = DIMX;
    dimY = DIMY;
    dimZ = DIMZ;
    VTCFileName = "";
    ProtocolFileName = "";
    VOIFileName = "";
    subHeaders = std::vector<MyVmpHeader>(0);
    for(int i = 0; i < NrOfMaps; i++){
        subHeaders.push_back(MyVmpHeader(NrOfTimePoints));
    }
    NamesOfComponentParameters = std::vector<std::string>(NrOfMapsParams);
    ComponentParams = std::vector<float>(NrOfMapsParams);
}

int MyVmp::getDimX(){
    return (XEnd - XStart) / Resolution;
}

int MyVmp::getDimY(){
    return (YEnd - YStart) / Resolution;
}

int MyVmp::getDimZ(){
    return (ZEnd - ZStart) / Resolution;
}

std::vector<float>& MyVmp::operator[](const std::size_t idx){
    return data[idx];
}

MyVmpHeader& MyVmp::getSubHeader(const std::size_t idx){
    return subHeaders[idx];
}


void MyVmp::addSubMap(){
    NrOfMaps++;
    subHeaders.push_back(MyVmpHeader());
    data.push_back(std::vector<float>(dimX*dimY*dimZ));
}

void MyVmp::removeAllSubMaps(){
    int nSubMaps = data.size();
    for(int i = 0; i < nSubMaps; i++){
        removeSubMap(data.size()-1);
    }
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

    write_zstring(output, VTCFileName);
    write_zstring(output, ProtocolFileName);
    write_zstring(output, VOIFileName);

    for(int i = 0; i < NrOfMaps; i++){
        write_uint32(output, static_cast<uint32_t>(subHeaders[i].MapType));
        write_float(output, subHeaders[i].ThreshMin);
        write_float(output, subHeaders[i].ThreshMax);

        write_zstring(output, subHeaders[i].NameOfMap);

        write_uint8(output, subHeaders[i].RedPositiveMinValue);
        write_uint8(output, subHeaders[i].GreenPositiveMinValue);
        write_uint8(output, subHeaders[i].YellowPositiveMinValue);

        write_uint8(output, subHeaders[i].RedPositiveMaxValue);
        write_uint8(output, subHeaders[i].GreenPositiveMaxValue);
        write_uint8(output, subHeaders[i].YellowPositiveMaxValue);

        write_uint8(output, subHeaders[i].RedNegativeMinValue);
        write_uint8(output, subHeaders[i].GreenNegativeMinValue);
        write_uint8(output, subHeaders[i].YellowNegativeMinValue);

        write_uint8(output, subHeaders[i].RedNegativeMaxValue);
        write_uint8(output, subHeaders[i].GreenNegativeMaxValue);
        write_uint8(output, subHeaders[i].YellowNegativeMaxValue);

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

    int dim = getDimX()*getDimY()*getDimZ();
    for(int i = 0; i < NrOfMaps; i++){
        for(int j = 0; j < dim; j++){
            write_float(output, data[i][j]);
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

    subHeaders = std::vector<MyVmpHeader>(NrOfMaps);

    for(int i = 0; i < NrOfMaps; i++){
        subHeaders[i].MapType = static_cast<MapTypeEnum>(read_uint32(input));
        subHeaders[i].ThreshMin = read_float(input);
        subHeaders[i].ThreshMax = read_float(input);

        subHeaders[i].NameOfMap = read_string(input);

        subHeaders[i].RedPositiveMinValue = read_uint8(input);
        subHeaders[i].GreenPositiveMinValue = read_uint8(input);
        subHeaders[i].YellowPositiveMinValue = read_uint8(input);

        subHeaders[i].RedPositiveMaxValue = read_uint8(input);
        subHeaders[i].GreenPositiveMaxValue = read_uint8(input);
        subHeaders[i].YellowPositiveMaxValue = read_uint8(input);

        subHeaders[i].RedNegativeMinValue = read_uint8(input);
        subHeaders[i].GreenNegativeMinValue = read_uint8(input);
        subHeaders[i].YellowNegativeMinValue = read_uint8(input);

        subHeaders[i].RedNegativeMaxValue = read_uint8(input);
        subHeaders[i].GreenNegativeMaxValue = read_uint8(input);
        subHeaders[i].YellowNegativeMaxValue = read_uint8(input);

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

    int realDimX = getDimX();
    int realDimY = getDimY();
    int realDimZ = getDimZ();

    data = std::vector<std::vector<float>>(NrOfMaps);
    int dim = realDimX*realDimY*realDimZ;
    for(int i = 0; i < NrOfMaps; i++){
        data[i] = std::vector<float>(dim);
        for(int j = 0; j < dim; j++){
            data[i][j] = read_float(input);
        }
    }

    input.close();
}

int MyVmp::getNrMaps(){
    return NrOfMaps;
}

