#pragma once

#include "Object.hpp"


namespace math {

class Sphere : public Object {
    
public:
    Point _pos;
    float Radius;
    
    Sphere(Point pos, float Radius);
    Sphere(Point pos, Point B);
    
    std::optional<Intersection> intersection(const Ray& ray) override;
    
    Vec get_normal_at(const Point& pt);
    
};

}


