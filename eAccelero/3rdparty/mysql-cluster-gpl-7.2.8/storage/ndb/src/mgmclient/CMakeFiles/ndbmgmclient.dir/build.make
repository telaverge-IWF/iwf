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
include storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/depend.make

# Include the progress variables for this target.
include storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/progress.make

# Include the compile flags for this target's objects.
include storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/flags.make

storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.o: storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/flags.make
storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.o: storage/ndb/src/mgmclient/CommandInterpreter.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.o"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmclient && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.o -c /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmclient/CommandInterpreter.cpp

storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.i"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmclient && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmclient/CommandInterpreter.cpp > CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.i

storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.s"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmclient && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmclient/CommandInterpreter.cpp -o CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.s

storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.o.requires:
.PHONY : storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.o.requires

storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.o.provides: storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.o.requires
	$(MAKE) -f storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/build.make storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.o.provides.build
.PHONY : storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.o.provides

storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.o.provides.build: storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.o

# Object files for target ndbmgmclient
ndbmgmclient_OBJECTS = \
"CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.o"

# External object files for target ndbmgmclient
ndbmgmclient_EXTERNAL_OBJECTS =

storage/ndb/src/mgmclient/libndbmgmclient.a: storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.o
storage/ndb/src/mgmclient/libndbmgmclient.a: storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/build.make
storage/ndb/src/mgmclient/libndbmgmclient.a: storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libndbmgmclient.a"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmclient && $(CMAKE_COMMAND) -P CMakeFiles/ndbmgmclient.dir/cmake_clean_target.cmake
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmclient && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ndbmgmclient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/build: storage/ndb/src/mgmclient/libndbmgmclient.a
.PHONY : storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/build

storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/requires: storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/CommandInterpreter.cpp.o.requires
.PHONY : storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/requires

storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmclient && $(CMAKE_COMMAND) -P CMakeFiles/ndbmgmclient.dir/cmake_clean.cmake
.PHONY : storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/clean

storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/depend:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmclient /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmclient /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : storage/ndb/src/mgmclient/CMakeFiles/ndbmgmclient.dir/depend

