#pragma once

#include "Object.hpp"


namespace math {

class Sphere : public Object {
    
public:
    Point Center;
    float Radius;
    
    Sphere(Point Center, float Radius);
    Sphere(Point Center, Point B);
    
    std::optional<Intersection> intersection(const Ray& ray) override;
    
    Vec get_normal_at(const math::Point& pt);
    
};

}


