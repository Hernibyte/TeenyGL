# TeenyGL

## A teeny graphics library for learning, fun and my portfolio if its posible.

TinyGL is a teeny graphics library written in C++ using OpenGL. The idea is to provide a simple and easy-to-use API for rendering 2D and 3D graphics.

### Getting Started
To get started with TeenyGL, clone the repository and build the project using CMake.

```cmd
git clone https://github.com/Hernibyte/TinyGL.git
cd TinyGL
cmake --preset vs2026-debug
```

You can then open the generated solution in Visual Studio and build the project.
The build configuration it's ALL_BUILD by default, remember you can change it for anyone you want.

I left .bat files in the 'cmake-fastbuild' directory for convenience but is only one command, be happy.

For now it's only support windows with msvc compiler but I hope to add support for other platforms with clang compiler and Ninja in the future.

### How to use
I added support for CMake FetchContent, it's a early imprementation but you can try if you want.

```CMakelists.txt
include(FetchContent)

FetchContent_Declare(
  TeenyGL
  GIT_REPOSITORY https://github.com/hernibyte/TeenyGL.git
  GIT_TAG main # We don't have release tag for now
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(TeenyGL)

# ... Your project config ...

target_compile_definitions(YourProject
  PUBLIC
    GLM_ENABLE_EXPERIMENTAL # This definition is mandatory, we hope to modify it in the future
)

target_include_libraries(YourProject
  PUBLIC
    TeenyGL::TeenyGL
)
```

I hope you find TeenyGL useful and enjoy learning graphics programming.
All feedback are welcome!

### Dependencies
- glfw
- glad
- glm
- spdlog
