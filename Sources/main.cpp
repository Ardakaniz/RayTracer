#include <iostream>

#include "math/Color.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"

#include "objects/Sphere.hpp"

int main() {
    Scene scene{ math::BLACK };
    scene.add_object<Sphere>(math::Point{ 0., 0., -20. }, 5.f, math::WHITE);

    CameraParams params{
        .width = 800,
        .height = 800,
        .fov_angle = 3.141592 / 6.,
        .position = { 0., 0., 20. }
    };
    Camera camera{ params };

    std::cout << "--- Camera params ---" << std::endl;
    std::cout << "Output width x height: " << camera.get_width() << "x" << camera.get_height() << std::endl;
    std::cout << "Viewport width / height: " << camera.get_viewport_width() << " / " << camera.get_viewport_height() << std::endl; 

    Renderer renderer{ scene, camera };
    renderer.render();
    if (!renderer.save_to_file("image.png")) {
        return -1;
    }
}