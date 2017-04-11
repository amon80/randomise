#include "connectivity3d18.h"

Connectivity3D18::Connectivity3D18()
{

}

std::vector<Point3D> Connectivity3D18::getNeighboursIndex(Point3D p){
    std::vector<Point3D> toReturn(18);
    //6 connectivity
    toReturn[0] = Point3D(p.x+1, p.y, p.z);
    toReturn[1] = Point3D(p.x-1, p.y, p.z);
    toReturn[2] = Point3D(p.x, p.y+1, p.z);
    toReturn[3] = Point3D(p.x, p.y-1, p.z);
    toReturn[4] = Point3D(p.x, p.y, p.z+1);
    toReturn[5] = Point3D(p.x, p.y, p.z-1);
    //other 12 to go
    toReturn[6] = Point3D(p.x+1, p.y+1, p.z);
    toReturn[7] = Point3D(p.x+1, p.y-1, p.z);
    toReturn[8] = Point3D(p.x-1, p.y+1, p.z);
    toReturn[9] = Point3D(p.x-1, p.y-1, p.z);
    toReturn[10] = Point3D(p.x+1, p.y, p.z+1);
    toReturn[11] = Point3D(p.x+1, p.y, p.z-1);
    toReturn[12] = Point3D(p.x-1, p.y, p.z+1);
    toReturn[13] = Point3D(p.x-1, p.y, p.z-1);
    toReturn[14] = Point3D(p.x, p.y+1, p.z+1);
    toReturn[15] = Point3D(p.x, p.y+1, p.z-1);
    toReturn[16] = Point3D(p.x, p.y-1, p.z+1);
    toReturn[17] = Point3D(p.x, p.y-1, p.z-1);
    return toReturn;
}
