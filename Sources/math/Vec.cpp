//
//  Vec.cpp
//  Ray_tracing
//
//

#include "math/Vec.hpp"
#include <cmath>

namespace math {
    float Vec::dot(const Vec &rhs) const {
        return x*rhs.x+y*rhs.y+z*rhs.z;
    }

    float Vec::length_sq() const {
        return x*x+y*y+z*z;
    }

    float Vec::length() const {
        return std::sqrt(x*x+y*y+z*z);
    }

    void Vec::normalize() {
        float norm=std::sqrt(x*x+y*y+z*z);
        x=x/norm;
        y=y/norm;
        z=z/norm;
    }

    Vec Vec::normalized() const {
        Vec Vec_n;
        Vec_n={x,y,z};
        Vec_n.normalize();
        return Vec_n;
    }

    /** OPERATORS **/

    Vec operator*(const Vec& lhs, const Vec& rhs) {
        return
            { .x = lhs.x * rhs.x
            , .y = lhs.y * rhs.y
            , .z = lhs.z * rhs.z
            };
    }

    Vec operator*(const Vec& lhs, float scalar) {
        return
            { .x = lhs.x * scalar
            , .y = lhs.y * scalar
            , .z = lhs.z * scalar
            };
    }
    
    Vec operator*(float scalar, const Vec& rhs) {
        return rhs * scalar;
    }

    Vec operator/(const Vec& lhs, const Vec& rhs) {
        return
            { .x = lhs.x / rhs.x
            , .y = lhs.y / rhs.y
            , .z = lhs.z / rhs.z
            };
    }

    Vec operator/(const Vec& lhs, float scalar) {
        return
            { .x = lhs.x / scalar
            , .y = lhs.y / scalar
            , .z = lhs.z / scalar
            };
    }

    Vec operator+(const Vec& lhs, const Vec& rhs) {
        return
            { .x = lhs.x + rhs.x
            , .y = lhs.y + rhs.y
            , .z = lhs.z + rhs.z
            };
    }

    Vec operator+(const Vec& lhs, float scalar) {
        return
            { .x = lhs.x + scalar
            , .y = lhs.y + scalar
            , .z = lhs.z + scalar
            };
    }

    Vec operator-(const Vec& lhs, const Vec& rhs) {
        return
            { .x = lhs.x - rhs.x
            , .y = lhs.y - rhs.y
            , .z = lhs.z - rhs.z
            };
    }

    Vec operator-(const Vec& lhs, float scalar) {
        return
            { .x = lhs.x - scalar
            , .y = lhs.y - scalar
            , .z = lhs.z - scalar
            };
    }

    Vec& operator*=(Vec& lhs, const Vec& rhs) {
        lhs = lhs * rhs;                      
        return lhs;                           
    }                                         
    Vec& operator*=(Vec& lhs, float scalar) { 
        lhs = lhs * scalar;                  
        return lhs;                          
    }

    Vec& operator/=(Vec& lhs, const Vec& rhs) {
        lhs = lhs / rhs;                      
        return lhs;                           
    }                                         
    Vec& operator/=(Vec& lhs, float scalar) { 
        lhs = lhs / scalar;                  
        return lhs;                          
    }

    Vec& operator+=(Vec& lhs, const Vec& rhs) {
        lhs = lhs + rhs;                      
        return lhs;                           
    }                                         
    Vec& operator+=(Vec& lhs, float scalar) { 
        lhs = lhs + scalar;                  
        return lhs;                          
    }

    Vec& operator-=(Vec& lhs, const Vec& rhs) {
        lhs = lhs - rhs;                      
        return lhs;                           
    }                                         
    Vec& operator-=(Vec& lhs, float scalar) { 
        lhs = lhs - scalar;                  
        return lhs;                          
    }

    std::ostream& operator<<(std::ostream& os, const Vec& vec) {
        os << "Vec(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return os;
    }
}
