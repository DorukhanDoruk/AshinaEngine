#pragma once

namespace ashina {

// Compiles and links a GLSL vertex + fragment program.
// RAII wrapper over one GL program. See HANDBOOK.md#shaders-compile-and-link
class Shader {
public:
    // Takes the two shader sources as read-only C text. See HANDBOOK.md#c-strings-const-char
    Shader(const char* vertexSrc, const char* fragmentSrc);
    ~Shader();

    // Non-copyable: one program handle, one owner.
    // See HANDBOOK.md#deleted-functions-and-non-copyable-types--delete
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    void bind() const;

private:
    // GL program name; 0 means "none". See HANDBOOK.md#unsigned-integer-handles
    unsigned int m_program = 0;
};

} // namespace ashina
