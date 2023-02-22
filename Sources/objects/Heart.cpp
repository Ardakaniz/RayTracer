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
            return f(ray.origin.translated(t*ray.direction));
        }
    );
}

math::Vec Heart::get_normal_at(const math::Point& pt) const
{
    //we will compute here grad(f) at pt
    const float g=(pt.x-_pos.x)*(pt.x-_pos.x)+a*(pt.z-_pos.z)*(pt.z-_pos.z)+(pt.y-_pos.y)*(pt.y-_pos.y)-d; // left part (under the cubic root)
    const float g_y3=(pt.y-_pos.y)*(pt.y-_pos.y)*(pt.y-_pos.y);
    const float df_x=3*2*(pt.x-_pos.x)*g*g-g_y3*c*2*(pt.x-_pos.x);
    const float df_y=3*2*(pt.y-_pos.y)*g*g-3*(pt.y-_pos.y)*(pt.y-_pos.y)*( c*(pt.x-_pos.x)*(pt.x-_pos.x)+b*(pt.z-_pos.z)*(pt.z-_pos.z) );
    const float df_z=3*2*a*(pt.z-_pos.z)*g*g-g_y3*b*2*(pt.z-_pos.z);
    math::Vec n={df_x,df_y,df_z};
    n.normalize();
    return n;
    
}

float Heart::f(const math::Point& N) const
{
    math::Point M=N.rotation_euler(_psi,_theta,_phi);
    const float left=(M.x-_pos.x)*(M.x-_pos.x)+a*(M.z-_pos.z)*(M.z-_pos.z)+(M.y-_pos.y)*(M.y-_pos.y)-d;
    const float right=(M.y-_pos.y)*(M.y-_pos.y)*(M.y-_pos.y)*(c*(M.x-_pos.x)*(M.x-_pos.x)+b*(M.z-_pos.z)*(M.z-_pos.z));
    return left*left*left-right;
}

float Heart::f_t(const math::Ray &ray,float t) const
{
    math::Point M_t=ray.origin;
    return f( M_t.translate(t*ray.direction) );
}
float Heart::f_tp(const math::Ray &ray, float t) const
{
    // to compute left part derivative (fog)' f: t--> t^3, g define as below
    const float g_x=(ray.origin.x-_pos.x+t*ray.direction.x); //left part of parametric eq ->x
    const float g_z=(ray.origin.z-_pos.z+t*ray.direction.z); //left part of parametric eq ->z
    const float g_y=(ray.origin.y-_pos.y+t*ray.direction.y); //left part of parametric eq ->y
    const float g=g_x*g_x+a*g_z*g_z+g_y*g_y-d; // left part without the cube power
    const float gp=2*ray.direction.x*g_x+a*2*ray.direction.z*g_z+2*ray.direction.y*g_y; //derivate respect to t
    const float left_derivative=gp*( 3*g*g);
    
    // to compute the right part derivative -(h*r)'
    const float h=g_y*g_y*g_y;
    const float hp=3*ray.direction.y*g_y*g_y;
    const float r=c*g_x*g_x+b*g_z*g_z;
    const float rp=2*c*g_x+2*b*g_z;
    const float right_derivative= -(hp*r+h*rp);
    
    return left_derivative+right_derivative;
}
