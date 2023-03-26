#include "objects/Box.hpp"
#include "objects/utils.hpp"

Box::Box(const math::Point& pos,float a_,float b_, float c_,float R_b_,const float psi, const float theta, const float phi,const math::Color& diffuse_color) :
Object(pos,psi,theta,phi,diffuse_color),
a(a_),
b(b_),
c(c_),
R_b(R_b_),

_sphere(pos, 1.8*2)
{}

std::optional<math::Intersection> Box::intersection(const math::Ray& ray) const {
    return utils::compute_intersec(
        _sphere,
        *this,
        ray,
        [&](const math::Ray& ray, float t) {
            const math::Point ray_pt{ ray.origin.translated(t*ray.direction) } ;
            const math::Point pt{ (ray_pt- _pos).rotation_euler(_psi,_theta,_phi) +_pos };
            return f(pt);
        }
    );
}
math::Vec Box::get_normal_at(const math::Point &N) const
{
    math::Point pt=(N-_pos).rotation_euler_inv(_psi,_theta,_phi);
    //we will compute here grad(f) at pt
    const float df_x=6*pt.x*pt.x*pt.x*pt.x*pt.x/(a*a*a*a*a*a);
    const float df_y=6*pt.y*pt.y*pt.y*pt.y*pt.y/(b*b*b*b*b*b);
    const float df_z=6*pt.z*pt.z*pt.z*pt.z*pt.z/(c*c*c*c*c*c);
    math::Point m={df_x,df_y,df_z}; // calcul du vec normal pour non tourné puis je tourne le vecteur
    math::Point n=m.rotation_euler(_psi,_theta,_phi);
    math::Vec n_rot=n.to_vec();
    n_rot.normalize();
    return n_rot;
}

float Box::f(const math::Point &M) const
{
    float X6=(M.x-_pos.x)*(M.x-_pos.x)*(M.x-_pos.x)*(M.x-_pos.x)*(M.x-_pos.x)*(M.x-_pos.x)/(a*a*a*a*a*a);
    float Y6=(M.y-_pos.y)*(M.y-_pos.y)*(M.y-_pos.y)*(M.y-_pos.y)*(M.y-_pos.y)*(M.y-_pos.y)/(b*b*b*b*b*b);
    float Z6=(M.z-_pos.z)*(M.z-_pos.z)*(M.z-_pos.z)*(M.z-_pos.z)*(M.z-_pos.z)*(M.z-_pos.z)/(c*c*c*c*c*c);
    return X6+Y6+Z6-R_b;
}
