#ifndef MYVMP_H
#define MYVMP_H

#include <vector>
#include <string>
#include "myvmpheader.h"

const int MAGIC_NUMBER = 0xA1B2C3D4;

class MyVmp
{
public:
    MyVmp(int NrOfMaps = 0, int NrOfTimePoints = 0, int NrOfMapsParams = 0);
    void readvmp(const char * filename);
    void writevmp(const char * filename);
    int getNrMaps();
    int getDimX();
    int getDimY();
    int getDimZ();
    std::vector<float>& operator[](const std::size_t idx);
    MyVmpHeader& getSubHeader(const std::size_t idx);
    void addSubMap();
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
    std::vector<MyVmpHeader> subHeaders;

    //actualdata
    std::vector<std::vector<float>> data;
};

#endif // MYVMP_H
