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
CMAKE_SOURCE_DIR = /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8

# Include any dependencies generated for this target.
include sql/CMakeFiles/udf_example.dir/depend.make

# Include the progress variables for this target.
include sql/CMakeFiles/udf_example.dir/progress.make

# Include the compile flags for this target's objects.
include sql/CMakeFiles/udf_example.dir/flags.make

sql/CMakeFiles/udf_example.dir/udf_example.c.o: sql/CMakeFiles/udf_example.dir/flags.make
sql/CMakeFiles/udf_example.dir/udf_example.c.o: sql/udf_example.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object sql/CMakeFiles/udf_example.dir/udf_example.c.o"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/sql && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/udf_example.dir/udf_example.c.o   -c /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/sql/udf_example.c

sql/CMakeFiles/udf_example.dir/udf_example.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/udf_example.dir/udf_example.c.i"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/sql && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/sql/udf_example.c > CMakeFiles/udf_example.dir/udf_example.c.i

sql/CMakeFiles/udf_example.dir/udf_example.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/udf_example.dir/udf_example.c.s"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/sql && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/sql/udf_example.c -o CMakeFiles/udf_example.dir/udf_example.c.s

sql/CMakeFiles/udf_example.dir/udf_example.c.o.requires:
.PHONY : sql/CMakeFiles/udf_example.dir/udf_example.c.o.requires

sql/CMakeFiles/udf_example.dir/udf_example.c.o.provides: sql/CMakeFiles/udf_example.dir/udf_example.c.o.requires
	$(MAKE) -f sql/CMakeFiles/udf_example.dir/build.make sql/CMakeFiles/udf_example.dir/udf_example.c.o.provides.build
.PHONY : sql/CMakeFiles/udf_example.dir/udf_example.c.o.provides

sql/CMakeFiles/udf_example.dir/udf_example.c.o.provides.build: sql/CMakeFiles/udf_example.dir/udf_example.c.o

# Object files for target udf_example
udf_example_OBJECTS = \
"CMakeFiles/udf_example.dir/udf_example.c.o"

# External object files for target udf_example
udf_example_EXTERNAL_OBJECTS =

sql/udf_example.so: sql/CMakeFiles/udf_example.dir/udf_example.c.o
sql/udf_example.so: sql/CMakeFiles/udf_example.dir/build.make
sql/udf_example.so: sql/CMakeFiles/udf_example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared module udf_example.so"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/sql && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/udf_example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sql/CMakeFiles/udf_example.dir/build: sql/udf_example.so
.PHONY : sql/CMakeFiles/udf_example.dir/build

sql/CMakeFiles/udf_example.dir/requires: sql/CMakeFiles/udf_example.dir/udf_example.c.o.requires
.PHONY : sql/CMakeFiles/udf_example.dir/requires

sql/CMakeFiles/udf_example.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/sql && $(CMAKE_COMMAND) -P CMakeFiles/udf_example.dir/cmake_clean.cmake
.PHONY : sql/CMakeFiles/udf_example.dir/clean

sql/CMakeFiles/udf_example.dir/depend:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/sql /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/sql /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/sql/CMakeFiles/udf_example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sql/CMakeFiles/udf_example.dir/depend
