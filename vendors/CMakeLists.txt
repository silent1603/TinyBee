add_subdirectory(sdl2)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(assimp)

option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
add_subdirectory(bullet)

option(BOX2D_INSTALL "Install Box2D library, includes, and CMake scripts" OFF)
option(BOX2D_BUILD_SHARED "Build Box2D shared library" ON)
option(BOX2D_BUILD_UNIT_TESTS "Build Box2D shared library" OFF)
option(BOX2D_BUILD_TESTBED "Build Box2D shared library" OFF)
add_subdirectory(box2d)

add_subdirectory(catch2)

add_subdirectory(spdlog)

add_subdirectory(entt)

add_subdirectory(freetype)

add_subdirectory(openal)

add_library(Glad STATIC glad/src/glad.c)

target_include_directories(Glad PUBLIC glad/include/)