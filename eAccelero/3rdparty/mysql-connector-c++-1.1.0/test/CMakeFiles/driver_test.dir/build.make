# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0

# Include any dependencies generated for this target.
include test/CMakeFiles/driver_test.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/driver_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/driver_test.dir/flags.make

test/CMakeFiles/driver_test.dir/driver_test.cpp.o: test/CMakeFiles/driver_test.dir/flags.make
test/CMakeFiles/driver_test.dir/driver_test.cpp.o: test/driver_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/driver_test.dir/driver_test.cpp.o"
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/driver_test.dir/driver_test.cpp.o -c /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/test/driver_test.cpp

test/CMakeFiles/driver_test.dir/driver_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/driver_test.dir/driver_test.cpp.i"
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/test/driver_test.cpp > CMakeFiles/driver_test.dir/driver_test.cpp.i

test/CMakeFiles/driver_test.dir/driver_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/driver_test.dir/driver_test.cpp.s"
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/test/driver_test.cpp -o CMakeFiles/driver_test.dir/driver_test.cpp.s

test/CMakeFiles/driver_test.dir/driver_test.cpp.o.requires:
.PHONY : test/CMakeFiles/driver_test.dir/driver_test.cpp.o.requires

test/CMakeFiles/driver_test.dir/driver_test.cpp.o.provides: test/CMakeFiles/driver_test.dir/driver_test.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/driver_test.dir/build.make test/CMakeFiles/driver_test.dir/driver_test.cpp.o.provides.build
.PHONY : test/CMakeFiles/driver_test.dir/driver_test.cpp.o.provides

test/CMakeFiles/driver_test.dir/driver_test.cpp.o.provides.build: test/CMakeFiles/driver_test.dir/driver_test.cpp.o

# Object files for target driver_test
driver_test_OBJECTS = \
"CMakeFiles/driver_test.dir/driver_test.cpp.o"

# External object files for target driver_test
driver_test_EXTERNAL_OBJECTS =

test/driver_test: test/CMakeFiles/driver_test.dir/driver_test.cpp.o
test/driver_test: test/CMakeFiles/driver_test.dir/build.make
test/driver_test: driver/libmysqlcppconn.so.5.1.1.0
test/driver_test: test/CMakeFiles/driver_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable driver_test"
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/driver_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/driver_test.dir/build: test/driver_test
.PHONY : test/CMakeFiles/driver_test.dir/build

test/CMakeFiles/driver_test.dir/requires: test/CMakeFiles/driver_test.dir/driver_test.cpp.o.requires
.PHONY : test/CMakeFiles/driver_test.dir/requires

test/CMakeFiles/driver_test.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/test && $(CMAKE_COMMAND) -P CMakeFiles/driver_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/driver_test.dir/clean

test/CMakeFiles/driver_test.dir/depend:
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0 /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/test /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0 /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/test /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/test/CMakeFiles/driver_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/driver_test.dir/depend

