# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ilyes/Programming-Projects/PROJECTS/TetrisCore

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/build

# Include any dependencies generated for this target.
include CMakeFiles/TetrisCore.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TetrisCore.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TetrisCore.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TetrisCore.dir/flags.make

CMakeFiles/TetrisCore.dir/src/main.c.o: CMakeFiles/TetrisCore.dir/flags.make
CMakeFiles/TetrisCore.dir/src/main.c.o: /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/main.c
CMakeFiles/TetrisCore.dir/src/main.c.o: CMakeFiles/TetrisCore.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ilyes/Programming-Projects/PROJECTS/TetrisCore/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TetrisCore.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TetrisCore.dir/src/main.c.o -MF CMakeFiles/TetrisCore.dir/src/main.c.o.d -o CMakeFiles/TetrisCore.dir/src/main.c.o -c /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/main.c

CMakeFiles/TetrisCore.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/TetrisCore.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/main.c > CMakeFiles/TetrisCore.dir/src/main.c.i

CMakeFiles/TetrisCore.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/TetrisCore.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/main.c -o CMakeFiles/TetrisCore.dir/src/main.c.s

CMakeFiles/TetrisCore.dir/src/GameWorld.c.o: CMakeFiles/TetrisCore.dir/flags.make
CMakeFiles/TetrisCore.dir/src/GameWorld.c.o: /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/GameWorld.c
CMakeFiles/TetrisCore.dir/src/GameWorld.c.o: CMakeFiles/TetrisCore.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ilyes/Programming-Projects/PROJECTS/TetrisCore/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/TetrisCore.dir/src/GameWorld.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TetrisCore.dir/src/GameWorld.c.o -MF CMakeFiles/TetrisCore.dir/src/GameWorld.c.o.d -o CMakeFiles/TetrisCore.dir/src/GameWorld.c.o -c /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/GameWorld.c

CMakeFiles/TetrisCore.dir/src/GameWorld.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/TetrisCore.dir/src/GameWorld.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/GameWorld.c > CMakeFiles/TetrisCore.dir/src/GameWorld.c.i

CMakeFiles/TetrisCore.dir/src/GameWorld.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/TetrisCore.dir/src/GameWorld.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/GameWorld.c -o CMakeFiles/TetrisCore.dir/src/GameWorld.c.s

CMakeFiles/TetrisCore.dir/src/Pieces.c.o: CMakeFiles/TetrisCore.dir/flags.make
CMakeFiles/TetrisCore.dir/src/Pieces.c.o: /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/Pieces.c
CMakeFiles/TetrisCore.dir/src/Pieces.c.o: CMakeFiles/TetrisCore.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ilyes/Programming-Projects/PROJECTS/TetrisCore/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/TetrisCore.dir/src/Pieces.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TetrisCore.dir/src/Pieces.c.o -MF CMakeFiles/TetrisCore.dir/src/Pieces.c.o.d -o CMakeFiles/TetrisCore.dir/src/Pieces.c.o -c /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/Pieces.c

CMakeFiles/TetrisCore.dir/src/Pieces.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/TetrisCore.dir/src/Pieces.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/Pieces.c > CMakeFiles/TetrisCore.dir/src/Pieces.c.i

CMakeFiles/TetrisCore.dir/src/Pieces.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/TetrisCore.dir/src/Pieces.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/Pieces.c -o CMakeFiles/TetrisCore.dir/src/Pieces.c.s

CMakeFiles/TetrisCore.dir/src/TetrisTime.c.o: CMakeFiles/TetrisCore.dir/flags.make
CMakeFiles/TetrisCore.dir/src/TetrisTime.c.o: /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/TetrisTime.c
CMakeFiles/TetrisCore.dir/src/TetrisTime.c.o: CMakeFiles/TetrisCore.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ilyes/Programming-Projects/PROJECTS/TetrisCore/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/TetrisCore.dir/src/TetrisTime.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TetrisCore.dir/src/TetrisTime.c.o -MF CMakeFiles/TetrisCore.dir/src/TetrisTime.c.o.d -o CMakeFiles/TetrisCore.dir/src/TetrisTime.c.o -c /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/TetrisTime.c

CMakeFiles/TetrisCore.dir/src/TetrisTime.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/TetrisCore.dir/src/TetrisTime.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/TetrisTime.c > CMakeFiles/TetrisCore.dir/src/TetrisTime.c.i

CMakeFiles/TetrisCore.dir/src/TetrisTime.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/TetrisCore.dir/src/TetrisTime.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/TetrisTime.c -o CMakeFiles/TetrisCore.dir/src/TetrisTime.c.s

CMakeFiles/TetrisCore.dir/src/scene/Scene.c.o: CMakeFiles/TetrisCore.dir/flags.make
CMakeFiles/TetrisCore.dir/src/scene/Scene.c.o: /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/scene/Scene.c
CMakeFiles/TetrisCore.dir/src/scene/Scene.c.o: CMakeFiles/TetrisCore.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ilyes/Programming-Projects/PROJECTS/TetrisCore/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/TetrisCore.dir/src/scene/Scene.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TetrisCore.dir/src/scene/Scene.c.o -MF CMakeFiles/TetrisCore.dir/src/scene/Scene.c.o.d -o CMakeFiles/TetrisCore.dir/src/scene/Scene.c.o -c /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/scene/Scene.c

CMakeFiles/TetrisCore.dir/src/scene/Scene.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/TetrisCore.dir/src/scene/Scene.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/scene/Scene.c > CMakeFiles/TetrisCore.dir/src/scene/Scene.c.i

