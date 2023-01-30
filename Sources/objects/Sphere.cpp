#include "objects/Sphere.hpp"


namespace math {

Sphere::Sphere(Point pos, float Radius_)
{
    _pos=pos;
    Radius=Radius_;
}

Sphere::Sphere(Point pos,math::Point B)
{
    _pos=pos;
    Vec AB;
    AB={B.x-pos.x,B.y-pos.y,B.z-pos.z};
    Radius=AB.length();
}

std::optional<Intersection> Sphere::intersection(const Ray& ray)
{
    Intersection Inters;
    Vec CA;
    CA.x=ray.origin.x-_pos.x;
    CA.y=ray.origin.y-_pos.y;
    CA.z=ray.origin.z-_pos.z;
    Point A;
    A=ray.origin;
    float CA2=CA.length_sq();
    const Vec u;
    u=ray.direction;
    
    float delta=4*u.dot(CA)*u.dot(CA)-4*(CA2-Radius*Radius);
    
    if (delta<0)
    {
        return std::nullopt_t;
        
    }
    
    else
    {
        float tp= ( -2*u.dot(CA)+std::sqrt(delta) )/2;
        float tm= ( -2*u.dot(CA)-std::sqrt(delta) )/2;
        Point TP;
        TP=A.translate(tp*u);
        Vec ATP={TP.x-A.x,TP.y-A.y,TP.z-A.z};
        
        Point TM;
        TM=A.translate(tm*u);
        Vec ATM={TM.x-A.x,TM.y-A.y,TM.z-A.z};
        
        if ( ATP.length_sq()<ATM.length_sq() )
        {
            Inters.point=TP;
            Inters.obj=*this;
            Inters.ray=ray;
            return Inters;
        }
        else
        {
            Inters.point=TM;
            Inters.obj=*this;
            Inters.ray=ray;
            return Inters
        }
        
    }
}



Vec Sphere::get_normal_at(const Point& pt)
{
    Vec n;
    n={pt.x-_pos.x,pt.y-_pos.y,pt.z-_pos.z};
    n.normalized();
    return n;
    
}

}
