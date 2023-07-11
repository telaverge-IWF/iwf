/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ABORT_SYM = 258,
     ACCESSIBLE_SYM = 259,
     ACTION = 260,
     ADD = 261,
     ADDDATE_SYM = 262,
     AFTER_SYM = 263,
     AGAINST = 264,
     AGGREGATE_SYM = 265,
     ALGORITHM_SYM = 266,
     ALL = 267,
     ALTER = 268,
     ANALYZE_SYM = 269,
     AND_AND_SYM = 270,
     AND_SYM = 271,
     ANY_SYM = 272,
     AS = 273,
     ASC = 274,
     ASCII_SYM = 275,
     ASENSITIVE_SYM = 276,
     AT_SYM = 277,
     AUTHORS_SYM = 278,
     AUTOEXTEND_SIZE_SYM = 279,
     AUTO_INC = 280,
     AVG_ROW_LENGTH = 281,
     AVG_SYM = 282,
     BACKUP_SYM = 283,
     BEFORE_SYM = 284,
     BEGIN_SYM = 285,
     BETWEEN_SYM = 286,
     BIGINT = 287,
     BINARY = 288,
     BINLOG_SYM = 289,
     BIN_NUM = 290,
     BIT_AND = 291,
     BIT_OR = 292,
     BIT_SYM = 293,
     BIT_XOR = 294,
     BLOB_SYM = 295,
     BLOCK_SYM = 296,
     BOOLEAN_SYM = 297,
     BOOL_SYM = 298,
     BOTH = 299,
     BTREE_SYM = 300,
     BY = 301,
     BYTE_SYM = 302,
     CACHE_SYM = 303,
     CALL_SYM = 304,
     CASCADE = 305,
     CASCADED = 306,
     CASE_SYM = 307,
     CAST_SYM = 308,
     CATALOG_NAME_SYM = 309,
     CHAIN_SYM = 310,
     CHANGE = 311,
     CHANGED = 312,
     CHARSET = 313,
     CHAR_SYM = 314,
     CHECKSUM_SYM = 315,
     CHECK_SYM = 316,
     CIPHER_SYM = 317,
     CLASS_ORIGIN_SYM = 318,
     CLIENT_SYM = 319,
     CLOSE_SYM = 320,
     COALESCE = 321,
     CODE_SYM = 322,
     COLLATE_SYM = 323,
     COLLATION_SYM = 324,
     COLUMNS = 325,
     COLUMN_SYM = 326,
     COLUMN_FORMAT_SYM = 327,
     COLUMN_NAME_SYM = 328,
     COMMENT_SYM = 329,
     COMMITTED_SYM = 330,
     COMMIT_SYM = 331,
     COMPACT_SYM = 332,
     COMPLETION_SYM = 333,
     COMPRESSED_SYM = 334,
     CONCURRENT = 335,
     CONDITION_SYM = 336,
     CONNECTION_SYM = 337,
     CONSISTENT_SYM = 338,
     CONSTRAINT = 339,
     CONSTRAINT_CATALOG_SYM = 340,
     CONSTRAINT_NAME_SYM = 341,
     CONSTRAINT_SCHEMA_SYM = 342,
     CONTAINS_SYM = 343,
     CONTEXT_SYM = 344,
     CONTINUE_SYM = 345,
     CONTRIBUTORS_SYM = 346,
     CONVERT_SYM = 347,
     COUNT_SYM = 348,
     CPU_SYM = 349,
     CREATE = 350,
     CROSS = 351,
     CUBE_SYM = 352,
     CURDATE = 353,
     CURRENT_USER = 354,
     CURSOR_SYM = 355,
     CURSOR_NAME_SYM = 356,
     CURTIME = 357,
     DATABASE = 358,
     DATABASES = 359,
     DATAFILE_SYM = 360,
     DATA_SYM = 361,
     DATETIME = 362,
     DATE_ADD_INTERVAL = 363,
     DATE_SUB_INTERVAL = 364,
     DATE_SYM = 365,
     DAY_HOUR_SYM = 366,
     DAY_MICROSECOND_SYM = 367,
     DAY_MINUTE_SYM = 368,
     DAY_SECOND_SYM = 369,
     DAY_SYM = 370,
     DEALLOCATE_SYM = 371,
     DECIMAL_NUM = 372,
     DECIMAL_SYM = 373,
     DECLARE_SYM = 374,
     DEFAULT = 375,
     DEFINER_SYM = 376,
     DELAYED_SYM = 377,
     DELAY_KEY_WRITE_SYM = 378,
     DELETE_SYM = 379,
     DESC = 380,
     DESCRIBE = 381,
     DES_KEY_FILE = 382,
     DETERMINISTIC_SYM = 383,
     DIRECTORY_SYM = 384,
     DISABLE_SYM = 385,
     DISCARD = 386,
     DISK_SYM = 387,
     DISTINCT = 388,
     DIV_SYM = 389,
     DOUBLE_SYM = 390,
     DO_SYM = 391,
     DROP = 392,
     DUAL_SYM = 393,
     DUMPFILE = 394,
     DUPLICATE_SYM = 395,
     DYNAMIC_SYM = 396,
     EACH_SYM = 397,
     ELSE = 398,
     ELSEIF_SYM = 399,
     ENABLE_SYM = 400,
     ENCLOSED = 401,
     END = 402,
     ENDS_SYM = 403,
     END_OF_INPUT = 404,
     ENGINES_SYM = 405,
     ENGINE_SYM = 406,
     ENUM = 407,
     EQ = 408,
     EQUAL_SYM = 409,
     ERROR_SYM = 410,
     ERRORS = 411,
     ESCAPED = 412,
     ESCAPE_SYM = 413,
     EVENTS_SYM = 414,
     EVENT_SYM = 415,
     EVERY_SYM = 416,
     EXECUTE_SYM = 417,
     EXISTS = 418,
     EXIT_SYM = 419,
     EXPANSION_SYM = 420,
     EXTENDED_SYM = 421,
     EXTENT_SIZE_SYM = 422,
     EXTRACT_SYM = 423,
     FALSE_SYM = 424,
     FAST_SYM = 425,
     FAULTS_SYM = 426,
     FETCH_SYM = 427,
     FILE_SYM = 428,
     FIRST_SYM = 429,
     FIXED_SYM = 430,
     FLOAT_NUM = 431,
     FLOAT_SYM = 432,
     FLUSH_SYM = 433,
     FORCE_SYM = 434,
     FOREIGN = 435,
     FOR_SYM = 436,
     FOUND_SYM = 437,
     FROM = 438,
     FULL = 439,
     FULLTEXT_SYM = 440,
     FUNCTION_SYM = 441,
     GE = 442,
     GENERAL = 443,
     GEOMETRYCOLLECTION = 444,
     GEOMETRY_SYM = 445,
     GET_FORMAT = 446,
     GLOBAL_SYM = 447,
     GRANT = 448,
     GRANTS = 449,
     GROUP_SYM = 450,
     GROUP_CONCAT_SYM = 451,
     GT_SYM = 452,
     HANDLER_SYM = 453,
     HASH_SYM = 454,
     HAVING = 455,
     HELP_SYM = 456,
     HEX_NUM = 457,
     HIGH_PRIORITY = 458,
     HOST_SYM = 459,
     HOSTS_SYM = 460,
     HOUR_MICROSECOND_SYM = 461,
     HOUR_MINUTE_SYM = 462,
     HOUR_SECOND_SYM = 463,
     HOUR_SYM = 464,
     IDENT = 465,
     IDENTIFIED_SYM = 466,
     IDENT_QUOTED = 467,
     IF = 468,
     IGNORE_SYM = 469,
     IGNORE_SERVER_IDS_SYM = 470,
     IMPORT = 471,
     INDEXES = 472,
     INDEX_SYM = 473,
     INFILE = 474,
     INITIAL_SIZE_SYM = 475,
     INNER_SYM = 476,
     INOUT_SYM = 477,
     INSENSITIVE_SYM = 478,
     INSERT = 479,
     INSERT_METHOD = 480,
     INSTALL_SYM = 481,
     INTERVAL_SYM = 482,
     INTO = 483,
     INT_SYM = 484,
     INVOKER_SYM = 485,
     IN_SYM = 486,
     IO_SYM = 487,
     IPC_SYM = 488,
     IS = 489,
     ISOLATION = 490,
     ISSUER_SYM = 491,
     ITERATE_SYM = 492,
     JOIN_SYM = 493,
     KEYS = 494,
     KEY_BLOCK_SIZE = 495,
     KEY_SYM = 496,
     KILL_SYM = 497,
     LANGUAGE_SYM = 498,
     LAST_SYM = 499,
     LE = 500,
     LEADING = 501,
     LEAVES = 502,
     LEAVE_SYM = 503,
     LEFT = 504,
     LESS_SYM = 505,
     LEVEL_SYM = 506,
     LEX_HOSTNAME = 507,
     LIKE = 508,
     LIMIT = 509,
     LINEAR_SYM = 510,
     LINES = 511,
     LINESTRING = 512,
     LIST_SYM = 513,
     LOAD = 514,
     LOCAL_SYM = 515,
     LOCATOR_SYM = 516,
     LOCKS_SYM = 517,
     LOCK_SYM = 518,
     LOGFILE_SYM = 519,
     LOGS_SYM = 520,
     LONGBLOB = 521,
     LONGTEXT = 522,
     LONG_NUM = 523,
     LONG_SYM = 524,
     LOOP_SYM = 525,
     LOW_PRIORITY = 526,
     LT = 527,
     MASTER_BIND_SYM = 528,
     MASTER_CONNECT_RETRY_SYM = 529,
     MASTER_HOST_SYM = 530,
     MASTER_LOG_FILE_SYM = 531,
     MASTER_LOG_POS_SYM = 532,
     MASTER_PASSWORD_SYM = 533,
     MASTER_PORT_SYM = 534,
     MASTER_SERVER_ID_SYM = 535,
     MASTER_SSL_CAPATH_SYM = 536,
     MASTER_SSL_CA_SYM = 537,
     MASTER_SSL_CERT_SYM = 538,
     MASTER_SSL_CIPHER_SYM = 539,
     MASTER_SSL_KEY_SYM = 540,
     MASTER_SSL_SYM = 541,
     MASTER_SSL_VERIFY_SERVER_CERT_SYM = 542,
     MASTER_SYM = 543,
     MASTER_USER_SYM = 544,
     MASTER_HEARTBEAT_PERIOD_SYM = 545,
     MATCH = 546,
     MAX_CONNECTIONS_PER_HOUR = 547,
     MAX_QUERIES_PER_HOUR = 548,
     MAX_ROWS = 549,
     MAX_SIZE_SYM = 550,
     MAX_SYM = 551,
     MAX_UPDATES_PER_HOUR = 552,
     MAX_USER_CONNECTIONS_SYM = 553,
     MAX_VALUE_SYM = 554,
     MEDIUMBLOB = 555,
     MEDIUMINT = 556,
     MEDIUMTEXT = 557,
     MEDIUM_SYM = 558,
     MEMORY_SYM = 559,
     MERGE_SYM = 560,
     MESSAGE_TEXT_SYM = 561,
     MICROSECOND_SYM = 562,
     MIGRATE_SYM = 563,
     MINUTE_MICROSECOND_SYM = 564,
     MINUTE_SECOND_SYM = 565,
     MINUTE_SYM = 566,
     MIN_ROWS = 567,
     MIN_SYM = 568,
     MODE_SYM = 569,
     MODIFIES_SYM = 570,
     MODIFY_SYM = 571,
     MOD_SYM = 572,
     MONTH_SYM = 573,
     MULTILINESTRING = 574,
     MULTIPOINT = 575,
     MULTIPOLYGON = 576,
     MUTEX_SYM = 577,
     MYSQL_ERRNO_SYM = 578,
     NAMES_SYM = 579,
     NAME_SYM = 580,
     NATIONAL_SYM = 581,
     NATURAL = 582,
     NCHAR_STRING = 583,
     NCHAR_SYM = 584,
     NDBCLUSTER_SYM = 585,
     NE = 586,
     NEG = 587,
     NEW_SYM = 588,
     NEXT_SYM = 589,
     NODEGROUP_SYM = 590,
     NONE_SYM = 591,
     NOT2_SYM = 592,
     NOT_SYM = 593,
     NOW_SYM = 594,
     NO_SYM = 595,
     NO_WAIT_SYM = 596,
     NO_WRITE_TO_BINLOG = 597,
     NULL_SYM = 598,
     NUM = 599,
     NUMERIC_SYM = 600,
     NVARCHAR_SYM = 601,
     OFFLINE_SYM = 602,
     OFFSET_SYM = 603,
     OLD_PASSWORD = 604,
     ON = 605,
     ONE_SHOT_SYM = 606,
     ONE_SYM = 607,
     ONLINE_SYM = 608,
     OPEN_SYM = 609,
     OPTIMIZE = 610,
     OPTIONS_SYM = 611,
     OPTION = 612,
     OPTIONALLY = 613,
     OR2_SYM = 614,
     ORDER_SYM = 615,
     OR_OR_SYM = 616,
     OR_SYM = 617,
     OUTER = 618,
     OUTFILE = 619,
     OUT_SYM = 620,
     OWNER_SYM = 621,
     PACK_KEYS_SYM = 622,
     PAGE_SYM = 623,
     PARAM_MARKER = 624,
     PARSER_SYM = 625,
     PARTIAL = 626,
     PARTITIONING_SYM = 627,
     PARTITIONS_SYM = 628,
     PARTITION_SYM = 629,
     PASSWORD = 630,
     PHASE_SYM = 631,
     PLUGINS_SYM = 632,
     PLUGIN_SYM = 633,
     POINT_SYM = 634,
     POLYGON = 635,
     PORT_SYM = 636,
     POSITION_SYM = 637,
     PRECISION = 638,
     PREPARE_SYM = 639,
     PRESERVE_SYM = 640,
     PREV_SYM = 641,
     PRIMARY_SYM = 642,
     PRIVILEGES = 643,
     PROCEDURE_SYM = 644,
     PROCESS = 645,
     PROCESSLIST_SYM = 646,
     PROFILE_SYM = 647,
     PROFILES_SYM = 648,
     PROXY_SYM = 649,
     PURGE = 650,
     QUARTER_SYM = 651,
     QUERY_SYM = 652,
     QUICK = 653,
     RANGE_SYM = 654,
     READS_SYM = 655,
     READ_ONLY_SYM = 656,
     READ_SYM = 657,
     READ_WRITE_SYM = 658,
     REAL = 659,
     REBUILD_SYM = 660,
     RECOVER_SYM = 661,
     REDOFILE_SYM = 662,
     REDO_BUFFER_SIZE_SYM = 663,
     REDUNDANT_SYM = 664,
     REFERENCES = 665,
     REGEXP = 666,
     RELAY = 667,
     RELAYLOG_SYM = 668,
     RELAY_LOG_FILE_SYM = 669,
     RELAY_LOG_POS_SYM = 670,
     RELAY_THREAD = 671,
     RELEASE_SYM = 672,
     RELOAD = 673,
     REMOVE_SYM = 674,
     RENAME = 675,
     REORGANIZE_SYM = 676,
     REPAIR = 677,
     REPEATABLE_SYM = 678,
     REPEAT_SYM = 679,
     REPLACE = 680,
     REPLICATION = 681,
     REQUIRE_SYM = 682,
     RESET_SYM = 683,
     RESIGNAL_SYM = 684,
     RESOURCES = 685,
     RESTORE_SYM = 686,
     RESTRICT = 687,
     RESUME_SYM = 688,
     RETURNS_SYM = 689,
     RETURN_SYM = 690,
     REVOKE = 691,
     RIGHT = 692,
     ROLLBACK_SYM = 693,
     ROLLUP_SYM = 694,
     ROUTINE_SYM = 695,
     ROWS_SYM = 696,
     ROW_FORMAT_SYM = 697,
     ROW_SYM = 698,
     RTREE_SYM = 699,
     SAVEPOINT_SYM = 700,
     SCHEDULE_SYM = 701,
     SCHEMA_NAME_SYM = 702,
     SECOND_MICROSECOND_SYM = 703,
     SECOND_SYM = 704,
     SECURITY_SYM = 705,
     SELECT_SYM = 706,
     SENSITIVE_SYM = 707,
     SEPARATOR_SYM = 708,
     SERIALIZABLE_SYM = 709,
     SERIAL_SYM = 710,
     SESSION_SYM = 711,
     SERVER_SYM = 712,
     SERVER_OPTIONS = 713,
     SET = 714,
     SET_VAR = 715,
     SHARE_SYM = 716,
     SHIFT_LEFT = 717,
     SHIFT_RIGHT = 718,
     SHOW = 719,
     SHUTDOWN = 720,
     SIGNAL_SYM = 721,
     SIGNED_SYM = 722,
     SIMPLE_SYM = 723,
     SLAVE = 724,
     SLOW = 725,
     SMALLINT = 726,
     SNAPSHOT_SYM = 727,
     SOCKET_SYM = 728,
     SONAME_SYM = 729,
     SOUNDS_SYM = 730,
     SOURCE_SYM = 731,
     SPATIAL_SYM = 732,
     SPECIFIC_SYM = 733,
     SQLEXCEPTION_SYM = 734,
     SQLSTATE_SYM = 735,
     SQLWARNING_SYM = 736,
     SQL_BIG_RESULT = 737,
     SQL_BUFFER_RESULT = 738,
     SQL_CACHE_SYM = 739,
     SQL_CALC_FOUND_ROWS = 740,
     SQL_NO_CACHE_SYM = 741,
     SQL_SMALL_RESULT = 742,
     SQL_SYM = 743,
     SQL_THREAD = 744,
     SSL_SYM = 745,
     STARTING = 746,
     STARTS_SYM = 747,
     START_SYM = 748,
     STATUS_SYM = 749,
     STDDEV_SAMP_SYM = 750,
     STD_SYM = 751,
     STOP_SYM = 752,
     STORAGE_SYM = 753,
     STRAIGHT_JOIN = 754,
     STRING_SYM = 755,
     SUBCLASS_ORIGIN_SYM = 756,
     SUBDATE_SYM = 757,
     SUBJECT_SYM = 758,
     SUBPARTITIONS_SYM = 759,
     SUBPARTITION_SYM = 760,
     SUBSTRING = 761,
     SUM_SYM = 762,
     SUPER_SYM = 763,
     SUSPEND_SYM = 764,
     SWAPS_SYM = 765,
     SWITCHES_SYM = 766,
     SYSDATE = 767,
     TABLES = 768,
     TABLESPACE = 769,
     TABLE_REF_PRIORITY = 770,
     TABLE_SYM = 771,
     TABLE_CHECKSUM_SYM = 772,
     TABLE_NAME_SYM = 773,
     TEMPORARY = 774,
     TEMPTABLE_SYM = 775,
     TERMINATED = 776,
     TEXT_STRING = 777,
     TEXT_SYM = 778,
     THAN_SYM = 779,
     THEN_SYM = 780,
     TIMESTAMP = 781,
     TIMESTAMP_ADD = 782,
     TIMESTAMP_DIFF = 783,
     TIME_SYM = 784,
     TINYBLOB = 785,
     TINYINT = 786,
     TINYTEXT = 787,
     TO_SYM = 788,
     TRAILING = 789,
     TRANSACTION_SYM = 790,
     TRIGGERS_SYM = 791,
     TRIGGER_SYM = 792,
     TRIM = 793,
     TRUE_SYM = 794,
     TRUNCATE_SYM = 795,
     TYPES_SYM = 796,
     TYPE_SYM = 797,
     UDF_RETURNS_SYM = 798,
     ULONGLONG_NUM = 799,
     UNCOMMITTED_SYM = 800,
     UNDEFINED_SYM = 801,
     UNDERSCORE_CHARSET = 802,
     UNDOFILE_SYM = 803,
     UNDO_BUFFER_SIZE_SYM = 804,
     UNDO_SYM = 805,
     UNICODE_SYM = 806,
     UNINSTALL_SYM = 807,
     UNION_SYM = 808,
     UNIQUE_SYM = 809,
     UNKNOWN_SYM = 810,
     UNLOCK_SYM = 811,
     UNSIGNED = 812,
     UNTIL_SYM = 813,
     UPDATE_SYM = 814,
     UPGRADE_SYM = 815,
     USAGE = 816,
     USER = 817,
     USE_FRM = 818,
     USE_SYM = 819,
     USING = 820,
     UTC_DATE_SYM = 821,
     UTC_TIMESTAMP_SYM = 822,
     UTC_TIME_SYM = 823,
     VALUES = 824,
     VALUE_SYM = 825,
     VARBINARY = 826,
     VARCHAR = 827,
     VARIABLES = 828,
     VARIANCE_SYM = 829,
     VARYING = 830,
     VAR_SAMP_SYM = 831,
     VIEW_SYM = 832,
     WAIT_SYM = 833,
     WARNINGS = 834,
     WEEK_SYM = 835,
     WHEN_SYM = 836,
     WHERE = 837,
     WHILE_SYM = 838,
     WITH = 839,
     WITH_CUBE_SYM = 840,
     WITH_ROLLUP_SYM = 841,
     WORK_SYM = 842,
     WRAPPER_SYM = 843,
     WRITE_SYM = 844,
     X509_SYM = 845,
     XA_SYM = 846,
     XML_SYM = 847,
     XOR = 848,
     YEAR_MONTH_SYM = 849,
     YEAR_SYM = 850,
     ZEROFILL = 851
   };
