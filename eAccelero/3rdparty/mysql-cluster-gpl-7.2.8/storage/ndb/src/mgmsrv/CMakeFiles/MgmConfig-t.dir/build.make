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
include storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/depend.make

# Include the progress variables for this target.
include storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/progress.make

# Include the compile flags for this target's objects.
include storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/flags.make

storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/testConfig.cpp.o: storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/flags.make
storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/testConfig.cpp.o: storage/ndb/src/mgmsrv/testConfig.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/testConfig.cpp.o"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmsrv && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MgmConfig-t.dir/testConfig.cpp.o -c /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmsrv/testConfig.cpp

storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/testConfig.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MgmConfig-t.dir/testConfig.cpp.i"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmsrv && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmsrv/testConfig.cpp > CMakeFiles/MgmConfig-t.dir/testConfig.cpp.i

storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/testConfig.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MgmConfig-t.dir/testConfig.cpp.s"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmsrv && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmsrv/testConfig.cpp -o CMakeFiles/MgmConfig-t.dir/testConfig.cpp.s

storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/testConfig.cpp.o.requires:
.PHONY : storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/testConfig.cpp.o.requires

storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/testConfig.cpp.o.provides: storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/testConfig.cpp.o.requires
	$(MAKE) -f storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/build.make storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/testConfig.cpp.o.provides.build
.PHONY : storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/testConfig.cpp.o.provides

storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/testConfig.cpp.o.provides.build: storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/testConfig.cpp.o

# Object files for target MgmConfig-t
MgmConfig__t_OBJECTS = \
"CMakeFiles/MgmConfig-t.dir/testConfig.cpp.o"

# External object files for target MgmConfig-t
MgmConfig__t_EXTERNAL_OBJECTS =

storage/ndb/src/mgmsrv/MgmConfig-t: storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/testConfig.cpp.o
storage/ndb/src/mgmsrv/MgmConfig-t: storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/build.make
storage/ndb/src/mgmsrv/MgmConfig-t: storage/ndb/src/mgmapi/libndbmgmapi.a
storage/ndb/src/mgmsrv/MgmConfig-t: storage/ndb/src/common/debugger/libndbtrace.a
storage/ndb/src/mgmsrv/MgmConfig-t: storage/ndb/src/mgmsrv/libndbconf.a
storage/ndb/src/mgmsrv/MgmConfig-t: storage/ndb/src/common/logger/libndblogger.a
storage/ndb/src/mgmsrv/MgmConfig-t: storage/ndb/src/common/util/libndbgeneral.a
storage/ndb/src/mgmsrv/MgmConfig-t: storage/ndb/src/common/portlib/libndbportlib.a
storage/ndb/src/mgmsrv/MgmConfig-t: storage/ndb/src/mgmapi/libndbmgmapi.a
storage/ndb/src/mgmsrv/MgmConfig-t: storage/ndb/src/mgmsrv/libndbconf.a
storage/ndb/src/mgmsrv/MgmConfig-t: storage/ndb/src/common/portlib/libndbportlib.a
storage/ndb/src/mgmsrv/MgmConfig-t: storage/ndb/src/common/debugger/libndbtrace.a
storage/ndb/src/mgmsrv/MgmConfig-t: storage/ndb/src/common/logger/libndblogger.a
storage/ndb/src/mgmsrv/MgmConfig-t: storage/ndb/src/common/util/libndbgeneral.a
storage/ndb/src/mgmsrv/MgmConfig-t: storage/ndb/src/common/debugger/signaldata/libndbsignaldata.a
storage/ndb/src/mgmsrv/MgmConfig-t: mysys/libmysys.a
storage/ndb/src/mgmsrv/MgmConfig-t: dbug/libdbug.a
storage/ndb/src/mgmsrv/MgmConfig-t: mysys/libmysys.a
storage/ndb/src/mgmsrv/MgmConfig-t: dbug/libdbug.a
storage/ndb/src/mgmsrv/MgmConfig-t: strings/libstrings.a
storage/ndb/src/mgmsrv/MgmConfig-t: probes_mysql.o
storage/ndb/src/mgmsrv/MgmConfig-t: storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable MgmConfig-t"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmsrv && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MgmConfig-t.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/build: storage/ndb/src/mgmsrv/MgmConfig-t
.PHONY : storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/build

storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/requires: storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/testConfig.cpp.o.requires
.PHONY : storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/requires

storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmsrv && $(CMAKE_COMMAND) -P CMakeFiles/MgmConfig-t.dir/cmake_clean.cmake
.PHONY : storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/clean

storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/depend:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmsrv /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmsrv /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : storage/ndb/src/mgmsrv/CMakeFiles/MgmConfig-t.dir/depend
