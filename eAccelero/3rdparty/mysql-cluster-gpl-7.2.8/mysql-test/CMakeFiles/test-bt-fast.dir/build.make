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

# Utility rule file for test-bt-fast.

# Include the progress variables for this target.
include mysql-test/CMakeFiles/test-bt-fast.dir/progress.make

mysql-test/CMakeFiles/test-bt-fast:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/mysql-test && echo Running tests
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/mysql-test && echo OS=Linux
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/mysql-test && export MTR_BUILD_THREAD=auto
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/mysql-test && perl ./mysql-test-run.pl --force --comment=ps --timer --skip-ndbcluster --ps-protocol --report-features --experimental=collections/default.experimental
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/mysql-test && perl ./mysql-test-run.pl --force --comment=stress --suite=stress --experimental=collections/default.experimental

test-bt-fast: mysql-test/CMakeFiles/test-bt-fast
test-bt-fast: mysql-test/CMakeFiles/test-bt-fast.dir/build.make
.PHONY : test-bt-fast

# Rule to build all files generated by this target.
mysql-test/CMakeFiles/test-bt-fast.dir/build: test-bt-fast
.PHONY : mysql-test/CMakeFiles/test-bt-fast.dir/build

mysql-test/CMakeFiles/test-bt-fast.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/mysql-test && $(CMAKE_COMMAND) -P CMakeFiles/test-bt-fast.dir/cmake_clean.cmake
.PHONY : mysql-test/CMakeFiles/test-bt-fast.dir/clean

mysql-test/CMakeFiles/test-bt-fast.dir/depend:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/mysql-test /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/mysql-test /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/mysql-test/CMakeFiles/test-bt-fast.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mysql-test/CMakeFiles/test-bt-fast.dir/depend

