#include "connectivity3d26.h"

Connectivity3D26::Connectivity3D26()
{

}

std::vector<Point3D> Connectivity3D26::getNeighboursIndex(Point3D p){
    std::vector<Point3D> toReturn(27);
    //6 connectivity
    toReturn[0] = Point3D(p.x+1, p.y, p.z);
    toReturn[1] = Point3D(p.x-1, p.y, p.z);
    toReturn[2] = Point3D(p.x, p.y+1, p.z);
    toReturn[3] = Point3D(p.x, p.y-1, p.z);
    toReturn[4] = Point3D(p.x, p.y, p.z+1);
    toReturn[5] = Point3D(p.x, p.y, p.z-1);
    //18 connectivity
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
    //other 8 to go
    toReturn[18] = Point3D(p.x+1, p.y+1, p.z+1);
    toReturn[19] = Point3D(p.x+1, p.y+1, p.z-1);
    toReturn[20] = Point3D(p.x+1, p.y-1, p.z+1);
    toReturn[21] = Point3D(p.x+1, p.y-1, p.z-1);
    toReturn[22] = Point3D(p.x-1, p.y+1, p.z+1);
    toReturn[23] = Point3D(p.x-1, p.y+1, p.z-1);
    toReturn[24] = Point3D(p.x-1, p.y-1, p.z+1);
    toReturn[25] = Point3D(p.x-1, p.y-1, p.z-1);
    return toReturn;
}
