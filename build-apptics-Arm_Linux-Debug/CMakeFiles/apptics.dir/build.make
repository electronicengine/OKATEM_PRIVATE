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
CMAKE_SOURCE_DIR = /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug

# Include any dependencies generated for this target.
include CMakeFiles/apptics.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/apptics.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/apptics.dir/flags.make

CMakeFiles/apptics.dir/main.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/main.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/apptics.dir/main.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/main.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/main.cpp

CMakeFiles/apptics.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/main.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/main.cpp > CMakeFiles/apptics.dir/main.cpp.i

CMakeFiles/apptics.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/main.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/main.cpp -o CMakeFiles/apptics.dir/main.cpp.s

CMakeFiles/apptics.dir/src/mainoperation.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/mainoperation.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/mainoperation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/apptics.dir/src/mainoperation.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/mainoperation.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/mainoperation.cpp

CMakeFiles/apptics.dir/src/mainoperation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/mainoperation.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/mainoperation.cpp > CMakeFiles/apptics.dir/src/mainoperation.cpp.i

CMakeFiles/apptics.dir/src/mainoperation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/mainoperation.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/mainoperation.cpp -o CMakeFiles/apptics.dir/src/mainoperation.cpp.s

CMakeFiles/apptics.dir/src/lcdhmi.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/lcdhmi.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/lcdhmi.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/apptics.dir/src/lcdhmi.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/lcdhmi.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/lcdhmi.cpp

CMakeFiles/apptics.dir/src/lcdhmi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/lcdhmi.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/lcdhmi.cpp > CMakeFiles/apptics.dir/src/lcdhmi.cpp.i

CMakeFiles/apptics.dir/src/lcdhmi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/lcdhmi.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/lcdhmi.cpp -o CMakeFiles/apptics.dir/src/lcdhmi.cpp.s

CMakeFiles/apptics.dir/src/lasertracker.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/lasertracker.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/lasertracker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/apptics.dir/src/lasertracker.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/lasertracker.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/lasertracker.cpp

CMakeFiles/apptics.dir/src/lasertracker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/lasertracker.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/lasertracker.cpp > CMakeFiles/apptics.dir/src/lasertracker.cpp.i

CMakeFiles/apptics.dir/src/lasertracker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/lasertracker.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/lasertracker.cpp -o CMakeFiles/apptics.dir/src/lasertracker.cpp.s

CMakeFiles/apptics.dir/src/serialcom.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/serialcom.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/serialcom.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/apptics.dir/src/serialcom.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/serialcom.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/serialcom.cpp

CMakeFiles/apptics.dir/src/serialcom.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/serialcom.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/serialcom.cpp > CMakeFiles/apptics.dir/src/serialcom.cpp.i

CMakeFiles/apptics.dir/src/serialcom.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/serialcom.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/serialcom.cpp -o CMakeFiles/apptics.dir/src/serialcom.cpp.s

CMakeFiles/apptics.dir/src/lorawan.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/lorawan.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/lorawan.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/apptics.dir/src/lorawan.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/lorawan.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/lorawan.cpp

CMakeFiles/apptics.dir/src/lorawan.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/lorawan.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/lorawan.cpp > CMakeFiles/apptics.dir/src/lorawan.cpp.i

CMakeFiles/apptics.dir/src/lorawan.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/lorawan.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/lorawan.cpp -o CMakeFiles/apptics.dir/src/lorawan.cpp.s

CMakeFiles/apptics.dir/src/spicom.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/spicom.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/spicom.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/apptics.dir/src/spicom.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/spicom.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/spicom.cpp

CMakeFiles/apptics.dir/src/spicom.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/spicom.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/spicom.cpp > CMakeFiles/apptics.dir/src/spicom.cpp.i

CMakeFiles/apptics.dir/src/spicom.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/spicom.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/spicom.cpp -o CMakeFiles/apptics.dir/src/spicom.cpp.s

CMakeFiles/apptics.dir/src/stmdriver.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/stmdriver.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/stmdriver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/apptics.dir/src/stmdriver.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/stmdriver.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/stmdriver.cpp

CMakeFiles/apptics.dir/src/stmdriver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/stmdriver.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/stmdriver.cpp > CMakeFiles/apptics.dir/src/stmdriver.cpp.i

CMakeFiles/apptics.dir/src/stmdriver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/stmdriver.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/stmdriver.cpp -o CMakeFiles/apptics.dir/src/stmdriver.cpp.s

CMakeFiles/apptics.dir/src/sfpmonitor.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/sfpmonitor.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/sfpmonitor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/apptics.dir/src/sfpmonitor.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/sfpmonitor.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/sfpmonitor.cpp

CMakeFiles/apptics.dir/src/sfpmonitor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/sfpmonitor.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/sfpmonitor.cpp > CMakeFiles/apptics.dir/src/sfpmonitor.cpp.i

CMakeFiles/apptics.dir/src/sfpmonitor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/sfpmonitor.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/sfpmonitor.cpp -o CMakeFiles/apptics.dir/src/sfpmonitor.cpp.s

CMakeFiles/apptics.dir/src/udpsocket.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/udpsocket.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/udpsocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/apptics.dir/src/udpsocket.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/udpsocket.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/udpsocket.cpp

