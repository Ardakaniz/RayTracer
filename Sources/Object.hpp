//
//  Object.hpp
//  Ray_tracing
//
//

#ifndef Object_hpp
#define Object_hpp
#pragma once
#include "Ray.hpp"

class Object {
    
    std::optional<Intersection> intersection(const math::Ray& ray);
    Vec get_normal_at(const Point& pt);
};


#endif /* Object_hpp */
