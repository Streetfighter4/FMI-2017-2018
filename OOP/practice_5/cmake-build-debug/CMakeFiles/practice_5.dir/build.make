# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /home/yasen/Installs/clion-2017.3.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/yasen/Installs/clion-2017.3.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yasen/Programming/FMI-2017-2018/OOP/practice_5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yasen/Programming/FMI-2017-2018/OOP/practice_5/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/practice_5.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/practice_5.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/practice_5.dir/flags.make

CMakeFiles/practice_5.dir/main.cpp.o: CMakeFiles/practice_5.dir/flags.make
CMakeFiles/practice_5.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yasen/Programming/FMI-2017-2018/OOP/practice_5/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/practice_5.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/practice_5.dir/main.cpp.o -c /home/yasen/Programming/FMI-2017-2018/OOP/practice_5/main.cpp

CMakeFiles/practice_5.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/practice_5.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yasen/Programming/FMI-2017-2018/OOP/practice_5/main.cpp > CMakeFiles/practice_5.dir/main.cpp.i

CMakeFiles/practice_5.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/practice_5.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yasen/Programming/FMI-2017-2018/OOP/practice_5/main.cpp -o CMakeFiles/practice_5.dir/main.cpp.s

CMakeFiles/practice_5.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/practice_5.dir/main.cpp.o.requires

CMakeFiles/practice_5.dir/main.cpp.o.provides: CMakeFiles/practice_5.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/practice_5.dir/build.make CMakeFiles/practice_5.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/practice_5.dir/main.cpp.o.provides

CMakeFiles/practice_5.dir/main.cpp.o.provides.build: CMakeFiles/practice_5.dir/main.cpp.o


CMakeFiles/practice_5.dir/DynamicArray.cpp.o: CMakeFiles/practice_5.dir/flags.make
CMakeFiles/practice_5.dir/DynamicArray.cpp.o: ../DynamicArray.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yasen/Programming/FMI-2017-2018/OOP/practice_5/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/practice_5.dir/DynamicArray.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/practice_5.dir/DynamicArray.cpp.o -c /home/yasen/Programming/FMI-2017-2018/OOP/practice_5/DynamicArray.cpp

CMakeFiles/practice_5.dir/DynamicArray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/practice_5.dir/DynamicArray.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yasen/Programming/FMI-2017-2018/OOP/practice_5/DynamicArray.cpp > CMakeFiles/practice_5.dir/DynamicArray.cpp.i

CMakeFiles/practice_5.dir/DynamicArray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/practice_5.dir/DynamicArray.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yasen/Programming/FMI-2017-2018/OOP/practice_5/DynamicArray.cpp -o CMakeFiles/practice_5.dir/DynamicArray.cpp.s

CMakeFiles/practice_5.dir/DynamicArray.cpp.o.requires:

.PHONY : CMakeFiles/practice_5.dir/DynamicArray.cpp.o.requires

CMakeFiles/practice_5.dir/DynamicArray.cpp.o.provides: CMakeFiles/practice_5.dir/DynamicArray.cpp.o.requires
	$(MAKE) -f CMakeFiles/practice_5.dir/build.make CMakeFiles/practice_5.dir/DynamicArray.cpp.o.provides.build
.PHONY : CMakeFiles/practice_5.dir/DynamicArray.cpp.o.provides

CMakeFiles/practice_5.dir/DynamicArray.cpp.o.provides.build: CMakeFiles/practice_5.dir/DynamicArray.cpp.o


# Object files for target practice_5
practice_5_OBJECTS = \
"CMakeFiles/practice_5.dir/main.cpp.o" \
"CMakeFiles/practice_5.dir/DynamicArray.cpp.o"

# External object files for target practice_5
practice_5_EXTERNAL_OBJECTS =

practice_5: CMakeFiles/practice_5.dir/main.cpp.o
practice_5: CMakeFiles/practice_5.dir/DynamicArray.cpp.o
practice_5: CMakeFiles/practice_5.dir/build.make
practice_5: CMakeFiles/practice_5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yasen/Programming/FMI-2017-2018/OOP/practice_5/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable practice_5"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/practice_5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/practice_5.dir/build: practice_5

.PHONY : CMakeFiles/practice_5.dir/build

CMakeFiles/practice_5.dir/requires: CMakeFiles/practice_5.dir/main.cpp.o.requires
CMakeFiles/practice_5.dir/requires: CMakeFiles/practice_5.dir/DynamicArray.cpp.o.requires

.PHONY : CMakeFiles/practice_5.dir/requires

CMakeFiles/practice_5.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/practice_5.dir/cmake_clean.cmake
.PHONY : CMakeFiles/practice_5.dir/clean

CMakeFiles/practice_5.dir/depend:
	cd /home/yasen/Programming/FMI-2017-2018/OOP/practice_5/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yasen/Programming/FMI-2017-2018/OOP/practice_5 /home/yasen/Programming/FMI-2017-2018/OOP/practice_5 /home/yasen/Programming/FMI-2017-2018/OOP/practice_5/cmake-build-debug /home/yasen/Programming/FMI-2017-2018/OOP/practice_5/cmake-build-debug /home/yasen/Programming/FMI-2017-2018/OOP/practice_5/cmake-build-debug/CMakeFiles/practice_5.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/practice_5.dir/depend

