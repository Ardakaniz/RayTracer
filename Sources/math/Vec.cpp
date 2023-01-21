//
//  Vec.cpp
//  Ray_tracing
//
//

#include "math/Vec.hpp"
#include <cmath>

float math::Vec::dot(const Vec &rhs) const
{
    return x*rhs.x+y*rhs.y+z*rhs.z;
}

float math::Vec::length_sq() const
{
    return x*x+y*y+z*z;
}

float math::Vec::length() const
{
    return std::sqrt(x*x+y*y+z*z);
}

void math::Vec::normalize()
{
    float norm=std::sqrt(x*x+y*y+z*z);
    x=x/norm;
    y=y/norm;
    z=z/norm;
}

math::Vec math::Vec::normalized() const
{
    math::Vec Vec_n;
    Vec_n={x,y,z};
    Vec_n.normalize();
    return Vec_n;
}
