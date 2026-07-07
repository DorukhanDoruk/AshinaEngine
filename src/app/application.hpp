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
    // Owned by value (composition): built and destroyed with the Application.
    // See HANDBOOK.md#composition-owning-by-value
    Window m_window;
    Renderer m_renderer;
};

} // namespace ashina
