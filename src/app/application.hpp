#pragma once

#include "app/window.hpp"
#include "render/renderer.hpp"

namespace ashina {

// Top-level engine object: owns the window and renderer, runs the main loop.
class Application {
public:
    Application();

    void run();

private:
    Window m_window;
    Renderer m_renderer;
};

} // namespace ashina
