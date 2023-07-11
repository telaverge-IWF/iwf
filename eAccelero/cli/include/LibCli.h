/* ********************************-*-C-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/


#ifndef __LIBCLI_H__
#define __LIBCLI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "CommonStructure.h"

#define MAX_LOGIN_ATTEMPTS 5
#define ONE_HOUR 3600

#define CLI_OK          0
#define CLI_ERROR       -1
#define CLI_QUIT        -2
#define CLI_ERROR_ARG       -3
#define CLI_ERROR_MSG   -4

#define AUTH_USER_NOT_FOUND -1
#define AUTH_WRONG_PASSWORD -2

#define MAX_HISTORY     256

#define PRIVILEGE_UNPRIVILEGED  PRIVILEGE_OPERATOR
#define PRIVILEGE_PRIVILEGED    PRIVILEGE_ADMIN

#define LIBCLI_HAS_ENABLE   1

#define PRINT_PLAIN     0
#define PRINT_FILTERED      0x01
#define PRINT_BUFFERED      0x02

#define CLI_MAX_LINE_LENGTH     4096
#define CLI_MAX_LINE_WORDS      128
#define CLI_MODES_MAX       50

#define true    1
#define false   0

    enum cli_modes {
        MODE_ANY=-1,
        MODE_EXEC=0,
        MODE_CONFIG,        
        MODE_CONFIG_DRE,
        MODE_CONFIG_AVLMGR,
        MODE_CONFIG_REPMGR, 
        MODE_CONFIG_CMGR,
        MODE_CONFIG_DIABASE,    
        MODE_DIABASE_PTABLE,    
        MODE_DIABASE_REALMTABLE,        
        MODE_DIABASE_LOCALHOST,     
        MODE_PTABLE_PEER,
        MODE_ASF_GROUP_TABLE,    
        MODE_CONFIG_ERLBF,
        MODE_CONFIG_VIRTUAL_IP,  
        MODE_CONFIG_ADD_ERLBF_PEER,  
        MODE_CONFIG_MOD_ERLBF_PEER, 
        MODE_CONFIG_TRANSFORM,
        MODE_CONFIG_PEER,
        MODE_CONFIG_LOCALHOST,
        MODE_MODIFY_LOCALHOST,
        MODE_CONFIG_REALM,
        MODE_PEER_DICTIONARY,
        MODE_GENERAL_CONFIG,
        MODE_SCTP_CONFIG,
        MODE_TLS_CONFIG,
        MODE_CONFIG_STATIC_ROUTING,
        MODE_STATIC_PEER_CONFIG,
        MODE_CONFIG_SIGTRAN,
        MODE_CONFIG_SIGTRAN_M3UA,
        MODE_CONFIG_SIGTRAN_SCTP,
        MODE_CONFIG_LOCAL,
        MODE_CONFIG_LOCAL_PCSSN,
        MODE_CONFIG_LOCAL_GT,
        MODE_CONFIG_SCTP_PROFILE,
        MODE_CONFIG_ADD_SCTP_ENDPOINT,
        MODE_CONFIG_MODIFY_SCTP_ENDPOINT,
        MODE_CONFIG_ADD_ASSOCIATION,
        MODE_CONFIG_MODIFY_ASSOCIATION,
        MODE_CONFIG_ADD_ASSOCIATION_SET,
        MODE_CONFIG_MODIFY_ASSOCIATION_SET,
        MODE_CONFIG_DESTINATION,
        MODE_CONFIG_DESTINATION_PCSSN,
        MODE_CONFIG_DESTINATION_GT,
        MODE_CONFIG_REMOTEROUTE,
        MODE_CONFIG_IWF,
        MODE_TRANS_RULE_SS7,
        MODE_TRANS_RULE_DIAMETER,
        MODE_TRANS_RULE_HTTP,
        MODE_CONFIG_ADD_S6A_MAP,
        MODE_CONFIG_MODIFY_S6A_MAP,
        MODE_CONFIG_ADD_MAP_S6A,
        MODE_CONFIG_MODIFY_MAP_S6A,
        MODE_CONFIG_CAP_RO,
        MODE_CONFIG_CAP_RO_IDP,
        MODE_CONFIG_CAP_RO_IDP_SMS,
        MODE_CONFIG_CAP_PROTO,
        MODE_CONFIG_CAP_TIMERS,
        MODE_CONFIG_DCCA,
        MODE_CONFIG_FAILURE_HANDLING,
        MODE_CONFIG_DCCA_DESTINATION,
        MODE_CONFIG_CAP_RRB,
        MODE_CONFIG_RRB_CALL_SCENARIO,
        MODE_CONFIG_MO_CAP_V1,
        MODE_CONFIG_MO_CAP_V2,
        MODE_CONFIG_MT_CAP_V1,
        MODE_CONFIG_MT_CAP_V2,
        MODE_CONFIG_SMS_CAP_V3,
        MODE_IWF_GENERAL_CONFIG
    };

    struct unp {
        char username[MAX_NAME_LEN];
        unsigned char password[MAX_NAME_LEN];
        unsigned char encryptedPassword[MAX_NAME_LEN];
        unsigned char newPassword[MAX_NAME_LEN];
        char allowNewPassword;
        char verifyNewPassword;
        char setNewPassword;
        char passwordChanged;   
        int privilege;
    };

    struct cli_def {
        int completion_callback;
        struct cli_command *commands;
        struct cli_command *searchCmd;
        int (*auth_callback)(struct cli_def *,unsigned char *,unsigned char *);
        int (*adduser_callback)(struct cli_def *,unsigned char *, unsigned char *);
        int (*deleteuser_callback)(struct cli_def *,unsigned char *, unsigned char *);
        int (*modifyuser_callback)(struct cli_def *,unsigned char *, unsigned char *);   
        int (*regular_callback)(struct cli_def *cli);
        int (*enable_callback)(char *);
        char *banner;
        struct unp user;
        char *loginuser;
        char *enable_password;
        char *history[MAX_HISTORY];
        char showprompt;
        char *promptchar;
        char *hostname;
        char *modestring;
        int privilege;
        int mode;
        int state;
        struct cli_filter *filters;
        void (*print_callback)(struct cli_def *cli, char *string);
        FILE *client;
        /* internal buffers */
        void *conn;
        void *service;
        char *commandname;  // temporary buffer for cli_command_name() to prevent leak
        char *buffer;
        unsigned buf_size;
        struct timeval timeout_tm;
        unsigned int idle_timeout;
        int (*idle_timeout_callback)(struct cli_def *);
        time_t last_action;
        struct sockaddr_in server_addr;
        int recv_sock;
        int num_modes;
        int trackMode[10];
        SetConfigReq req;
        struct AvaMgrConfigPrimaryVirtualIpAddressReq virtualIps;
        char allow_exit;
        int delusr;
        int dict_count;
        int ssn_count;
        int max_attempts;
        int user_found;
        int local_transport_count;
        int localhost_mode;
        int has_capro_idp_config;
        int sgsn_addr_map_count;
        int ext_tele_srvc_count;
        int ext_bearer_srvc_count;
        int vplmnid_count;
        int dcca_feature_count;
        int dcca_endpoint_count;
        int sgsn_prefix_map_count;
        char *cmd;
    };

    struct cli_filter {
        int (*filter)(struct cli_def *cli, char *string, void *data);
        void *data;
        struct cli_filter *next;
    };

    struct cli_command {
        char *command;
        char *help;
        char *range_string;
        char *range_help;
        int (*callback)(struct cli_def *, char *, char **, int);
        unsigned int unique_len;
        int privilege;
        int mode;
        int cmdId;
        int optionalFlag;
        long long range[1][2];
        struct cli_command *next;
        struct cli_command *children;
        struct cli_command *parent;
    };

    struct thread_args {
        // struct cli_def *cli;
        int socket;
        int recv_port;
        int signalVal;
    };

    struct mess_args {
        void *ptr;  
    };

    struct _ClientData
    {
        pthread_t tid;
        struct cli_def *cli;
        int       inUse;
    };

    enum cli_states {
        STATE_LOGIN,
        STATE_PASSWORD,
        STATE_NORMAL,
        STATE_ENABLE_PASSWORD,
        STATE_ENABLE,
        STATE_ADD_USER,
        STATE_ADD_USER_PASSWORD,
        STATE_MOD_USER_PASSWORD,
        STATE_DELETE_USER_PASSWORD,
        STATE_EXIT_WITHOUT_SENT,
        STATE_DELETE_PEERGROUP,
        STATE_ACTIVATE_SWITCHOVER,
        STATE_USER_EXIT
    };

    struct cli_def *cli_init();
    int cli_done(struct cli_def *cli);
    struct cli_command *cli_register_command(struct cli_def *cli, struct cli_command *parent, char *command, int (*callback)(struct cli_def *, char *, char **, int), int privilege, int mode, char *help);
    int cli_unregister_command(struct cli_def *cli, char *command);
    int cli_run_command(struct cli_def *cli, char *command);
    //int cli_loop(struct cli_def *cli, int sockfd); 
    void* cli_loop(void *args);/*calsoft */

    int cli_file(struct cli_def *cli, FILE *fh, int privilege, int mode);
    void cli_set_auth_callback(struct cli_def *cli, int (*auth_callback)(struct cli_def *,unsigned char *, unsigned char *));
    void cli_set_adduser_callback(struct cli_def *cli, int (*adduser_callback)(struct cli_def *,unsigned char *,unsigned char *));
    void cli_set_deleteuser_callback(struct cli_def *cli, int (*deleteuser_callback)(struct cli_def *,unsigned char *,unsigned char *));
    void cli_set_modifyuser_callback(struct cli_def *cli, int (*modifyuser_callback)(struct cli_def *,unsigned char *,unsigned char *));
    void cli_set_enable_callback(struct cli_def *cli, int (*enable_callback)(char *));
    void cli_allow_user(struct cli_def *cli, char *username, char *password);
    void cli_allow_enable(struct cli_def *cli, char *password);
    void cli_deny_user(struct cli_def *cli, char *username);
    void cli_set_banner(struct cli_def *cli, char *banner);
    void cli_set_hostname(struct cli_def *cli, char *hostname);
    void cli_set_promptchar(struct cli_def *cli, char *promptchar);
    void cli_set_modestring(struct cli_def *cli, char *modestring);
    int cli_set_privilege(struct cli_def *cli, int privilege);
    int cli_set_configmode(struct cli_def *cli, int mode, char *config_desc);
    void cli_reprompt(struct cli_def *cli);
    void cli_regular(struct cli_def *cli, int (*callback)(struct cli_def *cli));
    void cli_regular_interval(struct cli_def *cli, int seconds);
    void cli_print(struct cli_def *cli, char *format, ...) __attribute__((format (printf, 2, 3)));
    void cli_bufprint(struct cli_def *cli, char *format, ...) __attribute__((format (printf, 2, 3)));
    void cli_vabufprint(struct cli_def *cli, char *format, va_list ap);
    void cli_error(struct cli_def *cli, char *format, ...) __attribute__((format (printf, 2, 3)));
    void cli_print_callback(struct cli_def *cli, void (*callback)(struct cli_def *, char *));
    void cli_free_history(struct cli_def *cli);
    void cli_set_idle_timeout(struct cli_def *cli, unsigned int seconds);
    void cli_set_idle_timeout_callback(struct cli_def *cli, unsigned int seconds, int (*callback)(struct cli_def *));
    extern int search_cmd_onId(struct cli_def *cli, struct cli_command *c, int cmdId);
    int cli_show_help(struct cli_def *cli, struct cli_command *c);
    extern int cli_track_configmode(struct cli_def *cli, int oldmode, int newMode, char actionFlag);
    int cli_validate_string(struct cli_def *cli, char *string);
    extern int dre_add_user(char *user,char *passwd,char *priv);
#ifdef __cplusplus
}
#endif

#endif
