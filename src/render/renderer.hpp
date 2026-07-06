#pragma once

struct GLFWwindow;

namespace ashina {

// Owns the OpenGL state. For v1 it just loads GL and clears the screen.
class Renderer {
public:
    // Loads OpenGL via GLEW. The window's context must be current first.
    void init(GLFWwindow* window);

    // Clears the framebuffer with the clear color.
    void clear();
};

} // namespace ashina