CMakeFiles/apptics.dir/src/udpsocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/udpsocket.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/udpsocket.cpp > CMakeFiles/apptics.dir/src/udpsocket.cpp.i

CMakeFiles/apptics.dir/src/udpsocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/udpsocket.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/udpsocket.cpp -o CMakeFiles/apptics.dir/src/udpsocket.cpp.s

CMakeFiles/apptics.dir/src/ethernetsocket.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/ethernetsocket.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/ethernetsocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/apptics.dir/src/ethernetsocket.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/ethernetsocket.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/ethernetsocket.cpp

CMakeFiles/apptics.dir/src/ethernetsocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/ethernetsocket.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/ethernetsocket.cpp > CMakeFiles/apptics.dir/src/ethernetsocket.cpp.i

CMakeFiles/apptics.dir/src/ethernetsocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/ethernetsocket.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/ethernetsocket.cpp -o CMakeFiles/apptics.dir/src/ethernetsocket.cpp.s

CMakeFiles/apptics.dir/src/queue.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/queue.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/queue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/apptics.dir/src/queue.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/queue.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/queue.cpp

CMakeFiles/apptics.dir/src/queue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/queue.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/queue.cpp > CMakeFiles/apptics.dir/src/queue.cpp.i

CMakeFiles/apptics.dir/src/queue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/queue.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/queue.cpp -o CMakeFiles/apptics.dir/src/queue.cpp.s

CMakeFiles/apptics.dir/src/json.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/json.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/json.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/apptics.dir/src/json.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/json.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/json.cpp

CMakeFiles/apptics.dir/src/json.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/json.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/json.cpp > CMakeFiles/apptics.dir/src/json.cpp.i

CMakeFiles/apptics.dir/src/json.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/json.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/json.cpp -o CMakeFiles/apptics.dir/src/json.cpp.s

CMakeFiles/apptics.dir/src/globals.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/globals.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/globals.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/apptics.dir/src/globals.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/globals.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/globals.cpp

CMakeFiles/apptics.dir/src/globals.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/globals.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/globals.cpp > CMakeFiles/apptics.dir/src/globals.cpp.i

CMakeFiles/apptics.dir/src/globals.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/globals.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/globals.cpp -o CMakeFiles/apptics.dir/src/globals.cpp.s

CMakeFiles/apptics.dir/src/cameradriver.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/cameradriver.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/cameradriver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/apptics.dir/src/cameradriver.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/cameradriver.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/cameradriver.cpp

CMakeFiles/apptics.dir/src/cameradriver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/cameradriver.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/cameradriver.cpp > CMakeFiles/apptics.dir/src/cameradriver.cpp.i

CMakeFiles/apptics.dir/src/cameradriver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/cameradriver.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/cameradriver.cpp -o CMakeFiles/apptics.dir/src/cameradriver.cpp.s

CMakeFiles/apptics.dir/src/v4l2ctrl.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/v4l2ctrl.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/v4l2ctrl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/apptics.dir/src/v4l2ctrl.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/v4l2ctrl.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/v4l2ctrl.cpp

CMakeFiles/apptics.dir/src/v4l2ctrl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/v4l2ctrl.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/v4l2ctrl.cpp > CMakeFiles/apptics.dir/src/v4l2ctrl.cpp.i

CMakeFiles/apptics.dir/src/v4l2ctrl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/v4l2ctrl.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/v4l2ctrl.cpp -o CMakeFiles/apptics.dir/src/v4l2ctrl.cpp.s

CMakeFiles/apptics.dir/src/remotecontrolinterface.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/remotecontrolinterface.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/remotecontrolinterface.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/apptics.dir/src/remotecontrolinterface.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/remotecontrolinterface.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/remotecontrolinterface.cpp

CMakeFiles/apptics.dir/src/remotecontrolinterface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/remotecontrolinterface.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/remotecontrolinterface.cpp > CMakeFiles/apptics.dir/src/remotecontrolinterface.cpp.i

CMakeFiles/apptics.dir/src/remotecontrolinterface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/remotecontrolinterface.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/remotecontrolinterface.cpp -o CMakeFiles/apptics.dir/src/remotecontrolinterface.cpp.s

CMakeFiles/apptics.dir/src/driverinterface.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/driverinterface.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/driverinterface.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/apptics.dir/src/driverinterface.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/driverinterface.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/driverinterface.cpp

CMakeFiles/apptics.dir/src/driverinterface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/driverinterface.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/driverinterface.cpp > CMakeFiles/apptics.dir/src/driverinterface.cpp.i

CMakeFiles/apptics.dir/src/driverinterface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/driverinterface.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/driverinterface.cpp -o CMakeFiles/apptics.dir/src/driverinterface.cpp.s

CMakeFiles/apptics.dir/src/environmentinterface.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/environmentinterface.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/environmentinterface.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Building CXX object CMakeFiles/apptics.dir/src/environmentinterface.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/environmentinterface.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/environmentinterface.cpp

CMakeFiles/apptics.dir/src/environmentinterface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/environmentinterface.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/environmentinterface.cpp > CMakeFiles/apptics.dir/src/environmentinterface.cpp.i

