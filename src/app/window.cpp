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

    // Store `this` on the GLFW window so the static callbacks can find us again.
    // See HANDBOOK.md#window-user-pointer
    glfwSetWindowUserPointer(m_handle, this);

    // Register the C-style callbacks. Taking the address of a static member gives a
    // plain function pointer. See HANDBOOK.md#glfw-callbacks-and-function-pointers
    glfwSetFramebufferSizeCallback(m_handle, &Window::framebufferSizeCallback);
    glfwSetKeyCallback(m_handle, &Window::keyCallback);

    // The framebuffer size can differ from the requested window size (e.g. on hi-DPI
    // screens), so read the real size now. See HANDBOOK.md#viewport
    glfwGetFramebufferSize(m_handle, &m_width, &m_height);
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

// Save the handler. framebufferSizeCallback runs it on every resize.
void Window::setResizeCallback(std::function<void(int, int)> callback) {
    m_onResize = callback; // copy it into the member. See HANDBOOK.md#stdfunction-and-lambdas
}

// GLFW calls this when the framebuffer is resized. It is static, so we get the owning
// Window back through the user pointer. See HANDBOOK.md#window-user-pointer
void Window::framebufferSizeCallback(GLFWwindow* win, int width, int height) {
    // Cast the void* back to the Window that owns this GLFW window.
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(win));
    self->m_width = width;   // remember the new size
    self->m_height = height;
    if (self->m_onResize) {  // a std::function is falsy when empty; only call if set
        self->m_onResize(width, height);
    }
}

// GLFW calls this on every key event. We only act on ESC to close the window.
// A callback must not let a C++ exception escape back into GLFW (C code), so the body
// stays simple. See HANDBOOK.md#glfw-callbacks-and-function-pointers
void Window::keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(win, GLFW_TRUE); // ask the main loop to stop
    }
}

} // namespace ashina
