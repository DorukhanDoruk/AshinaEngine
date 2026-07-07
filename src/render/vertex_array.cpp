#include "render/vertex_array.hpp"

#include <GL/glew.h>

namespace ashina {

// Constructor: create a VAO. See HANDBOOK.md#vertex-array-object-vao
VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_id);
}

// Destructor: free the VAO. See HANDBOOK.md#raii
VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind() const {
    glBindVertexArray(m_id);
}

// Describe one attribute inside each vertex. See HANDBOOK.md#vertex-attributes
void VertexArray::addAttribute(unsigned int index, int componentCount,
                               std::size_t stride, std::size_t offset) {
    glBindVertexArray(m_id);          // record the layout into this VAO
    glEnableVertexAttribArray(index); // turn this attribute on
    // static_cast for the stride; reinterpret_cast turns the offset number into the
    // const void* this old GL function expects.
    // See HANDBOOK.md#static_cast and HANDBOOK.md#reinterpret_cast-and-the-offset-as-pointer-idiom
    glVertexAttribPointer(index, componentCount, GL_FLOAT, GL_FALSE,
                          static_cast<GLsizei>(stride),
                          reinterpret_cast<const void*>(offset));
}

} // namespace ashina
