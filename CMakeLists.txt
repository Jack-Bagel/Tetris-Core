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

    src/scene/TetrisHandler.c
    src/scene/TetrisLogic.c
    src/scene/TetrisRenderer.c
    src/scene/TetrisStartScreen.c
    src/scene/TetrisPauseScreen.c
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Fixes includes path
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# Libraries
target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARY}
    /usr/local/lib/libSDL2.a
    /usr/local/lib/libSDL2_image.a
    /usr/local/lib/libSDL2_ttf.a
    # ${SDL2_MIXER_LIBRARIES}
    m # math
    freetype
)

# Includes
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include/scene)