CMakeFiles/apptics.dir/src/environmentinterface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/environmentinterface.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/environmentinterface.cpp -o CMakeFiles/apptics.dir/src/environmentinterface.cpp.s

CMakeFiles/apptics.dir/src/routingtable.cpp.o: CMakeFiles/apptics.dir/flags.make
CMakeFiles/apptics.dir/src/routingtable.cpp.o: /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/routingtable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_20) "Building CXX object CMakeFiles/apptics.dir/src/routingtable.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apptics.dir/src/routingtable.cpp.o -c /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/routingtable.cpp

CMakeFiles/apptics.dir/src/routingtable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apptics.dir/src/routingtable.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/routingtable.cpp > CMakeFiles/apptics.dir/src/routingtable.cpp.i

CMakeFiles/apptics.dir/src/routingtable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apptics.dir/src/routingtable.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics/src/routingtable.cpp -o CMakeFiles/apptics.dir/src/routingtable.cpp.s

# Object files for target apptics
apptics_OBJECTS = \
"CMakeFiles/apptics.dir/main.cpp.o" \
"CMakeFiles/apptics.dir/src/mainoperation.cpp.o" \
"CMakeFiles/apptics.dir/src/lcdhmi.cpp.o" \
"CMakeFiles/apptics.dir/src/lasertracker.cpp.o" \
"CMakeFiles/apptics.dir/src/serialcom.cpp.o" \
"CMakeFiles/apptics.dir/src/lorawan.cpp.o" \
"CMakeFiles/apptics.dir/src/spicom.cpp.o" \
"CMakeFiles/apptics.dir/src/stmdriver.cpp.o" \
"CMakeFiles/apptics.dir/src/sfpmonitor.cpp.o" \
"CMakeFiles/apptics.dir/src/udpsocket.cpp.o" \
"CMakeFiles/apptics.dir/src/ethernetsocket.cpp.o" \
"CMakeFiles/apptics.dir/src/queue.cpp.o" \
"CMakeFiles/apptics.dir/src/json.cpp.o" \
"CMakeFiles/apptics.dir/src/globals.cpp.o" \
"CMakeFiles/apptics.dir/src/cameradriver.cpp.o" \
"CMakeFiles/apptics.dir/src/v4l2ctrl.cpp.o" \
"CMakeFiles/apptics.dir/src/remotecontrolinterface.cpp.o" \
"CMakeFiles/apptics.dir/src/driverinterface.cpp.o" \
"CMakeFiles/apptics.dir/src/environmentinterface.cpp.o" \
"CMakeFiles/apptics.dir/src/routingtable.cpp.o"

# External object files for target apptics
apptics_EXTERNAL_OBJECTS =

apptics: CMakeFiles/apptics.dir/main.cpp.o
apptics: CMakeFiles/apptics.dir/src/mainoperation.cpp.o
apptics: CMakeFiles/apptics.dir/src/lcdhmi.cpp.o
apptics: CMakeFiles/apptics.dir/src/lasertracker.cpp.o
apptics: CMakeFiles/apptics.dir/src/serialcom.cpp.o
apptics: CMakeFiles/apptics.dir/src/lorawan.cpp.o
apptics: CMakeFiles/apptics.dir/src/spicom.cpp.o
apptics: CMakeFiles/apptics.dir/src/stmdriver.cpp.o
apptics: CMakeFiles/apptics.dir/src/sfpmonitor.cpp.o
apptics: CMakeFiles/apptics.dir/src/udpsocket.cpp.o
apptics: CMakeFiles/apptics.dir/src/ethernetsocket.cpp.o
apptics: CMakeFiles/apptics.dir/src/queue.cpp.o
apptics: CMakeFiles/apptics.dir/src/json.cpp.o
apptics: CMakeFiles/apptics.dir/src/globals.cpp.o
apptics: CMakeFiles/apptics.dir/src/cameradriver.cpp.o
apptics: CMakeFiles/apptics.dir/src/v4l2ctrl.cpp.o
apptics: CMakeFiles/apptics.dir/src/remotecontrolinterface.cpp.o
apptics: CMakeFiles/apptics.dir/src/driverinterface.cpp.o
apptics: CMakeFiles/apptics.dir/src/environmentinterface.cpp.o
apptics: CMakeFiles/apptics.dir/src/routingtable.cpp.o
apptics: CMakeFiles/apptics.dir/build.make
apptics: CMakeFiles/apptics.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_21) "Linking CXX executable apptics"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/apptics.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/apptics.dir/build: apptics

.PHONY : CMakeFiles/apptics.dir/build

CMakeFiles/apptics.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/apptics.dir/cmake_clean.cmake
.PHONY : CMakeFiles/apptics.dir/clean

CMakeFiles/apptics.dir/depend:
	cd /home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics /home/yusuf/Documents/workspace/OKATEM_PRIVATE/apptics /home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug /home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug /home/yusuf/Documents/workspace/OKATEM_PRIVATE/build-apptics-Arm_Linux-Debug/CMakeFiles/apptics.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/apptics.dir/depend
