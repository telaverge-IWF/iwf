#ifndef _REPL_ERRORS_H
#define _REPL_ERRORS_H

typedef enum{
    SUCCESS=0x00,
    REPL_AUTH_CONTINUE = 0x01,
    REPL_AUTH_ERROR = 0x02,
    /**
     * The server reported that this object is too big
     */
    REPL_E2BIG = 0x04,
    /**
     * The server is too busy to handle your request right now.
     * please back off and try again at a later time.
     */
    REPL_EBUSY = 0x05,
    /**
     * Internal error inside the library. You would have
     * to destroy the instance and create a new one to recover.
     */
    REPL_EINTERNAL = 0x06,
    /**
     * Invalid arguments specified.
     */
    REPL_EINVAL = 0x07,
    /**
     * The server is out of memory
     */
    REPL_ENOMEM = 0x08,
    /**
     * An invalid range specified
     */
    REPL_ERANGE = 0x09,
    /**
     * A generic error code.
     */
    REPL_ERROR = 0x0a,
    /**
     * The server tried to perform the requested operation, but failed
     * due to a temporary constraint. Retrying the operation may work.
     */
    REPL_ETMPFAIL = 0x0b,
    /**
     * The key already exists
     */
    REPL_KEY_EEXISTS = 0x0c,
    /**
     * The key does not exists
     */
    REPL_KEY_ENOENT = 0x0d,
    /**
     * Failed to open shared object
     */
    REPL_DLOPEN_FAILED = 0x0e,
    /**
     * Failed to locate the requested symbol in the shared object
     */
    REPL_DLSYM_FAILED = 0x0f,
    /**
     * A network related problem occured (name lookup, read/write/connect
     * etc)
     */
    REPL_NETWORK_ERROR = 0x10,
    /**
     * The server who received the request is not responsible for the
     * object anymore. (This happens during changes in the cluster
     * topology)
     */
    REPL_NOT_MY_VBUCKET = 0x11,
    /**
     * The object was not stored on the server
     */
    REPL_NOT_STORED = 0x12,
    /**
     * The server doesn't support the requested command.
     */
    REPL_NOT_SUPPORTED = 0x13,
    /**
     * The server doesn't know what that command is.
     */
    REPL_UNKNOWN_COMMAND = 0x14,
    /**
     * The server failed to resolve the requested hostname
     */
    REPL_UNKNOWN_HOST = 0x15,
    /**
     * There is something wrong with the datastream received from
     * the server
     */
    REPL_PROTOCOL_ERROR = 0x16,
    /**
     * The operation timed out
     */
    REPL_ETIMEDOUT = 0x17,
    /**
     * Failed to connect to the requested server
     */
    REPL_CONNECT_ERROR = 0x18,
    /**
     * The requested bucket does not exist
     */
    REPL_BUCKET_ENOENT = 0x19,
    /**
     * The client ran out of memory
     */
    REPL_CLIENT_ENOMEM = 0x1a,
    /**
     * The client encountered a temporary error (retry might resolve
     * the problem)
     */
    REPL_CLIENT_ETMPFAIL = 0x1b,
    /**
     * The instance of libcouchbase can't be used in this context
     */
    REPL_EBADHANDLE = 0x1c,
    /**
     * Unexpected usage of the server protocol
     */
    REPL_SERVER_BUG = 0x1d,
    /**
     * Libcouchbase cannot load the plugin because of version mismatch
     */
    REPL_PLUGIN_VERSION_MISMATCH = 0x1e,
    /**
     * The bootstrap hosts list use an invalid/unsupported format
     */
    REPL_INVALID_HOST_FORMAT = 0x1f,
    /**
     * Invalid character used in the path component of an URL
     */
    REPL_INVALID_CHAR = 0x20,

    /**
     * Too many nodes were requested for the observe criteria
     */
    REPL_DURABILITY_ETOOMANY = 0x21,

    /**
     * The same key was passed multiple times in a command list
     */
    REPL_DUPLICATE_COMMANDS = 0x22,

    /**
     * The config says that there is no server yet at that
     * position (-1 in the vbucket map)
     */
    REPL_NO_MATCHING_SERVER = 0x23,

    /**
     * An environment variable recognized by libcouchbase was detected,
     * but it contains an invalid value format
     */
    REPL_BAD_ENVIRONMENT = 0x24,

    /** An operation has not yet completed */
    REPL_BUSY = 0x25,

    /** Administrator account must not be used to access the data
     * in the bucket */
    REPL_INVALID_USERNAME = 0x26,

    /*All Replication connectors are in use*/
    REPL_ALL_CONNECTORS_INUSE = 0x27,

    /*No Keys are present ( for bulk fetch IWF) */
    REPL_NO_KEYS_FOR_BULK_FETCH = 0x28,



}ReplErrors;


#endif
