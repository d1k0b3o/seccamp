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
include test/CMakeFiles/trlwemain.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/trlwemain.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/trlwemain.dir/flags.make

test/CMakeFiles/trlwemain.dir/trlwemain.cpp.o: test/CMakeFiles/trlwemain.dir/flags.make
test/CMakeFiles/trlwemain.dir/trlwemain.cpp.o: ../test/trlwemain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hagarikuo/seccamp/TFHE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/trlwemain.dir/trlwemain.cpp.o"
	cd /home/hagarikuo/seccamp/TFHE/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/trlwemain.dir/trlwemain.cpp.o -c /home/hagarikuo/seccamp/TFHE/test/trlwemain.cpp

test/CMakeFiles/trlwemain.dir/trlwemain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/trlwemain.dir/trlwemain.cpp.i"
	cd /home/hagarikuo/seccamp/TFHE/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hagarikuo/seccamp/TFHE/test/trlwemain.cpp > CMakeFiles/trlwemain.dir/trlwemain.cpp.i

test/CMakeFiles/trlwemain.dir/trlwemain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/trlwemain.dir/trlwemain.cpp.s"
	cd /home/hagarikuo/seccamp/TFHE/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hagarikuo/seccamp/TFHE/test/trlwemain.cpp -o CMakeFiles/trlwemain.dir/trlwemain.cpp.s

test/CMakeFiles/trlwemain.dir/trlwemain.cpp.o.requires:

.PHONY : test/CMakeFiles/trlwemain.dir/trlwemain.cpp.o.requires

test/CMakeFiles/trlwemain.dir/trlwemain.cpp.o.provides: test/CMakeFiles/trlwemain.dir/trlwemain.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/trlwemain.dir/build.make test/CMakeFiles/trlwemain.dir/trlwemain.cpp.o.provides.build
.PHONY : test/CMakeFiles/trlwemain.dir/trlwemain.cpp.o.provides

test/CMakeFiles/trlwemain.dir/trlwemain.cpp.o.provides.build: test/CMakeFiles/trlwemain.dir/trlwemain.cpp.o


# Object files for target trlwemain
trlwemain_OBJECTS = \
"CMakeFiles/trlwemain.dir/trlwemain.cpp.o"

# External object files for target trlwemain
trlwemain_EXTERNAL_OBJECTS =

test/trlwemain: test/CMakeFiles/trlwemain.dir/trlwemain.cpp.o
test/trlwemain: test/CMakeFiles/trlwemain.dir/build.make
test/trlwemain: src/libTFHE.a
test/trlwemain: RANDEN/libRANDEN.a
test/trlwemain: test/CMakeFiles/trlwemain.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hagarikuo/seccamp/TFHE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable trlwemain"
	cd /home/hagarikuo/seccamp/TFHE/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/trlwemain.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/trlwemain.dir/build: test/trlwemain

.PHONY : test/CMakeFiles/trlwemain.dir/build

test/CMakeFiles/trlwemain.dir/requires: test/CMakeFiles/trlwemain.dir/trlwemain.cpp.o.requires

.PHONY : test/CMakeFiles/trlwemain.dir/requires

test/CMakeFiles/trlwemain.dir/clean:
	cd /home/hagarikuo/seccamp/TFHE/build/test && $(CMAKE_COMMAND) -P CMakeFiles/trlwemain.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/trlwemain.dir/clean

test/CMakeFiles/trlwemain.dir/depend:
	cd /home/hagarikuo/seccamp/TFHE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hagarikuo/seccamp/TFHE /home/hagarikuo/seccamp/TFHE/test /home/hagarikuo/seccamp/TFHE/build /home/hagarikuo/seccamp/TFHE/build/test /home/hagarikuo/seccamp/TFHE/build/test/CMakeFiles/trlwemain.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/trlwemain.dir/depend

