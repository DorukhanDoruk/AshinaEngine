#include "app/application.hpp"

namespace ashina {

Application::Application()
    : m_window(1280, 720, "AshinaEngine") {
    // GLEW must load after the window's context is current.
    m_renderer.init(m_window.handle());
}

void Application::run() {
    while (!m_window.shouldClose()) {
        m_renderer.clear();
        m_window.swapBuffers();
        Window::pollEvents();
    }
}

} // namespace ashina
