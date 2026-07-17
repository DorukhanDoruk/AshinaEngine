#include "app/application.hpp"

namespace ashina {

// The member initializer list builds m_window before the body runs. Order matters:
// the window (and its context) must exist before the renderer loads GL.
// See HANDBOOK.md#member-initializer-list
Application::Application()
    : m_window(1280, 720, "AshinaEngine") {
    // GLEW must load after the window's context is current.
    m_renderer.init(m_window.handle());

    // Forward resize events to the renderer's viewport. The lambda captures `this`
    // so it can reach m_renderer. Safe to wire now: resize events only fire later,
    // inside run(). See HANDBOOK.md#stdfunction-and-lambdas
    m_window.setResizeCallback([this](int width, int height) {
        m_renderer.onResize(width, height);
    });
}

// The main loop: keep drawing frames until the window is closed.
void Application::run() {
    while (!m_window.shouldClose()) {
        m_renderer.clear();     // erase the previous frame
        m_renderer.draw();      // draw the triangle
        m_window.swapBuffers(); // present it
        // static call through the class name, not an object.
        // See HANDBOOK.md#static-member-functions
        Window::pollEvents();   // handle OS and input events
    }
}

} // namespace ashina
