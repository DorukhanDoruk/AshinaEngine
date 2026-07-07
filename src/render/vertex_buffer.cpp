#include "render/vertex_buffer.hpp"

#include <GL/glew.h>

namespace ashina {

// Constructor: create a VBO, select it, and upload the data once.
// See HANDBOOK.md#vertex-buffer-object-vbo
VertexBuffer::VertexBuffer(const void* data, std::size_t size) {
    glGenBuffers(1, &m_id);              // ask OpenGL for a buffer name into m_id
    glBindBuffer(GL_ARRAY_BUFFER, m_id); // make it the current array buffer
    // static_cast converts size to the exact type OpenGL wants. See HANDBOOK.md#static_cast
    // GL_STATIC_DRAW: set once, draw many times. See HANDBOOK.md#gl_static_draw
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), data, GL_STATIC_DRAW);
}

// Destructor: free the VBO. See HANDBOOK.md#raii
VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_id);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_id); // select this VBO again
}

} // namespace ashina
