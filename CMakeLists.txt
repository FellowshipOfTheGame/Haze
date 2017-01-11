cmake_minimum_required(VERSION 3.0)
project(Haze)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/Modules")

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(Haze/3rdparty/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(Haze/3rdparty/assimp)

option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
add_subdirectory(Haze/3rdparty/bullet)

find_package(OpenAL REQUIRED)
find_package(ALUT REQUIRED)
if(OPENAL_FOUND)
    message("OPENAL FOUND")
endif()

if(ALUT_FOUND)
    message("ALUT FOUND")
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(Haze/3rdparty/assimp/include/
        Haze/3rdparty/bullet/src/
        Haze/3rdparty/glad/include/
        Haze/3rdparty/glfw/include/
        Haze/3rdparty/glm/
        Haze/3rdparty/stb/
        ${ALUT_INCLUDE_DIRS})

include_directories(Haze/include/
        Haze/include/Core/
        Haze/include/Audio/
        Haze/include/Graphics/
        Haze/include/Physics/)

file(GLOB PROJECT_HEADERS Haze/include/*.hpp
        Haze/include/Core/*.hpp
        Haze/include/Audio/*.hpp
        Haze/include/Graphics/*.hpp
        Haze/include/Physics/*.hpp)

file(GLOB PROJECT_SOURCES Haze/src/*.cpp
        Haze/src/Core/*.cpp
        Haze/src/Audio/*.cpp
        Haze/src/Graphics/*.cpp
        Haze/src/Physics/*.cpp)

file(GLOB PROJECT_SHADERS Haze/shader/*.comp
        Haze/shader/*.frag
        Haze/shader/*.geom
        Haze/shader/*.vert)

file(GLOB 3RDPARTY_SOURCES Haze/3rdparty/glad/src/glad.c)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
        README.md
        .gitattributes
        .gitignore
        .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("3rdpartys" FILES ${3RDPARTY_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${3RDPARTY_SOURCES})
target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES} ${ALUT_LIBRARIES}
                      BulletDynamics BulletCollision LinearMath)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
