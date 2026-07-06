#include "render/renderer.hpp"

#include <GL/glew.h> // must come before GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

namespace ashina {

void Renderer::init(GLFWwindow* window) {
    glewExperimental = GL_TRUE; // needed to load core-profile entry points
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to load OpenGL\n";
        throw std::runtime_error("glewInit failed");
    }

    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

void Renderer::clear() {
    glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

} // namespace ashina
