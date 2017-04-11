#ifndef CONNECTIVITY3D6_H
#define CONNECTIVITY3D6_H

#include "connectivity3d.h"

class Connectivity3D6 : public Connectivity3D
{
public:
    Connectivity3D6();
    std::vector<Point3D> getNeighboursIndex(Point3D p);
};

#endif // CONNECTIVITY3D6_H
