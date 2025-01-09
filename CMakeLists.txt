cmake_minimum_required (VERSION 3.5)
project (TetrisCore)

# All packages used
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Set static linking
# set(CMAKE_EXE_LINKER_FLAGS "-static")

# Where all the C files go
set(PROJECT_SOURCE_FILES
    src/main.c
    src/GameWorld.c
    src/Pieces.c
    src/TetrisTime.c
    src/TetrisUtils.c
    src/TetrisInputEvent.c
    src/Button.c
    src/ResourceRegistry.c
    src/TetrisLogic.c
    src/TetrisRenderer.c

    src/scene/SceneHandler.c
    src/scene/MainMenuScene.c
    src/scene/PauseMenuScene.c
    src/scene/GameOverScene.c
    src/scene/OnePlayerScene.c
    src/scene/TwoPlayerScene.c
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Fixes includes path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# Libraries
target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARY}
    /usr/local/lib/libSDL2main.a
    /usr/local/lib/libSDL2.a
    /usr/local/lib/libSDL2_image.a
    /usr/local/lib/libSDL2_ttf.a
    /usr/local/lib/libSDL2_mixer.a
    m # math
    freetype

    # SDL2::SDL2
    # SDL2_image::SDL2_image
    # SDL2_ttf::SDL2_ttf
    # SDL2_mixer::SDL2_mixer
)

# Includes
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include/scene)
