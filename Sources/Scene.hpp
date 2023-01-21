#pragma once

#include "math/Color.hpp"

class Scene {
public:
    Scene(math::Color background_color = math::BLACK);

    inline math::Color get_background_color() const
    { return _background_color; }

private:
    const math::Color _background_color{ math::BLACK };
};