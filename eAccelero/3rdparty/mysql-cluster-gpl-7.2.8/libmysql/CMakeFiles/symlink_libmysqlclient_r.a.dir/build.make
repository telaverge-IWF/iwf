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

# Utility rule file for symlink_libmysqlclient_r.a.

# Include the progress variables for this target.
include libmysql/CMakeFiles/symlink_libmysqlclient_r.a.dir/progress.make

libmysql/CMakeFiles/symlink_libmysqlclient_r.a: libmysql/libmysqlclient_r.a

libmysql/libmysqlclient_r.a: libmysql/libmysqlclient.a
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating libmysqlclient_r.a"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/libmysql && /usr/bin/cmake -E remove -f /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/libmysql/libmysqlclient_r.a
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/libmysql && /usr/bin/cmake -E create_symlink libmysqlclient.a libmysqlclient_r.a

symlink_libmysqlclient_r.a: libmysql/CMakeFiles/symlink_libmysqlclient_r.a
symlink_libmysqlclient_r.a: libmysql/libmysqlclient_r.a
symlink_libmysqlclient_r.a: libmysql/CMakeFiles/symlink_libmysqlclient_r.a.dir/build.make
.PHONY : symlink_libmysqlclient_r.a

# Rule to build all files generated by this target.
libmysql/CMakeFiles/symlink_libmysqlclient_r.a.dir/build: symlink_libmysqlclient_r.a
.PHONY : libmysql/CMakeFiles/symlink_libmysqlclient_r.a.dir/build

libmysql/CMakeFiles/symlink_libmysqlclient_r.a.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/libmysql && $(CMAKE_COMMAND) -P CMakeFiles/symlink_libmysqlclient_r.a.dir/cmake_clean.cmake
.PHONY : libmysql/CMakeFiles/symlink_libmysqlclient_r.a.dir/clean

libmysql/CMakeFiles/symlink_libmysqlclient_r.a.dir/depend:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/libmysql /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/libmysql /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/libmysql/CMakeFiles/symlink_libmysqlclient_r.a.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libmysql/CMakeFiles/symlink_libmysqlclient_r.a.dir/depend

