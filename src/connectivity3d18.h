#ifndef CONNECTIVITY3D18_H
#define CONNECTIVITY3D18_H

#include "connectivity3d.h"

class Connectivity3D18 : public Connectivity3D
{
public:
    Connectivity3D18();
    std::vector<Point3D> getNeighboursIndex(Point3D p);
};

#endif // CONNECTIVITY3D18_H
