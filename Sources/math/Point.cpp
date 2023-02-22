#include <cmath>
#include "math/Point.hpp"
#include "math/Vec.hpp"

namespace math {
    Point& Point::translate(const Vec& vec) {
        x += vec.x;
        y += vec.y;
        z += vec.z;

        return *this;
    }

    Point Point::translated(const Vec& vec) const {
        return { x + vec.x, y + vec.y, z + vec.z };
    }

    Point Point::rotation_euler(float psi, float theta, float phi) const
    {
        // B=(a b c // d e f // g h i) matrice de transfo euler pt'=B*pt
        float a=std::cos(psi)*std::cos(phi)-std::sin(psi)*std::cos(theta)*std::sin(phi);
        float b=std::sin(psi)*std::cos(phi)+std::cos(psi)*std::cos(theta)*std::sin(phi);
        float c=std::sin(theta)*std::sin(phi);
        float d=-std::cos(psi)*std::sin(phi)-std::sin(psi)*std::cos(theta)*std::cos(phi);
        float e=-std::sin(psi)*std::sin(phi)+std::cos(psi)*std::cos(theta)*std::cos(phi);
        float f=std::sin(theta)*std::cos(phi);
        float g=std::sin(psi)*std::sin(theta);
        float h=-std::cos(psi)*std::sin(theta);
        float i=std::cos(theta);
        
        float xp=a*x+b*y+c*z;
        float yp=d*x+e*y+f*z;
        float zp=g*x+h*y+i*z;
        Point Pt_rot={xp,yp,zp};
        return Pt_rot;
        
    }
    Point Point::rotation_euler_inv(float psi, float theta, float phi) const
    {
        // A=(a b c // d e f // g h i) matrice de transfo euler inv pt=A.pt'
        float a=std::cos(psi)*std::cos(phi)-std::sin(psi)*std::cos(theta)*std::sin(phi);
        float b=-std::cos(psi)*std::sin(phi)-std::sin(psi)*std::cos(theta)*std::cos(phi);
        float c=std::sin(psi)*std::sin(theta);
        float d=std::sin(psi)*std::cos(phi)+std::cos(psi)*std::cos(theta)*std::sin(phi);
        float e=-std::sin(psi)*std::sin(phi)+std::cos(psi)*std::cos(theta)*std::cos(phi);
        float f=-std::cos(psi)*std::sin(theta);
        float g=std::sin(theta)*std::sin(phi);
        float h=std::sin(theta)*std::cos(phi);
        float i=std::cos(theta);
        
        float xp=a*x+b*y+c*z;
        float yp=d*x+e*y+f*z;
        float zp=g*x+h*y+i*z;
        Point Pt_rot_inv={xp,yp,zp};
        return Pt_rot_inv;
    }

    Vec Point::to_vec() const {
        return { x, y, z };
    }

    Point operator+(const Point& lhs, const Point& rhs) {
        return {
            .x = lhs.x + rhs.x,
            .y = lhs.y + rhs.y,
            .z = lhs.z + rhs.z
        };
    }

    Point operator-(const Point& lhs, const Point& rhs) {
        return {
            .x = lhs.x - rhs.x,
            .y = lhs.y - rhs.y,
            .z = lhs.z - rhs.z
        };
    }

    Point& operator+=(Point& lhs, const Point& rhs) {
        lhs = lhs + rhs;
        return lhs;
    }

    Point& operator-=(Point& lhs, const Point& rhs) {
        lhs = lhs - rhs;
        return lhs;
    }
}
