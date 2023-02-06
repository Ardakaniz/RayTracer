#include "objects/Sphere.hpp"




Sphere::Sphere(math::Point pos, float Radius_,const math::Color& diffuse_color) :
Object(pos,diffuse_color),
Radius(Radius_)
{}

Sphere::Sphere(math::Point pos,math::Point B,const math::Color& diffuse_color) :
Object(pos,diffuse_color)
{
    const math::Vec AB={B.x-pos.x,B.y-pos.y,B.z-pos.z};
    Radius=AB.length();
}

std::optional<math::Intersection> Sphere::intersection(const math::Ray& ray) const 
{
    math::Vec CA={ray.origin.x-_pos.x,ray.origin.y-_pos.y,CA.z=ray.origin.z-_pos.z};
    math::Point A=ray.origin;
    float CA2=CA.length_sq();
    math::Vec u=ray.direction;
    
    float delta=4*u.dot(CA)*u.dot(CA)-4*(CA2-Radius*Radius);
    
    if (delta<0)
    {
        return std::nullopt;
        
    }
    
    else
    {
        float tm= ( -2*u.dot(CA)-std::sqrt(delta) )/2;
        math::Point TM=A.translate(tm*u);
        return math::Intersection {TM,*this,ray,tm};
    }
}

math::Vec Sphere::get_normal_at(const math::Point& pt) const
{
    math::Vec n={pt.x-_pos.x,pt.y-_pos.y,pt.z-_pos.z};
    n.normalized();
    return n;
    
}

