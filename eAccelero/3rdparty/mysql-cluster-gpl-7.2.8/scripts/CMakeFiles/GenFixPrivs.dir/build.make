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

# Utility rule file for GenFixPrivs.

# Include the progress variables for this target.
include scripts/CMakeFiles/GenFixPrivs.dir/progress.make

scripts/CMakeFiles/GenFixPrivs: scripts/mysql_fix_privilege_tables_sql.c

scripts/mysql_fix_privilege_tables_sql.c: scripts/comp_sql
scripts/mysql_fix_privilege_tables_sql.c: scripts/mysql_system_tables.sql
scripts/mysql_fix_privilege_tables_sql.c: scripts/mysql_system_tables_fix.sql
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating mysql_fix_privilege_tables_sql.c"
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/scripts && /usr/bin/cmake -E chdir /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/scripts /usr/bin/cat mysql_system_tables.sql mysql_system_tables_fix.sql > /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/scripts/mysql_fix_privilege_tables.sql
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/scripts && /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/scripts/comp_sql mysql_fix_privilege_tables mysql_fix_privilege_tables.sql mysql_fix_privilege_tables_sql.c

GenFixPrivs: scripts/CMakeFiles/GenFixPrivs
GenFixPrivs: scripts/mysql_fix_privilege_tables_sql.c
GenFixPrivs: scripts/CMakeFiles/GenFixPrivs.dir/build.make
.PHONY : GenFixPrivs

# Rule to build all files generated by this target.
scripts/CMakeFiles/GenFixPrivs.dir/build: GenFixPrivs
.PHONY : scripts/CMakeFiles/GenFixPrivs.dir/build

scripts/CMakeFiles/GenFixPrivs.dir/clean:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/scripts && $(CMAKE_COMMAND) -P CMakeFiles/GenFixPrivs.dir/cmake_clean.cmake
.PHONY : scripts/CMakeFiles/GenFixPrivs.dir/clean

scripts/CMakeFiles/GenFixPrivs.dir/depend:
	cd /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/scripts /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8 /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/scripts /opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/scripts/CMakeFiles/GenFixPrivs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : scripts/CMakeFiles/GenFixPrivs.dir/depend

