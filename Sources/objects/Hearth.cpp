

#include "objects/Hearth.hpp"

Hearth::Hearth(math::Point pos, float a_,float b_, float c_, float d_,const math::Color& diffuse_color) :
Object(pos,diffuse_color),
a(a_),
b(b_),
c(c_),
d(d_)
{}

float Hearth::f(math::Point M)
{
    float left=(M.x-_pos.x)*(M.x-_pos.x)+a*(M.y-_pos.y)*(M.y-_pos.y)+(M.z-_pos.z)*(M.z-_pos.z)-d;
    float right=(M.z-_pos.z)*(M.z-_pos.z)*(M.z-_pos.z)*(c*(M.x-_pos.x)*(M.x-_pos.x)+b*(M.y-_pos.y)*(M.y-_pos.y));
    return left*left*left-right;
}

float Hearth::f_t(const math::Ray &ray,float t)
{
    math::Point M_t=ray.origin;
    return f( M_t.translate(t*ray.direction) );
}
float Hearth::f_tp(const math::Ray &ray, float t)
{
    // to compute left part derivative (fog)' f: t--> t^3, g define as below
    float g_x=(ray.origin.x-_pos.x+t*ray.direction.x); //left part of parametric eq ->x
    float g_y=(ray.origin.y-_pos.y+t*ray.direction.y); //left part of parametric eq ->y
    float g_z=(ray.origin.z-_pos.z+t*ray.direction.z); //left part of parametric eq ->z
    float g=g_x*g_x+a*g_y*g_y+g_z*g_z-d; // left part without the cube power
    float gp=2*ray.direction.x*g_x+a*2*ray.direction.y*g_y+2*ray.direction.z*g_z; //derivate respect to t
    float left_derivative=gp*( 3*g*g);
    
    // to compute the right part derivative -(h*r)'
    float h=g_z*g_z*g_z;
    float hp=3*ray.direction.z*g_z*g_z;
    float r=c*g_x*g_x+b*g_y*g_y;
    float rp=2*c*g_x+2*b*g_y;
    float right_derivative= -(hp*r+h*rp);
    
    return left_derivative+right_derivative;
}

std::optional<math::Intersection> Hearth::intersection(const math::Ray& ray) const
{
    return std::nullopt;
}

math::Vec Hearth::get_normal_at(const math::Point& pt) const
{
    //we will compute here grad(f) at pt
    float g=(pt.x-_pos.x)*(pt.x-_pos.x)+a*(pt.y-_pos.y)*(pt.y-_pos.y)+(pt.z-_pos.z)*(pt.z-_pos.z)-d; // left part (under the cubic root)
    float g_z3=(pt.z-_pos.z)*(pt.z-_pos.z)*(pt.z-_pos.z);
    float df_x=3*2*(pt.x-_pos.x)*g*g-g_z3*c*2*(pt.x-_pos.x);
    float df_y=3*2*a*(pt.y-_pos.y)*g*g-g_z3*b*2*(pt.y-_pos.y);
    float df_z=3*2*(pt.z-_pos.z)*g*g-3*(pt.z-_pos.z)*(pt.z-_pos.z)*( c*(pt.x-_pos.x)*(pt.x-_pos.x)+b*(pt.y-_pos.y)*(pt.y-_pos.y) );
    math::Vec n={df_x,df_y,df_z};
    n.normalize();
    return n;
    
}

