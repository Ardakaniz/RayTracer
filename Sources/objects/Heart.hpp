
#ifndef Heart_hpp
#define Heart_hpp

#include "Object.hpp"
#include "math/Point.hpp"
#include "math/Ray.hpp"
#include "math/Vec.hpp"

#include "objects/Sphere.hpp"

class Heart : public Object {
public:
    float a; // width of the heart a>0
    float b; // inclination pf the heart's lobes
    float c; // inclination pf the heart's lobes,  increasing c imply lobes get more split
    // b,c have almost the same role, the bigest one give the orientation by its sign.  positive imply up (ie the peak is botside) b,c must satisfy (|b/c|>1/10 or |c/b|>1/10) to look like a heart
    float d; // d>0, overall size
    // (x^2+y^2+az^2-d)^3-c.x^2.y^3-b.z^2.y^3=0
    Heart(const math::Point& pos, float a_,float b_, float c_, float d_,const float psi, const float theta, const float phi,const math::Color& diffuse_color = math::WHITE);
    
    
    std::optional<math::Intersection> intersection(const math::Ray& ray) const override ;
    
    math::Vec get_normal_at(const math::Point& N) const override;

private:
    float f(const math::Point& N) const; // parametric equation
    float f_t(const math::Ray &ray ,float t) const; //  f_t=0 equation to solve to find intersection
    float f_tp(const math::Ray &ray,float t) const; // its derivative to compute zero with Newton algorithm

    Sphere _sphere;
};
#endif /* Heart_hpp */
