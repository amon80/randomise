#include "myglm.h"
#include "binaryio.h"
#include <fstream>
#include <iostream>
#include <string>

MyGLM::MyGLM()
{

}

void readglm(const char * filename){
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
    std::vector<int> nConfoundStudies;

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
    std::string nameOfCortexBasedMaskfile;

    //Opening file in read only binary mode
    std::ifstream input(filename, std::ios::binary);

    //START READING

    version = read_uint16(input);
    typeGLMFlag = read_uint8(input);
    rfxGLMFlag = read_uint8(input);

    if(rfxGLMFlag == 1){
        nSubjects = read_uint32(input);
        nPredictorsForSubject = read_uint32(input);
    }

    nTimePoints = read_uint32(input);
    nAllPredictors = read_uint32(input);
    nConfoundPredictors = read_uint32(input);
    nStudies = read_uint32(input);

    if(nStudies > 1){
        nStudiesConfoundInfo = read_uint32(input);
        nConfoundStudies = std::vector<int>(nStudiesConfoundInfo);
        for(int i = 0; i < nStudiesConfoundInfo; i++)
            nConfoundStudies[i] = read_uint32(input);
    }

    separatePredictorsFlag = read_uint8(input);
    timeCourseNormalizationFlag = read_uint8(input);
    resolution = read_uint16(input);
    serialCorrelationPerformedFlag = read_uint8(input);
    meanSerialCorrelationBeforeCorrection = read_float(input);
    meanSerialCorrelationAfterCorrection = read_float(input);

    if(typeGLMFlag == 0){
        dimX = read_uint16(input);
        dimY = read_uint16(input);
        dimZ = read_uint16(input);
    }
    if(typeGLMFlag == 1){
        startX = read_uint16(input);
        endX = read_uint16(input);
        startY = read_uint16(input);
        endY = read_uint16(input);
        startZ = read_uint16(input);
        endZ = read_uint16(input);
    }
    if(typeGLMFlag == 2){
        nVertices = read_uint32(input);
    }

    cortexBasedMaskFlag = read_uint8(input);
    nVoxelsInMask = read_uint32(input);

    nameOfCortexBasedMaskfile = read_string(input);

    std::vector<int> nTimePointsForStudy(nStudies);
    std::vector<std::string> vtcNames(nStudies);
    std::vector<std::string> sdmNames(nStudies);
    std::vector<std::string> ssmNames;

    if(typeGLMFlag == 2)
        ssmNames = std::vector<std::string>(nStudies);
    for(int i = 0; i < nStudies; i++){
        nTimePointsForStudy[i] = read_uint32(input);
        vtcNames[i] = read_string(input);
        if(typeGLMFlag == 2)
            ssmNames[i] = read_string(input);
        sdmNames[i] = read_string(input);
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

    //START ------DATA not in the docs---------
    std::vector<std::string> predictors(50);
    std::vector<std::string> patients(50);
    for(int i = 0; i < 50; i++){
        predictors[i] = read_string(input);
        patients[i] = read_string(input);
        std::cout << "Predictor " << i << " - " << predictors[i] << std::endl;
        std::cout << "Patient " << i << " - " << patients[i] << std::endl;
        for(int j = 0; j < 3; j++){
            //NOTE: Maybe the commented function in binaryio?????
            read_uint32(input);
        }
    }
    //END --------DATA not in the docs----------

    //Ok, so all that's left now is the actual data
    std::vector<std::vector<float>> data(nValues);
    for(int i = 0; i < nValues; i++){
        data[i] = std::vector<float>(nVoxel);
        for(int j = 0; j < nVoxel; j++)
            data[i][j] = read_float(input);
    }

    //closing file
    input.close();
}
