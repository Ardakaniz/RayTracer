#pragma once

#include "Object.hpp"




class Sphere : public Object {
    
public:
    float Radius;
    
    Sphere(math::Point pos, float Radius_,const math::Color& diffuse_color = math::WHITE);
    Sphere(math::Point pos, math::Point B,const math::Color& diffuse_color = math::WHITE);
    
    std::optional<math::Intersection> intersection(const math::Ray& ray) const override;
    
    math::Vec get_normal_at(const math::Point& pt) const override;
    
};




