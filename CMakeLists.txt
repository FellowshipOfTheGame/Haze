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

#find_package(FMOD REQUIRED)
#if(FMOD_FOUND)
#    message("FMOD found")
#endif()

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
        #${FMOD_INCLUDE_DIRS}
        )

include_directories(Haze/include/
        Haze/include/Core/
        #Haze/include/Audio/
        Haze/include/Graphics/
        Haze/include/Physics/
        )

file(GLOB PROJECT_HDR Haze/include/*.hpp)
file(GLOB PROJECT_HDR_CORE Haze/include/Core/*.hpp)
#file(GLOB PROJECT_HDR_AUDIO Haze/include/Audio/*.hpp)
file(GLOB PROJECT_HDR_PHYSICS Haze/include/Physics/*.hpp)
file(GLOB PROJECT_HDR_GRAPHICS Haze/include/Graphics/*.hpp)
file(GLOB PROJECT_HDR_LEARNOGL Haze/include/LearnOpenGL/*.h)

file(GLOB PROJECT_SRC Haze/src/*.cpp)
file(GLOB PROJECT_SRC_CORE Haze/src/Core/*.cpp)
#file(GLOB PROJECT_SRC_AUDIO Haze/src/Audio/*.cpp)
file(GLOB PROJECT_SRC_PHYSICS Haze/src/Physics/*.cpp)
file(GLOB PROJECT_SRC_GRAPHICS Haze/src/Graphics/*.cpp)

file(GLOB PROJECT_SHADERS Haze/shader/*.glsl)

file(GLOB 3RDPARTY_SOURCES Haze/3rdparty/glad/src/glad.c
        Haze/3rdparty/stb_image.c)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
        README.md
        .gitattributes
        .gitignore
        .gitmodules)

source_group("Headers"  FILES ${PROJECT_HDR})
source_group("Headers\\Core" FILES ${PROJECT_HDR_CORE})
#source_group("Headers\\Audio" FILES ${PROJECT_HDR_AUDIO})
source_group("Headers\\Physics" FILES ${PROJECT_HDR_PHYSICS})
source_group("Headers\\Graphics" FILES ${PROJECT_HDR_GRAPHICS})
source_group("Headers\\LearnOpenGL" FILES ${PROJECT_HDR_LEARNOGL})


file(GLOB_RECURSE 3RDPARTY_HDR_GLM Haze/3rdparty/glm/)
file(GLOB_RECURSE 3RDPARTY_HDR_STB Haze/3rdparty/stb/)

source_group("Headers\\glm" FILES ${3RDPARTY_HDR_GLM})
source_group("Headers\\stb" FILES ${3RDPARTY_HDR_STB})

file(GLOB PROJECT_HEADERS ${PROJECT_HDR} ${PROJECT_HDR_CORE} ${PROJECT_HDR_AUDIO} ${PROJECT_HDR_PHYSICS} ${PROJECT_HDR_GRAPHICS} ${PROJECT_HDR_LEARNOGL})

source_group("Sources" FILES ${PROJECT_SRC})
source_group("Sources\\Core" FILES ${PROJECT_SRC_CORE})
#source_group("Sources\\Audio" FILES ${PROJECT_SRC_AUDIO})
source_group("Sources\\Physics" FILES ${PROJECT_SRC_PHYSICS})
source_group("Sources\\Graphics" FILES ${PROJECT_SRC_GRAPHICS})

file(GLOB PROJECT_SOURCES ${PROJECT_SRC} ${PROJECT_SRC_CORE} ${PROJECT_SRC_AUDIO} ${PROJECT_SRC_PHYSICS} ${PROJECT_SRC_GRAPHICS})

file(GLOB THIRD_SRCS ${GL_SRCS} ${GLM_SRCS} ${STB_SRCS})

source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("3rdpartys" FILES ${3RDPARTY_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable( ${PROJECT_NAME}
                ${PROJECT_SOURCES}
                ${PROJECT_HEADERS}
                ${PROJECT_SHADERS}
                ${PROJECT_CONFIGS}
                ${3RDPARTY_SOURCES})

target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLAD_LIBRARIES} #${FMOD_LIBRARIES}
                      BulletDynamics BulletCollision LinearMath)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