#endif
/* Tokens.  */
#define ABORT_SYM 258
#define ACCESSIBLE_SYM 259
#define ACTION 260
#define ADD 261
#define ADDDATE_SYM 262
#define AFTER_SYM 263
#define AGAINST 264
#define AGGREGATE_SYM 265
#define ALGORITHM_SYM 266
#define ALL 267
#define ALTER 268
#define ANALYZE_SYM 269
#define AND_AND_SYM 270
#define AND_SYM 271
#define ANY_SYM 272
#define AS 273
#define ASC 274
#define ASCII_SYM 275
#define ASENSITIVE_SYM 276
#define AT_SYM 277
#define AUTHORS_SYM 278
#define AUTOEXTEND_SIZE_SYM 279
#define AUTO_INC 280
#define AVG_ROW_LENGTH 281
#define AVG_SYM 282
#define BACKUP_SYM 283
#define BEFORE_SYM 284
#define BEGIN_SYM 285
#define BETWEEN_SYM 286
#define BIGINT 287
#define BINARY 288
#define BINLOG_SYM 289
#define BIN_NUM 290
#define BIT_AND 291
#define BIT_OR 292
#define BIT_SYM 293
#define BIT_XOR 294
#define BLOB_SYM 295
#define BLOCK_SYM 296
#define BOOLEAN_SYM 297
#define BOOL_SYM 298
#define BOTH 299
#define BTREE_SYM 300
#define BY 301
#define BYTE_SYM 302
#define CACHE_SYM 303
#define CALL_SYM 304
#define CASCADE 305
#define CASCADED 306
#define CASE_SYM 307
#define CAST_SYM 308
#define CATALOG_NAME_SYM 309
#define CHAIN_SYM 310
#define CHANGE 311
#define CHANGED 312
#define CHARSET 313
#define CHAR_SYM 314
#define CHECKSUM_SYM 315
#define CHECK_SYM 316
#define CIPHER_SYM 317
#define CLASS_ORIGIN_SYM 318
#define CLIENT_SYM 319
#define CLOSE_SYM 320
#define COALESCE 321
#define CODE_SYM 322
#define COLLATE_SYM 323
#define COLLATION_SYM 324
#define COLUMNS 325
#define COLUMN_SYM 326
#define COLUMN_FORMAT_SYM 327
#define COLUMN_NAME_SYM 328
#define COMMENT_SYM 329
#define COMMITTED_SYM 330
#define COMMIT_SYM 331
#define COMPACT_SYM 332
#define COMPLETION_SYM 333
#define COMPRESSED_SYM 334
#define CONCURRENT 335
#define CONDITION_SYM 336
#define CONNECTION_SYM 337
#define CONSISTENT_SYM 338
#define CONSTRAINT 339
#define CONSTRAINT_CATALOG_SYM 340
#define CONSTRAINT_NAME_SYM 341
#define CONSTRAINT_SCHEMA_SYM 342
#define CONTAINS_SYM 343
#define CONTEXT_SYM 344
#define CONTINUE_SYM 345
#define CONTRIBUTORS_SYM 346
#define CONVERT_SYM 347
#define COUNT_SYM 348
#define CPU_SYM 349
#define CREATE 350
#define CROSS 351
#define CUBE_SYM 352
#define CURDATE 353
#define CURRENT_USER 354
#define CURSOR_SYM 355
#define CURSOR_NAME_SYM 356
#define CURTIME 357
#define DATABASE 358
#define DATABASES 359
#define DATAFILE_SYM 360
#define DATA_SYM 361
#define DATETIME 362
#define DATE_ADD_INTERVAL 363
#define DATE_SUB_INTERVAL 364
#define DATE_SYM 365
#define DAY_HOUR_SYM 366
#define DAY_MICROSECOND_SYM 367
#define DAY_MINUTE_SYM 368
#define DAY_SECOND_SYM 369
#define DAY_SYM 370
#define DEALLOCATE_SYM 371
#define DECIMAL_NUM 372
#define DECIMAL_SYM 373
#define DECLARE_SYM 374
#define DEFAULT 375
#define DEFINER_SYM 376
#define DELAYED_SYM 377
#define DELAY_KEY_WRITE_SYM 378
#define DELETE_SYM 379
#define DESC 380
#define DESCRIBE 381
#define DES_KEY_FILE 382
#define DETERMINISTIC_SYM 383
#define DIRECTORY_SYM 384
#define DISABLE_SYM 385
#define DISCARD 386
#define DISK_SYM 387
#define DISTINCT 388
#define DIV_SYM 389
#define DOUBLE_SYM 390
#define DO_SYM 391
#define DROP 392
#define DUAL_SYM 393
#define DUMPFILE 394
#define DUPLICATE_SYM 395
#define DYNAMIC_SYM 396
#define EACH_SYM 397
#define ELSE 398
#define ELSEIF_SYM 399
#define ENABLE_SYM 400
#define ENCLOSED 401
#define END 402
#define ENDS_SYM 403
#define END_OF_INPUT 404
#define ENGINES_SYM 405
#define ENGINE_SYM 406
#define ENUM 407
#define EQ 408
#define EQUAL_SYM 409
#define ERROR_SYM 410
#define ERRORS 411
#define ESCAPED 412
#define ESCAPE_SYM 413
#define EVENTS_SYM 414
#define EVENT_SYM 415
#define EVERY_SYM 416
#define EXECUTE_SYM 417
#define EXISTS 418
#define EXIT_SYM 419
#define EXPANSION_SYM 420
#define EXTENDED_SYM 421
#define EXTENT_SIZE_SYM 422
#define EXTRACT_SYM 423
#define FALSE_SYM 424
#define FAST_SYM 425
#define FAULTS_SYM 426
#define FETCH_SYM 427
#define FILE_SYM 428
#define FIRST_SYM 429
#define FIXED_SYM 430
#define FLOAT_NUM 431
#define FLOAT_SYM 432
#define FLUSH_SYM 433
#define FORCE_SYM 434
#define FOREIGN 435
#define FOR_SYM 436
#define FOUND_SYM 437
#define FROM 438
#define FULL 439
#define FULLTEXT_SYM 440
#define FUNCTION_SYM 441
#define GE 442
#define GENERAL 443
#define GEOMETRYCOLLECTION 444
#define GEOMETRY_SYM 445
#define GET_FORMAT 446
#define GLOBAL_SYM 447
#define GRANT 448
#define GRANTS 449
#define GROUP_SYM 450
#define GROUP_CONCAT_SYM 451
#define GT_SYM 452
#define HANDLER_SYM 453
#define HASH_SYM 454
#define HAVING 455
#define HELP_SYM 456
#define HEX_NUM 457
#define HIGH_PRIORITY 458
#define HOST_SYM 459
#define HOSTS_SYM 460
#define HOUR_MICROSECOND_SYM 461
#define HOUR_MINUTE_SYM 462
#define HOUR_SECOND_SYM 463
#define HOUR_SYM 464
#define IDENT 465
#define IDENTIFIED_SYM 466
#define IDENT_QUOTED 467
#define IF 468
#define IGNORE_SYM 469
#define IGNORE_SERVER_IDS_SYM 470
#define IMPORT 471
#define INDEXES 472
#define INDEX_SYM 473
#define INFILE 474
#define INITIAL_SIZE_SYM 475
#define INNER_SYM 476
#define INOUT_SYM 477
#define INSENSITIVE_SYM 478
#define INSERT 479
#define INSERT_METHOD 480
#define INSTALL_SYM 481
#define INTERVAL_SYM 482
#define INTO 483
#define INT_SYM 484
#define INVOKER_SYM 485
#define IN_SYM 486
#define IO_SYM 487
#define IPC_SYM 488
#define IS 489
#define ISOLATION 490
#define ISSUER_SYM 491
#define ITERATE_SYM 492
#define JOIN_SYM 493
#define KEYS 494
#define KEY_BLOCK_SIZE 495
#define KEY_SYM 496
#define KILL_SYM 497
#define LANGUAGE_SYM 498
#define LAST_SYM 499
#define LE 500
#define LEADING 501
#define LEAVES 502
#define LEAVE_SYM 503
#define LEFT 504
#define LESS_SYM 505
#define LEVEL_SYM 506
#define LEX_HOSTNAME 507
#define LIKE 508
#define LIMIT 509
#define LINEAR_SYM 510
#define LINES 511
#define LINESTRING 512
#define LIST_SYM 513
#define LOAD 514
#define LOCAL_SYM 515
#define LOCATOR_SYM 516
#define LOCKS_SYM 517
#define LOCK_SYM 518
#define LOGFILE_SYM 519
#define LOGS_SYM 520
#define LONGBLOB 521
#define LONGTEXT 522
#define LONG_NUM 523
#define LONG_SYM 524
#define LOOP_SYM 525
#define LOW_PRIORITY 526
#define LT 527
#define MASTER_BIND_SYM 528
#define MASTER_CONNECT_RETRY_SYM 529
#define MASTER_HOST_SYM 530
#define MASTER_LOG_FILE_SYM 531
#define MASTER_LOG_POS_SYM 532
#define MASTER_PASSWORD_SYM 533
#define MASTER_PORT_SYM 534
#define MASTER_SERVER_ID_SYM 535
#define MASTER_SSL_CAPATH_SYM 536
#define MASTER_SSL_CA_SYM 537
#define MASTER_SSL_CERT_SYM 538
#define MASTER_SSL_CIPHER_SYM 539
#define MASTER_SSL_KEY_SYM 540
#define MASTER_SSL_SYM 541
#define MASTER_SSL_VERIFY_SERVER_CERT_SYM 542
#define MASTER_SYM 543
#define MASTER_USER_SYM 544
#define MASTER_HEARTBEAT_PERIOD_SYM 545
#define MATCH 546
#define MAX_CONNECTIONS_PER_HOUR 547
#define MAX_QUERIES_PER_HOUR 548
#define MAX_ROWS 549
#define MAX_SIZE_SYM 550
#define MAX_SYM 551
#define MAX_UPDATES_PER_HOUR 552
#define MAX_USER_CONNECTIONS_SYM 553
#define MAX_VALUE_SYM 554
#define MEDIUMBLOB 555
#define MEDIUMINT 556
#define MEDIUMTEXT 557
#define MEDIUM_SYM 558
#define MEMORY_SYM 559
#define MERGE_SYM 560
#define MESSAGE_TEXT_SYM 561
#define MICROSECOND_SYM 562
#define MIGRATE_SYM 563
#define MINUTE_MICROSECOND_SYM 564
#define MINUTE_SECOND_SYM 565
#define MINUTE_SYM 566
#define MIN_ROWS 567
#define MIN_SYM 568
#define MODE_SYM 569
#define MODIFIES_SYM 570
#define MODIFY_SYM 571
#define MOD_SYM 572
#define MONTH_SYM 573
#define MULTILINESTRING 574
#define MULTIPOINT 575
#define MULTIPOLYGON 576
#define MUTEX_SYM 577
#define MYSQL_ERRNO_SYM 578
#define NAMES_SYM 579
#define NAME_SYM 580
#define NATIONAL_SYM 581
#define NATURAL 582
#define NCHAR_STRING 583
#define NCHAR_SYM 584
#define NDBCLUSTER_SYM 585
#define NE 586
#define NEG 587
#define NEW_SYM 588
#define NEXT_SYM 589
#define NODEGROUP_SYM 590
#define NONE_SYM 591
#define NOT2_SYM 592
#define NOT_SYM 593
#define NOW_SYM 594
#define NO_SYM 595
#define NO_WAIT_SYM 596
#define NO_WRITE_TO_BINLOG 597
#define NULL_SYM 598
#define NUM 599
#define NUMERIC_SYM 600
#define NVARCHAR_SYM 601
#define OFFLINE_SYM 602
#define OFFSET_SYM 603
#define OLD_PASSWORD 604
#define ON 605
#define ONE_SHOT_SYM 606
#define ONE_SYM 607
#define ONLINE_SYM 608
#define OPEN_SYM 609
#define OPTIMIZE 610
#define OPTIONS_SYM 611
#define OPTION 612
#define OPTIONALLY 613
#define OR2_SYM 614
#define ORDER_SYM 615
#define OR_OR_SYM 616
#define OR_SYM 617
#define OUTER 618
#define OUTFILE 619
#define OUT_SYM 620
#define OWNER_SYM 621
#define PACK_KEYS_SYM 622
#define PAGE_SYM 623
#define PARAM_MARKER 624
#define PARSER_SYM 625
#define PARTIAL 626
#define PARTITIONING_SYM 627
#define PARTITIONS_SYM 628
#define PARTITION_SYM 629
#define PASSWORD 630
#define PHASE_SYM 631
#define PLUGINS_SYM 632
#define PLUGIN_SYM 633
#define POINT_SYM 634
#define POLYGON 635
#define PORT_SYM 636
#define POSITION_SYM 637
#define PRECISION 638
#define PREPARE_SYM 639
#define PRESERVE_SYM 640
#define PREV_SYM 641
#define PRIMARY_SYM 642
#define PRIVILEGES 643
#define PROCEDURE_SYM 644
#define PROCESS 645
#define PROCESSLIST_SYM 646
#define PROFILE_SYM 647
#define PROFILES_SYM 648
#define PROXY_SYM 649
#define PURGE 650
#define QUARTER_SYM 651
#define QUERY_SYM 652
#define QUICK 653
#define RANGE_SYM 654
#define READS_SYM 655
#define READ_ONLY_SYM 656
#define READ_SYM 657
#define READ_WRITE_SYM 658
#define REAL 659
#define REBUILD_SYM 660
#define RECOVER_SYM 661
#define REDOFILE_SYM 662
#define REDO_BUFFER_SIZE_SYM 663
#define REDUNDANT_SYM 664
#define REFERENCES 665
#define REGEXP 666
#define RELAY 667
#define RELAYLOG_SYM 668
#define RELAY_LOG_FILE_SYM 669
#define RELAY_LOG_POS_SYM 670
#define RELAY_THREAD 671
#define RELEASE_SYM 672
#define RELOAD 673
#define REMOVE_SYM 674
#define RENAME 675
#define REORGANIZE_SYM 676
#define REPAIR 677
#define REPEATABLE_SYM 678
#define REPEAT_SYM 679
#define REPLACE 680
#define REPLICATION 681
#define REQUIRE_SYM 682
#define RESET_SYM 683
#define RESIGNAL_SYM 684
#define RESOURCES 685
#define RESTORE_SYM 686
#define RESTRICT 687
#define RESUME_SYM 688
#define RETURNS_SYM 689
#define RETURN_SYM 690
#define REVOKE 691
#define RIGHT 692
#define ROLLBACK_SYM 693
#define ROLLUP_SYM 694
#define ROUTINE_SYM 695
#define ROWS_SYM 696
#define ROW_FORMAT_SYM 697
#define ROW_SYM 698
#define RTREE_SYM 699
#define SAVEPOINT_SYM 700
#define SCHEDULE_SYM 701
#define SCHEMA_NAME_SYM 702
#define SECOND_MICROSECOND_SYM 703
#define SECOND_SYM 704
#define SECURITY_SYM 705
#define SELECT_SYM 706
#define SENSITIVE_SYM 707
#define SEPARATOR_SYM 708
#define SERIALIZABLE_SYM 709
#define SERIAL_SYM 710
#define SESSION_SYM 711
#define SERVER_SYM 712
#define SERVER_OPTIONS 713
#define SET 714
#define SET_VAR 715
#define SHARE_SYM 716
#define SHIFT_LEFT 717
#define SHIFT_RIGHT 718
#define SHOW 719
#define SHUTDOWN 720
#define SIGNAL_SYM 721
#define SIGNED_SYM 722
#define SIMPLE_SYM 723
#define SLAVE 724
#define SLOW 725
#define SMALLINT 726
#define SNAPSHOT_SYM 727
#define SOCKET_SYM 728
#define SONAME_SYM 729
#define SOUNDS_SYM 730
#define SOURCE_SYM 731
#define SPATIAL_SYM 732
#define SPECIFIC_SYM 733
#define SQLEXCEPTION_SYM 734
#define SQLSTATE_SYM 735
#define SQLWARNING_SYM 736
#define SQL_BIG_RESULT 737
#define SQL_BUFFER_RESULT 738
#define SQL_CACHE_SYM 739
#define SQL_CALC_FOUND_ROWS 740
#define SQL_NO_CACHE_SYM 741
#define SQL_SMALL_RESULT 742
#define SQL_SYM 743
#define SQL_THREAD 744
#define SSL_SYM 745
#define STARTING 746
#define STARTS_SYM 747
#define START_SYM 748
#define STATUS_SYM 749
#define STDDEV_SAMP_SYM 750
#define STD_SYM 751
#define STOP_SYM 752
#define STORAGE_SYM 753
#define STRAIGHT_JOIN 754
#define STRING_SYM 755
#define SUBCLASS_ORIGIN_SYM 756
#define SUBDATE_SYM 757
#define SUBJECT_SYM 758
#define SUBPARTITIONS_SYM 759
#define SUBPARTITION_SYM 760
#define SUBSTRING 761
#define SUM_SYM 762
#define SUPER_SYM 763
#define SUSPEND_SYM 764
#define SWAPS_SYM 765
#define SWITCHES_SYM 766
#define SYSDATE 767
#define TABLES 768
#define TABLESPACE 769
#define TABLE_REF_PRIORITY 770
#define TABLE_SYM 771
#define TABLE_CHECKSUM_SYM 772
#define TABLE_NAME_SYM 773
#define TEMPORARY 774
#define TEMPTABLE_SYM 775
#define TERMINATED 776
#define TEXT_STRING 777
#define TEXT_SYM 778
#define THAN_SYM 779
#define THEN_SYM 780
#define TIMESTAMP 781
#define TIMESTAMP_ADD 782
#define TIMESTAMP_DIFF 783
#define TIME_SYM 784
#define TINYBLOB 785
#define TINYINT 786
#define TINYTEXT 787
#define TO_SYM 788
#define TRAILING 789
#define TRANSACTION_SYM 790
#define TRIGGERS_SYM 791
#define TRIGGER_SYM 792
#define TRIM 793
#define TRUE_SYM 794
#define TRUNCATE_SYM 795
#define TYPES_SYM 796
#define TYPE_SYM 797
#define UDF_RETURNS_SYM 798
#define ULONGLONG_NUM 799
#define UNCOMMITTED_SYM 800
#define UNDEFINED_SYM 801
#define UNDERSCORE_CHARSET 802
#define UNDOFILE_SYM 803
#define UNDO_BUFFER_SIZE_SYM 804
#define UNDO_SYM 805
#define UNICODE_SYM 806
#define UNINSTALL_SYM 807
#define UNION_SYM 808
#define UNIQUE_SYM 809
#define UNKNOWN_SYM 810
#define UNLOCK_SYM 811
#define UNSIGNED 812
#define UNTIL_SYM 813
#define UPDATE_SYM 814
#define UPGRADE_SYM 815
#define USAGE 816
#define USER 817
#define USE_FRM 818
#define USE_SYM 819
#define USING 820
#define UTC_DATE_SYM 821
#define UTC_TIMESTAMP_SYM 822
#define UTC_TIME_SYM 823
#define VALUES 824
#define VALUE_SYM 825
#define VARBINARY 826
#define VARCHAR 827
#define VARIABLES 828
#define VARIANCE_SYM 829
#define VARYING 830
#define VAR_SAMP_SYM 831
#define VIEW_SYM 832
#define WAIT_SYM 833
#define WARNINGS 834
#define WEEK_SYM 835
#define WHEN_SYM 836
#define WHERE 837
#define WHILE_SYM 838
#define WITH 839
#define WITH_CUBE_SYM 840
#define WITH_ROLLUP_SYM 841
#define WORK_SYM 842
#define WRAPPER_SYM 843
#define WRITE_SYM 844
#define X509_SYM 845
#define XA_SYM 846
#define XML_SYM 847
#define XOR 848
#define YEAR_MONTH_SYM 849
#define YEAR_SYM 850
#define ZEROFILL 851




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 737 "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/sql/sql_yacc.yy"
{
  int  num;
  ulong ulong_num;
  ulonglong ulonglong_number;
  longlong longlong_number;
  LEX_STRING lex_str;
  LEX_STRING *lex_str_ptr;
  LEX_SYMBOL symbol;
  Table_ident *table;
  char *simple_string;
  Item *item;
  Item_num *item_num;
  List<Item> *item_list;
  List<String> *string_list;
  String *string;
  Key_part_spec *key_part;
  TABLE_LIST *table_list;
  udf_func *udf;
  LEX_USER *lex_user;
  struct sys_var_with_base variable;
  enum enum_var_type var_type;
  Key::Keytype key_type;
  enum ha_key_alg key_alg;
  handlerton *db_type;
  enum row_type row_type;
  enum ha_rkey_function ha_rkey_mode;
  enum enum_tx_isolation tx_isolation;
  enum Cast_target cast_type;
  enum Item_udftype udf_type;
  CHARSET_INFO *charset;
  thr_lock_type lock_type;
  interval_type interval, interval_time_st;
  timestamp_type date_time_type;
  st_select_lex *select_lex;
  chooser_compare_func_creator boolfunc2creator;
  struct sp_cond_type *spcondtype;
  struct { int vars, conds, hndlrs, curs; } spblock;
  sp_name *spname;
  LEX *lex;
  sp_head *sphead;
  struct p_elem_val *p_elem_value;
  enum index_hint_type index_hint;
#ifndef MCP_WL3749
  enum ha_build_method build_method;
#endif
  enum enum_filetype filetype;
  enum Foreign_key::fk_option m_fk_option;
  enum enum_yes_no_unknown m_yes_no_unk;
  Diag_condition_item_name diag_condition_item_name;
}
/* Line 1489 of yacc.c.  */
#line 1292 "/opt/checkout/eAccelero/3rdparty/mysql-cluster-gpl-7.2.8/sql/sql_yacc.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif


