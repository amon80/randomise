#ifndef TFCE_H
#define TFCE_H

#include "statisticalmap3d.h"

struct index3D{
    int x;
    int y;
    int z;
};

StatisticalMap3D createMapFromMask(StatisticalMap3D& map, StatisticalMap3D &mask);
StatisticalMap3D createMask(StatisticalMap3D& map, bool (*confront)(const float, const float), const float value);
void computeTfceIteration(StatisticalMap3D& map, StatisticalMap3D& tfce_map, float h, float increment, float E, float H);
void tfce(StatisticalMap3D& map, float E = 0.5, float H = 2.0, float dh = 0.1);
int find_clusters_3D(StatisticalMap3D& image);
void turn_into_extent_map(StatisticalMap3D& clustered_map, int num_clusters);

#endif // TFCE_H
