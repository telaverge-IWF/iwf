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
include extra/CMakeFiles/mysql_waitpid.dir/depend.make

# Include the progress variables for this target.
include extra/CMakeFiles/mysql_waitpid.dir/progress.make

# Include the compile flags for this target's objects.
include extra/CMakeFiles/mysql_waitpid.dir/flags.make

extra/CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.o: extra/CMakeFiles/mysql_waitpid.dir/flags.make
extra/CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.o: extra/mysql_waitpid.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object extra/CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.o"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/extra && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.o   -c /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/extra/mysql_waitpid.c

extra/CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.i"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/extra && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/extra/mysql_waitpid.c > CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.i

extra/CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.s"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/extra && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/extra/mysql_waitpid.c -o CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.s

extra/CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.o.requires:
.PHONY : extra/CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.o.requires

extra/CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.o.provides: extra/CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.o.requires
	$(MAKE) -f extra/CMakeFiles/mysql_waitpid.dir/build.make extra/CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.o.provides.build
.PHONY : extra/CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.o.provides

extra/CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.o.provides.build: extra/CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.o

# Object files for target mysql_waitpid
mysql_waitpid_OBJECTS = \
"CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.o"

# External object files for target mysql_waitpid
mysql_waitpid_EXTERNAL_OBJECTS =

extra/mysql_waitpid: extra/CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.o
extra/mysql_waitpid: extra/CMakeFiles/mysql_waitpid.dir/build.make
extra/mysql_waitpid: mysys/libmysys.a
extra/mysql_waitpid: dbug/libdbug.a
extra/mysql_waitpid: mysys/libmysys.a
extra/mysql_waitpid: dbug/libdbug.a
extra/mysql_waitpid: strings/libstrings.a
extra/mysql_waitpid: probes_mysql.o
extra/mysql_waitpid: extra/CMakeFiles/mysql_waitpid.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable mysql_waitpid"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/extra && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mysql_waitpid.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extra/CMakeFiles/mysql_waitpid.dir/build: extra/mysql_waitpid
.PHONY : extra/CMakeFiles/mysql_waitpid.dir/build

extra/CMakeFiles/mysql_waitpid.dir/requires: extra/CMakeFiles/mysql_waitpid.dir/mysql_waitpid.c.o.requires
.PHONY : extra/CMakeFiles/mysql_waitpid.dir/requires

extra/CMakeFiles/mysql_waitpid.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/extra && $(CMAKE_COMMAND) -P CMakeFiles/mysql_waitpid.dir/cmake_clean.cmake
.PHONY : extra/CMakeFiles/mysql_waitpid.dir/clean

extra/CMakeFiles/mysql_waitpid.dir/depend:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/extra /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/extra /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/extra/CMakeFiles/mysql_waitpid.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extra/CMakeFiles/mysql_waitpid.dir/depend

