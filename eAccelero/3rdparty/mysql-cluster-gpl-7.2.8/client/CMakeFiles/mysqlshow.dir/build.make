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
include client/CMakeFiles/mysqlshow.dir/depend.make

# Include the progress variables for this target.
include client/CMakeFiles/mysqlshow.dir/progress.make

# Include the compile flags for this target's objects.
include client/CMakeFiles/mysqlshow.dir/flags.make

client/CMakeFiles/mysqlshow.dir/mysqlshow.c.o: client/CMakeFiles/mysqlshow.dir/flags.make
client/CMakeFiles/mysqlshow.dir/mysqlshow.c.o: client/mysqlshow.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object client/CMakeFiles/mysqlshow.dir/mysqlshow.c.o"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/client && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/mysqlshow.dir/mysqlshow.c.o   -c /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/client/mysqlshow.c

client/CMakeFiles/mysqlshow.dir/mysqlshow.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mysqlshow.dir/mysqlshow.c.i"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/client && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/client/mysqlshow.c > CMakeFiles/mysqlshow.dir/mysqlshow.c.i

client/CMakeFiles/mysqlshow.dir/mysqlshow.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mysqlshow.dir/mysqlshow.c.s"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/client && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/client/mysqlshow.c -o CMakeFiles/mysqlshow.dir/mysqlshow.c.s

client/CMakeFiles/mysqlshow.dir/mysqlshow.c.o.requires:
.PHONY : client/CMakeFiles/mysqlshow.dir/mysqlshow.c.o.requires

client/CMakeFiles/mysqlshow.dir/mysqlshow.c.o.provides: client/CMakeFiles/mysqlshow.dir/mysqlshow.c.o.requires
	$(MAKE) -f client/CMakeFiles/mysqlshow.dir/build.make client/CMakeFiles/mysqlshow.dir/mysqlshow.c.o.provides.build
.PHONY : client/CMakeFiles/mysqlshow.dir/mysqlshow.c.o.provides

client/CMakeFiles/mysqlshow.dir/mysqlshow.c.o.provides.build: client/CMakeFiles/mysqlshow.dir/mysqlshow.c.o

# Object files for target mysqlshow
mysqlshow_OBJECTS = \
"CMakeFiles/mysqlshow.dir/mysqlshow.c.o"

# External object files for target mysqlshow
mysqlshow_EXTERNAL_OBJECTS =

client/mysqlshow: client/CMakeFiles/mysqlshow.dir/mysqlshow.c.o
client/mysqlshow: client/CMakeFiles/mysqlshow.dir/build.make
client/mysqlshow: libmysql/libmysqlclient.a
client/mysqlshow: probes_mysql.o
client/mysqlshow: client/CMakeFiles/mysqlshow.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable mysqlshow"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mysqlshow.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
client/CMakeFiles/mysqlshow.dir/build: client/mysqlshow
.PHONY : client/CMakeFiles/mysqlshow.dir/build

client/CMakeFiles/mysqlshow.dir/requires: client/CMakeFiles/mysqlshow.dir/mysqlshow.c.o.requires
.PHONY : client/CMakeFiles/mysqlshow.dir/requires

client/CMakeFiles/mysqlshow.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/client && $(CMAKE_COMMAND) -P CMakeFiles/mysqlshow.dir/cmake_clean.cmake
.PHONY : client/CMakeFiles/mysqlshow.dir/clean

client/CMakeFiles/mysqlshow.dir/depend:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/client /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/client /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/client/CMakeFiles/mysqlshow.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : client/CMakeFiles/mysqlshow.dir/depend
