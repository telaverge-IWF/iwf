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
include storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/depend.make

# Include the progress variables for this target.
include storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/progress.make

# Include the compile flags for this target's objects.
include storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/flags.make

storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/CountingPool.cpp.o: storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/flags.make
storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/CountingPool.cpp.o: storage/ndb/src/kernel/vm/CountingPool.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/CountingPool.cpp.o"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/vm && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/CountingPool-t.dir/CountingPool.cpp.o -c /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/vm/CountingPool.cpp

storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/CountingPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CountingPool-t.dir/CountingPool.cpp.i"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/vm && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/vm/CountingPool.cpp > CMakeFiles/CountingPool-t.dir/CountingPool.cpp.i

storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/CountingPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CountingPool-t.dir/CountingPool.cpp.s"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/vm && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/vm/CountingPool.cpp -o CMakeFiles/CountingPool-t.dir/CountingPool.cpp.s

storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/CountingPool.cpp.o.requires:
.PHONY : storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/CountingPool.cpp.o.requires

storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/CountingPool.cpp.o.provides: storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/CountingPool.cpp.o.requires
	$(MAKE) -f storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/build.make storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/CountingPool.cpp.o.provides.build
.PHONY : storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/CountingPool.cpp.o.provides

storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/CountingPool.cpp.o.provides.build: storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/CountingPool.cpp.o

# Object files for target CountingPool-t
CountingPool__t_OBJECTS = \
"CMakeFiles/CountingPool-t.dir/CountingPool.cpp.o"

# External object files for target CountingPool-t
CountingPool__t_EXTERNAL_OBJECTS =

storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/CountingPool.cpp.o
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/build.make
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/kernel/vm/libndbtest.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/kernel/vm/libndbkernel.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/kernel/vm/libndbsched.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/kernel/error/libndberror.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/common/transporter/libndbtransport.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/common/mgmcommon/libndbmgmcommon.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/mgmapi/libndbmgmapi.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/common/portlib/libndbportlib.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/common/util/libndbgeneral.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/mgmsrv/libndbconf.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/mgmapi/libndbmgmapi.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/mgmsrv/libndbconf.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/common/portlib/libndbportlib.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/common/debugger/libndbtrace.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/common/logger/libndblogger.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/common/util/libndbgeneral.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/common/debugger/libndbtrace.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/common/logger/libndblogger.a
storage/ndb/src/kernel/vm/CountingPool-t: mysys/libmysys.a
storage/ndb/src/kernel/vm/CountingPool-t: dbug/libdbug.a
storage/ndb/src/kernel/vm/CountingPool-t: mysys/libmysys.a
storage/ndb/src/kernel/vm/CountingPool-t: dbug/libdbug.a
storage/ndb/src/kernel/vm/CountingPool-t: strings/libstrings.a
storage/ndb/src/kernel/vm/CountingPool-t: probes_mysql.o
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/common/debugger/signaldata/libndbsignaldata.a
storage/ndb/src/kernel/vm/CountingPool-t: storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable CountingPool-t"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/vm && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CountingPool-t.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/build: storage/ndb/src/kernel/vm/CountingPool-t
.PHONY : storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/build

storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/requires: storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/CountingPool.cpp.o.requires
.PHONY : storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/requires

storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/vm && $(CMAKE_COMMAND) -P CMakeFiles/CountingPool-t.dir/cmake_clean.cmake
.PHONY : storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/clean

storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/depend:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/vm /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/vm /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : storage/ndb/src/kernel/vm/CMakeFiles/CountingPool-t.dir/depend
