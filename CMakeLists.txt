# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.16)

project ("Platformer")
set(CMAKE_CXX_STANDARD 20)

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${PROJECT_BINARY_DIR})

# Include sub-projects.
add_executable(${PROJECT_NAME} src/main/Game.cpp
        src/glad.c
                                src/engine/io/Window.h src/engine/io/Window.cpp 
                                src/engine/utils/Timer.h src/engine/utils/Timer.cpp 
                                #src/scenes/SceneHandler.cpp src/scenes/SceneHandler.h 
                                #src/scenes/adt/ISceneManipulator.h 
                                #src/scenes/SceneEnvir.cpp src/scenes/SceneEnvir.h
                               # src/scenes/Scenes.h 
                                #src/engine/graphics/Renderer.cpp src/engine/graphics/Renderer.h 
                                src/engine/graphics/Camera.cpp src/engine/graphics/Camera.h 
                                #src/scenes/adt/NkContext.cpp src/scenes/adt/NkContext.h 
                                #src/audio/AudioRemote.h
        #src/scenes/regular/TestScene.cpp src/scenes/regular/TestScene.h)
        src/Sprite.cpp src/Sprite.h src/Shader.h src/Shader.cpp src/engine/io/ResourceLoader.h src/engine/io/ResourceLoader.cpp src/Camera.h src/Map.cpp src/Map.h src/Player.cpp src/Player.h src/Audio.cpp)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
include_directories( ${OPENGL_INCLUDE_DIRS} )
add_dependencies(${PROJECT_NAME} OpenGL::GL)

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/Libraries/openal-soft)

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/Libraries/libsndfile)
#find_package(libsndfile REQUIRED COMPONENTS OpenGL)

find_library(
        LIB_SND_FILE
        NAMES libsndfile-1
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/libsndfile/lib/win_cb)

target_link_libraries(
        ${PROJECT_NAME}
        ${LIB_SND_FILE})

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glm)

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glfw)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glfw/include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/stb)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/libsndfile/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Nuklear)

#target_link_directories(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/libsndfile/lib/win_cb)

target_link_libraries(${PROJECT_NAME}
        OpenGL::GL
        glm::glm
        OpenAL
#        libsndfile-1.lib
#        ${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.h
        glfw)


add_library(nuklear STATIC "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Nuklear/nuklear.c")
target_compile_definitions(nuklear PUBLIC
        NK_INCLUDE_FIXED_TYPES
        NK_INCLUDE_STANDARD_IO
        NK_INCLUDE_DEFAULT_ALLOCATOR
        NK_INCLUDE_VERTEX_BUFFER_OUTPUT
        NK_INCLUDE_FONT_BAKING
        NK_KEYSTATE_BASED_INPUT
        )
set_target_properties(nuklear PROPERTIES LINKER_LANGUAGE C)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_AUTOGEN_VERBOSE ON)
#set(CMAKE_VERBOSE_MAKEFILE ON)
