# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/blake/桌面/CMake_learn/program2_detect

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/blake/桌面/CMake_learn/program2_detect/build

# Include any dependencies generated for this target.
include detectfunc/CMakeFiles/detectfunc.dir/depend.make

# Include the progress variables for this target.
include detectfunc/CMakeFiles/detectfunc.dir/progress.make

# Include the compile flags for this target's objects.
include detectfunc/CMakeFiles/detectfunc.dir/flags.make

detectfunc/CMakeFiles/detectfunc.dir/src/detectfunc.cpp.o: detectfunc/CMakeFiles/detectfunc.dir/flags.make
detectfunc/CMakeFiles/detectfunc.dir/src/detectfunc.cpp.o: ../detectfunc/src/detectfunc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/blake/桌面/CMake_learn/program2_detect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object detectfunc/CMakeFiles/detectfunc.dir/src/detectfunc.cpp.o"
	cd /home/blake/桌面/CMake_learn/program2_detect/build/detectfunc && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/detectfunc.dir/src/detectfunc.cpp.o -c /home/blake/桌面/CMake_learn/program2_detect/detectfunc/src/detectfunc.cpp

detectfunc/CMakeFiles/detectfunc.dir/src/detectfunc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/detectfunc.dir/src/detectfunc.cpp.i"
	cd /home/blake/桌面/CMake_learn/program2_detect/build/detectfunc && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/blake/桌面/CMake_learn/program2_detect/detectfunc/src/detectfunc.cpp > CMakeFiles/detectfunc.dir/src/detectfunc.cpp.i

detectfunc/CMakeFiles/detectfunc.dir/src/detectfunc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/detectfunc.dir/src/detectfunc.cpp.s"
	cd /home/blake/桌面/CMake_learn/program2_detect/build/detectfunc && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/blake/桌面/CMake_learn/program2_detect/detectfunc/src/detectfunc.cpp -o CMakeFiles/detectfunc.dir/src/detectfunc.cpp.s

# Object files for target detectfunc
detectfunc_OBJECTS = \
"CMakeFiles/detectfunc.dir/src/detectfunc.cpp.o"

# External object files for target detectfunc
detectfunc_EXTERNAL_OBJECTS =

detectfunc/libdetectfunc.a: detectfunc/CMakeFiles/detectfunc.dir/src/detectfunc.cpp.o
detectfunc/libdetectfunc.a: detectfunc/CMakeFiles/detectfunc.dir/build.make
detectfunc/libdetectfunc.a: detectfunc/CMakeFiles/detectfunc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/blake/桌面/CMake_learn/program2_detect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libdetectfunc.a"
	cd /home/blake/桌面/CMake_learn/program2_detect/build/detectfunc && $(CMAKE_COMMAND) -P CMakeFiles/detectfunc.dir/cmake_clean_target.cmake
	cd /home/blake/桌面/CMake_learn/program2_detect/build/detectfunc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/detectfunc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
detectfunc/CMakeFiles/detectfunc.dir/build: detectfunc/libdetectfunc.a

.PHONY : detectfunc/CMakeFiles/detectfunc.dir/build

detectfunc/CMakeFiles/detectfunc.dir/clean:
	cd /home/blake/桌面/CMake_learn/program2_detect/build/detectfunc && $(CMAKE_COMMAND) -P CMakeFiles/detectfunc.dir/cmake_clean.cmake
.PHONY : detectfunc/CMakeFiles/detectfunc.dir/clean

detectfunc/CMakeFiles/detectfunc.dir/depend:
	cd /home/blake/桌面/CMake_learn/program2_detect/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/blake/桌面/CMake_learn/program2_detect /home/blake/桌面/CMake_learn/program2_detect/detectfunc /home/blake/桌面/CMake_learn/program2_detect/build /home/blake/桌面/CMake_learn/program2_detect/build/detectfunc /home/blake/桌面/CMake_learn/program2_detect/build/detectfunc/CMakeFiles/detectfunc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : detectfunc/CMakeFiles/detectfunc.dir/depend

