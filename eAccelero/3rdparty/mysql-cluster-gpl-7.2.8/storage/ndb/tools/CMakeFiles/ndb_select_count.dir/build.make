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
include storage/ndb/tools/CMakeFiles/ndb_select_count.dir/depend.make

# Include the progress variables for this target.
include storage/ndb/tools/CMakeFiles/ndb_select_count.dir/progress.make

# Include the compile flags for this target's objects.
include storage/ndb/tools/CMakeFiles/ndb_select_count.dir/flags.make

storage/ndb/tools/CMakeFiles/ndb_select_count.dir/select_count.cpp.o: storage/ndb/tools/CMakeFiles/ndb_select_count.dir/flags.make
storage/ndb/tools/CMakeFiles/ndb_select_count.dir/select_count.cpp.o: storage/ndb/tools/select_count.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object storage/ndb/tools/CMakeFiles/ndb_select_count.dir/select_count.cpp.o"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/tools && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ndb_select_count.dir/select_count.cpp.o -c /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/tools/select_count.cpp

storage/ndb/tools/CMakeFiles/ndb_select_count.dir/select_count.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndb_select_count.dir/select_count.cpp.i"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/tools && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/tools/select_count.cpp > CMakeFiles/ndb_select_count.dir/select_count.cpp.i

storage/ndb/tools/CMakeFiles/ndb_select_count.dir/select_count.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndb_select_count.dir/select_count.cpp.s"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/tools && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/tools/select_count.cpp -o CMakeFiles/ndb_select_count.dir/select_count.cpp.s

storage/ndb/tools/CMakeFiles/ndb_select_count.dir/select_count.cpp.o.requires:
.PHONY : storage/ndb/tools/CMakeFiles/ndb_select_count.dir/select_count.cpp.o.requires

storage/ndb/tools/CMakeFiles/ndb_select_count.dir/select_count.cpp.o.provides: storage/ndb/tools/CMakeFiles/ndb_select_count.dir/select_count.cpp.o.requires
	$(MAKE) -f storage/ndb/tools/CMakeFiles/ndb_select_count.dir/build.make storage/ndb/tools/CMakeFiles/ndb_select_count.dir/select_count.cpp.o.provides.build
.PHONY : storage/ndb/tools/CMakeFiles/ndb_select_count.dir/select_count.cpp.o.provides

storage/ndb/tools/CMakeFiles/ndb_select_count.dir/select_count.cpp.o.provides.build: storage/ndb/tools/CMakeFiles/ndb_select_count.dir/select_count.cpp.o

# Object files for target ndb_select_count
ndb_select_count_OBJECTS = \
"CMakeFiles/ndb_select_count.dir/select_count.cpp.o"

# External object files for target ndb_select_count
ndb_select_count_EXTERNAL_OBJECTS =

storage/ndb/tools/ndb_select_count: storage/ndb/tools/CMakeFiles/ndb_select_count.dir/select_count.cpp.o
storage/ndb/tools/ndb_select_count: storage/ndb/tools/CMakeFiles/ndb_select_count.dir/build.make
storage/ndb/tools/ndb_select_count: storage/ndb/src/libndbclient_static.a
storage/ndb/tools/ndb_select_count: storage/ndb/test/src/libndbNDBT.a
storage/ndb/tools/ndb_select_count: mysys/libmysys.a
storage/ndb/tools/ndb_select_count: dbug/libdbug.a
storage/ndb/tools/ndb_select_count: mysys/libmysys.a
storage/ndb/tools/ndb_select_count: dbug/libdbug.a
storage/ndb/tools/ndb_select_count: probes_mysql.o
storage/ndb/tools/ndb_select_count: strings/libstrings.a
storage/ndb/tools/ndb_select_count: storage/ndb/tools/CMakeFiles/ndb_select_count.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ndb_select_count"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/tools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ndb_select_count.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
storage/ndb/tools/CMakeFiles/ndb_select_count.dir/build: storage/ndb/tools/ndb_select_count
.PHONY : storage/ndb/tools/CMakeFiles/ndb_select_count.dir/build

storage/ndb/tools/CMakeFiles/ndb_select_count.dir/requires: storage/ndb/tools/CMakeFiles/ndb_select_count.dir/select_count.cpp.o.requires
.PHONY : storage/ndb/tools/CMakeFiles/ndb_select_count.dir/requires

storage/ndb/tools/CMakeFiles/ndb_select_count.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/tools && $(CMAKE_COMMAND) -P CMakeFiles/ndb_select_count.dir/cmake_clean.cmake
.PHONY : storage/ndb/tools/CMakeFiles/ndb_select_count.dir/clean

storage/ndb/tools/CMakeFiles/ndb_select_count.dir/depend:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/tools /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/tools /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/tools/CMakeFiles/ndb_select_count.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : storage/ndb/tools/CMakeFiles/ndb_select_count.dir/depend