CMakeFiles/TetrisCore.dir/src/scene/Scene.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/TetrisCore.dir/src/scene/Scene.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/scene/Scene.c -o CMakeFiles/TetrisCore.dir/src/scene/Scene.c.s

CMakeFiles/TetrisCore.dir/src/scene/SceneHandler.c.o: CMakeFiles/TetrisCore.dir/flags.make
CMakeFiles/TetrisCore.dir/src/scene/SceneHandler.c.o: /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/scene/SceneHandler.c
CMakeFiles/TetrisCore.dir/src/scene/SceneHandler.c.o: CMakeFiles/TetrisCore.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ilyes/Programming-Projects/PROJECTS/TetrisCore/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/TetrisCore.dir/src/scene/SceneHandler.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TetrisCore.dir/src/scene/SceneHandler.c.o -MF CMakeFiles/TetrisCore.dir/src/scene/SceneHandler.c.o.d -o CMakeFiles/TetrisCore.dir/src/scene/SceneHandler.c.o -c /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/scene/SceneHandler.c

CMakeFiles/TetrisCore.dir/src/scene/SceneHandler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/TetrisCore.dir/src/scene/SceneHandler.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/scene/SceneHandler.c > CMakeFiles/TetrisCore.dir/src/scene/SceneHandler.c.i

CMakeFiles/TetrisCore.dir/src/scene/SceneHandler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/TetrisCore.dir/src/scene/SceneHandler.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/scene/SceneHandler.c -o CMakeFiles/TetrisCore.dir/src/scene/SceneHandler.c.s

CMakeFiles/TetrisCore.dir/src/scene/SceneRenderer.c.o: CMakeFiles/TetrisCore.dir/flags.make
CMakeFiles/TetrisCore.dir/src/scene/SceneRenderer.c.o: /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/scene/SceneRenderer.c
CMakeFiles/TetrisCore.dir/src/scene/SceneRenderer.c.o: CMakeFiles/TetrisCore.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ilyes/Programming-Projects/PROJECTS/TetrisCore/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/TetrisCore.dir/src/scene/SceneRenderer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TetrisCore.dir/src/scene/SceneRenderer.c.o -MF CMakeFiles/TetrisCore.dir/src/scene/SceneRenderer.c.o.d -o CMakeFiles/TetrisCore.dir/src/scene/SceneRenderer.c.o -c /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/scene/SceneRenderer.c

CMakeFiles/TetrisCore.dir/src/scene/SceneRenderer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/TetrisCore.dir/src/scene/SceneRenderer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/scene/SceneRenderer.c > CMakeFiles/TetrisCore.dir/src/scene/SceneRenderer.c.i

CMakeFiles/TetrisCore.dir/src/scene/SceneRenderer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/TetrisCore.dir/src/scene/SceneRenderer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/src/scene/SceneRenderer.c -o CMakeFiles/TetrisCore.dir/src/scene/SceneRenderer.c.s

# Object files for target TetrisCore
TetrisCore_OBJECTS = \
"CMakeFiles/TetrisCore.dir/src/main.c.o" \
"CMakeFiles/TetrisCore.dir/src/GameWorld.c.o" \
"CMakeFiles/TetrisCore.dir/src/Pieces.c.o" \
"CMakeFiles/TetrisCore.dir/src/TetrisTime.c.o" \
"CMakeFiles/TetrisCore.dir/src/scene/Scene.c.o" \
"CMakeFiles/TetrisCore.dir/src/scene/SceneHandler.c.o" \
"CMakeFiles/TetrisCore.dir/src/scene/SceneRenderer.c.o"

# External object files for target TetrisCore
TetrisCore_EXTERNAL_OBJECTS =

TetrisCore: CMakeFiles/TetrisCore.dir/src/main.c.o
TetrisCore: CMakeFiles/TetrisCore.dir/src/GameWorld.c.o
TetrisCore: CMakeFiles/TetrisCore.dir/src/Pieces.c.o
TetrisCore: CMakeFiles/TetrisCore.dir/src/TetrisTime.c.o
TetrisCore: CMakeFiles/TetrisCore.dir/src/scene/Scene.c.o
TetrisCore: CMakeFiles/TetrisCore.dir/src/scene/SceneHandler.c.o
TetrisCore: CMakeFiles/TetrisCore.dir/src/scene/SceneRenderer.c.o
TetrisCore: CMakeFiles/TetrisCore.dir/build.make
TetrisCore: /usr/lib64/libGL.so
TetrisCore: /usr/lib64/libGLU.so
TetrisCore: /usr/local/lib64/libSDL2main.a
TetrisCore: /usr/local/lib64/libSDL2_image-2.0.so.0.800.2
TetrisCore: /usr/lib64/libpng.so
TetrisCore: /usr/local/lib64/libSDL2-2.0.so.0.3000.9
TetrisCore: CMakeFiles/TetrisCore.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ilyes/Programming-Projects/PROJECTS/TetrisCore/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable TetrisCore"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TetrisCore.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TetrisCore.dir/build: TetrisCore
.PHONY : CMakeFiles/TetrisCore.dir/build

CMakeFiles/TetrisCore.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TetrisCore.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TetrisCore.dir/clean

CMakeFiles/TetrisCore.dir/depend:
	cd /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ilyes/Programming-Projects/PROJECTS/TetrisCore /home/ilyes/Programming-Projects/PROJECTS/TetrisCore /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/build /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/build /home/ilyes/Programming-Projects/PROJECTS/TetrisCore/build/CMakeFiles/TetrisCore.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/TetrisCore.dir/depend

