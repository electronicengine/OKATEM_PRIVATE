# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/yusuf/Documents/workspace/rapidjson

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yusuf/Documents/workspace/rapidjson/build

# Include any dependencies generated for this target.
include example/CMakeFiles/simplereader.dir/depend.make

# Include the progress variables for this target.
include example/CMakeFiles/simplereader.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/simplereader.dir/flags.make

example/CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.o: example/CMakeFiles/simplereader.dir/flags.make
example/CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.o: ../example/simplereader/simplereader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/rapidjson/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.o"
	cd /home/yusuf/Documents/workspace/rapidjson/build/example && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.o -c /home/yusuf/Documents/workspace/rapidjson/example/simplereader/simplereader.cpp

example/CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.i"
	cd /home/yusuf/Documents/workspace/rapidjson/build/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/rapidjson/example/simplereader/simplereader.cpp > CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.i

example/CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.s"
	cd /home/yusuf/Documents/workspace/rapidjson/build/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/rapidjson/example/simplereader/simplereader.cpp -o CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.s

# Object files for target simplereader
simplereader_OBJECTS = \
"CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.o"

# External object files for target simplereader
simplereader_EXTERNAL_OBJECTS =

bin/simplereader: example/CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.o
bin/simplereader: example/CMakeFiles/simplereader.dir/build.make
bin/simplereader: example/CMakeFiles/simplereader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yusuf/Documents/workspace/rapidjson/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/simplereader"
	cd /home/yusuf/Documents/workspace/rapidjson/build/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simplereader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/simplereader.dir/build: bin/simplereader

.PHONY : example/CMakeFiles/simplereader.dir/build

example/CMakeFiles/simplereader.dir/clean:
	cd /home/yusuf/Documents/workspace/rapidjson/build/example && $(CMAKE_COMMAND) -P CMakeFiles/simplereader.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/simplereader.dir/clean

example/CMakeFiles/simplereader.dir/depend:
	cd /home/yusuf/Documents/workspace/rapidjson/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yusuf/Documents/workspace/rapidjson /home/yusuf/Documents/workspace/rapidjson/example /home/yusuf/Documents/workspace/rapidjson/build /home/yusuf/Documents/workspace/rapidjson/build/example /home/yusuf/Documents/workspace/rapidjson/build/example/CMakeFiles/simplereader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/simplereader.dir/depend

