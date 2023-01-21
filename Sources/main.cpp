#include <iostream>

#include "math/Color.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Scene scene{ math::BLUE };
    Camera camera{ 1920, 1080 };

    Renderer renderer{ scene, camera };
    if (!renderer.save_to_file("image.png")) {
        return -1;
    }
}