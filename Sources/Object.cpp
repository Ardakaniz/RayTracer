#include "Object.hpp"
#include "math/Ray.hpp"
Object::Object(const math::Point& pos,const float psi, const float theta, const float phi, const math::Color& diffuse_color) :
	_pos{ pos },
    _psi{ psi },
    _theta{ theta },
    _phi { phi },
    _diffuse_color{ diffuse_color }
{ }


math::Color Object::get_diffuse_color(const Light& light,const math::Point& P) const
{
    
    const math::Color Cs=light.color;
    const math::Color Kd=_diffuse_color;
    const math::Vec N=get_normal_at(P);
    const math::Ray S{light.pos,P};
    const float cos_pi_mth=N.dot(S.direction);
    const math::Color Cd={-Kd.r*Cs.r*cos_pi_mth,-Kd.g*Cs.g*cos_pi_mth,-Kd.b*Cs.b*cos_pi_mth};
    return Cd;
}



