cmake_minimum_required(VERSION 3.10)

project(ET)

set (CMAKE_CXX_STANDARD 11)
set(VENDOR_PATHS ${PROJECT_SOURCE_DIR}/vendors)

find_package(OpenGL REQUIRED)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/vendors/sdl2/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(vendors)
file(GLOB_RECURSE PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE PROJECT_HEADERS ${PROJECT_SOURCE_DIR}/src/*.hpp)
file(GLOB VENDOR_SOURCE ${VENDOR_PATHS}/imgui/*.h 
        ${VENDOR_PATHS}/imgui/*.cpp 
        ${VENDOR_PATHS}/imgui/backends/imgui_impl_opengl3.h
        ${VENDOR_PATHS}/imgui/backends/imgui_impl_sdl.h 
        ${VENDOR_PATHS}/imgui/backends/imgui_impl_opengl3.cpp 
        ${VENDOR_PATHS}/imgui/backends/imgui_impl_sdl.cpp) 
source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${PROJECT_SOURCES})
source_group(TREE ${PROJECT_SOURCE_DIR} PREFIX "include" FILES ${PROJECT_HEADERS})

add_executable(ET ${PROJECT_HEADERS} ${PROJECT_SOURCES}  ${VENDOR_SOURCE})

target_include_directories(ET PRIVATE ${VENDOR_PATHS} 
                            PRIVATE ${VENDOR_PATHS}/imgui 
                            PRIVATE ${VENDOR_PATHS}/sdl2/include
                            PRIVATE ${VENDOR_PATHS}/glad/include
                            PRIVATE ${VENDOR_PATHS}/imgui/backends 
                            PRIVATE ${VENDOR_PATHS}/stb/ 
                            PRIVATE ${VENDOR_PATHS}/glm/ 
                            PRIVATE ${VENDOR_PATHS}/box2d/include/ 
                            PRIVATE ${VENDOR_PATHS}/catch2/src 
                            PRIVATE ${VENDOR_PATHS}/spdlog/include 
                            PRIVATE ${VENDOR_PATHS}/entt/src 
                            PRIVATE ${VENDOR_PATHS}/freetype/include 
)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set_target_properties( ${PROJECT_NAME} SDL2 SDL2main Glad box2d Catch2 Catch2WithMain spdlog freetype
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}" 
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}" 
)
target_link_directories(ET PUBLIC ${PROJECT_SOURCE_DIR}/lib)

target_link_libraries(ET PUBLIC SDL2 
                         PUBLIC SDL2main 
                         PUBLIC Glad 
                         PUBLIC Catch2::Catch2 
                         PUBLIC Catch2::Catch2WithMain
                         PUBLIC box2d 
                         PUBLIC spdlog::spdlog 
                         PUBLIC EnTT::EnTT 
                         PUBLIC freetype 
                         PUBLIC ${OPENGL_gl_LIBRARY})
if(UNIX AND NOT APPLE)
target_link_libraries(ET PUBLIC ${CMAKE_DL_LIBS})
elseif(APPLE)
endif()
