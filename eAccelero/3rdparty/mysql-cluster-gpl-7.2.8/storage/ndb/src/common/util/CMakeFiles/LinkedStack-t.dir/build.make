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
include storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/depend.make

# Include the progress variables for this target.
include storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/progress.make

# Include the compile flags for this target's objects.
include storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/flags.make

storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.o: storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/flags.make
storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.o: storage/ndb/src/common/util/LinkedStack.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.o"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/common/util && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.o -c /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/common/util/LinkedStack.cpp

storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.i"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/common/util && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/common/util/LinkedStack.cpp > CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.i

storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.s"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/common/util && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/common/util/LinkedStack.cpp -o CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.s

storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.o.requires:
.PHONY : storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.o.requires

storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.o.provides: storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.o.requires
	$(MAKE) -f storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/build.make storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.o.provides.build
.PHONY : storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.o.provides

storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.o.provides.build: storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.o

# Object files for target LinkedStack-t
LinkedStack__t_OBJECTS = \
"CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.o"

# External object files for target LinkedStack-t
LinkedStack__t_EXTERNAL_OBJECTS =

storage/ndb/src/common/util/LinkedStack-t: storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.o
storage/ndb/src/common/util/LinkedStack-t: storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/build.make
storage/ndb/src/common/util/LinkedStack-t: storage/ndb/src/common/util/libndbgeneral.a
storage/ndb/src/common/util/LinkedStack-t: storage/ndb/src/common/debugger/libndbtrace.a
storage/ndb/src/common/util/LinkedStack-t: storage/ndb/src/common/logger/libndblogger.a
storage/ndb/src/common/util/LinkedStack-t: storage/ndb/src/common/util/libndbgeneral.a
storage/ndb/src/common/util/LinkedStack-t: storage/ndb/src/common/debugger/libndbtrace.a
storage/ndb/src/common/util/LinkedStack-t: storage/ndb/src/common/logger/libndblogger.a
storage/ndb/src/common/util/LinkedStack-t: mysys/libmysys.a
storage/ndb/src/common/util/LinkedStack-t: dbug/libdbug.a
storage/ndb/src/common/util/LinkedStack-t: mysys/libmysys.a
storage/ndb/src/common/util/LinkedStack-t: dbug/libdbug.a
storage/ndb/src/common/util/LinkedStack-t: strings/libstrings.a
storage/ndb/src/common/util/LinkedStack-t: probes_mysql.o
storage/ndb/src/common/util/LinkedStack-t: storage/ndb/src/common/debugger/signaldata/libndbsignaldata.a
storage/ndb/src/common/util/LinkedStack-t: storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable LinkedStack-t"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/common/util && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LinkedStack-t.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/build: storage/ndb/src/common/util/LinkedStack-t
.PHONY : storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/build

storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/requires: storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/LinkedStack.cpp.o.requires
.PHONY : storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/requires

storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/common/util && $(CMAKE_COMMAND) -P CMakeFiles/LinkedStack-t.dir/cmake_clean.cmake
.PHONY : storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/clean

storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/depend:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/common/util /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/common/util /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : storage/ndb/src/common/util/CMakeFiles/LinkedStack-t.dir/depend

