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
include storage/ndb/src/CMakeFiles/ndbclient_static.dir/depend.make

# Include the progress variables for this target.
include storage/ndb/src/CMakeFiles/ndbclient_static.dir/progress.make

# Include the compile flags for this target's objects.
include storage/ndb/src/CMakeFiles/ndbclient_static.dir/flags.make

storage/ndb/src/ndbclient_static_depends.c: storage/ndb/src/ndbapi/libndbapi.a
storage/ndb/src/ndbclient_static_depends.c: storage/ndb/src/common/transporter/libndbtransport.a
storage/ndb/src/ndbclient_static_depends.c: storage/ndb/src/common/debugger/libndbtrace.a
storage/ndb/src/ndbclient_static_depends.c: storage/ndb/src/common/debugger/signaldata/libndbsignaldata.a
storage/ndb/src/ndbclient_static_depends.c: storage/ndb/src/mgmapi/libndbmgmapi.a
storage/ndb/src/ndbclient_static_depends.c: storage/ndb/src/common/mgmcommon/libndbmgmcommon.a
storage/ndb/src/ndbclient_static_depends.c: storage/ndb/src/common/logger/libndblogger.a
storage/ndb/src/ndbclient_static_depends.c: storage/ndb/src/common/portlib/libndbportlib.a
storage/ndb/src/ndbclient_static_depends.c: storage/ndb/src/common/util/libndbgeneral.a
storage/ndb/src/ndbclient_static_depends.c: storage/ndb/src/mgmsrv/libndbconf.a
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ndbclient_static_depends.c"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src && /usr/bin/cmake -E touch /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/ndbclient_static_depends.c

storage/ndb/src/CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.o: storage/ndb/src/CMakeFiles/ndbclient_static.dir/flags.make
storage/ndb/src/CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.o: storage/ndb/src/ndbclient_static_depends.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object storage/ndb/src/CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.o"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.o   -c /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/ndbclient_static_depends.c

storage/ndb/src/CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.i"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/ndbclient_static_depends.c > CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.i

storage/ndb/src/CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.s"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/ndbclient_static_depends.c -o CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.s

storage/ndb/src/CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.o.requires:
.PHONY : storage/ndb/src/CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.o.requires

storage/ndb/src/CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.o.provides: storage/ndb/src/CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.o.requires
	$(MAKE) -f storage/ndb/src/CMakeFiles/ndbclient_static.dir/build.make storage/ndb/src/CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.o.provides.build
.PHONY : storage/ndb/src/CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.o.provides

storage/ndb/src/CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.o.provides.build: storage/ndb/src/CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.o

# Object files for target ndbclient_static
ndbclient_static_OBJECTS = \
"CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.o"

# External object files for target ndbclient_static
ndbclient_static_EXTERNAL_OBJECTS =

storage/ndb/src/libndbclient_static.a: storage/ndb/src/CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.o
storage/ndb/src/libndbclient_static.a: storage/ndb/src/CMakeFiles/ndbclient_static.dir/build.make
storage/ndb/src/libndbclient_static.a: storage/ndb/src/CMakeFiles/ndbclient_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libndbclient_static.a"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src && $(CMAKE_COMMAND) -P CMakeFiles/ndbclient_static.dir/cmake_clean_target.cmake
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ndbclient_static.dir/link.txt --verbose=$(VERBOSE)
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src && rm /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/libndbclient_static.a
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src && /usr/bin/cmake -P /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/merge_archives_ndbclient_static.cmake

# Rule to build all files generated by this target.
storage/ndb/src/CMakeFiles/ndbclient_static.dir/build: storage/ndb/src/libndbclient_static.a
.PHONY : storage/ndb/src/CMakeFiles/ndbclient_static.dir/build

storage/ndb/src/CMakeFiles/ndbclient_static.dir/requires: storage/ndb/src/CMakeFiles/ndbclient_static.dir/ndbclient_static_depends.c.o.requires
.PHONY : storage/ndb/src/CMakeFiles/ndbclient_static.dir/requires

storage/ndb/src/CMakeFiles/ndbclient_static.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src && $(CMAKE_COMMAND) -P CMakeFiles/ndbclient_static.dir/cmake_clean.cmake
.PHONY : storage/ndb/src/CMakeFiles/ndbclient_static.dir/clean

storage/ndb/src/CMakeFiles/ndbclient_static.dir/depend: storage/ndb/src/ndbclient_static_depends.c
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/CMakeFiles/ndbclient_static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : storage/ndb/src/CMakeFiles/ndbclient_static.dir/depend

