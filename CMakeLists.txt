cmake_minimum_required(VERSION 3.8)

project(TinyLB VERSION 0.0.1  DESCRIPTION "A Tiny Engine" LANGUAGES C CXX)

set (CMAKE_CXX_STANDARD 11)

set(PROJECT_PATH ${PROJECT_SOURCE_DIR}/tinylb)

set(APP_PATHS ${PROJECT_SOURCE_DIR}/app)
set(SHADER_PATHS ${PROJECT_PATH}/shaders)
set(PROJECT_EXTERNAL_SRC ${PROJECT_PATH}/src)
set(PROJECT_EXTERNAL_INCLUDE ${PROJECT_PATH}/include)
set(VENDOR_PATHS ${PROJECT_PATH}/external)
set(RESOURCE_PATH ${PROJECT_PATH}/resources)


if(WIN32)
list(APPEND LIB_PATHS "${CMAKE_BINARY_DIR}/bin")
list(APPEND LIB_PATHS "${CMAKE_BINARY_DIR}/lib")
#find_package(Vulkan REQUIRED FATAL_ERROR) # error
endif(WIN32)

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

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/tinylb/external/imgui/imgui.h")
message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

if(WIN32)
conan_basic_setup(TARGETS)
endif()
if(UNIX AND NOT APPLE)
conan_basic_setup()
endif()

file(GLOB_RECURSE PROJECT_APP   ${APP_PATHS}/*.hpp ${APP_PATHS}/*.h ${APP_PATHS}/*.c)
file(GLOB_RECURSE PROJECT_EXTERNAL_SOURCES   ${PROJECT_EXTERNAL_SRC}/*.cpp )
file(GLOB_RECURSE PROJECT_EXTERNAL_HEADERS   ${PROJECT_EXTERNAL_INCLUDE}/*.hpp)
file(GLOB_RECURSE PROJECT_VENDOR_HEADER ${VENDOR_PATHS}/*.hpp ${VENDOR_PATHS}/*.h)
file(GLOB PROJECT_VENDOR_SRC ${VENDOR_PATHS}/imgui/*.cpp 
                                     ${VENDOR_PATHS}/imgui/backends/imgui_impl_opengl3.cpp 
                                     ${VENDOR_PATHS}/imgui/backends/imgui_impl_glfw.cpp 
                                     ${VENDOR_PATH}/imguizmo/*cpp )

file(GLOB_RECURSE PROJECT_SHADERS   ${SHADER_PATHS}/*.comp ${SHADER_PATHS}/*.frag ${SHADER_PATHS}/*.geom ${SHADER_PATHS}/*.vert)
file(GLOB_RECURSE PROJECT_RESOURCES ${RESOURCE_PATH}/*.*)
file(GLOB PROJECT_CONFIGS   CMakeLists.txt Readme.md .gitattributes .gitignore .gitmodules conanfile.py conanfile.txt LICENSE README.md)

source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_APP})
source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_SHADERS})
source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_EXTERNAL_SOURCES})
source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_EXTERNAL_HEADERS})
source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_VENDOR_HEADER})
source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_VENDOR_SRC})
source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_RESOURCES})
source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${PROJECT_CONFIGS})


add_executable(TinyLB  ${PROJECT_EXTERNAL_HEADERS} ${PROJECT_VENDOR_HEADER} ${PROJECT_VENDOR_SRC} ${PROJECT_EXTERNAL_SOURCES} ${PROJECT_APP} ${PROJECT_SHADERS} ${PROJECT_CONFIGS} ${PROJECT_RESOURCES})


add_subdirectory(tinylb)

target_include_directories(TinyLB PRIVATE ${PROJECT_EXTERNAL_INCLUDE} 
                            PRIVATE ${VENDOR_PATHS}  
                            PRIVATE ${VENDOR_PATHS}/imgui 
                            PRIVATE ${VENDOR_PATHS}/GLFW 
                            PRIVATE ${VENDOR_PATHS}/glad 
                            PRIVATE ${VENDOR_PATHS}/KHR 
                            PRIVATE ${VENDOR_PATHS}/stb
                            PRIVATE ${VENDOR_PATHS}/spdlog 
                            PRIVATE ${VENDOR_PATHS}/AL 
                            PRIVATE ${VENDOR_PATHS}/lua 
                            PRIVATE ${VENDOR_PATHS}/catch2  
                            PRIVATE ${VENDOR_PATHS}/entt 
                            PRIVATE ${VENDOR_PATHS}/box2d 
                            PRIVATE ${VENDOR_PATHS}/bullet 
                            PRIVATE ${VENDOR_PATHS}/assimp 
                            PRIVATE ${VENDOR_PATHS}/glm 
                            PRIVATE ${VENDOR_PATHS}/imguizmo 
                            PRIVATE ${VENDOR_PATHS}/nlohmann  
                            PRIVATE ${VENDOR_PATHS}/freetype2 
                            PRIVATE ${VENDOR_PATHS}/tinyxml2 
                            PRIVATE ${VENDOR_PATHS}/imgui/backends 
                            PRIVATE ${VENDOR_PATHS}/yaml-cpp
                            PRIVATE ${VENDOR_PATHS}/SDL2 
                            #PRIVATE ${Vulkan_INCLUDE_DIRS}      
                            
)
if(WIN32)
target_link_directories(TinyLB PRIVATE ${LIB_PATHS})
endif()

target_link_libraries(TinyLB PRIVATE ${CONAN_LIBS}) #${Vulkan_LIBRARIES})
#target_link_libraries(TinyLB PRIVATE CONAN_PKG::poco)