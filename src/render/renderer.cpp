#include "render/renderer.hpp"

#include "render/shader.hpp"
#include "render/vertex_array.hpp"
#include "render/vertex_buffer.hpp"

// GLEW must be included before GLFW. See HANDBOOK.md#include-order-glew-before-glfw
#include <GL/glew.h> // must come before GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

namespace ashina {

// File-local shader sources. See HANDBOOK.md#anonymous-namespace
namespace {

// Raw string literal keeps the GLSL text exactly as written, newlines and all.
// See HANDBOOK.md#raw-string-literals
const char* kVertexSrc = R"(#version 460 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;
out vec3 vColor;
void main() {
    vColor = aColor;
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)";

const char* kFragmentSrc = R"(#version 460 core
in vec3 vColor;
out vec4 FragColor;
void main() {
    FragColor = vec4(vColor, 1.0);
}
)";

} // namespace

// Defined here, where Shader/VertexArray/VertexBuffer are complete, so the
// unique_ptr members can be destroyed. `= default` asks the compiler to write them.
// See HANDBOOK.md#defaulted-functions--default
// and HANDBOOK.md#out-of-line-destructor-for-incomplete-types
Renderer::Renderer() = default;
Renderer::~Renderer() = default;

// Load OpenGL, set the viewport, and build the triangle's GPU resources.
void Renderer::init(GLFWwindow* window) {
    glewExperimental = GL_TRUE; // needed to load core-profile entry points
    // Load the GL function pointers. See HANDBOOK.md#opengl-context-glfw-and-glew
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to load OpenGL\n";
        throw std::runtime_error("glewInit failed"); // See HANDBOOK.md#exceptions
    }

    int width = 0;
    int height = 0;
    // Pass the addresses so the function can write into width/height.
    // See HANDBOOK.md#references-and-pointers
    glfwGetFramebufferSize(window, &width, &height);
    onResize(width, height); // startup and resize share this one viewport path

    // Interleaved vertex data: position (vec2) + color (vec3). A fixed C-style array
    // of floats. See HANDBOOK.md#c-style-arrays-and-sizeof
    // and HANDBOOK.md#number-literals-the-f-suffix
    const float vertices[] = {
        // pos          // color
         0.0f,  0.5f,   1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
    };

    // make_unique builds the object and hands back an owning unique_ptr.
    // See HANDBOOK.md#stdmake_unique
    m_vao = std::make_unique<VertexArray>();
    m_vao->bind(); // -> reaches the owned object. See HANDBOOK.md#smart-pointers-stdunique_ptr
    // sizeof(vertices) is the whole array's byte size. See HANDBOOK.md#c-style-arrays-and-sizeof
    m_vbo = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

    // Bytes between one vertex and the next: 5 floats. See HANDBOOK.md#stdsize_t
    const std::size_t stride = 5 * sizeof(float);
    m_vao->addAttribute(0, 2, stride, 0);                 // position
    m_vao->addAttribute(1, 3, stride, 2 * sizeof(float)); // color

    m_shader = std::make_unique<Shader>(kVertexSrc, kFragmentSrc);
}

// Wipe the screen to the background color each frame.
// See HANDBOOK.md#clearing-the-framebuffer
void Renderer::clear() {
    glClearColor(0.1f, 0.12f, 0.15f, 1.0f); // pick the background color
    glClear(GL_COLOR_BUFFER_BIT);           // erase the previous frame
}

// Draw the triangle: use the shader, bind the layout, issue the draw.
void Renderer::draw() {
    m_shader->bind();
    m_vao->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3); // 3 vertices, one triangle
}

// Set the drawing rectangle to the whole framebuffer. See HANDBOOK.md#viewport
void Renderer::onResize(int width, int height) {
    glViewport(0, 0, width, height); // (x, y) origin at bottom-left, then size
}

} // namespace ashina
