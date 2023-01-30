//
//  Vec.hpp
//  Ray_tracing


#ifndef Vec_hpp
#define Vec_hpp
#pragma once

#include <iostream>

namespace math {
    struct Vec {
        float x;
        float y;
        float z;
        
        float dot(const Vec& rhs) const;
        float length_sq() const;
        float length() const;
        void normalize();
        Vec normalized() const;
    };

    Vec operator*(const Vec& lhs, const Vec& rhs);
    Vec operator*(const Vec& lhs, float scalar);
    Vec operator*(float scalar, const Vec& rhs);

    Vec operator/(const Vec& lhs, const Vec& rhs);
    Vec operator/(const Vec& lhs, float scalar);

    Vec operator+(const Vec& lhs, const Vec& rhs);
    Vec operator+(const Vec& lhs, float scalar);

    Vec operator-(const Vec& lhs, const Vec& rhs);
    Vec operator-(const Vec& lhs, float scalar);

    Vec& operator*=(Vec& lhs, const Vec& rhs);
    Vec& operator*=(Vec& lhs, float scalar);
    Vec& operator/=(Vec& lhs, const Vec& rhs);
    Vec& operator/=(Vec& lhs, float scalar);
    Vec& operator+=(Vec& lhs, const Vec& rhs);
    Vec& operator+=(Vec& lhs, float scalar);
    Vec& operator-=(Vec& lhs, const Vec& rhs);
    Vec& operator-=(Vec& lhs, float scalar);
    
    std::ostream& operator<<(std::ostream& os, const Vec& vec);
}

#endif /* Vec_hpp */
