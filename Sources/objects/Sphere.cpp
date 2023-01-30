#include "objects/Sphere.hpp"


namespace math {

Sphere::Sphere(Point Center_, float Radius_)
{
    Center=Center_;
    Radius=Radius_;
}

Sphere::Sphere(Point Center_,math::Point B)
{
    Center=Center_;
    Vec AB;
    AB={B.x-Center_.x,B.y-Center_.y,B.z-Center_.z};
    Radius=AB.length();
}

std::optional<Intersection> Sphere::intersection(const Ray& ray)
{
    Intersection Inters;
    Vec CA;
    CA.x=Ray.origin.x-Center.x;
    CA.y=Ray.origin.y-Center.y;
    CA.z=Ray.origin.z-Center.z;
    float CA2=CA.length_sq();
    const Vec u;
    u=Ray.direrction;
    
    float delta=4*u.dot(CA)*u.dot(CA)-4*(CA2-Radius*Radius)
    
    if (delta<0)
    {
        return std::nullopt_t;
        
    }

    else
    {
        tp= ( -2*u.dot(CA)+std::sqrt(delta) )/2
        tm= ( -2*u.dot(CA)-std::sqrt(delta) )/2
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

}
