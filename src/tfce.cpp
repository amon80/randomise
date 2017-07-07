#include "tfce.h"
#include "mymath.h"
#include "point3d.h"
#include "connectivity3d18.h"
#include <cmath>
#include <queue>

void computeTfceIteration(StatisticalMap3D& map, StatisticalMap3D& tfce_map, float h, float E, float H, Connectivity3D * C){
    int i = 0;
    StatisticalMap3D binaryClusterMap = createMask(map, moreThan, h);
    std::map<float, float> extensions = find_clusters_3D(binaryClusterMap, C);
    turn_into_extent_map(binaryClusterMap, extensions);
	float hAtH = pow(h, H);
    binaryClusterMap.applyOperation(elevate, E);
    binaryClusterMap.applyOperation(multiply, hAtH);
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
	StatisticalMap3D maskPosData = createMask(map, moreThan, 0);
	StatisticalMap3D posData = createMapFromMask(map, maskPosData);
    MinMaxStructure m = posData.findMinMax();
    float minData = m.min;
    float maxData = m.max;
    float rangeData = maxData - minData;
    int i;
    float precision = rangeData/dh;
    int steps;
    float increment;

	if (maxData > 0) {
		//100 steps max
		if (precision > 100) {
			increment = rangeData / 100;
		}
		else {
			increment = dh;
		}

		steps = (int)floor(rangeData / increment);
		for (i = 0; i < steps; i++) {
			computeTfceIteration(posData, tfce_map, minData + i*increment, E, H, C);
		}
		tfce_map.applyOperation(multiply, increment);
	}
    map = tfce_map;
}

void turn_into_extent_map(StatisticalMap3D& clustered_map, std::map<float, float>& extensions){
    int n = clustered_map.size();
    for (int j = 0; j < n; ++j)
        clustered_map[j] = extensions[clustered_map[j]];
}

std::map<float, float> find_clusters_3D(StatisticalMap3D& image, Connectivity3D * C){
    float label = 2;
    std::queue<Point3D> q;
    std::map<float, float> extensions;
	//0 is not a cluster identifier
    extensions[0] = 0;
    int dimX = image.sizeX();
    int dimY = image.sizeY();
    int dimZ = image.sizeZ();
    for (int xindex = 0; xindex < dimX; ++xindex) {
        for (int yindex = 0; yindex < dimY; ++yindex) {
            for (int zindex = 0; zindex < dimZ; ++zindex) {
                Point3D currentIndex(xindex, yindex, zindex);
                if(image(currentIndex) == 1) {
                    //Found new cluster
					//Start the exploration from here
                    q.push(currentIndex);
					//Initializing cluster extension
                    extensions[label] = 1;
					//Marking the voxel as belonging to cluster
                    image(currentIndex) = label;
                    //Cluster exploration starts
                    while(!q.empty()){
                        Point3D queueFront = q.front();
                        q.pop();
                        std::vector<Point3D> neighbours = image.getNeighbours(queueFront, C);
                        for(Point3D n: neighbours){
                            if(image(n) == 1){
                                extensions[label] += 1;
                                image(n) = label;
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
    return extensions;
}
