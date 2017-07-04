#ifndef TFCE_H
#define TFCE_H

#include "statisticalmap3d.h"
#include <map>

StatisticalMap3D createMapFromMask(StatisticalMap3D& map, StatisticalMap3D &mask);
StatisticalMap3D createMask(StatisticalMap3D& map, bool (*confront)(const float, const float), const float value);
void computeTfceIteration(StatisticalMap3D& map, StatisticalMap3D& tfce_map, float h, float E, float H, Connectivity3D *C);
void tfce(StatisticalMap3D& map, float E = 0.5, float H = 2.0, float dh = 0.1, Connectivity3D * C = nullptr);
std::map<float, float> find_clusters_3D(StatisticalMap3D& image, Connectivity3D *C);
void turn_into_extent_map(StatisticalMap3D& clustered_map, std::map<float, float> &extensions);

#endif // TFCE_H
