#include <iostream>
#include <stdexcept>
#include <functional>

#include "HelloTriangleApplication.h"
#include "Sphere.h"

int main() {
    std::vector<Vertex> V;
    std::vector<uint16_t> I;
    DrawSphere(0.3f, 10, 10, V, I, { 1.0f, 1.0f, 1.0f });
    Shape s = { V, I };
    Canvas app(s);

    try {
        app.run();
    }

    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}