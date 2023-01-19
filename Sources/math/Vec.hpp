//
//  Vec.hpp
//  Ray_tracing


#ifndef Vec_hpp
#define Vec_hpp
#pragma once

namespace math {
    struct Vec {
        float x;
        float y;
        float z;
        
        float dot(const Vec& rhs) const;
        float lenght_sq() const;
        float lenght() const;
        void normalize();
        Vec normalized() const;
        
    };
}

#endif /* Vec_hpp */
