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
include storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/depend.make

# Include the progress variables for this target.
include storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/progress.make

# Include the compile flags for this target's objects.
include storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/flags.make

storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/test_workqueue.c.o: storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/flags.make
storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/test_workqueue.c.o: storage/ndb/memcache/unit/test_workqueue.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/test_workqueue.c.o"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/unit && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/test_workqueue.dir/test_workqueue.c.o   -c /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/unit/test_workqueue.c

storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/test_workqueue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_workqueue.dir/test_workqueue.c.i"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/unit && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/unit/test_workqueue.c > CMakeFiles/test_workqueue.dir/test_workqueue.c.i

storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/test_workqueue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_workqueue.dir/test_workqueue.c.s"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/unit && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/unit/test_workqueue.c -o CMakeFiles/test_workqueue.dir/test_workqueue.c.s

storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/test_workqueue.c.o.requires:
.PHONY : storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/test_workqueue.c.o.requires

storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/test_workqueue.c.o.provides: storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/test_workqueue.c.o.requires
	$(MAKE) -f storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/build.make storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/test_workqueue.c.o.provides.build
.PHONY : storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/test_workqueue.c.o.provides

storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/test_workqueue.c.o.provides.build: storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/test_workqueue.c.o

storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/__/src/workqueue.c.o: storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/flags.make
storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/__/src/workqueue.c.o: storage/ndb/memcache/src/workqueue.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/__/src/workqueue.c.o"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/unit && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/test_workqueue.dir/__/src/workqueue.c.o   -c /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/src/workqueue.c

storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/__/src/workqueue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_workqueue.dir/__/src/workqueue.c.i"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/unit && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/src/workqueue.c > CMakeFiles/test_workqueue.dir/__/src/workqueue.c.i

storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/__/src/workqueue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_workqueue.dir/__/src/workqueue.c.s"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/unit && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/src/workqueue.c -o CMakeFiles/test_workqueue.dir/__/src/workqueue.c.s

storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/__/src/workqueue.c.o.requires:
.PHONY : storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/__/src/workqueue.c.o.requires

storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/__/src/workqueue.c.o.provides: storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/__/src/workqueue.c.o.requires
	$(MAKE) -f storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/build.make storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/__/src/workqueue.c.o.provides.build
.PHONY : storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/__/src/workqueue.c.o.provides

storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/__/src/workqueue.c.o.provides.build: storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/__/src/workqueue.c.o

# Object files for target test_workqueue
test_workqueue_OBJECTS = \
"CMakeFiles/test_workqueue.dir/test_workqueue.c.o" \
"CMakeFiles/test_workqueue.dir/__/src/workqueue.c.o"

# External object files for target test_workqueue
test_workqueue_EXTERNAL_OBJECTS =

storage/ndb/memcache/unit/test_workqueue: storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/test_workqueue.c.o
storage/ndb/memcache/unit/test_workqueue: storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/__/src/workqueue.c.o
storage/ndb/memcache/unit/test_workqueue: storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/build.make
storage/ndb/memcache/unit/test_workqueue: storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable test_workqueue"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/unit && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_workqueue.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/build: storage/ndb/memcache/unit/test_workqueue
.PHONY : storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/build

storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/requires: storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/test_workqueue.c.o.requires
storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/requires: storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/__/src/workqueue.c.o.requires
.PHONY : storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/requires

storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/unit && $(CMAKE_COMMAND) -P CMakeFiles/test_workqueue.dir/cmake_clean.cmake
.PHONY : storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/clean

storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/depend:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/unit /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/unit /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : storage/ndb/memcache/unit/CMakeFiles/test_workqueue.dir/depend

