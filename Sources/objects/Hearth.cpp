

#include "objects/Hearth.hpp"

Hearth::Hearth(const math::Point& pos, float a_,float b_, float c_, float d_,const math::Color& diffuse_color) :
Object(pos,diffuse_color),
a(a_),
b(b_),
c(c_),
d(d_)
{}

std::optional<math::Intersection> Hearth::intersection(const math::Ray& ray) const {
    // Wont work for now, we should add a circumscribed circle to first roughly
    // compute if there is intersection or not 

    // How best to choose these values?
    constexpr float COARSE_DT = 1.;
    constexpr float EPS = 1e-3;
    constexpr unsigned int MAX_ITER = 100;
    
    float t{ 0. };
    unsigned int iter_count{ 0 };
    const bool initial_sign{ f_t(ray, t) < 0 };

    while ((f_t(ray, t) < 0) == initial_sign && iter_count < MAX_ITER) {
        ++iter_count;
        t += COARSE_DT;
    }

    if (iter_count == MAX_ITER)
        return std::nullopt;

    float lower_t{ t - COARSE_DT }, higher_t{ t };
    while (higher_t - lower_t > EPS && iter_count < MAX_ITER) {
        t = (higher_t - lower_t) / 2.;

        if ((f_t(ray, t) < 0) == initial_sign)
            lower_t = t;
        else
            higher_t = t;

        ++iter_count;
    }

    return math::Intersection{
        .point = ray.point_at(t),
        .obj = *this,
        .ray = ray,
        .distance = t
    };
}

math::Vec Hearth::get_normal_at(const math::Point& pt) const
{
    //we will compute here grad(f) at pt
    const float g=(pt.x-_pos.x)*(pt.x-_pos.x)+a*(pt.y-_pos.y)*(pt.y-_pos.y)+(pt.z-_pos.z)*(pt.z-_pos.z)-d; // left part (under the cubic root)
    const float g_z3=(pt.z-_pos.z)*(pt.z-_pos.z)*(pt.z-_pos.z);
    const float df_x=3*2*(pt.x-_pos.x)*g*g-g_z3*c*2*(pt.x-_pos.x);
    const float df_y=3*2*a*(pt.y-_pos.y)*g*g-g_z3*b*2*(pt.y-_pos.y);
    const float df_z=3*2*(pt.z-_pos.z)*g*g-3*(pt.z-_pos.z)*(pt.z-_pos.z)*( c*(pt.x-_pos.x)*(pt.x-_pos.x)+b*(pt.y-_pos.y)*(pt.y-_pos.y) );
    math::Vec n={df_x,df_y,df_z};
    n.normalize();
    return n;
    
}

float Hearth::f(const math::Point& M) const
{
    const float left=(M.x-_pos.x)*(M.x-_pos.x)+a*(M.y-_pos.y)*(M.y-_pos.y)+(M.z-_pos.z)*(M.z-_pos.z)-d;
    const float right=(M.z-_pos.z)*(M.z-_pos.z)*(M.z-_pos.z)*(c*(M.x-_pos.x)*(M.x-_pos.x)+b*(M.y-_pos.y)*(M.y-_pos.y));
    return left*left*left-right;
}

float Hearth::f_t(const math::Ray &ray,float t) const
{
    math::Point M_t=ray.origin;
    return f( M_t.translate(t*ray.direction) );
}
float Hearth::f_tp(const math::Ray &ray, float t) const
{
    // to compute left part derivative (fog)' f: t--> t^3, g define as below
    const float g_x=(ray.origin.x-_pos.x+t*ray.direction.x); //left part of parametric eq ->x
    const float g_y=(ray.origin.y-_pos.y+t*ray.direction.y); //left part of parametric eq ->y
    const float g_z=(ray.origin.z-_pos.z+t*ray.direction.z); //left part of parametric eq ->z
    const float g=g_x*g_x+a*g_y*g_y+g_z*g_z-d; // left part without the cube power
    const float gp=2*ray.direction.x*g_x+a*2*ray.direction.y*g_y+2*ray.direction.z*g_z; //derivate respect to t
    const float left_derivative=gp*( 3*g*g);
    
    // to compute the right part derivative -(h*r)'
    const float h=g_z*g_z*g_z;
    const float hp=3*ray.direction.z*g_z*g_z;
    const float r=c*g_x*g_x+b*g_y*g_y;
    const float rp=2*c*g_x+2*b*g_y;
    const float right_derivative= -(hp*r+h*rp);
    
    return left_derivative+right_derivative;
}