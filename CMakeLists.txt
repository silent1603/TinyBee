cmake_minimum_required(VERSION 3.13)

project(TINYBEE VERSION 0.1 DESCRIPTION "a dumb engine" LANGUAGES C CXX)

set(PROJECT_PATH ${PROJECT_SOURCE_DIR}/TinyBee)
set(SRC_PATH ${PROJECT_PATH}/src)
set(VENDOR_PATH ${PROJECT_PATH}/vendors)
set(HEADER_PATH ${PROJECT_PATH}/include)
set(SHADER_PATH ${PROJECT_PATH}/shaders)

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

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/TinyBee/vendors/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

file(GLOB_RECURSE PROJECT_HEADER ${HEADER_PATH}/*.hpp ${HEADER_PATH}/*.h)
file(GLOB_RECURSE PROJECT_SRC ${SRC_PATH}/*.cpp)
file(GLOB_RECURSE PROJECT_SHADER ${SHADER_PATH}/*.comp ${SHADER_PATH}/*.frag ${SHADER_PATH}/*.geom ${SHADER_PATH}/*.vert)
file(GLOB_RECURSE VENDOR_HEADER ${VENDOR_PATH}/glfw/include/*.h ${VENDOR_PATH}/glfw/include/*.hpp 
                                ${VENDOR_PATH}/assimp/include/*.h ${VENDOR_PATH}/assimp/include/*.hpp 
                                ${VENDOR_PATH}/bullet3/src/*h ${VENDOR_PATH}/bullet3/src/*.hpp 
                                ${VENDOR_PATH}/glad/include/*.h ${VENDOR_PATH}/glad/include/*.hpp 
                                ${VENDOR_PATH}/glm/glm/*.h ${VENDOR_PATH}/glm/glm/*.hpp    
                                ${VENDOR_PATH}/stb/*.h  
                                ${VENDOR_PATH}/imgui/*h 
                                ${VENDOR_PATH}/imguizmo/*h 
                                ${VENDOR_PATH}/spdlog/include/*.h 
                                ${VENDOR_PATH}/entt/src/*.h ${VENDOR_PATH}/entt/src/*.hpp  
                                ${VENDOR_PATH}/catch2/src/*.h ${VENDOR_PATH}/catch2/src/*.hpp)
file(GLOB VENDOR_SOURCE ${VENDOR_PATH}/imgui/*.cpp 
                        ${VENDOR_PATH}/imgui/backends/imgui_impl_glfw.cpp 
                        ${VENDOR_PATH}/imgui/backends/imgui_impl_opengl3.cpp 
                        ${VENDOR_PATH}/imguizmo/*cpp 
)

file(GLOB PROJECT_CONFIG CMakeLists.txt .gitignore .gitmodules)

source_group(TREE ${PROJECT_PATH} FILES ${VENDOR_HEADER})
source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_HEADER})
source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_SRC})
source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_SHADER})
source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${PROJECT_CONFIG})

add_subdirectory(${PROJECT_PATH})

add_executable(TINYBEE ${PROJECT_HEADER} ${VENDOR_HEADER} ${VENDOR_SOURCE}  ${PROJECT_SRC} ${PROJECT_SHADER} ${PROJECT_CONFIG})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_PATH}/include/ 
                                            ${VENDOR_PATH}/glfw/include/ 
                                            ${VENDOR_PATH}/assimp/include/ 
                                            ${VENDOR_PATH}/bullet/src/ 
                                            ${VENDOR_PATH}/glfw/include/ 
                                            ${VENDOR_PATH}/glad/include/ 
                                            ${VENDOR_PATH}/glm/glm/ 
                                            ${VENDOR_PATH}/stb/ 
                                            ${VENDOR_PATH}/imgui/  
                                            ${VENDOR_PATH}/imgui/backends/ 
                                            ${VENDOR_PATH}/imguizmo/ 
                                            ${VENDOR_PATH}/spdlog/include/ 
                                            ${VENDOR_PATH}/entt/src/  
                                            ${VENDOR_PATH}/catch2/src/ 
                                            ${VENDOR_PATH}/box2d/include/ 
                                            ${VENDOR_PATH}/ 
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

target_link_libraries(${PROJECT_NAME} PUBLIC glfw 
                                    PUBLIC assimp 
                                    PUBLIC BulletDynamics 
                                    PUBLIC BulletCollision 
                                    PUBLIC LinearMath 
                                    PRIVATE Glad 
                                    PRIVATE Catch2::Catch2 
                                    PUBLIC box2d 
)

set_target_properties( ${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)