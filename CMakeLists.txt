cmake_minimum_required(VERSION 3.20)
project(AshinaEngine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# GLFW: window + input + OpenGL context
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# GLEW: OpenGL function loader (glew-cmake mirror builds cleanly via FetchContent)
find_package(OpenGL REQUIRED)
set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(ONLY_LIBS ON CACHE BOOL "" FORCE)
# glew-cmake ships a very old cmake_minimum_required that CMake 4.x rejects;
# allow it to configure under the legacy policy version.
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
FetchContent_Declare(
    glew
    GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
    GIT_TAG glew-cmake-2.2.0
)
FetchContent_MakeAvailable(glew)

# Match the MSVC runtime of GLEW to the rest of the build (glfw + exe use the
# DLL runtime). Without this MSVC warns LNK4098 about a LIBCMT/MSVCRT mismatch.
if (MSVC)
    set_property(TARGET libglew_static PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

add_executable(AshinaEngine
    src/main.cpp
    src/app/application.cpp
    src/app/window.cpp
    src/render/renderer.cpp
    src/render/shader.cpp
    src/render/vertex_buffer.cpp
    src/render/vertex_array.cpp
)

target_include_directories(AshinaEngine PRIVATE src)
target_link_libraries(AshinaEngine PRIVATE glfw libglew_static OpenGL::GL)
