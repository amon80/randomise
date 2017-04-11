#include "tfce.h"
#include "mymath.h"
#include <cmath>
#include <queue>

void computeTfceIteration(StatisticalMap3D& map, StatisticalMap3D& tfce_map, float h, float increment, float E, float H){
    int i = 0;
    StatisticalMap3D binaryClusterMap = createMask(map, moreThan, h);
	//START - Slowest functions
    std::map<float, float> extensions = find_clusters_3D(binaryClusterMap);
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

void tfce(StatisticalMap3D& map, float E, float H, float dh){
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

        if (precision > 200) {
            increment = rangeData/200;
        } else{
            increment = dh;
        }

        steps = (int) ceil(rangeData / increment);
        for (i = 0; i < steps; i++) {
            computeTfceIteration(map, tfce_map, minData + i*increment, increment, E, H);
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

std::vector<index3D> getNeighbours(int x, int y, int z, int dimX, int dimY, int dimZ, StatisticalMap3D& map){
    std::vector<index3D> toReturn;
    for (int j = -1; j <= 1; ++j) {
        if (x+j < 0)
            continue;
        if (x+j >= dimX)
            continue;
        for (int k = -1; k <= 1; ++k) {
            if (y+k < 0)
                continue;
            if (y+k >= dimY)
                continue;
            for (int h = -1; h <= 1; ++h) {
                if (z+h < 0)
                    continue;
                if (z+h >= dimZ)
                    continue;
				if (map(x + j, y + k, z + h) == 1) {
					index3D currentIndex;
					currentIndex.x = x + j;
					currentIndex.y = y + k;
					currentIndex.z = z + h;
					toReturn.push_back(currentIndex);
				}
            }
        }
    }
    return toReturn;
}

std::map<float, float> find_clusters_3D(StatisticalMap3D& image){
    int label = 2;
    std::queue<index3D> q;
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
                //Found new cluster
                if(toReturn(xindex,yindex,zindex) == 1) {
                    index3D currentIndex;
                    currentIndex.x = xindex;
                    currentIndex.y = yindex;
                    currentIndex.z = zindex;
					//Start the exploration from here
                    q.push(currentIndex);
					//Initializing cluster extension
                    extensions[label] = 1;
					//Marking the voxel as belonging to cluster
					toReturn(xindex, yindex, zindex) = label;
                    //Cluster exploration starts
                    while(!q.empty()){
                        index3D queueFront = q.front();
                        int x = queueFront.x;
                        int y = queueFront.y;
                        int z = queueFront.z;
                        q.pop();
                        std::vector<index3D> neighbours = getNeighbours(x, y, z, dimX, dimY, dimZ, toReturn);
                        for(index3D n: neighbours){
                            extensions[label] += 1;
                            toReturn(n.x, n.y, n.z) = label;
                            q.push(n);
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
