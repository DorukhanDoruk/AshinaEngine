#pragma once

#include <cstddef> // std::size_t. See HANDBOOK.md#stdsize_t

namespace ashina {

// Owns one OpenGL vertex array object (VAO) and its attribute layout.
// See HANDBOOK.md#vertex-array-object-vao and HANDBOOK.md#raii
class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    // Prevent copying the vertex array accidentaly
    // See HANDBOOK.md#deleted-functions-and-non-copyable-types--delete
    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    void bind() const;

    // Sets up one float vertex attribute. The vertex buffer holding the data
    // must be bound before calling this. See HANDBOOK.md#vertex-attributes
    void addAttribute(unsigned int index, int componentCount, std::size_t stride,
                       std::size_t offset);

private:
    // OpenGL VAO name; 0 means "none". See HANDBOOK.md#unsigned-integer-handles
    unsigned int m_id = 0;
};

} // namespace ashina
