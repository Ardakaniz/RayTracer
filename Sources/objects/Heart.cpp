#include "objects/Heart.hpp"
#include "objects/utils.hpp"

Heart::Heart(const math::Point& pos, float a_,float b_, float c_, float d_,const float psi, const float theta, const float phi,const math::Color& diffuse_color) :
Object(pos,psi,theta,phi,diffuse_color),
a(a_),
b(b_),
c(c_),
d(d_),
_sphere(pos, 1.42f)
{}

std::optional<math::Intersection> Heart::intersection(const math::Ray& ray) const {
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

math::Vec Heart::get_normal_at(const math::Point& N) const
{
    //we will compute gradf at the point pt on the surface translated into (0,0,0) and not rotated
    math::Point pt=(N-_pos).rotation_euler_inv(_psi,_theta,_phi);
    const float g=pt.x*pt.x+a*pt.z*pt.z+pt.y*pt.y-d;
    const float g_y3=pt.y*pt.y*pt.y;
    const float df_x=3*2*pt.x*g*g-g_y3*c*2*pt.x;
    const float df_y=3*2*pt.y*g*g-3*pt.y*pt.y*( c*pt.x*pt.x+b*pt.z*pt.z );
    const float df_z=3*2*a*pt.z*g*g-g_y3*b*2*pt.z;
    math::Point m={df_x,df_y,df_z};
    math::Point n=m.rotation_euler(_psi,_theta,_phi);
    math::Vec n_rot=n.to_vec();
    n_rot.normalize();
    return n_rot;
    
}

float Heart::f(const math::Point& M) const
{
    //function that sets the surface of the Heart
    const float left=(M.x-_pos.x)*(M.x-_pos.x)+a*(M.z-_pos.z)*(M.z-_pos.z)+(M.y-_pos.y)*(M.y-_pos.y)-d;
    const float right=(M.y-_pos.y)*(M.y-_pos.y)*(M.y-_pos.y)*(c*(M.x-_pos.x)*(M.x-_pos.x)+b*(M.z-_pos.z)*(M.z-_pos.z));
    return left*left*left-right;
}

