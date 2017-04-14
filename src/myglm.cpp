#include "myglm.h"
#include <fstream>
#include <cctype>
#include <iostream>

MyGLM::MyGLM()
{

}


char * readString(std::ifstream& input)
{
    int j = 0;
    char * string = new char[MAXLENGTHFILENAME];
    char * buffer = new char[1];
    while(true){
        input.read((char*)buffer, 1);
        if(!iscntrl(*buffer))
            string[j++] = *buffer;
        else{
            break;
        }
    }
    delete[] buffer;
    return string;
}

void readglm(const char * filename){
    int * intBuffer = new int[1];
    float * floatBuffer = new float[1];
    char * charBuffer = new char[1];

    //Variables declaration
    int version;
    int typeGLMFlag;
    int rfxGLMFlag;

    int nSubjects;
    int nPredictorsForSubject;

    int nTimePoints;
    int nAllPredictors;
    int nConfoundPredictors;
    int nStudies;

    int nStudiesConfoundInfo;
    int * nConfoundStudies;

    int separatePredictorsFlag;
    int timeCourseNormalizationFlag;
    int resolution;
    int serialCorrelationPerformedFlag;
    float meanSerialCorrelationBeforeCorrection;
    float meanSerialCorrelationAfterCorrection;

    int dimX;
    int dimY;
    int dimZ;

    int startX;
    int endX;
    int startY;
    int endY;
    int startZ;
    int endZ;

    int nVertices;

    int cortexBasedMaskFlag;
    int nVoxelsInMask;
    char * nameOfCortexBasedMaskfile;

    //Opening file in read only binary mode
    std::ifstream input(filename, std::ios::binary);

    //START READING

    //Calculating lenght
    input.seekg (0, input.end);
    int length = input.tellg();
    input.seekg (0, input.beg);

    input.read((char *)intBuffer, 2);
    version = *intBuffer;
    input.read((char *)intBuffer, 1);
    typeGLMFlag = *intBuffer;
    input.read((char *)intBuffer, 1);
    rfxGLMFlag = *intBuffer;

    if(rfxGLMFlag == 1){
        input.read((char *)intBuffer, 4);
        nSubjects = *intBuffer;
        input.read((char*)intBuffer, 4);
        nPredictorsForSubject = *intBuffer;
    }

    input.read((char*)intBuffer, 4);
    nTimePoints = *intBuffer;
    input.read((char*)intBuffer, 4);
    nAllPredictors = *intBuffer;
    input.read((char *)intBuffer, 4);
    nConfoundPredictors = *intBuffer;
    input.read((char *)intBuffer, 4);
    nStudies = *intBuffer;

    if(nStudies > 1){
        input.read((char *)intBuffer, 4);
        nStudiesConfoundInfo = *intBuffer;
        nConfoundStudies = new int[nStudiesConfoundInfo];
        for(int i = 0; i < nStudiesConfoundInfo; i++){
            input.read((char *)intBuffer, 4);
            nConfoundStudies[i] = *intBuffer;
        }
    }

    input.read((char *)intBuffer, 1);
    separatePredictorsFlag = *intBuffer;
    input.read((char *)intBuffer, 1);
    timeCourseNormalizationFlag = *intBuffer;
    input.read((char *)intBuffer, 2);
    resolution = *intBuffer;
    input.read((char *)intBuffer, 1);
    serialCorrelationPerformedFlag = *intBuffer;
    input.read((char *)floatBuffer, 4);
    meanSerialCorrelationBeforeCorrection = *floatBuffer;
    input.read((char *)floatBuffer, 4);
    meanSerialCorrelationAfterCorrection = *floatBuffer;

    if(typeGLMFlag == 0){
        input.read((char *)intBuffer, 2);
        dimX = *intBuffer;
        input.read((char *)intBuffer, 2);
        dimY = *intBuffer;
        input.read((char *)intBuffer, 2);
        dimZ = *intBuffer;
    }
    if(typeGLMFlag == 1){
        input.read((char *)intBuffer, 2);
        startX = *intBuffer;
        input.read((char *)intBuffer, 2);
        endX = *intBuffer;
        input.read((char *)intBuffer, 2);
        startY = *intBuffer;
        input.read((char *)intBuffer, 2);
        endY = *intBuffer;
        input.read((char *)intBuffer, 2);
        startZ = *intBuffer;
        input.read((char *)intBuffer, 2);
        endZ = *intBuffer;
    }
    if(typeGLMFlag == 2){
        input.read((char *)intBuffer, 4);
        nVertices = *intBuffer;
    }

    input.read((char*)intBuffer, 1);
    cortexBasedMaskFlag = *intBuffer;
    input.read((char*)intBuffer, 4);
    nVoxelsInMask = *intBuffer;

    nameOfCortexBasedMaskfile = readString(input);

    int * nTimePointsForStudy = new int[nStudies];
    char ** vtcNames = new char*[nStudies];
    char ** sdmNames = new char*[nStudies];
    char ** ssmNames;
    if(typeGLMFlag == 2)
        ssmNames = new char*[nStudies];

    for(int i = 0; i < nStudies; i++){
        input.read((char *)intBuffer, 4);
        nTimePointsForStudy[i] = *intBuffer;
        vtcNames[i] = readString(input);
        if(typeGLMFlag == 2)
            ssmNames[i] = readString(input);
        sdmNames[i] = readString(input);
    }
    /*
    for(int i = 0; i < nStudies; i++){
        std::cout << "VTC " << i << " " << vtcNames[i] << std::endl;
        std::cout << "SDM " << i << " " << sdmNames[i] << std::endl;
    }
    */
    if(rfxGLMFlag == 0){
        //TODO
    }
    int nValues;
    int nVoxel;

    if(typeGLMFlag == 0){
        nVoxel = dimX * dimY * dimZ;
    }
    if(typeGLMFlag == 1){
        nVoxel = (endX - startX)/resolution * (endY - startY)/resolution * (endZ-startZ)/resolution;
    }
    if(typeGLMFlag == 2){
        nVoxel = nVertices;
    }

    if(rfxGLMFlag == 0){
        if(serialCorrelationPerformedFlag == 0){
            nValues = 2 * nAllPredictors + 2;
        }
        if(serialCorrelationPerformedFlag == 1){
            nValues = 2 * nAllPredictors + 3;
        }
        if(serialCorrelationPerformedFlag == 2){
            nValues = 2 * nAllPredictors + 4;
        }
    }
    if(rfxGLMFlag == 1){
        nValues = 1 + nSubjects * nPredictorsForSubject;
    }

    int actualDataBytes = nValues * nVoxel;
    actualDataBytes *= 4;
    //START ------DATA not in the docs---------
    char ** predictors = new char*[50];
    char ** patients = new char*[50];
    for(int i = 0; i < 50; i++){
        predictors[i] = readString(input);
        patients[i] = readString(input);
        std::cout << "Predictor " << i << " - " << predictors[i] << std::endl;
        std::cout << "Patient " << i << " - " << patients[i] << std::endl;
        for(int j = 0; j < 3; j++){
            input.read((char*)intBuffer, 4);
            std::cout << i << " - " << j << " - " << *intBuffer << std::endl;
        }
    }
    //END --------DATA not in the docs----------

    //check if #bytes to read corrisponds to # of data bytes
    int currentPos = input.tellg();
    int toTheEndOfFile = length - currentPos;
    std::cout << "Bytes to read until the end of the file " << toTheEndOfFile << std::endl;

    //Ok, so all that's left now is the actual data
    float ** data = new float*[nValues];
    for(int i = 0; i < nValues; i++){
        std::cout << "Inizio volume " << i << std::endl;
        data[i] = new float[nVoxel];
        for(int j = 0; j < nVoxel; j++){
            input.read((char*)floatBuffer,4);
            std::cout << "Volume " << i << " Voxel " << j << " - " << *floatBuffer << std::endl;
            data[i][j] = *floatBuffer;
        }
        std::cout << "Fine volume " << i << std::endl;
    }

    currentPos = input.tellg();
    if(input.eof())
        std::cout << "EOF" << std::endl;

    //deleting all buffers
    delete[] intBuffer;
    delete[] floatBuffer;
    delete[] charBuffer;

    //closing file
    input.close();
}
