# AshinaEngine

A small C++ game/rendering engine I am building from scratch while I learn C++.

This is a learn-as-I-build project. I am new to C++, so I grow the engine one small,
well-understood step at a time instead of pulling in big pieces I cannot explain yet.
The source is commented heavily on purpose: it doubles as my own notes, so future-me (and
anyone curious) can read *why* each line is there, not just *what* it does.

## Built with

- **C++20**
- **OpenGL 4.6** (core profile)
- **GLFW 3.4** — window, input, and the GL context
- **GLEW 2.2.0** — OpenGL function loader
- **CMake** with `FetchContent` — GLFW and GLEW are pulled and built automatically, so
  there is no manual dependency setup.

## Build and run

You need CMake and a C++20 compiler. The first configure downloads GLFW and GLEW, so an
internet connection is required that one time.

```
cmake -S . -B build
cmake --build build
```

On Windows / MSVC the executable lands at `build/Debug/AshinaEngine.exe`
(use `--config Release` for a release build). Run it and you should see a colored triangle
on a dark background.

## License

MIT — see [LICENSE](LICENSE).
