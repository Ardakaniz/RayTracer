#include <iostream>

#include "math/Color.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Scene scene{ math::BLUE };

    CameraParams params{
        .width = 800,
        .height = 600,
        .fov_angle = 3.141592 / 6.,
        .position = { 0., 0., 2. }
    };
    Camera camera{ params };

    Renderer renderer{ scene, camera };
    renderer.render();
    if (!renderer.save_to_file("image.png")) {
        return -1;
    }
}