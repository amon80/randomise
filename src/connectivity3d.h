#ifndef CONNECTIVITY3D_H
#define CONNECTIVITY3D_H

#include "point3d.h"
#include <vector>

class Connectivity3D
{
public:
    Connectivity3D();
    virtual std::vector<Point3D> getNeighboursIndex(Point3D p) = 0;
};

#endif // CONNECTIVITY3D_H
