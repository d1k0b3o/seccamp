# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/hagarikuo/seccamp/TFHE

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hagarikuo/seccamp/TFHE/build

# Include any dependencies generated for this target.
include test/CMakeFiles/tlwemain.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/tlwemain.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/tlwemain.dir/flags.make

test/CMakeFiles/tlwemain.dir/tlwemain.cpp.o: test/CMakeFiles/tlwemain.dir/flags.make
test/CMakeFiles/tlwemain.dir/tlwemain.cpp.o: ../test/tlwemain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hagarikuo/seccamp/TFHE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/tlwemain.dir/tlwemain.cpp.o"
	cd /home/hagarikuo/seccamp/TFHE/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tlwemain.dir/tlwemain.cpp.o -c /home/hagarikuo/seccamp/TFHE/test/tlwemain.cpp

test/CMakeFiles/tlwemain.dir/tlwemain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tlwemain.dir/tlwemain.cpp.i"
	cd /home/hagarikuo/seccamp/TFHE/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hagarikuo/seccamp/TFHE/test/tlwemain.cpp > CMakeFiles/tlwemain.dir/tlwemain.cpp.i

test/CMakeFiles/tlwemain.dir/tlwemain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tlwemain.dir/tlwemain.cpp.s"
	cd /home/hagarikuo/seccamp/TFHE/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hagarikuo/seccamp/TFHE/test/tlwemain.cpp -o CMakeFiles/tlwemain.dir/tlwemain.cpp.s

test/CMakeFiles/tlwemain.dir/tlwemain.cpp.o.requires:

.PHONY : test/CMakeFiles/tlwemain.dir/tlwemain.cpp.o.requires

test/CMakeFiles/tlwemain.dir/tlwemain.cpp.o.provides: test/CMakeFiles/tlwemain.dir/tlwemain.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/tlwemain.dir/build.make test/CMakeFiles/tlwemain.dir/tlwemain.cpp.o.provides.build
.PHONY : test/CMakeFiles/tlwemain.dir/tlwemain.cpp.o.provides

test/CMakeFiles/tlwemain.dir/tlwemain.cpp.o.provides.build: test/CMakeFiles/tlwemain.dir/tlwemain.cpp.o


# Object files for target tlwemain
tlwemain_OBJECTS = \
"CMakeFiles/tlwemain.dir/tlwemain.cpp.o"

# External object files for target tlwemain
tlwemain_EXTERNAL_OBJECTS =

test/tlwemain: test/CMakeFiles/tlwemain.dir/tlwemain.cpp.o
test/tlwemain: test/CMakeFiles/tlwemain.dir/build.make
test/tlwemain: src/libTFHE.a
test/tlwemain: RANDEN/libRANDEN.a
test/tlwemain: test/CMakeFiles/tlwemain.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hagarikuo/seccamp/TFHE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tlwemain"
	cd /home/hagarikuo/seccamp/TFHE/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tlwemain.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/tlwemain.dir/build: test/tlwemain

.PHONY : test/CMakeFiles/tlwemain.dir/build

test/CMakeFiles/tlwemain.dir/requires: test/CMakeFiles/tlwemain.dir/tlwemain.cpp.o.requires

.PHONY : test/CMakeFiles/tlwemain.dir/requires

test/CMakeFiles/tlwemain.dir/clean:
	cd /home/hagarikuo/seccamp/TFHE/build/test && $(CMAKE_COMMAND) -P CMakeFiles/tlwemain.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/tlwemain.dir/clean

test/CMakeFiles/tlwemain.dir/depend:
	cd /home/hagarikuo/seccamp/TFHE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hagarikuo/seccamp/TFHE /home/hagarikuo/seccamp/TFHE/test /home/hagarikuo/seccamp/TFHE/build /home/hagarikuo/seccamp/TFHE/build/test /home/hagarikuo/seccamp/TFHE/build/test/CMakeFiles/tlwemain.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/tlwemain.dir/depend

