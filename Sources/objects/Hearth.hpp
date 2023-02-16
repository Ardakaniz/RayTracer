
#ifndef Hearth_hpp
#define Hearth_hpp

#include "Object.hpp"
#include "math/Point.hpp"
#include "math/Ray.hpp"
#include "math/Vec.hpp"

class Hearth : public Object {
    
public:
    float a; // width of the hearth a>0
    float b; // inclination pf the heart's lobes
    float c; // inclination pf the heart's lobes,  increasing c imply lobes get more split
    // b/c have almost the same role, the bigest one give the orientation by its sign.  positive imply up (ie the peak is botside)
    float d; // d>0, overall size
    // (x^2+a^2+z^2-1)^3-c.x^2.z^3-b.y^2.z^3=0 parametric equation
    
    
    Hearth(math::Point pos, float a_,float b_, float c_, float d_,const math::Color& diffuse_color = math::WHITE);
    
    float f(math::Point M); // parametric equation
    float f_t(const math::Ray &ray ,float t); //  f_t=0 equation to solve to find intersection
    float f_tp(const math::Ray &ray,float t); // its derivative to compute zero with Newton algorithm
    
    
    
    std::optional<math::Intersection> intersection(const math::Ray& ray) const override ;
    
    math::Vec get_normal_at(const math::Point& pt) const override;
};
#endif /* Hearth_hpp */
