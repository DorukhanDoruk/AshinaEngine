#pragma once

// std::function: a type-erased holder for any callable (a function, a lambda, ...).
// See HANDBOOK.md#stdfunction-and-lambdas
#include <functional>

// Forward declaration: we only use GLFWwindow through a pointer here, so we do not
// need its full definition. See HANDBOOK.md#forward-declaration
struct GLFWwindow;

// All engine code lives in this namespace.
// See HANDBOOK.md#namespaces-and-the-scope-resolution-operator
namespace ashina {

// Thin GLFW wrapper: owns one window and its OpenGL context.
// RAII type: the constructor creates the window, the destructor destroys it.
// See HANDBOOK.md#raii
class Window {
public: // usable from outside. See HANDBOOK.md#access-specifiers
    // Constructor: creates the window. `title` is read-only C text.
    // See HANDBOOK.md#constructors-and-destructors and HANDBOOK.md#c-strings-const-char
    Window(int width, int height, const char* title);
    // Destructor: destroys the window and shuts GLFW down.
    ~Window();

    // Delete the copy operations so two Windows cannot own the same handle.
    // See HANDBOOK.md#deleted-functions-and-non-copyable-types--delete
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // `const` promises this call will not change the Window.
    // See HANDBOOK.md#const-and-const-correctness
    bool shouldClose() const;
    void swapBuffers();
    // static: belongs to the class, not one object. See HANDBOOK.md#static-member-functions
    static void pollEvents();

    // Tiny accessor defined right here. See HANDBOOK.md#inline-member-functions
    GLFWwindow* handle() const { return m_handle; }

    // Current framebuffer size in pixels. Kept up to date when the window resizes.
    int width() const { return m_width; }
    int height() const { return m_height; }

    // Register a handler to run when the window is resized. Application uses this to
    // pass the new size to the Renderer, so Window never has to know about Renderer.
    // See HANDBOOK.md#stdfunction-and-lambdas
    void setResizeCallback(std::function<void(int, int)> callback);

private: // hidden from outside
    // GLFW calls these C-style, so they must be static: a static member has no hidden
    // `this`, so its address is a plain function pointer GLFW can store.
    // See HANDBOOK.md#glfw-callbacks-and-function-pointers
    static void framebufferSizeCallback(GLFWwindow* win, int width, int height);
    static void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods);

    // Raw pointer to the GLFW window; starts empty.
    // See HANDBOOK.md#references-and-pointers, HANDBOOK.md#nullptr
    // and HANDBOOK.md#default-member-initializers
    GLFWwindow* m_handle = nullptr;

    // Framebuffer size in pixels; framebufferSizeCallback keeps these in sync.
    int m_width = 0;
    int m_height = 0;

    // Handler run on resize, if one was set. See HANDBOOK.md#stdfunction-and-lambdas
    std::function<void(int, int)> m_onResize;
};

} // namespace ashina
