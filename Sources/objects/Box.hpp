#pragma once

#include "Object.hpp"
#include "math/Point.hpp"
#include "math/Ray.hpp"
#include "math/Vec.hpp"

#include "objects/Sphere.hpp"
class Box : public Object {
    public:
    float a;
    float b;
    float c;
    float R_b;
    
    // (x/a)^6+(y/b)^6+(z/c)^6=R_b
    
    Box(const math::Point& pos,float a_,float b_, float c_,float R_b_,const float psi, const float theta, const float phi,const math::Color& diffuse_color = math::WHITE);
    
    std::optional<math::Intersection> intersection(const math::Ray& ray) const override ;
    
    math::Vec get_normal_at(const math::Point& M) const override;
    
private:
    float f(const math::Point& M) const; // parametric equation
    Sphere _sphere;
    
    
    
};

