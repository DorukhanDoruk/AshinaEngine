#include "render/shader.hpp"

#include <GL/glew.h>

#include <iostream>
#include <stdexcept>

namespace ashina {

// File-local helpers live in an anonymous namespace. See HANDBOOK.md#anonymous-namespace
namespace {

// Compiles one shader stage. Throws on failure after logging the info log.
// See HANDBOOK.md#shaders-compile-and-link
unsigned int compileStage(GLenum type, const char* src) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr); // hand GL the source text
    glCompileShader(shader);

    int ok = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok); // did it compile?
    if (!ok) {
        char log[512]; // fixed buffer for the error text. See HANDBOOK.md#c-style-arrays-and-sizeof
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        std::cerr << "Shader compile failed: " << log << "\n";
        glDeleteShader(shader); // free it before leaving. See HANDBOOK.md#cleanup-before-throw
        throw std::runtime_error("shader compile failed");
    }
    return shader;
}

} // namespace

// Constructor: compile both stages, then link them into one program.
Shader::Shader(const char* vertexSrc, const char* fragmentSrc) {
    unsigned int vertex = compileStage(GL_VERTEX_SHADER, vertexSrc);
    unsigned int fragment = compileStage(GL_FRAGMENT_SHADER, fragmentSrc);

    m_program = glCreateProgram();
    glAttachShader(m_program, vertex);
    glAttachShader(m_program, fragment);
    glLinkProgram(m_program);

    int ok = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetProgramInfoLog(m_program, sizeof(log), nullptr, log);
        std::cerr << "Shader link failed: " << log << "\n";
        // Free everything we made before throwing. See HANDBOOK.md#cleanup-before-throw
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteProgram(m_program);
        throw std::runtime_error("shader link failed");
    }

    // The shaders are linked into the program now; the stage objects are no
    // longer needed.
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

// Destructor: free the GL program. See HANDBOOK.md#raii
Shader::~Shader() {
    glDeleteProgram(m_program);
}

void Shader::bind() const {
    glUseProgram(m_program); // make the GPU use this program
}

} // namespace ashina
