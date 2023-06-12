# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.16)

project("Platformer")
set(CMAKE_CXX_STANDARD 20)

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${PROJECT_BINARY_DIR})

# Include sub-projects.
add_executable(${PROJECT_NAME}
        src/main/Game.cpp
        src/glad.c
        src/engine/io/Window.h
        src/engine/io/Window.cpp
        src/engine/utils/Timer.h
        src/engine/utils/Timer.cpp
        src/Sprite.cpp
        src/Sprite.h
        src/Shader.h
        src/Shader.cpp
        src/engine/io/ResourceLoader.h
        src/engine/io/ResourceLoader.cpp
        src/Map.cpp
        src/Map.h
        src/Player.cpp
        src/Player.h
        )
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
include_directories(${OPENGL_INCLUDE_DIRS})
add_dependencies(${PROJECT_NAME} OpenGL::GL)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glfw)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glfw/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/stb)

target_link_libraries(${PROJECT_NAME}
        OpenGL::GL
        #        ${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.h
        glfw)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Change this to false if you want to disable warnings_as_errors in developer mode
set(OPT_WARNINGS_AS_ERRORS_DEVELOPER_DEFAULT TRUE)
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else ()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif ()

# Experience shows that explicit package naming can help make it easier to sort
# out potential ABI related issues before they start, while helping you
# track a build to a specific GIT SHA
set(CPACK_PACKAGE_FILE_NAME
        "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${GIT_SHORT_SHA}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}"
        )
