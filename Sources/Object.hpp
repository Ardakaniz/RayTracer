//
//  Object.hpp
//  Ray_tracing
//
//

#ifndef Object_hpp
#define Object_hpp
#pragma once

#include "math/Color.hpp"
#include "math/Vec.hpp"
#include "Light.hpp"
#include "math/Intersection.hpp"
#include <optional>
#include <cmath>
namespace math {
struct Point;
struct Ray;
}

class Object {
public:
    Object(const math::Point& pos,const float psi, const float theta, const float phi,const math::Color& diffuse_color);
    virtual ~Object() = default;

    virtual std::optional<math::Intersection>  intersection(const math::Ray& ray) const = 0;
    virtual math::Vec get_normal_at(const math::Point& pt) const  = 0 ;
    math::Color get_diffuse_color(const Light& light,const math::Point& P) const ;

protected:
    const math::Point _pos;
    const math::Color _diffuse_color;
    const float _psi;
    const float _theta;
    const float _phi;
    // orientation de l'objet cf angle Euler (faut faire les calculs d'intersection dans la base tournée
    // mon idée juste tourner la surface et normal donc f(pt), grad(pt) 
};

#endif /* Object_hpp */
