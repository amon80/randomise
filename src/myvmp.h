#ifndef MYVMP_H
#define MYVMP_H

#include <vector>
#include <string>
#include "myvmpheader.h"

const int MAGIC_NUMBER = 0xA1B2C3D4;
const int VERSION_NUMBER = 6;
const int DIMX = 256;
const int DIMY = 256;
const int DIMZ = 256;
const int STARTX = 57;
const int ENDX = 231;
const int STARTY = 52;
const int ENDY = 172;
const int STARTZ = 59;
const int ENDZ = 197;
const int RESOLUTION = 3;
const int DOCTYPE = 1;

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
