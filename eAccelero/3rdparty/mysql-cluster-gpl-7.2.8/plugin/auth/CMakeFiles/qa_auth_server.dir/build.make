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
include plugin/auth/CMakeFiles/qa_auth_server.dir/depend.make

# Include the progress variables for this target.
include plugin/auth/CMakeFiles/qa_auth_server.dir/progress.make

# Include the compile flags for this target's objects.
include plugin/auth/CMakeFiles/qa_auth_server.dir/flags.make

plugin/auth/CMakeFiles/qa_auth_server.dir/qa_auth_server.c.o: plugin/auth/CMakeFiles/qa_auth_server.dir/flags.make
plugin/auth/CMakeFiles/qa_auth_server.dir/qa_auth_server.c.o: plugin/auth/qa_auth_server.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object plugin/auth/CMakeFiles/qa_auth_server.dir/qa_auth_server.c.o"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/plugin/auth && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/qa_auth_server.dir/qa_auth_server.c.o   -c /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/plugin/auth/qa_auth_server.c

plugin/auth/CMakeFiles/qa_auth_server.dir/qa_auth_server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qa_auth_server.dir/qa_auth_server.c.i"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/plugin/auth && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/plugin/auth/qa_auth_server.c > CMakeFiles/qa_auth_server.dir/qa_auth_server.c.i

plugin/auth/CMakeFiles/qa_auth_server.dir/qa_auth_server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qa_auth_server.dir/qa_auth_server.c.s"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/plugin/auth && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/plugin/auth/qa_auth_server.c -o CMakeFiles/qa_auth_server.dir/qa_auth_server.c.s

plugin/auth/CMakeFiles/qa_auth_server.dir/qa_auth_server.c.o.requires:
.PHONY : plugin/auth/CMakeFiles/qa_auth_server.dir/qa_auth_server.c.o.requires

plugin/auth/CMakeFiles/qa_auth_server.dir/qa_auth_server.c.o.provides: plugin/auth/CMakeFiles/qa_auth_server.dir/qa_auth_server.c.o.requires
	$(MAKE) -f plugin/auth/CMakeFiles/qa_auth_server.dir/build.make plugin/auth/CMakeFiles/qa_auth_server.dir/qa_auth_server.c.o.provides.build
.PHONY : plugin/auth/CMakeFiles/qa_auth_server.dir/qa_auth_server.c.o.provides

plugin/auth/CMakeFiles/qa_auth_server.dir/qa_auth_server.c.o.provides.build: plugin/auth/CMakeFiles/qa_auth_server.dir/qa_auth_server.c.o

# Object files for target qa_auth_server
qa_auth_server_OBJECTS = \
"CMakeFiles/qa_auth_server.dir/qa_auth_server.c.o"

# External object files for target qa_auth_server
qa_auth_server_EXTERNAL_OBJECTS =

plugin/auth/qa_auth_server.so: plugin/auth/CMakeFiles/qa_auth_server.dir/qa_auth_server.c.o
plugin/auth/qa_auth_server.so: plugin/auth/CMakeFiles/qa_auth_server.dir/build.make
plugin/auth/qa_auth_server.so: probes_mysql.o
plugin/auth/qa_auth_server.so: libservices/libmysqlservices.a
plugin/auth/qa_auth_server.so: plugin/auth/CMakeFiles/qa_auth_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared module qa_auth_server.so"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/plugin/auth && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/qa_auth_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
plugin/auth/CMakeFiles/qa_auth_server.dir/build: plugin/auth/qa_auth_server.so
.PHONY : plugin/auth/CMakeFiles/qa_auth_server.dir/build

plugin/auth/CMakeFiles/qa_auth_server.dir/requires: plugin/auth/CMakeFiles/qa_auth_server.dir/qa_auth_server.c.o.requires
.PHONY : plugin/auth/CMakeFiles/qa_auth_server.dir/requires

plugin/auth/CMakeFiles/qa_auth_server.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/plugin/auth && $(CMAKE_COMMAND) -P CMakeFiles/qa_auth_server.dir/cmake_clean.cmake
.PHONY : plugin/auth/CMakeFiles/qa_auth_server.dir/clean

plugin/auth/CMakeFiles/qa_auth_server.dir/depend:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/plugin/auth /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/plugin/auth /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/plugin/auth/CMakeFiles/qa_auth_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plugin/auth/CMakeFiles/qa_auth_server.dir/depend

