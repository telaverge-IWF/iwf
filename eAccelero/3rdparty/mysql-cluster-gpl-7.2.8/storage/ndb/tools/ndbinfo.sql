#
# SQL commands for creating the tables in MySQL Server which
# are used by the NDBINFO storage engine to access system
# information and statistics from MySQL Cluster
#
# Only create objects if NDBINFO is supported
SELECT @have_ndbinfo:= COUNT(*) FROM information_schema.engines WHERE engine='NDBINFO' AND support IN ('YES', 'DEFAULT');

# Only create objects if version >= 7.1
SET @str=IF(@have_ndbinfo,'SELECT @have_ndbinfo:= (@@ndbinfo_version >= (7 << 16) | (1 << 8)) || @ndbinfo_skip_version_check','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# Only create objects if ndbinfo namespace is free
SET @str=IF(@have_ndbinfo,'SET @@ndbinfo_show_hidden=TRUE','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'SELECT @have_ndbinfo:= COUNT(*) = 0 FROM information_schema.tables WHERE table_schema = @@ndbinfo_database AND LEFT(table_name, LENGTH(@@ndbinfo_table_prefix)) = @@ndbinfo_table_prefix AND engine != "ndbinfo"','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'SET @@ndbinfo_show_hidden=default','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'CREATE DATABASE IF NOT EXISTS `ndbinfo`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# Set NDBINFO in offline mode during (re)create of tables
# and views to avoid errors caused by no such table or
# different table definition in NDB
SET @str=IF(@have_ndbinfo,'SET @@global.ndbinfo_offline=TRUE','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# Drop any old views in ndbinfo
SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`transporters`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`logspaces`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`logbuffers`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`resources`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`counters`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`nodes`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`memoryusage`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`diskpagebuffer`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`diskpagebuffer`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`threadblocks`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`threadstat`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`cluster_transactions`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`server_transactions`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`cluster_operations`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'DROP VIEW IF EXISTS `ndbinfo`.`server_operations`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# Drop any old lookup tables in ndbinfo
SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`blocks`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`config_params`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$dbtc_apiconnect_state`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$dblqh_tcconnect_state`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.ndb$tables
SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$tables`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$tables` (`table_id` INT UNSIGNED,`table_name` VARCHAR(512),`comment` VARCHAR(512)) COMMENT="metadata for tables available through ndbinfo" ENGINE=NDBINFO','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.ndb$columns
SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$columns`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$columns` (`table_id` INT UNSIGNED,`column_id` INT UNSIGNED,`column_name` VARCHAR(512),`column_type` INT UNSIGNED,`comment` VARCHAR(512)) COMMENT="metadata for columns available through ndbinfo " ENGINE=NDBINFO','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.ndb$test
SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$test`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$test` (`node_id` INT UNSIGNED,`block_number` INT UNSIGNED,`block_instance` INT UNSIGNED,`counter` INT UNSIGNED,`counter2` BIGINT UNSIGNED) COMMENT="for testing" ENGINE=NDBINFO','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.ndb$pools
SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$pools`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$pools` (`node_id` INT UNSIGNED,`block_number` INT UNSIGNED,`block_instance` INT UNSIGNED,`pool_name` VARCHAR(512),`used` BIGINT UNSIGNED COMMENT "currently in use",`total` BIGINT UNSIGNED COMMENT "total allocated",`high` BIGINT UNSIGNED COMMENT "in use high water mark",`entry_size` BIGINT UNSIGNED COMMENT "size in bytes of each object",`config_param1` INT UNSIGNED COMMENT "config param 1 affecting pool",`config_param2` INT UNSIGNED COMMENT "config param 2 affecting pool",`config_param3` INT UNSIGNED COMMENT "config param 3 affecting pool",`config_param4` INT UNSIGNED COMMENT "config param 4 affecting pool") COMMENT="pool usage" ENGINE=NDBINFO','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.ndb$transporters
SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$transporters`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$transporters` (`node_id` INT UNSIGNED,`remote_node_id` INT UNSIGNED,`connection_status` INT UNSIGNED) COMMENT="transporter status" ENGINE=NDBINFO','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.ndb$logspaces
SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$logspaces`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$logspaces` (`node_id` INT UNSIGNED,`log_type` INT UNSIGNED COMMENT "0 = REDO, 1 = DD-UNDO",`log_id` INT UNSIGNED,`log_part` INT UNSIGNED,`total` BIGINT UNSIGNED COMMENT "total allocated",`used` BIGINT UNSIGNED COMMENT "currently in use",`high` BIGINT UNSIGNED COMMENT "in use high water mark") COMMENT="logspace usage" ENGINE=NDBINFO','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.ndb$logbuffers
SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$logbuffers`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$logbuffers` (`node_id` INT UNSIGNED,`log_type` INT UNSIGNED COMMENT "0 = REDO, 1 = DD-UNDO",`log_id` INT UNSIGNED,`log_part` INT UNSIGNED,`total` BIGINT UNSIGNED COMMENT "total allocated",`used` BIGINT UNSIGNED COMMENT "currently in use",`high` BIGINT UNSIGNED COMMENT "in use high water mark") COMMENT="logbuffer usage" ENGINE=NDBINFO','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.ndb$resources
SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$resources`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$resources` (`node_id` INT UNSIGNED,`resource_id` INT UNSIGNED,`reserved` INT UNSIGNED COMMENT "reserved for this resource",`used` INT UNSIGNED COMMENT "currently in use",`max` INT UNSIGNED COMMENT "max available",`high` INT UNSIGNED COMMENT "in use high water mark") COMMENT="resources usage (a.k.a superpool)" ENGINE=NDBINFO','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.ndb$counters
SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$counters`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$counters` (`node_id` INT UNSIGNED,`block_number` INT UNSIGNED,`block_instance` INT UNSIGNED,`counter_id` INT UNSIGNED,`val` BIGINT UNSIGNED COMMENT "monotonically increasing since process start") COMMENT="monotonic counters" ENGINE=NDBINFO','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.ndb$nodes
SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$nodes`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$nodes` (`node_id` INT UNSIGNED,`uptime` BIGINT UNSIGNED COMMENT "time in seconds that node has been running",`status` INT UNSIGNED COMMENT "starting/started/stopped etc.",`start_phase` INT UNSIGNED COMMENT "start phase if node is starting",`config_generation` INT UNSIGNED COMMENT "configuration generation number") COMMENT="node status" ENGINE=NDBINFO','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.ndb$diskpagebuffer
SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$diskpagebuffer`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$diskpagebuffer` (`node_id` INT UNSIGNED,`block_instance` INT UNSIGNED,`pages_written` BIGINT UNSIGNED COMMENT "Pages written to disk",`pages_written_lcp` BIGINT UNSIGNED COMMENT "Pages written by local checkpoint",`pages_read` BIGINT UNSIGNED COMMENT "Pages read from disk",`log_waits` BIGINT UNSIGNED COMMENT "Page writes waiting for log to be written to disk",`page_requests_direct_return` BIGINT UNSIGNED COMMENT "Page in buffer and no requests waiting for it",`page_requests_wait_queue` BIGINT UNSIGNED COMMENT "Page in buffer, but some requests are already waiting for it",`page_requests_wait_io` BIGINT UNSIGNED COMMENT "Page not in buffer, waiting to be read from disk") COMMENT="disk page buffer info" ENGINE=NDBINFO','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.ndb$threadblocks
SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$threadblocks`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$threadblocks` (`node_id` INT UNSIGNED COMMENT "node id",`thr_no` INT UNSIGNED COMMENT "thread number",`block_number` INT UNSIGNED COMMENT "block number",`block_instance` INT UNSIGNED COMMENT "block instance") COMMENT="which blocks are run in which threads" ENGINE=NDBINFO','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.ndb$threadstat
SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$threadstat`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$threadstat` (`node_id` INT UNSIGNED COMMENT "node id",`thr_no` INT UNSIGNED COMMENT "thread number",`thr_nm` VARCHAR(512) COMMENT "thread name",`c_loop` BIGINT UNSIGNED COMMENT "No of loops in main loop",`c_exec` BIGINT UNSIGNED COMMENT "No of signals executed",`c_wait` BIGINT UNSIGNED COMMENT "No of times waited for more input",`c_l_sent_prioa` BIGINT UNSIGNED COMMENT "No of prio A signals sent to own node",`c_l_sent_priob` BIGINT UNSIGNED COMMENT "No of prio B signals sent to own node",`c_r_sent_prioa` BIGINT UNSIGNED COMMENT "No of prio A signals sent to remote node",`c_r_sent_priob` BIGINT UNSIGNED COMMENT "No of prio B signals sent to remote node",`os_tid` BIGINT UNSIGNED COMMENT "OS thread id",`os_now` BIGINT UNSIGNED COMMENT "OS gettimeofday (millis)",`os_ru_utime` BIGINT UNSIGNED COMMENT "OS user CPU time (micros)",`os_ru_stime` BIGINT UNSIGNED COMMENT "OS system CPU time (micros)",`os_ru_minflt` BIGINT UNSIGNED COMMENT "OS page reclaims (soft page faults",`os_ru_majflt` BIGINT UNSIGNED COMMENT "OS page faults (hard page faults)",`os_ru_nvcsw` BIGINT UNSIGNED COMMENT "OS voluntary context switches",`os_ru_nivcsw` BIGINT UNSIGNED COMMENT "OS involuntary context switches") COMMENT="Statistics on execution threads" ENGINE=NDBINFO','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.ndb$transactions
SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$transactions`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$transactions` (`node_id` INT UNSIGNED COMMENT "node id",`block_instance` INT UNSIGNED COMMENT "TC instance no",`objid` INT UNSIGNED COMMENT "Object id of transaction object",`apiref` INT UNSIGNED COMMENT "API reference",`transid0` INT UNSIGNED COMMENT "Transaction id",`transid1` INT UNSIGNED COMMENT "Transaction id",`state` INT UNSIGNED COMMENT "Transaction state",`flags` INT UNSIGNED COMMENT "Transaction flags",`c_ops` INT UNSIGNED COMMENT "No of operations in transaction",`outstanding` INT UNSIGNED COMMENT "Currently outstanding request",`timer` INT UNSIGNED COMMENT "Timer (seconds)") COMMENT="transactions" ENGINE=NDBINFO','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.ndb$operations
SET @str=IF(@have_ndbinfo,'DROP TABLE IF EXISTS `ndbinfo`.`ndb$operations`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$operations` (`node_id` INT UNSIGNED COMMENT "node id",`block_instance` INT UNSIGNED COMMENT "LQH instance no",`objid` INT UNSIGNED COMMENT "Object id of operation object",`tcref` INT UNSIGNED COMMENT "TC reference",`apiref` INT UNSIGNED COMMENT "API reference",`transid0` INT UNSIGNED COMMENT "Transaction id",`transid1` INT UNSIGNED COMMENT "Transaction id",`tableid` INT UNSIGNED COMMENT "Table id",`fragmentid` INT UNSIGNED COMMENT "Fragment id",`op` INT UNSIGNED COMMENT "Operation type",`state` INT UNSIGNED COMMENT "Operation state",`flags` INT UNSIGNED COMMENT "Operation flags") COMMENT="operations" ENGINE=NDBINFO','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.blocks
SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`blocks` (block_number INT UNSIGNED PRIMARY KEY, block_name VARCHAR(512))','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'INSERT INTO `ndbinfo`.`blocks` VALUES (254, "CMVMI"), (248, "DBACC"), (250, "DBDICT"), (246, "DBDIH"), (247, "DBLQH"), (245, "DBTC"), (249, "DBTUP"), (253, "NDBFS"), (251, "NDBCNTR"), (252, "QMGR"), (255, "TRIX"), (244, "BACKUP"), (256, "DBUTIL"), (257, "SUMA"), (258, "DBTUX"), (259, "TSMAN"), (260, "LGMAN"), (261, "PGMAN"), (262, "RESTORE"), (263, "DBINFO"), (264, "DBSPJ"), (265, "THRMAN"), (266, "TRPMAN")','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.config_params
SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`config_params` (param_number INT UNSIGNED PRIMARY KEY, param_name VARCHAR(512))','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'INSERT INTO `ndbinfo`.`config_params` VALUES (179, "MaxNoOfSubscriptions"), (180, "MaxNoOfSubscribers"), (181, "MaxNoOfConcurrentSubOperations"), (5, "HostName"), (3, "NodeId"), (101, "NoOfReplicas"), (103, "MaxNoOfAttributes"), (102, "MaxNoOfTables"), (149, "MaxNoOfOrderedIndexes"), (150, "MaxNoOfUniqueHashIndexes"), (110, "MaxNoOfConcurrentIndexOperations"), (105, "MaxNoOfTriggers"), (109, "MaxNoOfFiredTriggers"), (100, "MaxNoOfSavedMessages"), (177, "LockExecuteThreadToCPU"), (178, "LockMaintThreadsToCPU"), (176, "RealtimeScheduler"), (114, "LockPagesInMainMemory"), (123, "TimeBetweenWatchDogCheck"), (174, "SchedulerExecutionTimer"), (175, "SchedulerSpinTimer"), (141, "TimeBetweenWatchDogCheckInitial"), (124, "StopOnError"), (107, "MaxNoOfConcurrentOperations"), (627, "MaxDMLOperationsPerTransaction"), (151, "MaxNoOfLocalOperations"), (152, "MaxNoOfLocalScans"), (153, "BatchSizePerLocalScan"), (106, "MaxNoOfConcurrentTransactions"), (108, "MaxNoOfConcurrentScans"), (111, "TransactionBufferMemory"), (113, "IndexMemory"), (112, "DataMemory"), (154, "UndoIndexBuffer"), (155, "UndoDataBuffer"), (156, "RedoBuffer"), (157, "LongMessageBuffer"), (160, "DiskPageBufferMemory"), (198, "SharedGlobalMemory"), (115, "StartPartialTimeout"), (116, "StartPartitionedTimeout"), (117, "StartFailureTimeout"), (619, "StartNoNodegroupTimeout"), (118, "HeartbeatIntervalDbDb"), (618, "ConnectCheckIntervalDelay"), (119, "HeartbeatIntervalDbApi"), (120, "TimeBetweenLocalCheckpoints"), (121, "TimeBetweenGlobalCheckpoints"), (170, "TimeBetweenEpochs"), (171, "TimeBetweenEpochsTimeout"), (182, "MaxBufferedEpochs"), (632, "NoOfFragmentLogParts"), (126, "NoOfFragmentLogFiles"), (140, "FragmentLogFileSize"), (189, "InitFragmentLogFiles"), (190, "DiskIOThreadPool"), (159, "MaxNoOfOpenFiles"), (162, "InitialNoOfOpenFiles"), (129, "TimeBetweenInactiveTransactionAbortCheck"), (130, "TransactionInactiveTimeout"), (131, "TransactionDeadlockDetectionTimeout"), (148, "Diskless"), (122, "ArbitrationTimeout"), (142, "Arbitration"), (7, "DataDir"), (125, "FileSystemPath"), (250, "LogLevelStartup"), (251, "LogLevelShutdown"), (252, "LogLevelStatistic"), (253, "LogLevelCheckpoint"), (254, "LogLevelNodeRestart"), (255, "LogLevelConnection"), (259, "LogLevelCongestion"), (258, "LogLevelError"), (256, "LogLevelInfo"), (158, "BackupDataDir"), (163, "DiskSyncSize"), (164, "DiskCheckpointSpeed"), (165, "DiskCheckpointSpeedInRestart"), (133, "BackupMemory"), (134, "BackupDataBufferSize"), (135, "BackupLogBufferSize"), (136, "BackupWriteSize"), (139, "BackupMaxWriteSize"), (161, "StringMemory"), (169, "MaxAllocate"), (166, "MemReportFrequency"), (167, "BackupReportFrequency"), (184, "StartupStatusReportFrequency"), (168, "ODirect"), (172, "CompressedBackup"), (173, "CompressedLCP"), (203, "ExtraSendBufferMemory"), (9, "TotalSendBufferMemory"), (185, "Nodegroup"), (186, "MaxNoOfExecutionThreads"), (188, "__ndbmt_lqh_workers"), (187, "__ndbmt_lqh_threads"), (191, "__ndbmt_classic"), (628, "ThreadConfig"), (193, "FileSystemPathDD"), (194, "FileSystemPathDataFiles"), (195, "FileSystemPathUndoFiles"), (196, "InitialLogfileGroup"), (197, "InitialTablespace"), (605, "MaxLCPStartDelay"), (606, "BuildIndexThreads"), (607, "HeartbeatOrder"), (608, "DictTrace"), (609, "MaxStartFailRetries"), (610, "StartFailRetryDelay"), (613, "EventLogBufferSize"), (614, "Numa"), (611, "RedoOverCommitLimit"), (612, "RedoOverCommitCounter"), (615, "LateAlloc"), (616, "TwoPassInitialNodeRestartCopy"), (617, "MaxParallelScansPerFragment"), (620, "IndexStatAutoCreate"), (621, "IndexStatAutoUpdate"), (622, "IndexStatSaveSize"), (623, "IndexStatSaveScale"), (624, "IndexStatTriggerPct"), (625, "IndexStatTriggerScale"), (626, "IndexStatUpdateDelay"), (629, "CrashOnCorruptedTuple"), (630, "MinFreePct")','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.ndb$dbtc_apiconnect_state
SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$dbtc_apiconnect_state` (state_int_value  INT UNSIGNED PRIMARY KEY, state_name VARCHAR(256), state_friendly_name VARCHAR(256), state_description VARCHAR(256))','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'INSERT INTO `ndbinfo`.`ndb$dbtc_apiconnect_state` VALUES (0, "CS_CONNECTED", "Connected", "An allocated idle transaction object"), (1, "CS_DISCONNECTED", "Disconnected", "An unallocated connection object"), (2, "CS_STARTED", "Started", "A started transaction"), (3, "CS_RECEIVING", "Receiving", "A transaction receiving operations"), (7, "CS_RESTART", "", ""), (8, "CS_ABORTING", "Aborting", "A transaction aborting"), (9, "CS_COMPLETING", "Completing", "A transaction completing"), (10, "CS_COMPLETE_SENT", "Completing", "A transaction completing"), (11, "CS_PREPARE_TO_COMMIT", "", ""), (12, "CS_COMMIT_SENT", "Committing", "A transaction committing"), (13, "CS_START_COMMITTING", "", ""), (14, "CS_COMMITTING", "Committing", "A transaction committing"), (15, "CS_REC_COMMITTING", "", ""), (16, "CS_WAIT_ABORT_CONF", "Aborting", ""), (17, "CS_WAIT_COMPLETE_CONF", "Completing", ""), (18, "CS_WAIT_COMMIT_CONF", "Committing", ""), (19, "CS_FAIL_ABORTING", "TakeOverAborting", ""), (20, "CS_FAIL_ABORTED", "TakeOverAborting", ""), (21, "CS_FAIL_PREPARED", "", ""), (22, "CS_FAIL_COMMITTING", "TakeOverCommitting", ""), (23, "CS_FAIL_COMMITTED", "TakeOverCommitting", ""), (24, "CS_FAIL_COMPLETED", "TakeOverCompleting", ""), (25, "CS_START_SCAN", "Scanning", ""), (26, "CS_SEND_FIRE_TRIG_REQ", "Precomitting", ""), (27, "CS_WAIT_FIRE_TRIG_REQ", "Precomitting", "")','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.ndb$dblqh_tcconnect_state
SET @str=IF(@have_ndbinfo,'CREATE TABLE `ndbinfo`.`ndb$dblqh_tcconnect_state` (state_int_value  INT UNSIGNED PRIMARY KEY, state_name VARCHAR(256), state_friendly_name VARCHAR(256), state_description VARCHAR(256))','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

SET @str=IF(@have_ndbinfo,'INSERT INTO `ndbinfo`.`ndb$dblqh_tcconnect_state` VALUES (0, "IDLE", "Idle", ""), (1, "WAIT_ACC", "WaitLock", ""), (2, "WAIT_TUPKEYINFO", "", ""), (3, "WAIT_ATTR", "WaitData", ""), (4, "WAIT_TUP", "WaitTup", ""), (5, "STOPPED", "Stopped", ""), (6, "LOG_QUEUED", "LogPrepare", ""), (7, "PREPARED", "Prepared", ""), (8, "LOG_COMMIT_WRITTEN_WAIT_SIGNAL", "", ""), (9, "LOG_COMMIT_QUEUED_WAIT_SIGNAL", "", ""), (10, "COMMIT_STOPPED", "CommittingStopped", ""), (11, "LOG_COMMIT_QUEUED", "Committing", ""), (12, "COMMIT_QUEUED", "Committing", ""), (13, "COMMITTED", "Committed", ""), (35, "WAIT_TUP_COMMIT", "Committing", ""), (14, "WAIT_ACC_ABORT", "Aborting", ""), (15, "ABORT_QUEUED", "Aborting", ""), (16, "ABORT_STOPPED", "AbortingStopped", ""), (17, "WAIT_AI_AFTER_ABORT", "Aborting", ""), (18, "LOG_ABORT_QUEUED", "Aborting", ""), (19, "WAIT_TUP_TO_ABORT", "Aborting", ""), (20, "WAIT_SCAN_AI", "Scanning", ""), (21, "SCAN_STATE_USED", "Scanning", ""), (22, "SCAN_FIRST_STOPPED", "Scanning", ""), (23, "SCAN_CHECK_STOPPED", "Scanning", ""), (24, "SCAN_STOPPED", "ScanningStopped", ""), (25, "SCAN_RELEASE_STOPPED", "ScanningStopped", ""), (26, "SCAN_CLOSE_STOPPED", "ScanningStopped", ""), (27, "COPY_CLOSE_STOPPED", "ScanningStopped", ""), (28, "COPY_FIRST_STOPPED", "ScanningStopped", ""), (29, "COPY_STOPPED", "ScanningStopped", ""), (30, "SCAN_TUPKEY", "Scanning", ""), (31, "COPY_TUPKEY", "NodeRecoveryScanning", ""), (32, "TC_NOT_CONNECTED", "Idle", ""), (33, "PREPARED_RECEIVED_COMMIT", "Committing", ""), (34, "LOG_COMMIT_WRITTEN", "Committing", "")','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.transporters
SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`transporters` AS SELECT node_id, remote_node_id,  CASE connection_status  WHEN 0 THEN "CONNECTED"  WHEN 1 THEN "CONNECTING"  WHEN 2 THEN "DISCONNECTED"  WHEN 3 THEN "DISCONNECTING"  ELSE NULL  END AS status FROM `ndbinfo`.`ndb$transporters`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.logspaces
SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`logspaces` AS SELECT node_id,  CASE log_type  WHEN 0 THEN "REDO"  WHEN 1 THEN "DD-UNDO"  ELSE NULL  END AS log_type, log_id, log_part, total, used FROM `ndbinfo`.`ndb$logspaces`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.logbuffers
SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`logbuffers` AS SELECT node_id,  CASE log_type  WHEN 0 THEN "REDO"  WHEN 1 THEN "DD-UNDO"  ELSE "<unknown>"  END AS log_type, log_id, log_part, total, used FROM `ndbinfo`.`ndb$logbuffers`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.resources
SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`resources` AS SELECT node_id,  CASE resource_id  WHEN 0 THEN "RESERVED"  WHEN 1 THEN "DISK_OPERATIONS"  WHEN 2 THEN "DISK_RECORDS"  WHEN 3 THEN "DATA_MEMORY"  WHEN 4 THEN "JOBBUFFER"  WHEN 5 THEN "FILE_BUFFERS"  WHEN 6 THEN "TRANSPORTER_BUFFERS"  WHEN 7 THEN "DISK_PAGE_BUFFER"  WHEN 8 THEN "QUERY_MEMORY"  WHEN 9 THEN "SCHEMA_TRANS_MEMORY"  ELSE "<unknown>"  END AS resource_name, reserved, used, max FROM `ndbinfo`.`ndb$resources`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.counters
SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`counters` AS SELECT node_id, b.block_name, block_instance, counter_id, CASE counter_id  WHEN 1 THEN "ATTRINFO"  WHEN 2 THEN "TRANSACTIONS"  WHEN 3 THEN "COMMITS"  WHEN 4 THEN "READS"  WHEN 5 THEN "SIMPLE_READS"  WHEN 6 THEN "WRITES"  WHEN 7 THEN "ABORTS"  WHEN 8 THEN "TABLE_SCANS"  WHEN 9 THEN "RANGE_SCANS"  WHEN 10 THEN "OPERATIONS"  WHEN 11 THEN "READS_RECEIVED"  WHEN 12 THEN "LOCAL_READS_SENT"  WHEN 13 THEN "REMOTE_READS_SENT"  WHEN 14 THEN "READS_NOT_FOUND"  WHEN 15 THEN "TABLE_SCANS_RECEIVED"  WHEN 16 THEN "LOCAL_TABLE_SCANS_SENT"  WHEN 17 THEN "RANGE_SCANS_RECEIVED"  WHEN 18 THEN "LOCAL_RANGE_SCANS_SENT"  WHEN 19 THEN "REMOTE_RANGE_SCANS_SENT"  WHEN 20 THEN "SCAN_BATCHES_RETURNED"  WHEN 21 THEN "SCAN_ROWS_RETURNED"  WHEN 22 THEN "PRUNED_RANGE_SCANS_RECEIVED"  WHEN 23 THEN "CONST_PRUNED_RANGE_SCANS_RECEIVED"  WHEN 24 THEN "LOCAL_READS"  WHEN 25 THEN "LOCAL_WRITES"  ELSE "<unknown>"  END AS counter_name, val FROM `ndbinfo`.`ndb$counters` c LEFT JOIN `ndbinfo`.blocks b ON c.block_number = b.block_number','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.nodes
SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`nodes` AS SELECT node_id, uptime, CASE status  WHEN 0 THEN "NOTHING"  WHEN 1 THEN "CMVMI"  WHEN 2 THEN "STARTING"  WHEN 3 THEN "STARTED"  WHEN 4 THEN "SINGLEUSER"  WHEN 5 THEN "STOPPING_1"  WHEN 6 THEN "STOPPING_2"  WHEN 7 THEN "STOPPING_3"  WHEN 8 THEN "STOPPING_4"  ELSE "<unknown>"  END AS status, start_phase, config_generation FROM `ndbinfo`.`ndb$nodes`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.memoryusage
SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`memoryusage` AS SELECT node_id,  pool_name AS memory_type,  SUM(used*entry_size) AS used,  SUM(used) AS used_pages,  SUM(total*entry_size) AS total,  SUM(total) AS total_pages FROM `ndbinfo`.`ndb$pools` WHERE block_number IN (248, 254) AND   (pool_name = "Index memory" OR pool_name = "Data memory") GROUP BY node_id, memory_type','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.diskpagebuffer
SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`diskpagebuffer` AS SELECT node_id, block_instance, pages_written, pages_written_lcp, pages_read, log_waits, page_requests_direct_return, page_requests_wait_queue, page_requests_wait_io FROM `ndbinfo`.`ndb$diskpagebuffer`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.diskpagebuffer
SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`diskpagebuffer` AS SELECT node_id, block_instance, pages_written, pages_written_lcp, pages_read, log_waits, page_requests_direct_return, page_requests_wait_queue, page_requests_wait_io FROM `ndbinfo`.`ndb$diskpagebuffer`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.threadblocks
SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`threadblocks` AS SELECT t.node_id, t.thr_no, b.block_name, t.block_instance FROM `ndbinfo`.`ndb$threadblocks` t LEFT JOIN `ndbinfo`.blocks b ON t.block_number = b.block_number','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.threadstat
SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`threadstat` AS SELECT * from `ndbinfo`.`ndb$threadstat`','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.cluster_transactions
SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`cluster_transactions` AS SELECT t.node_id, t.block_instance, t.transid0 + (t.transid1 << 32) as transid, s.state_friendly_name as state,  t.c_ops as count_operations,  t.outstanding as outstanding_operations,  t.timer as inactive_seconds,  (t.apiref & 65535) as client_node_id,  (t.apiref >> 16) as client_block_ref FROM `ndbinfo`.`ndb$transactions` t LEFT JOIN `ndbinfo`.`ndb$dbtc_apiconnect_state` s        ON s.state_int_value = t.state','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.server_transactions
SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`server_transactions` AS SELECT map.mysql_connection_id, t.*FROM information_schema.ndb_transid_mysql_connection_map map JOIN `ndbinfo`.cluster_transactions t   ON (map.ndb_transid >> 32) = (t.transid >> 32)','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.cluster_operations
SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`cluster_operations` AS SELECT o.node_id, o.block_instance, o.transid0 + (o.transid1 << 32) as transid, case o.op  when 1 then "READ" when 2 then "READ-SH" when 3 then "READ-EX" when 4 then "INSERT" when 5 then "UPDATE" when 6 then "DELETE" when 7 then "WRITE" when 8 then "UNLOCK" when 9 then "REFRESH" when 257 then "SCAN" when 258 then "SCAN-SH" when 259 then "SCAN-EX" ELSE "<unknown>" END as operation_type,  s.state_friendly_name as state,  o.tableid,  o.fragmentid,  (o.apiref & 65535) as client_node_id,  (o.apiref >> 16) as client_block_ref,  (o.tcref & 65535) as tc_node_id,  ((o.tcref >> 16) & 511) as tc_block_no,  ((o.tcref >> (16 + 9)) & 127) as tc_block_instance FROM `ndbinfo`.`ndb$operations` o LEFT JOIN `ndbinfo`.`ndb$dblqh_tcconnect_state` s        ON s.state_int_value = o.state','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# ndbinfo.server_operations
SET @str=IF(@have_ndbinfo,'CREATE OR REPLACE DEFINER=`root@localhost` SQL SECURITY INVOKER VIEW `ndbinfo`.`server_operations` AS SELECT map.mysql_connection_id, o.* FROM `ndbinfo`.cluster_operations o JOIN information_schema.ndb_transid_mysql_connection_map map  ON (map.ndb_transid >> 32) = (o.transid >> 32)','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

# Finally turn off offline mode
SET @str=IF(@have_ndbinfo,'SET @@global.ndbinfo_offline=FALSE','SET @dummy = 0');
PREPARE stmt FROM @str;
EXECUTE stmt;
DROP PREPARE stmt;

