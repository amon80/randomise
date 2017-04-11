#ifndef CONNECTIVITY3D26_H
#define CONNECTIVITY3D26_H

#include "connectivity3d.h"

class Connectivity3D26 : public Connectivity3D
{
public:
    Connectivity3D26();
    std::vector<Point3D> getNeighboursIndex(Point3D p);
};

#endif // CONNECTIVITY3D26_H
