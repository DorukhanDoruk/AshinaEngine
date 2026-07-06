#pragma once

struct GLFWwindow;

namespace ashina {

// Thin GLFW wrapper: owns one window and its OpenGL context.
class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool shouldClose() const;
    void swapBuffers();
    static void pollEvents();

    GLFWwindow* handle() const { return m_handle; }

private:
    GLFWwindow* m_handle = nullptr;
};

} // namespace ashina
