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
include examples/CMakeFiles/connection_meta_schemaobj.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/connection_meta_schemaobj.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/connection_meta_schemaobj.dir/flags.make

examples/CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.o: examples/CMakeFiles/connection_meta_schemaobj.dir/flags.make
examples/CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.o: examples/connection_meta_schemaobj.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.o"
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.o -c /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples/connection_meta_schemaobj.cpp

examples/CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.i"
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples/connection_meta_schemaobj.cpp > CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.i

examples/CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.s"
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples/connection_meta_schemaobj.cpp -o CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.s

examples/CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.o.requires:
.PHONY : examples/CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.o.requires

examples/CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.o.provides: examples/CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/connection_meta_schemaobj.dir/build.make examples/CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.o.provides.build
.PHONY : examples/CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.o.provides

examples/CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.o.provides.build: examples/CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.o

# Object files for target connection_meta_schemaobj
connection_meta_schemaobj_OBJECTS = \
"CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.o"

# External object files for target connection_meta_schemaobj
connection_meta_schemaobj_EXTERNAL_OBJECTS =

examples/connection_meta_schemaobj: examples/CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.o
examples/connection_meta_schemaobj: examples/CMakeFiles/connection_meta_schemaobj.dir/build.make
examples/connection_meta_schemaobj: driver/libmysqlcppconn-static.a
examples/connection_meta_schemaobj: examples/CMakeFiles/connection_meta_schemaobj.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable connection_meta_schemaobj"
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/connection_meta_schemaobj.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/connection_meta_schemaobj.dir/build: examples/connection_meta_schemaobj
.PHONY : examples/CMakeFiles/connection_meta_schemaobj.dir/build

examples/CMakeFiles/connection_meta_schemaobj.dir/requires: examples/CMakeFiles/connection_meta_schemaobj.dir/connection_meta_schemaobj.cpp.o.requires
.PHONY : examples/CMakeFiles/connection_meta_schemaobj.dir/requires

examples/CMakeFiles/connection_meta_schemaobj.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples && $(CMAKE_COMMAND) -P CMakeFiles/connection_meta_schemaobj.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/connection_meta_schemaobj.dir/clean

examples/CMakeFiles/connection_meta_schemaobj.dir/depend:
	cd /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0 /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0 /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples /opt/checkout/eAccelero/3rdparty/mysql-connector-c++-1.1.0/examples/CMakeFiles/connection_meta_schemaobj.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/connection_meta_schemaobj.dir/depend
