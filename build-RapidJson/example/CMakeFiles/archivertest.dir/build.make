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
include example/CMakeFiles/archivertest.dir/depend.make

# Include the progress variables for this target.
include example/CMakeFiles/archivertest.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/archivertest.dir/flags.make

example/CMakeFiles/archivertest.dir/archiver/archiver.cpp.o: example/CMakeFiles/archivertest.dir/flags.make
example/CMakeFiles/archivertest.dir/archiver/archiver.cpp.o: ../example/archiver/archiver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/rapidjson/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/archivertest.dir/archiver/archiver.cpp.o"
	cd /home/yusuf/Documents/workspace/rapidjson/build/example && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/archivertest.dir/archiver/archiver.cpp.o -c /home/yusuf/Documents/workspace/rapidjson/example/archiver/archiver.cpp

example/CMakeFiles/archivertest.dir/archiver/archiver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/archivertest.dir/archiver/archiver.cpp.i"
	cd /home/yusuf/Documents/workspace/rapidjson/build/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/rapidjson/example/archiver/archiver.cpp > CMakeFiles/archivertest.dir/archiver/archiver.cpp.i

example/CMakeFiles/archivertest.dir/archiver/archiver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/archivertest.dir/archiver/archiver.cpp.s"
	cd /home/yusuf/Documents/workspace/rapidjson/build/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/rapidjson/example/archiver/archiver.cpp -o CMakeFiles/archivertest.dir/archiver/archiver.cpp.s

example/CMakeFiles/archivertest.dir/archiver/archivertest.cpp.o: example/CMakeFiles/archivertest.dir/flags.make
example/CMakeFiles/archivertest.dir/archiver/archivertest.cpp.o: ../example/archiver/archivertest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/rapidjson/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object example/CMakeFiles/archivertest.dir/archiver/archivertest.cpp.o"
	cd /home/yusuf/Documents/workspace/rapidjson/build/example && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/archivertest.dir/archiver/archivertest.cpp.o -c /home/yusuf/Documents/workspace/rapidjson/example/archiver/archivertest.cpp

example/CMakeFiles/archivertest.dir/archiver/archivertest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/archivertest.dir/archiver/archivertest.cpp.i"
	cd /home/yusuf/Documents/workspace/rapidjson/build/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/rapidjson/example/archiver/archivertest.cpp > CMakeFiles/archivertest.dir/archiver/archivertest.cpp.i

example/CMakeFiles/archivertest.dir/archiver/archivertest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/archivertest.dir/archiver/archivertest.cpp.s"
	cd /home/yusuf/Documents/workspace/rapidjson/build/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/rapidjson/example/archiver/archivertest.cpp -o CMakeFiles/archivertest.dir/archiver/archivertest.cpp.s

# Object files for target archivertest
archivertest_OBJECTS = \
"CMakeFiles/archivertest.dir/archiver/archiver.cpp.o" \
"CMakeFiles/archivertest.dir/archiver/archivertest.cpp.o"

# External object files for target archivertest
archivertest_EXTERNAL_OBJECTS =

bin/archivertest: example/CMakeFiles/archivertest.dir/archiver/archiver.cpp.o
bin/archivertest: example/CMakeFiles/archivertest.dir/archiver/archivertest.cpp.o
bin/archivertest: example/CMakeFiles/archivertest.dir/build.make
bin/archivertest: example/CMakeFiles/archivertest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yusuf/Documents/workspace/rapidjson/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../bin/archivertest"
	cd /home/yusuf/Documents/workspace/rapidjson/build/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/archivertest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/archivertest.dir/build: bin/archivertest

.PHONY : example/CMakeFiles/archivertest.dir/build

example/CMakeFiles/archivertest.dir/clean:
	cd /home/yusuf/Documents/workspace/rapidjson/build/example && $(CMAKE_COMMAND) -P CMakeFiles/archivertest.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/archivertest.dir/clean

example/CMakeFiles/archivertest.dir/depend:
	cd /home/yusuf/Documents/workspace/rapidjson/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yusuf/Documents/workspace/rapidjson /home/yusuf/Documents/workspace/rapidjson/example /home/yusuf/Documents/workspace/rapidjson/build /home/yusuf/Documents/workspace/rapidjson/build/example /home/yusuf/Documents/workspace/rapidjson/build/example/CMakeFiles/archivertest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/archivertest.dir/depend

