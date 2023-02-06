#include <iostream>

#include "math/Color.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"

#include "objects/Sphere.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Scene scene{ math::BLACK };
    scene.add_object<math::Sphere>(math::Point{ 0., 0., -20. }, 5.);
    scene.add_light(Light{ math::Point{10., 10., 10.}, math::RED });

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