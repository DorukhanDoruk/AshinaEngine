#include "app/window.hpp"

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

namespace ashina {

Window::Window(int width, int height, const char* title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        throw std::runtime_error("glfwInit failed");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_handle) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        throw std::runtime_error("glfwCreateWindow failed");
    }

    glfwMakeContextCurrent(m_handle);
}

Window::~Window() {
    if (m_handle) {
        glfwDestroyWindow(m_handle);
    }
    glfwTerminate();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_handle);
}

void Window::swapBuffers() {
    glfwSwapBuffers(m_handle);
}

void Window::pollEvents() {
    glfwPollEvents();
}

} // namespace ashina
