#pragma once

#include <memory> // std::unique_ptr. See HANDBOOK.md#smart-pointers-stdunique_ptr

struct GLFWwindow; // forward declaration. See HANDBOOK.md#forward-declaration

namespace ashina {

// Forward-declare the types we only own through unique_ptr, so this header does
// not need their full definitions. See HANDBOOK.md#forward-declaration
class Shader;
class VertexArray;
class VertexBuffer;

// Owns the OpenGL state. For v2 it loads GL, sets up a triangle, and draws it.
class Renderer {
public:
    Renderer();
    // Declared here but defined in the .cpp, because the unique_ptr members need
    // the full types there. See HANDBOOK.md#out-of-line-destructor-for-incomplete-types
    ~Renderer();

    // Loads OpenGL via GLEW and builds the triangle resources. The window's
    // context must be current first.
    void init(GLFWwindow* window);

    // Clears the framebuffer with the clear color.
    void clear();

    // Draws the triangle.
    void draw();

    // Resets the viewport to the given size. Called once at startup and again on
    // every window resize. See HANDBOOK.md#viewport
    void onResize(int width, int height);

private:
    // Each unique_ptr exclusively owns its object and frees it automatically.
    // See HANDBOOK.md#smart-pointers-stdunique_ptr
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<VertexArray> m_vao;
    std::unique_ptr<VertexBuffer> m_vbo;
};

} // namespace ashina
