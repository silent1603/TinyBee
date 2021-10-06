add_subdirectory(sdl2)

option(BOX2D_INSTALL "Install Box2D library, includes, and CMake scripts" OFF)
option(BOX2D_BUILD_SHARED "Build Box2D shared library" ON)
option(BOX2D_BUILD_UNIT_TESTS "Build Box2D shared library" OFF)
option(BOX2D_BUILD_TESTBED "Build Box2D shared library" OFF)
add_subdirectory(box2d)

add_subdirectory(catch2)

add_subdirectory(spdlog)

add_subdirectory(entt)

add_subdirectory(freetype)

add_library(Glad STATIC glad/src/glad.c)

target_include_directories(Glad PUBLIC glad/include/)