# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/andres/clion/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/andres/clion/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/andres/Documents/Progra/CE3102-TaylorSIMD

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andres/Documents/Progra/CE3102-TaylorSIMD/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/meta.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/meta.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/meta.dir/flags.make

CMakeFiles/meta.dir/src/meta.cpp.o: CMakeFiles/meta.dir/flags.make
CMakeFiles/meta.dir/src/meta.cpp.o: ../src/meta.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andres/Documents/Progra/CE3102-TaylorSIMD/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/meta.dir/src/meta.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/meta.dir/src/meta.cpp.o -c /home/andres/Documents/Progra/CE3102-TaylorSIMD/src/meta.cpp

CMakeFiles/meta.dir/src/meta.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/meta.dir/src/meta.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andres/Documents/Progra/CE3102-TaylorSIMD/src/meta.cpp > CMakeFiles/meta.dir/src/meta.cpp.i

CMakeFiles/meta.dir/src/meta.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/meta.dir/src/meta.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andres/Documents/Progra/CE3102-TaylorSIMD/src/meta.cpp -o CMakeFiles/meta.dir/src/meta.cpp.s

CMakeFiles/meta.dir/src/meta.cpp.o.requires:

.PHONY : CMakeFiles/meta.dir/src/meta.cpp.o.requires

CMakeFiles/meta.dir/src/meta.cpp.o.provides: CMakeFiles/meta.dir/src/meta.cpp.o.requires
	$(MAKE) -f CMakeFiles/meta.dir/build.make CMakeFiles/meta.dir/src/meta.cpp.o.provides.build
.PHONY : CMakeFiles/meta.dir/src/meta.cpp.o.provides

CMakeFiles/meta.dir/src/meta.cpp.o.provides.build: CMakeFiles/meta.dir/src/meta.cpp.o


# Object files for target meta
meta_OBJECTS = \
"CMakeFiles/meta.dir/src/meta.cpp.o"

# External object files for target meta
meta_EXTERNAL_OBJECTS =

meta: CMakeFiles/meta.dir/src/meta.cpp.o
meta: CMakeFiles/meta.dir/build.make
meta: CMakeFiles/meta.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andres/Documents/Progra/CE3102-TaylorSIMD/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable meta"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/meta.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/meta.dir/build: meta

.PHONY : CMakeFiles/meta.dir/build

CMakeFiles/meta.dir/requires: CMakeFiles/meta.dir/src/meta.cpp.o.requires

.PHONY : CMakeFiles/meta.dir/requires

CMakeFiles/meta.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/meta.dir/cmake_clean.cmake
.PHONY : CMakeFiles/meta.dir/clean

CMakeFiles/meta.dir/depend:
	cd /home/andres/Documents/Progra/CE3102-TaylorSIMD/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andres/Documents/Progra/CE3102-TaylorSIMD /home/andres/Documents/Progra/CE3102-TaylorSIMD /home/andres/Documents/Progra/CE3102-TaylorSIMD/cmake-build-debug /home/andres/Documents/Progra/CE3102-TaylorSIMD/cmake-build-debug /home/andres/Documents/Progra/CE3102-TaylorSIMD/cmake-build-debug/CMakeFiles/meta.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/meta.dir/depend

