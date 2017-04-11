#include "connectivity3d6.h"

Connectivity3D6::Connectivity3D6()
{

}

std::vector<Point3D> Connectivity3D6::getNeighboursIndex(Point3D p){
    std::vector<Point3D> toReturn(6);
    toReturn[0] = Point3D(p.x+1, p.y, p.z);
    toReturn[1] = Point3D(p.x-1, p.y, p.z);
    toReturn[2] = Point3D(p.x, p.y+1, p.z);
    toReturn[3] = Point3D(p.x, p.y-1, p.z);
    toReturn[4] = Point3D(p.x, p.y, p.z+1);
    toReturn[5] = Point3D(p.x, p.y, p.z-1);
    return toReturn;
}
