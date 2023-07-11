# The set of languages for which implicit dependencies are needed:
SET(CMAKE_DEPENDS_LANGUAGES
  )
# The set of files for implicit dependencies of each language:

# Preprocessor definitions for this target.
SET(CMAKE_TARGET_DEFINITIONS
  "HAVE_CONFIG_H"
  "HAVE_NDB_CONFIG_H"
  "NDEBUG"
  )

# Targets to which this target links.
SET(CMAKE_TARGET_LINKED_INFO_FILES
  )

# The include file search paths:
SET(CMAKE_C_TARGET_INCLUDE_PATH
  "include"
  "storage/ndb/include"
  "sql"
  "regex"
  "storage/ndb/include/util"
  "storage/ndb/include/portlib"
  "storage/ndb/include/debugger"
  "storage/ndb/include/transporter"
  "storage/ndb/include/kernel"
  "storage/ndb/include/mgmapi"
  "storage/ndb/include/mgmcommon"
  "storage/ndb/include/ndbapi"
  "storage/ndb/include/logger"
  "cmd-line-utils/libedit"
  "storage/ndb/tools"
  "storage/ndb/test/include"
  "storage/ndb/src/ndbapi"
  )
SET(CMAKE_CXX_TARGET_INCLUDE_PATH ${CMAKE_C_TARGET_INCLUDE_PATH})
SET(CMAKE_Fortran_TARGET_INCLUDE_PATH ${CMAKE_C_TARGET_INCLUDE_PATH})
SET(CMAKE_ASM_TARGET_INCLUDE_PATH ${CMAKE_C_TARGET_INCLUDE_PATH})
