//
//  Ray.hpp
//  Ray_tracing
//
//

#ifndef Ray_hpp
#define Ray_hpp
#pragma once

#include "Point.hpp"
#include "Vec.hpp"

namespace math {
    struct Intersection;

    struct Ray {
        Point origin;
        Vec direction;
        
        Ray(Point origin_, Vec direction_);
        Ray(Point A, Point B);
        
        Ray reflected(const Intersection& intersec) const;
    };
}

#endif /* Ray_hpp */
