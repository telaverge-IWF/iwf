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
include examples/CMakeFiles/statement.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/statement.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/statement.dir/flags.make

examples/CMakeFiles/statement.dir/statement.cpp.o: examples/CMakeFiles/statement.dir/flags.make
examples/CMakeFiles/statement.dir/statement.cpp.o: examples/statement.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/CMakeFiles/statement.dir/statement.cpp.o"
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/statement.dir/statement.cpp.o -c /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples/statement.cpp

examples/CMakeFiles/statement.dir/statement.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/statement.dir/statement.cpp.i"
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples/statement.cpp > CMakeFiles/statement.dir/statement.cpp.i

examples/CMakeFiles/statement.dir/statement.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/statement.dir/statement.cpp.s"
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples/statement.cpp -o CMakeFiles/statement.dir/statement.cpp.s

examples/CMakeFiles/statement.dir/statement.cpp.o.requires:
.PHONY : examples/CMakeFiles/statement.dir/statement.cpp.o.requires

examples/CMakeFiles/statement.dir/statement.cpp.o.provides: examples/CMakeFiles/statement.dir/statement.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/statement.dir/build.make examples/CMakeFiles/statement.dir/statement.cpp.o.provides.build
.PHONY : examples/CMakeFiles/statement.dir/statement.cpp.o.provides

examples/CMakeFiles/statement.dir/statement.cpp.o.provides.build: examples/CMakeFiles/statement.dir/statement.cpp.o

# Object files for target statement
statement_OBJECTS = \
"CMakeFiles/statement.dir/statement.cpp.o"

# External object files for target statement
statement_EXTERNAL_OBJECTS =

examples/statement: examples/CMakeFiles/statement.dir/statement.cpp.o
examples/statement: examples/CMakeFiles/statement.dir/build.make
examples/statement: driver/libmysqlcppconn-static.a
examples/statement: examples/CMakeFiles/statement.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable statement"
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/statement.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/statement.dir/build: examples/statement
.PHONY : examples/CMakeFiles/statement.dir/build

examples/CMakeFiles/statement.dir/requires: examples/CMakeFiles/statement.dir/statement.cpp.o.requires
.PHONY : examples/CMakeFiles/statement.dir/requires

examples/CMakeFiles/statement.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples && $(CMAKE_COMMAND) -P CMakeFiles/statement.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/statement.dir/clean

examples/CMakeFiles/statement.dir/depend:
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0 /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0 /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples/CMakeFiles/statement.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/statement.dir/depend

