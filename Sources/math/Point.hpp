//
//  Point.hpp
//  Ray_tracing
//
//

#ifndef Point_hpp
#define Point_hpp
#pragma once

namespace math {
    struct Vec;
    
    struct Point {
        float x;
        float y;
        float z;
        
        Point& translate(const Vec& vec);
    };
}
#endif /* Point_hpp */
