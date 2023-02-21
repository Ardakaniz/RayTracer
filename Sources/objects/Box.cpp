#include "objects/Box.hpp"
#include "objects/utils.hpp"

Box::Box(const math::Point& pos,float a_,float b_, float c_,float R_b_,const math::Color& diffuse_color) :
Object(pos, diffuse_color),
a(a_),
b(b_),
c(c_),
R_b(R_b_),
_sphere(pos, 3.f)
{}

std::optional<math::Intersection> Box::intersection(const math::Ray& ray) const {
    return utils::compute_intersec(
        _sphere,
        *this,
        ray,
        [&](const math::Ray& ray, float t) {
            return f(ray.origin.translated(t*ray.direction));
        }
    );
}
math::Vec Box::get_normal_at(const math::Point &pt) const
{
    //we will compute here grad(f) at pt
    const float df_x=6*(pt.x - _pos.x)*(pt.x - _pos.x)*(pt.x - _pos.x)*(pt.x - _pos.x)*(pt.x - _pos.x)/(a*a*a*a*a*a);
    const float df_y=6*(pt.y - _pos.y)*(pt.y - _pos.y)*(pt.y - _pos.y)*(pt.y - _pos.y)*(pt.y - _pos.y)/(b*b*b*b*b*b);
    const float df_z=6*(pt.z - _pos.z)*(pt.z - _pos.z)*(pt.z - _pos.z)*(pt.z - _pos.z)*(pt.z - _pos.z)/(c*c*c*c*c*c);
    math::Vec n={df_x,df_y,df_z};
    n.normalize();
    return n;
}

float Box::f(const math::Point &M) const
{
    float X6=(M.x-_pos.x)*(M.x-_pos.x)*(M.x-_pos.x)*(M.x-_pos.x)*(M.x-_pos.x)*(M.x-_pos.x)/(a*a*a*a*a*a);
    float Y6=(M.y-_pos.y)*(M.y-_pos.y)*(M.y-_pos.y)*(M.y-_pos.y)*(M.y-_pos.y)*(M.y-_pos.y)/(b*b*b*b*b*b);
    float Z6=(M.z-_pos.z)*(M.z-_pos.z)*(M.z-_pos.z)*(M.z-_pos.z)*(M.z-_pos.z)*(M.z-_pos.z)/(c*c*c*c*c*c);
    return X6+Y6+Z6-R_b;
}
