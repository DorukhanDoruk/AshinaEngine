#pragma once

#include <cstddef> // std::size_t. See HANDBOOK.md#stdsize_t

namespace ashina {

// Owns one OpenGL vertex buffer object (VBO). RAII wrapper.
// See HANDBOOK.md#vertex-buffer-object-vbo and HANDBOOK.md#raii
class VertexBuffer {
public:
    // `data` is a read-only block of bytes; `size` is how many.
    // See HANDBOOK.md#void-and-const-void and HANDBOOK.md#stdsize_t
    VertexBuffer(const void* data, std::size_t size);
    ~VertexBuffer();

    // Prevent copying the vertex buffer accidentaly
    // See HANDBOOK.md#deleted-functions-and-non-copyable-types--delete
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    void bind() const;

private:
    // OpenGL object name; 0 means "none". See HANDBOOK.md#unsigned-integer-handles
    unsigned int m_id = 0;
};

} // namespace ashina
