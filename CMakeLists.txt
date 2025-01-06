cmake_minimum_required (VERSION 3.2)
project (TetrisCore)

# All packages used
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
# find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

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
    src/TextureRegistry.c
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
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# Libraries
target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARY}
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    # ${SDL2_MIXER_LIBRARIES}
    # m # math
    # freetype
)

# Includes
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include/scene)
