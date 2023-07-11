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
include storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/depend.make

# Include the progress variables for this target.
include storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/progress.make

# Include the compile flags for this target's objects.
include storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/flags.make

storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.o: storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/flags.make
storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.o: storage/ndb/src/kernel/blocks/dblqh/redoLogReader/records.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.o"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.o -c /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh/redoLogReader/records.cpp

storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.i"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh/redoLogReader/records.cpp > CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.i

storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.s"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh/redoLogReader/records.cpp -o CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.s

storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.o.requires:
.PHONY : storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.o.requires

storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.o.provides: storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.o.requires
	$(MAKE) -f storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/build.make storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.o.provides.build
.PHONY : storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.o.provides

storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.o.provides.build: storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.o

storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.o: storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/flags.make
storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.o: storage/ndb/src/kernel/blocks/dblqh/redoLogReader/reader.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.o"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.o -c /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh/redoLogReader/reader.cpp

storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.i"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh/redoLogReader/reader.cpp > CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.i

storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.s"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh/redoLogReader/reader.cpp -o CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.s

storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.o.requires:
.PHONY : storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.o.requires

storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.o.provides: storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.o.requires
	$(MAKE) -f storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/build.make storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.o.provides.build
.PHONY : storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.o.provides

storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.o.provides.build: storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.o

# Object files for target ndb_redo_log_reader
ndb_redo_log_reader_OBJECTS = \
"CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.o" \
"CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.o"

# External object files for target ndb_redo_log_reader
ndb_redo_log_reader_EXTERNAL_OBJECTS =

storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.o
storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.o
storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/build.make
storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: storage/ndb/src/common/debugger/libndbtrace.a
storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: storage/ndb/src/common/logger/libndblogger.a
storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: storage/ndb/src/common/util/libndbgeneral.a
storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: storage/ndb/src/common/portlib/libndbportlib.a
storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: storage/ndb/src/common/debugger/libndbtrace.a
storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: storage/ndb/src/common/logger/libndblogger.a
storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: storage/ndb/src/common/util/libndbgeneral.a
storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: storage/ndb/src/common/debugger/signaldata/libndbsignaldata.a
storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: mysys/libmysys.a
storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: dbug/libdbug.a
storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: mysys/libmysys.a
storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: dbug/libdbug.a
storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: strings/libstrings.a
storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: probes_mysql.o
storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader: storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ndb_redo_log_reader"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ndb_redo_log_reader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/build: storage/ndb/src/kernel/blocks/dblqh/ndb_redo_log_reader
.PHONY : storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/build

storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/requires: storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/records.cpp.o.requires
storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/requires: storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/redoLogReader/reader.cpp.o.requires
.PHONY : storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/requires

storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh && $(CMAKE_COMMAND) -P CMakeFiles/ndb_redo_log_reader.dir/cmake_clean.cmake
.PHONY : storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/clean

storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/depend:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : storage/ndb/src/kernel/blocks/dblqh/CMakeFiles/ndb_redo_log_reader.dir/depend

