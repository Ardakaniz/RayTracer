//
//  Ray.cpp
//  Ray_tracing
//
//

#include "Ray.hpp"

math::Ray::Ray(Point origin_, Vec direction_)
{
    origin=origin_;
    direction=direction_;
}

math::Ray::Ray(Point A, Point B)
{
    origin=A;
    Vec dir;
    dir.x=B.x-A.x;
    dir.y=B.y-A.y;
    dir.z=B.z-A.z;
    dir.normalize();
    direction=dir;
    
}

