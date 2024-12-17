cmake_minimum_required (VERSION 3.2)
project (TetrisCore)

# All packages used
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

find_library(PNGLIB png)

# Set static linking
# set(CMAKE_EXE_LINKER_FLAGS "-static")

# Where all the C files go
set(PROJECT_SOURCE_FILES
    src/main.c
    src/GameWorld.c
    src/Pieces.c
    src/TetrisTime.c

    src/scene/Scene.c
    src/scene/SceneHandler.c
    src/scene/SceneRenderer.c
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Fixes includes path
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# Libraries
target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARY}
    ${SDL2_LIBRARIES}
    SDL2_image::SDL2_image
    ${PNGLIB}
    ${SDL2_MIXER_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    m # math
)

# Includes
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include/scene)
