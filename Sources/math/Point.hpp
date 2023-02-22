//
//  Point.hpp
//  Ray_tracing
//
//

#ifndef Point_hpp
#define Point_hpp
#pragma once

#include "math/Vec.hpp"

namespace math {
    struct Vec;
    
    struct Point {
        float x;
        float y;
        float z;
        
        Point& translate(const Vec& vec);
        Point translated(const Vec& vec) const;
        Point rotation_euler(float psi, float theta, float phi) const;
        Point rotation_euler_inv(float psi, float theta, float phi) const;

        Vec to_vec() const;
    };

    Point operator+(const Point& lhs, const Point& rhs);
    Point operator-(const Point& lhs, const Point& rhs);

    Point& operator+=(Point& lhs, const Point& rhs);
    Point& operator-=(Point& lhs, const Point& rhs);
}
#endif /* Point_hpp */
