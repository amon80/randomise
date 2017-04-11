#include "tfce.h"
#include "mymath.h"
#include "point3d.h"
#include "connectivity3d18.h"
#include <cmath>
#include <queue>

void computeTfceIteration(StatisticalMap3D& map, StatisticalMap3D& tfce_map, float h, float increment, float E, float H, Connectivity3D * C){
    int i = 0;
    StatisticalMap3D binaryClusterMap = createMask(map, moreThan, h);
	//START - Slowest functions
    std::map<float, float> extensions = find_clusters_3D(binaryClusterMap, C);
    turn_into_extent_map(binaryClusterMap, extensions);
	//END - Slowest functions
    binaryClusterMap.applyOperation(elevate, E);
    binaryClusterMap.applyOperation(multiply, pow(h,H));
    binaryClusterMap.applyOperation(multiply, increment);
    int dim = tfce_map.size();
    for (i = 0; i < dim; ++i)
        tfce_map[i] += binaryClusterMap[i];
}

StatisticalMap3D createMask(StatisticalMap3D& map, bool (*confront)(const float, const float), const float value){
    int n = map.size();
    StatisticalMap3D toReturn(map);
    for(int i = 0; i < n; i++)
        if(confront(map[i], value))
            toReturn[i] = 1;
        else
            toReturn[i] = 0;
    return toReturn;
}

StatisticalMap3D createMapFromMask(StatisticalMap3D& map, StatisticalMap3D& mask){
    StatisticalMap3D toReturn(map);
    int n = map.size();
    for (int i = 0; i < n; ++i)
        if(mask[i] == 0)
            toReturn[i] = 0;
    return toReturn;
}

void tfce(StatisticalMap3D& map, float E, float H, float dh, Connectivity3D * C){
    if(C == nullptr)
        C = new Connectivity3D18();
    StatisticalMap3D tfce_map(map);
    int n = tfce_map.size();
    for(int i = 0; i < n; i++)
        tfce_map[i] = 0;
    MinMaxStructure m = map.findMinMax();
    float minData = m.min;
    float maxData = m.max;
    float rangeData = maxData - minData;
    if(minData >= 0){
        int i;
        float precision = rangeData/dh;
        int steps;
        float increment;

        //200 steps max
        if (precision > 200) {
            increment = rangeData/200;
        } else{
            increment = dh;
        }

        steps = (int) ceil(rangeData / increment);
        for (i = 0; i < steps; i++) {
            computeTfceIteration(map, tfce_map, minData + i*increment, increment, E, H, C);
        }
    }else{
        StatisticalMap3D maskPosData = createMask(map, moreThan, 0);
        StatisticalMap3D maskNegData = createMask(map, lessThan, 0);
        StatisticalMap3D posData = createMapFromMask(map, maskPosData);
        StatisticalMap3D negData = createMapFromMask(map, maskNegData);
        negData.flipMap();
        tfce(posData, E, H, dh);
        tfce(negData, E, H, dh);
        negData.flipMap();
        tfce_map = posData + negData;
    }
    map = tfce_map;
}

void turn_into_extent_map(StatisticalMap3D& clustered_map, std::map<float, float>& extensions){
    int n = clustered_map.size();
    StatisticalMap3D extent_map(clustered_map);
    for (int j = 0; j < n; ++j)
        extent_map[j] = extensions[clustered_map[j]];
    clustered_map = extent_map;
}

std::map<float, float> find_clusters_3D(StatisticalMap3D& image, Connectivity3D * C){
    int label = 2;
    std::queue<Point3D> q;
    std::map<float, float> extensions;
	//0 is not a cluster identifier
    extensions[0] = 0;
    StatisticalMap3D toReturn(image);
    int dimX = image.sizeX();
    int dimY = image.sizeY();
    int dimZ = image.sizeZ();
    for (int xindex = 0; xindex < dimX; ++xindex) {
        for (int yindex = 0; yindex < dimY; ++yindex) {
            for (int zindex = 0; zindex < dimZ; ++zindex) {
                Point3D currentIndex(xindex, yindex, zindex);
                if(toReturn(currentIndex) == 1) {
                    //Found new cluster
					//Start the exploration from here
                    q.push(currentIndex);
					//Initializing cluster extension
                    extensions[label] = 1;
					//Marking the voxel as belonging to cluster
                    toReturn(currentIndex) = label;
                    //Cluster exploration starts
                    while(!q.empty()){
                        Point3D queueFront = q.front();
                        q.pop();
                        std::vector<Point3D> neighbours = toReturn.getNeighbours(queueFront, C);
                        for(Point3D n: neighbours){
                            if(toReturn(n) == 1){
                                extensions[label] += 1;
                                toReturn(n) = label;
                                q.push(n);
                            }
                        }
                    }
                    //cluster exploration ends, updating label for the next cluster
                    label++;
                }
            }
        }
    }

    image = toReturn;
    return extensions;
}
