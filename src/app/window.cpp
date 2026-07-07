#include "app/window.hpp"

// Library headers use angle brackets. See HANDBOOK.md#includes-and-pragma-once
#include <GLFW/glfw3.h>

#include <iostream>   // std::cerr. See HANDBOOK.md#output-streams-stdcerr
#include <stdexcept>  // std::runtime_error. See HANDBOOK.md#exceptions

namespace ashina {

// Constructor: bring up GLFW, ask for OpenGL 4.6 core, create the window.
// See HANDBOOK.md#opengl-context-glfw-and-glew
Window::Window(int width, int height, const char* title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n"; // print the reason first
        throw std::runtime_error("glfwInit failed"); // then stop. See HANDBOOK.md#exceptions
    }

    // Ask for an OpenGL 4.6 core-profile context before the window is created.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // nullptr: no shared window and no fullscreen monitor. See HANDBOOK.md#nullptr
    m_handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_handle) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        throw std::runtime_error("glfwCreateWindow failed");
    }

    // Make this window's OpenGL context active on this thread.
    glfwMakeContextCurrent(m_handle);
}

// Destructor: release the window and shut GLFW down. See HANDBOOK.md#raii
Window::~Window() {
    if (m_handle) { // only destroy if we actually created one
        glfwDestroyWindow(m_handle);
    }
    glfwTerminate();
}

// const member: does not change the Window. See HANDBOOK.md#const-and-const-correctness
bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_handle);
}

void Window::swapBuffers() {
    glfwSwapBuffers(m_handle); // present the finished frame
}

// static: no object needed. See HANDBOOK.md#static-member-functions
void Window::pollEvents() {
    glfwPollEvents(); // process OS and input events
}

} // namespace ashina
