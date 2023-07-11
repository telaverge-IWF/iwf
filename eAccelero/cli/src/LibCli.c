
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
#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#endif

#define _GNU_SOURCE
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <memory.h>
#if !defined(__APPLE__) && !defined(__FreeBSD__)
#include <malloc.h>
#endif
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#ifndef WIN32
#include <regex.h>
#endif
#include "LibCli.h"
#include "cmd_utils.h"
#include "CliParser.h"
#include "CliRegister.h"
#include "CliCallback.h"
#include "CliStrings.h"
#define _MULTI_THREADED
#include <pthread.h>
#include "InterfaceDefs.h"

#ifdef __GNUC__
# define UNUSED(d) d __attribute__ ((unused))
#else
# define UNUSED(d) d
#endif


extern int regular_callback(struct cli_def *cli);
extern int check_enable(char *password);
extern int idle_timeout(struct cli_def *cli);

extern int check_auth(char *username, char *password);
extern int regular_callback(struct cli_def *cli);
extern int check_enable(char *password);
extern void cli_commands_init(struct cli_def *cli);
extern int dre_add_user();
extern int dre_verify_UserPasswd(unsigned char *user,unsigned char *passwd);
extern int verify_user_password(struct cli_def *cli,unsigned char *user,unsigned char *passwd);
extern int adduser(struct cli_def *cli,unsigned char *user,unsigned char *passwd);
extern int deleteuser(struct cli_def *cli,unsigned char *user,unsigned char *passwd);
extern int modifyuser(struct cli_def *cli,unsigned char *user,unsigned char *passwd);
extern void* cli_mess(void *args);
extern void* cli_mess2(void *args);
extern void clisend(void );
extern void cli_log(const char *funName, int lineNo, int loglevel, const char *dataString, ...);

#ifdef WIN32
/*
 * Stupid windows has multiple namespaces for filedescriptors, with different
 * read/write functions required for each ..
 */
int read(int fd, void *buf, unsigned int count) {
    return recv(fd, buf, count, 0);
}

int write(int fd,const void *buf, unsigned int count) {
    int iSendCount;

    iSendCount = send(fd, buf, count, 0);

    if(iSendCount < 0)
        close(fd);

    return iSendCount;
}

int vasprintf(char **strp, const char *fmt, va_list args) {
    int size;

    size = vsnprintf(NULL, 0, fmt, args);
    if ((*strp = malloc(size + 1)) == NULL) {
        return -1;
    }

    size = vsnprintf(*strp, size + 1, fmt, args);
    return size;
}

int asprintf(char **strp, const char *fmt, ...) {
    va_list args;
    int size;

    va_start(args, fmt);
    size = vasprintf(strp, fmt, args);

    va_end(args);
    return size;
}

int fprintf(FILE *stream, const char *fmt, ...) {
    va_list args;
    int size;
    char *buf;

    va_start(args, fmt);
    size = vasprintf(&buf, fmt, args);
    if (size < 0) {
        goto out;
    }
    size = write(stream->_file, buf, size);
    free(buf);

out:
    va_end(args);
    return size;
}

/*
 * Dummy definitions to allow compilation on Windows
 */
int regex_dummy() {return 0;};
#define regfree(...) regex_dummy()
#define regexec(...) regex_dummy()
#define regcomp(...) regex_dummy()
#define regex_t int
#define REG_NOSUB   0
#define REG_EXTENDED    0
#define REG_ICASE   0
#endif

//number of client threads
#define MAX_CLIENT_THREADS 1024
int NumThreads = 0;
pthread_mutex_t ClientCounterLock = PTHREAD_MUTEX_INITIALIZER;
struct _ClientData ClientThreadData[MAX_CLIENT_THREADS];

void IncrementThreadCount(struct cli_def *cli)
{
    pthread_mutex_lock(&ClientCounterLock);
    ClientThreadData[NumThreads].cli = cli; 
    ClientThreadData[NumThreads].inUse = 1; 
    ClientThreadData[NumThreads].tid = pthread_self();
    if (NumThreads < MAX_CLIENT_THREADS)
        NumThreads++;
    pthread_mutex_unlock(&ClientCounterLock);
}
void DecrementThreadCount()
{
    pthread_t tid = pthread_self();
    int i;
    struct cli_def *cli = NULL;
    pthread_mutex_lock(&ClientCounterLock);
    for (i = 0; i < NumThreads; i++)
    {
        if(ClientThreadData[i].tid == tid)
        {
            cli = ClientThreadData[i].cli;
            break;
        }
    }

    if (i == NumThreads)
    {
        pthread_mutex_unlock(&ClientCounterLock);
        return;
    }

    ClientThreadData[i].inUse = 0;
    ClientThreadData[i].cli = NULL;
    pthread_mutex_unlock(&ClientCounterLock);
}

#define RETVALUE(x) do{ DecrementThreadCount(); return x; }while(0)

struct cli_filter_cmds
{
    char *cmd;
    char *help;
};

/* free and zero (to avoid double-free) */
#define free_z(p) do { if (p) { free(p); (p) = 0; } } while (0)

int cli_match_filter_init(struct cli_def *cli, int argc, char **argv, struct cli_filter *filt);
int cli_range_filter_init(struct cli_def *cli, int argc, char **argv, struct cli_filter *filt);
int cli_count_filter_init(struct cli_def *cli, int argc, char **argv, struct cli_filter *filt);
int cli_match_filter(struct cli_def *cli, char *string, void *data);
int cli_range_filter(struct cli_def *cli, char *string, void *data);
int cli_count_filter(struct cli_def *cli, char *string, void *data);

static struct cli_filter_cmds filter_cmds[] =
{
    { "begin",   "Begin with lines that match" },
    { "between", "Between lines that match" },
    { "count",   "Count of lines"   },
    { "exclude", "Exclude lines that match" },
    { "include", "Include lines that match" },
    { "grep",    "Include lines that match regex (options: -v, -i, -e)" },
    { "egrep",   "Include lines that match extended regex" },
    { NULL, NULL}
};

char *cli_command_name(struct cli_def *cli, struct cli_command *command)
{
    char *name = cli->commandname;
    char *o;

    if (name) free(name);
    if (!(name = calloc(1, 1)))
        return NULL;

    while (command)
    {
        o = name;
        asprintf(&name, "%s%s%s", command->command, *o ? " " : "", o);
        command = command->parent;
        free(o);
    }
    cli->commandname = name;
    return name;
}

/*******************************************************************************************
 *
 * FUNCTION NAME        : search_cmd_onId
 * DESCRIPTION          : The command is searched based on command id which is passed as 3rd 
 *          argument to the function. The purpose of the function to get the pointer
 *          to a command to assign its mode and privilege. The limitaion here is that
 *                      it does not give a pointer if some previlage is assigned already.
 *
 * SIDE EFFECTS         : None
 *
 *********************************************************************************************/

int search_cmd_onId(struct cli_def *cli, struct cli_command *c, int cmdId)
{
    struct cli_command *p;
    for(p = c; p; p = p->next)
    {
        if( (p->cmdId == cmdId) && (p->privilege == 0))
        {
            cli->searchCmd = p;
            return 0;
        }
        if (p->children)
            search_cmd_onId(cli, p->children, cmdId);
    }

    return 0;
}


void cli_set_auth_callback(struct cli_def *cli, int (*auth_callback)(struct cli_def *cli, unsigned char *, unsigned char *))
{
    cli->auth_callback = auth_callback;
}

void cli_set_adduser_callback(struct cli_def *cli, int (*adduser_callback)(struct cli_def *cli,unsigned char *,unsigned char *))
{
    cli->adduser_callback = adduser_callback;
}

void cli_set_deleteuser_callback(struct cli_def *cli, int (*deleteuser_callback)(struct cli_def *cli,unsigned char *,unsigned char *))
{
    cli->deleteuser_callback = deleteuser_callback;
}
void cli_set_modifyuser_callback(struct cli_def *cli, int (*modifyuser_callback)(struct cli_def *cli,unsigned char *,unsigned char *))
{
    cli->modifyuser_callback = modifyuser_callback;
}

void cli_set_enable_callback(struct cli_def *cli, int (*enable_callback)(char *))
{
    cli->enable_callback = enable_callback;
}

void cli_allow_user(struct cli_def *cli, char *username, char *password)
{
#if 0
    struct unp *u, *n;
    char buf[256];
    if (!(n = malloc(sizeof(struct unp))))
    {
        fprintf(stderr, "Couldn't allocate memory for user: %s", strerror_r(errno,buf,256));
        return;
    }
    if (!(n->username = strdup(username)))
    {
        fprintf(stderr, "Couldn't allocate memory for username: %s", strerror_r(errno,buf,256));
        free(n);
        return;
    }
    if (!(n->password = strdup(password)))
    {
        fprintf(stderr, "Couldn't allocate memory for password: %s", strerror_r(errno,buf, 256));
        free(n->username);
        free(n);
        return;
    }
    n->next = NULL;

    if (!cli->users)
        cli->users = n;
    else
    {
        for (u = cli->users; u && u->next; u = u->next);
        if (u) u->next = n;
    }
#endif
}

void cli_allow_enable(struct cli_def *cli, char *password)
{
    char buf[256];
    free_z(cli->enable_password);
    if (!(cli->enable_password = strdup(password)))
    {
        fprintf(stderr, "Couldn't allocate memory for enable password: %s", strerror_r(errno,buf,256));
    }
}

void cli_deny_user(struct cli_def *cli, char *username)
{
#if 0
    struct unp *u, *p = NULL;
    if (!cli->users) return;
    for (u = cli->users; u; u = u->next)
    {
        if (strcmp(username, u->username) == 0)
        {
            if (p)
                p->next = u->next;
            else
                cli->users = u->next;
            free(u->username);
            free(u->password);
            free(u);
            break;
        }
        p = u;
    }
#endif
}

void cli_set_banner(struct cli_def *cli, char *banner)
{
    free_z(cli->banner);
    if (banner && *banner)
        cli->banner = strdup(banner);
}

void cli_set_hostname(struct cli_def *cli, char *hostname)
{
    free_z(cli->hostname);
    if (hostname && *hostname)
        cli->hostname = strdup(hostname);
}

void cli_set_promptchar(struct cli_def *cli, char *promptchar)
{
    free_z(cli->promptchar);
    cli->promptchar = strdup(promptchar);
}

static int cli_build_shortest(struct cli_def *cli, struct cli_command *commands)
{
    struct cli_command *c, *p;
    char *cp, *pp;
    int len;

    for (c = commands; c; c = c->next)
    {
        c->unique_len = strlen(c->command);
        if ((c->mode != MODE_ANY && c->mode != cli->mode) ||
                c->privilege > cli->privilege)
            continue;

        c->unique_len = 1;
        for (p = commands; p; p = p->next)
        {
            if (c == p)
                continue;

            if ((p->mode != MODE_ANY && p->mode != cli->mode) ||
                    p->privilege > cli->privilege)
                continue;

            cp = c->command;
            pp = p->command;
            len = 1;

            while (*cp && *pp && *cp++ == *pp++)
                len++;

            if (len > c->unique_len)
                c->unique_len = len;
        }

        if (c->children)
            cli_build_shortest(cli, c->children);
    }

    return CLI_OK;
}

int cli_set_privilege(struct cli_def *cli, int priv)
{
    //int old = cli->privilege;
    cli->privilege = priv;

    cli_set_promptchar(cli, cli->privilege == PRIVILEGE_UNPRIVILEGED ? ">" : "# ");
    cli_build_shortest(cli, cli->commands);

    return priv;
}

void cli_set_modestring(struct cli_def *cli, char *modestring)
{
    free_z(cli->modestring);
    if ((modestring) && (*modestring))
        cli->modestring = strdup(modestring);
}
/*******************************************************************************************
 *
 * FUNCTION NAME        : cli_track_configmode
 * DESCRIPTION          : This function should be called together with "cli_set_configmode" call 
 *                      to track the mode changes. This tracking of mode changes will be required
 *          by the "exit" command to return to previous mode. The second argument points
 *          to the previous mode and 3rd argument points to the present cli mode. When
 *          mode is changed, this function should be called with true as 4th argument
 *          and when called from exit command callback 4th argument should be false.
 *
 * SIDE EFFECTS         : Changes the cli mode prompt message when called with false as 4th 
 *                      argument
 *
 *********************************************************************************************/

int cli_track_configmode(struct cli_def *cli, int oldmode, int newMode, char actionFlag)
{
    int prevMode;
    CLI_DEBUG_LOG("cli->num_modes = %d",cli->num_modes);
    if(actionFlag == true)
    {
        if(oldmode != newMode)
        {
            //CLI_MODES_MAX = 10
            if(cli->num_modes < CLI_MODES_MAX)
            {
                cli->num_modes++;
                cli->trackMode[cli->num_modes - 1] = newMode;
            }
        }
        return cli->num_modes;
    }
    else
    {
        char string[MAX_RECORD_SIZE];
        int i;
        memset(string, 0, MAX_RECORD_SIZE);

        if(cli->num_modes > 1)
        {
            //num_modes carries the total number of modes passed at present.
            if(cli->trackMode[cli->num_modes - 1] == 0)
            {
                --cli->num_modes;
            }

            //The latest mode stored is equal to the present cli mode.
            if(cli->trackMode[cli->num_modes - 1] == cli->mode)
            {
                cli->trackMode[cli->num_modes - 1] = 0;
                --cli->num_modes;
            }
        }   
        prevMode = cli->trackMode[cli->num_modes - 1];

        //Revert the mode prompt string.
        if(cli->modestring)
        {
            strncpy(string + strlen(string), cli->modestring,MAX_RECORD_SIZE - 1);

            for(i = strlen(string); i > 0; i--)
                if(string[i] == '/')
                    break;
            if(i != 0)
            {
                string[i] = ')';
                string[i+ 1] = '\0';
            }
            else
                string[i] = '\0';

            cli_set_modestring(cli, string);
        }
        if(cli->num_modes == 0)
        {
        }
        return prevMode;
    }
}

int cli_set_configmode(struct cli_def *cli, int mode, char *config_desc)
{
    CLI_DEBUG_LOG(" Entered ");
    int old = cli->mode;
    CLI_DEBUG_LOG("oldmode = %d",old);
    CLI_DEBUG_LOG("newMode = %d",mode);

    cli->mode = mode;

    if (mode != old)
    {
        if (!cli->mode)
        {
            // Not config mode
            cli_set_modestring(cli, NULL);
        }
        else if (config_desc && *config_desc)
        {
            char string[MAX_RECORD_SIZE];
            memset(string, 0, MAX_RECORD_SIZE);
            if(cli->modestring)
            {
                strncpy(string + strlen(string), cli->modestring,MAX_RECORD_SIZE - 1);
                string[strlen(string) - 1] =  '/';
                strncat(&string[strlen(string)], config_desc, MAX_RECORD_SIZE - 1);
                strncat(&string[strlen(string)], ")", MAX_RECORD_SIZE - 1);
            }
            else
                snprintf(string + strlen(string), MAX_RECORD_SIZE, "%s", config_desc);


            cli_set_modestring(cli, string);
        }
        cli_build_shortest(cli, cli->commands);
    }

    CLI_DEBUG_LOG(" Exited ");
    return old;
}
//Registers a command into cli tree
struct cli_command *cli_register_command(struct cli_def *cli,
        struct cli_command *parent, char *command,
        int (*callback)(struct cli_def *cli, char *, char **, int),
        int privilege, int mode, char *help)
{
    struct cli_command *c, *p;

    if (!command) return NULL;
    if (!(c = calloc(sizeof(struct cli_command), 1))) return NULL;

    c->callback = callback;
    c->next = NULL;
    if (!(c->command = strdup(command)))
    {
        if(c != NULL)
        {
            free_z(c);
        }
        c = NULL;
        return NULL;
    }
    c->parent = parent;
    c->privilege = privilege;
    c->mode = mode;
    if (help)
        if (!(c->help = strdup(help)))
        {
            if(c != NULL)
                free_z(c);
            c = NULL;
            return NULL;
        }

    if (parent)
    {
        if (!parent->children)
        {
            parent->children = c;
        }
        else
        {
            for (p = parent->children; p && p->next; p = p->next);
            if (p) p->next = c;
        }
    }
    else
    {
        if (!cli->commands)
        {
            cli->commands = c;
        }
        else
        {
            for (p = cli->commands; p && p->next; p = p->next);
            if (p) p->next = c;
        }
    }
    return c;
}

static void cli_free_command(struct cli_command *cmd)
{
    struct cli_command *c,*p;

    for (c = cmd->children; c;)
    {
        p = c->next;
        cli_free_command(c);
        c = p;
    }

    free(cmd->command);
    if (cmd->help) free(cmd->help);
    free(cmd);
}

int cli_unregister_command(struct cli_def *cli, char *command)
{
    struct cli_command *c, *p = NULL;

    if (!command) return -1;
    if (!cli->commands) return CLI_OK;

    for (c = cli->commands; c; c = c->next)
    {
        if (strcmp(c->command, command) == 0)
        {
            if (p)
                p->next = c->next;
            else
                cli->commands = c->next;

            cli_free_command(c);
            return CLI_OK;
        }
        p = c;
    }

    return CLI_OK;
}

int cli_show_help(struct cli_def *cli, struct cli_command *c)
{
    struct cli_command *p;

    for (p = c; p; p = p->next)
    {
        if (p->command && p->callback && cli->privilege >= p->privilege &&
                (p->mode == cli->mode || p->mode == MODE_ANY))
        {
            cli_error(cli, "  %-20s %s", cli_command_name(cli, p), p->help ? : "");
        }

    }

    return CLI_OK;
}

int cli_int_idle_timeout(struct cli_def *cli)
{
    cli_print(cli, "Idle timeout");
    CLI_WARNING_LOG("* Idle timeout *");
    return CLI_QUIT;
}
struct cli_def *cli_init()
{
    struct cli_def *cli;
    int oldmode;

    if (!(cli = calloc(sizeof(struct cli_def), 1)))
        return 0;

    cli->buf_size = 1024;
    if (!(cli->buffer = calloc(cli->buf_size, 1)))
    {
        free_z(cli);
        return 0;
    }


    cli->privilege = cli->mode = -1;
    cli_set_privilege(cli, PRIVILEGE_UNPRIVILEGED);
    oldmode = cli_set_configmode(cli, MODE_EXEC, 0);
    cli_track_configmode(cli, oldmode, MODE_EXEC,true);

    // Default to 1 second timeout intervals
    cli->timeout_tm.tv_sec = 1;
    cli->timeout_tm.tv_usec = 0;

    // Set default idle timeout callback, but no timeout
    cli_set_idle_timeout_callback(cli, 0, cli_int_idle_timeout);
    return cli;
}

void cli_unregister_all(struct cli_def *cli, struct cli_command *command)
{
    struct cli_command *c, *p = NULL;

    if (!command) command = cli->commands;
    if (!command) return;

    for (c = command; c; )
    {
        p = c->next;

        // Unregister all child commands
        if (c->children)
            cli_unregister_all(cli, c->children);

        if (c->command) free(c->command);
        if (c->help) free(c->help);
        if (c->range_string) free(c->range_string);
        if (c->range_help) free(c->range_help);
        free(c);

        c = p;
    }
}

int cli_done(struct cli_def *cli)
{
    CLI_DEBUG_LOG("* Exit from CLI and freeing all memory *");
    if (!cli) return CLI_OK;
    cli_free_history(cli);

    /* free all commands */
    cli_unregister_all(cli, 0);
    if(cli->client)
        fclose(cli->client);

    if(cli->recv_sock)
        close(cli->recv_sock);
    free_z(cli->commandname);
    free_z(cli->modestring);
    free_z(cli->banner);
    free_z(cli->promptchar);
    free_z(cli->hostname);
    free_z(cli->buffer);
    free_z(cli->cmd);
    free_z(cli);

    return CLI_OK;
}

static int cli_add_history(struct cli_def *cli, char *cmd)
{
    int i;
    for (i = 0; i < MAX_HISTORY; i++)
    {
        if (!cli->history[i])
        {
            if (i == 0 || strcasecmp(cli->history[i-1], cmd))
                if (!(cli->history[i] = strdup(cmd)))
                    return CLI_ERROR;
            return CLI_OK;
        }
    }
    // No space found, drop one off the beginning of the list
    free(cli->history[0]);
    for (i = 0; i < MAX_HISTORY-1; i++)
        cli->history[i] = cli->history[i+1];
    if (!(cli->history[MAX_HISTORY - 1] = strdup(cmd)))
        return CLI_ERROR;
    return CLI_OK;
}

void cli_free_history(struct cli_def *cli)
{
    int i;
    for (i = 0; i < MAX_HISTORY; i++)
    {
        if (cli->history[i])
            free_z(cli->history[i]);
    }
}

static int cli_parse_line(char *line, char *words[], int max_words)
{
    int nwords = 0;
    char *p = line;
    char *word_start = 0;
    int inquote = 0;

    while (*p)
    {
        if (!isspace(*p))
        {
            word_start = p;
            break;
        }
        p++;
    }

    while (nwords < max_words - 1)
    {
        if (!*p || *p == inquote || (word_start && !inquote && (isspace(*p) || *p == '|')))
        {
            if (word_start)
            {
                int len = p - word_start;

                memcpy(words[nwords] = malloc(len + 1), word_start, len);
                words[nwords++][len] = 0;
            }

            if (!*p)
                break;

            if (inquote)
                p++; /* skip over trailing quote */

            inquote = 0;
            word_start = 0;
        }
        else if (*p == '"' || *p == '\'')
        {
            inquote = *p++;
            word_start = p;
        }
        else
        {
            if (!word_start)
            {
                if (*p == '|')
                {
                    if (!(words[nwords++] = strdup("|")))
                        return 0;
                }
                else if (!isspace(*p))
                    word_start = p;
            }

            p++;
        }
    }

    return nwords;
}

static char *join_words(int argc, char **argv)
{
    char *p;
    int len = 0;
    int i;

    for (i = 0; i < argc; i++)
    {
        if (i)
            len += 1;

        len += strlen(argv[i]);
    }

    p = malloc(len + 1);
    p[0] = 0;

    for (i = 0; i < argc; i++)
    {
        if (i)
            strncat(p, " ",1);

        strncat(p, argv[i],strlen(argv[i]));
    }

    return p;
}

static int cli_find_command(struct cli_def *cli, struct cli_command *commands, int num_words, char *words[], int start_word, int filters[])
{
    struct cli_command *c, *optionalCmd;
    int c_words = num_words;



    if (filters[0])
        c_words = filters[0];

    // Deal with ? for help
    if (!words[start_word])
        return CLI_ERROR;

    if (words[start_word][strlen(words[start_word]) - 1] == '?')
    {
        int l = strlen(words[start_word])-1;
        // printing one line space in telnet terminal before help strings
        cli_print(cli,"");
        for (c = commands; c; c = c->next)
        {
            /* This is for displaying commands on '?' based on the present mode  */
            if (strncasecmp(c->command, words[start_word], l) == 0
                    && (c->callback || c->children)
                    && cli->privilege >= c->privilege
                    && (c->mode == cli->mode || c->mode == MODE_ANY)){
                // check for modify, no and commit commands to show in working modes
                if(!strcmp(c->command,"commit")) {
                    if((cli->mode == MODE_CONFIG_PEER) || 
                            (cli->mode == MODE_CONFIG_LOCALHOST) || 
                            (cli->mode == MODE_MODIFY_LOCALHOST) || 
                            (cli->mode == MODE_CONFIG_REALM) || 
                            (cli->mode == MODE_STATIC_PEER_CONFIG) || 
                            (cli->mode == MODE_CONFIG_LOCAL) || 
                            (cli->mode == MODE_CONFIG_SCTP_PROFILE) || 
                            (cli->mode == MODE_CONFIG_ADD_SCTP_ENDPOINT) || 
                            (cli->mode == MODE_CONFIG_MODIFY_SCTP_ENDPOINT) || 
                            (cli->mode == MODE_CONFIG_ADD_ASSOCIATION) || 
                            (cli->mode == MODE_CONFIG_MODIFY_ASSOCIATION) || 
                            (cli->mode == MODE_CONFIG_ADD_ASSOCIATION_SET) || 
                            (cli->mode == MODE_CONFIG_MODIFY_ASSOCIATION_SET) || 
                            (cli->mode == MODE_CONFIG_DESTINATION) ||
                            (cli->mode == MODE_CONFIG_REMOTEROUTE) ||
                            (cli->mode == MODE_CONFIG_ADD_S6A_MAP) ||
                            (cli->mode == MODE_CONFIG_MODIFY_S6A_MAP) ||
                            (cli->mode == MODE_CONFIG_ADD_MAP_S6A) ||
                            (cli->mode == MODE_CONFIG_MODIFY_MAP_S6A) ||
                            (cli->mode == MODE_CONFIG_CAP_RO_IDP) ||
                            (cli->mode == MODE_CONFIG_CAP_RO_IDP_SMS) ||
                            (cli->mode == MODE_CONFIG_ADD_ERLBF_PEER) ||
                            (cli->mode == MODE_CONFIG_DCCA_DESTINATION) ||
                            (cli->mode == MODE_CONFIG_FAILURE_HANDLING) ||
                            (cli->mode == MODE_TRANS_RULE_SS7) ||
                            (cli->mode == MODE_TRANS_RULE_DIAMETER) ||
                            (cli->mode == MODE_CONFIG_RRB_CALL_SCENARIO) ||
                            (cli->mode == MODE_TRANS_RULE_HTTP))
                        cli_error(cli, "  %-40s %s", c->command, c->help ? : "");
                }
                else if((!strcmp(c->command,"modify") || !strcmp(c->command,"no"))) {
                    if((cli->mode == MODE_EXEC) ||
                            (cli->mode == MODE_DIABASE_PTABLE) ||
                            (cli->mode == MODE_DIABASE_REALMTABLE) ||
                            (cli->mode == MODE_DIABASE_LOCALHOST) ||
                            (cli->mode == MODE_CONFIG_ERLBF) ||
                            (cli->mode == MODE_CONFIG_STATIC_ROUTING) ||
                            (cli->mode == MODE_CONFIG_MOD_ERLBF_PEER) ||
                            (cli->mode == MODE_CONFIG_SIGTRAN) ||
                            (cli->mode == MODE_CONFIG_SIGTRAN_SCTP) ||
                            (cli->mode == MODE_CONFIG_SIGTRAN_M3UA) ||
                            (cli->mode == MODE_CONFIG_IWF) ||
                            (cli->mode == MODE_CONFIG_DCCA) ||
                            (cli->mode == MODE_CONFIG_CAP_RO) ||
                            (cli->mode == MODE_CONFIG_CAP_RRB) ||
                            (cli->mode == MODE_TLS_CONFIG))
                        cli_error(cli, "  %-40s %s", c->command, c->help ? : "");
                }
                else
                    cli_error(cli, "  %-40s %s", c->command, c->help ? : ""); 
                //If the child command is optional, then print all next optional commands and till next
                //mandatory command
                if(c->optionalFlag == true) {

                    optionalCmd = c;
                    while(optionalCmd->optionalFlag == true){

                        optionalCmd = optionalCmd->children;
                        cli_error(cli, "  %-40s %s", optionalCmd->command, optionalCmd->help ? : "");
                    }

                }
                if((strncasecmp(c->command, words[start_word], strlen(c->command)) == 0) &&
                        (words[start_word][strlen(c->command)] == '?'))
                {
                    if(c->range_string)
                        cli_error(cli, "    %-40s %s", c->range_string, c->range_help ? : "");
                }
            }
        }

        return CLI_OK;
    }

    for (c = commands; c; c = c->next)
    {
        if (cli->privilege < c->privilege)
            continue;

        if (strncasecmp(c->command, "WORD", strlen("WORD")) == 0)
            goto AGAIN;

        if (c->command[0] == '<')
            goto AGAIN;

        //Optional parameter handling. Skip if optional parameter is not entered.
        if( c && (c->optionalFlag == true)){
            if(words[start_word])
            {
                while(strncasecmp(c->command, words[start_word], strlen(words[start_word]))){
                    if(c->children && c->children->children)
                        c = c->children->children;
                }
            }
        }
        if (strncasecmp(c->command, words[start_word], c->unique_len))
            continue;

        if (strcasecmp(c->command, words[start_word]))
            continue;

AGAIN:
        /* This is for finding exact command and its callback in particular mode */
        if (c->mode == cli->mode || c->mode == MODE_ANY)
        {
            int rc = CLI_OK;
            int f;
            struct cli_filter **filt = &cli->filters;

            // Found a word!
            if (!c->children)
            {
                // Last word
                if (!c->callback)
                {
                    cli_error(cli, "No callback for \"%s\"", cli_command_name(cli, c));
                    CLI_ERROR_LOG("No callback for \"%s\"", cli_command_name(cli, c));
                    return CLI_ERROR;
                }
            }
            else
            {
                if (start_word == c_words - 1)
                {
                    if (c->callback)
                        goto CORRECT_CHECKS;

                    cli_error(cli, "\tIncomplete command");
                    CLI_ERROR_LOG("Incomplete command");
                    return CLI_ERROR;
                }
                rc = cli_find_command(cli, c->children, num_words, words, start_word + 1, filters);
                if (rc == CLI_ERROR_ARG)
                {
                    if (c->callback)
                    {
                        rc = CLI_OK;
                        goto CORRECT_CHECKS;
                    }
                    else
                    {
                        cli_error(cli, "\tInvalid %s \"%s\"", commands->parent ? "argument" : "command", words[start_word]);
                        CLI_ERROR_LOG("\tInvalid %s \"%s\"", commands->parent ? "argument" : "command", words[start_word]);
                    }
                }
                return rc;
            }

            if (!c->callback)
            {
                cli_error(cli, "Internal server error processing \"%s\"", cli_command_name(cli, c));
                CLI_CRITICAL_LOG("Internal server error processing \"%s\"", cli_command_name(cli, c));
                return CLI_ERROR;
            }

CORRECT_CHECKS:
            for (f = 0; rc == CLI_OK && filters[f]; f++)
            {
                int n = num_words;
                char **argv;
                int argc;
                int len;

                if (filters[f+1])
                    n = filters[f+1];

                if (filters[f] == n - 1)
                {
                    cli_error(cli, "Missing filter");
                    CLI_ERROR_LOG("Missing filter");
                    return CLI_ERROR;
                }

                argv = words + filters[f] + 1;
                argc = n - (filters[f] + 1);
                len = strlen(argv[0]);
                if (argv[argc - 1][strlen(argv[argc - 1]) - 1] == '?')
                {
                    if (argc == 1)
                    {
                        int i;

                        for(i = 0; filter_cmds[i].cmd; i++)
                        {
                            cli_error(cli, "  %-20s %s", filter_cmds[i].cmd, filter_cmds[i].help );
                        }
                    }
                    else
                    {
                        if (argv[0][0] != 'c') // count
                            cli_error(cli, "  WORD");

                        if (argc > 2 || argv[0][0] == 'c') // count
                            cli_error(cli, "  <cr>");
                    }

                    return CLI_OK;
                }

                if (argv[0][0] == 'b' && len < 3) // [beg]in, [bet]ween
                {
                    cli_error(cli, "Ambiguous filter \"%s\" (begin, between)", argv[0]);
                    CLI_ERROR_LOG("Ambiguous filter \"%s\" (begin, between)", argv[0]);
                    return CLI_ERROR;
                }
                *filt = calloc(sizeof(struct cli_filter), 1);

                if (!strncmp("include", argv[0], len) ||
                        !strncmp("exclude", argv[0], len) ||
                        !strncmp("grep", argv[0], len) ||
                        !strncmp("egrep", argv[0], len))
                    rc = cli_match_filter_init(cli, argc, argv, *filt);
                else if (!strncmp("begin", argv[0], len) ||
                        !strncmp("between", argv[0], len))
                    rc = cli_range_filter_init(cli, argc, argv, *filt);
                else if (!strncmp("count", argv[0], len))
                    rc = cli_count_filter_init(cli, argc, argv, *filt);
                else
                {
                    cli_error(cli, "Invalid filter \"%s\"", argv[0]);
                    CLI_ERROR_LOG("Invalid filter \"%s\"", argv[0]);
                    rc = CLI_ERROR;
                }

                if (rc == CLI_OK)
                {
                    filt = &(*filt)->next;
                }
                else
                {
                    free(*filt);
                    *filt = 0;
                }
            }

            if (rc == CLI_OK)
            {
                /*Added check for not invoking callback function when '?' after complete command. 
                  Callback function is called only when  'Enter' key is pressed */
                if(strcmp(words[c_words - 1], "?") != 0)
                    rc = c->callback(cli, cli_command_name(cli, c), words, c_words);
            }
            while (cli->filters)
            {
                struct cli_filter *filt = cli->filters;

                // call one last time to clean up
                filt->filter(cli, NULL, filt->data);
                cli->filters = filt->next;
                free(filt);
            }

            return rc;
        }
        else if (cli->mode > MODE_CONFIG && c->mode == MODE_CONFIG)
        {
            // command matched but from another mode,
            // remember it if we fail to find correct command
            //again = c;
        }
    }
    if (start_word == 0)
    {
        cli_error(cli, "\tInvalid %s \"%s\"", commands->parent ? "argument" : "command", words[start_word]);
        CLI_ERROR_LOG("Invalid %s \"%s\"", commands->parent ? "argument" : "command", words[start_word]);
    }

    return CLI_ERROR_ARG;
}

/*******************************************************************************
 * Function name         : command_validate
 * return                : validation result
 * arguments             : cli tree, user command arguments
 * Description           : This function is a generic validation logic for
 *                      validating all the user input command
 * *******************************************************************************/

int command_validate(struct cli_def *cli,char *command[])
{
    CLI_DEBUG_LOG(" Entered ");
    struct cli_command *c = NULL;
    struct cli_command  *p = NULL;
    struct cli_command  *temp = NULL;
    long long range_value = 0;
    int result = CLI_OK;
    int i = 0;
    int offset = 0;


    c = cli->commands;
    if (!command) return -1;

#if 0
    if(!strcmp(command[0],"no")){
        offset++;   
        result = CLI_OK;
        return result;
    }
#endif

    /* find the command in the  command from head node of command tree */
    for (c = cli->commands; c; c = c->next)
    {
        if (strcmp(c->command, command[0+offset]) == 0)
        {
            break;
        }
    }
    if(c){

        /*command is found, so continue */
    }else{
        cli_error(cli,"\n\tCommand not found");
        CLI_ERROR_LOG("Command not found");
        result = CLI_ERROR_MSG;

        return result;

    }
    /*find the command matches any of the children */
    for(p = c,i=(1+offset); p->children; i++)
    {
        int optionalFlag = FALSE;
        bool ip_fqdn = false;

        if(NULL == command[i]) {
            break;
        }
        
        if(!(strcasecmp(p->command,"imsi-prefix")))
        {
            p = p->children;
            if(strcmp(p->command,"WORD")==0)
            {
                CLI_DEBUG_LOG("IMSI-Prefix entered = %s ",command[i]);
                //check for valid fqdn
                char imsi[MAX_FIELD_NAME] = "",c;
                strncpy(imsi,command[i],MAX_FIELD_NAME - 1);
                if(strlen(imsi) == 1)
                {
                    //check for imsi * or single digit if length is 1
                    if((imsi[0] != '*') && !isdigit(imsi[0]))
                    {
                        cli_error(cli,"\n\tInvalid IMSI = %s",imsi);
                        CLI_ERROR_LOG("Invalid IMSI = %s",imsi);
                        return CLI_ERROR_MSG;
                    }
                }
                else
                {
                    int i = 0;
                    for(i=0;i<strlen(imsi);i++)
                    {    
                        c = imsi[i];
                        //check for the imsi having only numeric digits
                        if(!isdigit(c))
                        {    
                            cli_error(cli,"\n\tInvalid IMSI Prefix = %s",imsi);
                            CLI_ERROR_LOG("Invalid IMSI Prefix = %s",imsi);
                            return CLI_ERROR_MSG;
                        }
                    }
                }
            }
            continue;
        }
        
        if(!(strcasecmp(p->command,"list")))
        {
            p = p->children;
            if(strcmp(p->command,"WORD")==0)
            {
                CLI_DEBUG_LOG("ServiceKey List entered = %s ",command[i]);
                //check for valid fqdn
                char serviceKey[MAX_FIELD_NAME] = "",c;
                strncpy(serviceKey,command[i],MAX_FIELD_NAME - 1);
                if(strlen(serviceKey) == 1)
                {
                    if((serviceKey[0] != '*') && !isdigit(serviceKey[0]))
                    {
                        cli_error(cli,"\n\tInvalid List = %s",serviceKey);
                        CLI_ERROR_LOG("Invalid List = %s",serviceKey);
                        return CLI_ERROR_MSG;
                    }
                }
                else if(strlen(serviceKey) > 1)
                {
                    int i = 0; 
                    for(i=0;i<strlen(serviceKey);i++)
                    {    
                        c = serviceKey[i];
                        //check for the list having either number/comma(,)
                        if(!(isdigit(c) || c == ','))
                        {    
                            cli_error(cli,"\n\tInvalid List = %s",serviceKey);
                            CLI_ERROR_LOG("Invalid List = %s",serviceKey);
                            return CLI_ERROR_MSG;
                        }
                    }
                }
            }
            continue;
        }

        /* Validation for IP ADDRESS and FQDN */
        if((strcasecmp(p->command,"ip")==0) ||
                (strcasecmp(p->command,"public-ip")==0) ||
                (strcasecmp(p->command,"local-ip")==0) ||
                (strcasecmp(p->command,"ip-addr")==0) ||
                (strcmp(p->command, "fqdn")==0))
        {
            if(strcmp(p->command, "fqdn")==0) {
                // to avoid validation for IP format for configuring peer.
                ip_fqdn = true;
            }

            p = p->children;
            if(strcmp(p->command,"WORD")==0)
            {
                if(ip_fqdn)
                {    
                    CLI_DEBUG_LOG("fqdn-name entered = %s ",command[i]);
                    //check for valid fqdn
                    char ipaddr[MAX_HOST_NAME] = "",c;
                    strncpy(ipaddr,command[i],MAX_HOST_NAME - 1);
                    int res = CLI_OK;
                    if((res = cli_validate_string(cli,ipaddr)) != CLI_OK)
                        return CLI_ERROR_MSG;

                    c = ipaddr[0];
                    //check for the first letter in domain name, it should be alphabet or a number
                    if(isalnum(c))
                    {    
                        int i = 0; 
                        for(i=1;i<strlen(ipaddr);i++)
                        {    
                            c = ipaddr[i];
                            if(i == strlen(ipaddr) - 1) 
                            {    
                                //check for the last letter in domain name, it should be alphabet or a number
                                if(!isalnum(c))
                                {    
                                    cli_error(cli,"\n\tInvalid Fqdn = %s",ipaddr);
                                    CLI_ERROR_LOG("Invalid Fqdn = %s",ipaddr);
                                    return CLI_ERROR_MSG;
                                }    
                            }    
                            else
                            {
                                //check for the middle letters, either alphabet or number or special characters . and -
                                if(!(isalnum(c) || c == '.' || c == '-'))
                                {    
                                    cli_error(cli,"\n\tInvalid Fqdn = %s",ipaddr);
                                    CLI_ERROR_LOG("Invalid Fqdn = %s",ipaddr);
                                    return CLI_ERROR_MSG;
                                }
                            }
                        }   
                    }    
                    else 
                    {    
                        cli_error(cli,"\n\tInvalid Fqdn = %s",command[i]);
                        CLI_ERROR_LOG("Invalid Fqdn = %s",command[i]);
                        return CLI_ERROR_MSG;
                    }
                }
                else
                {
                    CLI_DEBUG_LOG("ip address entered = %s ",command[i]);
                    unsigned char buf[sizeof(struct in6_addr)];
                    int isIpv4,isIpv6;
                    isIpv4 = inet_pton(AF_INET, command[i], buf);
                    if (isIpv4 <= 0)
                    {
                        if (isIpv4 == 0)
                        {
                            isIpv6 = inet_pton(AF_INET6, command[i], buf);
                            if(isIpv6 <= 0)
                            {
                                if (isIpv6 == 0)
                                {
                                    cli_error(cli,"\n\tInvalid Ip Address = %s",command[i]);
                                    CLI_ERROR_LOG("Invalid Ip Address = %s",command[i]);
                                    return CLI_ERROR_MSG;
                                }
                                else {
                                    perror("inet_pton");
                                    CLI_ERROR_LOG("inet_pton Error");
                                }
                            }
                        }
                        else  {                                                           
                            perror("inet_pton");
                            CLI_ERROR_LOG("inet_pton Error");
                        }
                    }
                }
            }
            continue;
        }

        if((strcasecmp(p->command,"global-title-addr-info")==0))
        {
            p = p->children;

            if(strcmp(p->command,"WORD") == 0)
            {
                if(strlen(command[i]) > MAX_GT_ADDR_DIGITS)
                {
                    cli_error(cli,"\n\tError: Invalid length for Global Title Addr Info : %s, please enter only Numeric Digits between %d to %d.",command[i], MIN_GT_ADDR_DIGITS, MAX_GT_ADDR_DIGITS);
                    CLI_ERROR_LOG("Invalid length for Gloabl Title Addr Info : %s, please enter only Numeric Digits between %d to %d.",command[i], MIN_GT_ADDR_DIGITS, MAX_GT_ADDR_DIGITS);
                    return CLI_ERROR_MSG;
                }
                int j=0;
                for(j=0;j<strlen(command[i]);j++)
                {
                    //check for Numeric Digits
                    if(!isdigit(command[i][j]))
                    {
                        cli_error(cli,"\n\tError: Invalid Global Title Addr Info : %s, please enter only Numeric Digits.",command[i]);
                        CLI_ERROR_LOG("Invalid Gloabl Title Addr Info : %s, please enter only Numeric Digits.",command[i]);
                        return CLI_ERROR_MSG;
                    }
                }
            }
            continue;
        }
    
        if((strcasecmp(p->command,"host")==0) ||
                (strcasecmp(p->command,"dest-host")==0) ||
                (strcasecmp(p->command,"to-peer")==0) ||
                (strcasecmp(p->command,"to-dest")==0) ||
                (strcmp(p->command, "dest-realm")==0) ||
                (strcmp(p->command, "realm")==0))
        {
            p = p->children;

            if(strcmp(p->command,"WORD") == 0)
            {
                char ValuebyUser[MAX_HOST_NAME] = "",c;
                strncpy(ValuebyUser,command[i],MAX_HOST_NAME - 1);
                int res = CLI_OK;
                if((res = cli_validate_string(cli,ValuebyUser)) != CLI_OK)
                    return CLI_ERROR_MSG;

                c = ValuebyUser[0];
                if(isalpha(c))
                {
                    int i = 0; 
                    for(i=1;i<strlen(ValuebyUser);i++)
                    {    
                        c = ValuebyUser[i];
                        //check for the middle letters, either alphabet or number or special characters . - @ * - 
                        if(!(isalnum(c) || c == '.' || c == '-' || c == '@' || c == '*' || c == '_'))
                        {    
                            cli_error(cli,"\n\tInvalid String = %s",ValuebyUser);
                            CLI_ERROR_LOG("Invalid String = %s",ValuebyUser);
                            return CLI_ERROR_MSG;
                        }    
                    }    
                }
                else
                {
                    cli_error(cli,"\n\tInvalid String = %s",ValuebyUser);
                    CLI_ERROR_LOG("Invalid String = %s",ValuebyUser);
                    return CLI_ERROR_MSG;
                }
                continue;
            }
        }

        p = p->children;
        if(strcmp(p->command,"WORD") == 0)
        {
            char ValuebyUser[MAX_HOST_NAME] = "";
            strncpy(ValuebyUser,command[i],MAX_HOST_NAME - 1);
            int res = CLI_OK;
            if((res = cli_validate_string(cli,ValuebyUser)) != CLI_OK)
                return CLI_ERROR_MSG;
            continue;
        }

        result = CLI_ERROR;
        temp = p;
        for(;p;p = p->next)
        {
            if(strcmp(p->command,command[i]) == 0)
            {
                result = CLI_OK;
                break;
            }else if(p->optionalFlag == TRUE){
                result = CLI_OK;
                p = p->children;
                i--;
                //printf("Optional parameter\n");
                optionalFlag = TRUE; 
                break;
            }
        }
        if(optionalFlag == TRUE){
            continue;
        }


        if(!p){
            p = temp;
#if 0
            if( p && (p->optionalFlag == true)){
                if(command[i])
                {
                    while(strncasecmp(p->command, command[i], strlen(command[i]))){
                        if(p->children && p->children->children)
                            p = p->children->children;
                    }
                }
            }
#endif 
            for(;p;p= p->next)
            {
                if(p->range_string  != NULL)
                {
                    result = CLI_OK;
                    break;
                }
            }

            if(p){

                if(p->range_string != NULL)
                {
                    int k;
                    for(k=0;command[i][k] != '\0'; k++)
                    {

                        if(isdigit(command[i][k]) == 0) {
                            CLI_ERROR_LOG("Error: Input not a number");
                            cli_error(cli,"\n\tError: Input not a number");
                            return  CLI_ERROR_MSG;
                        }
                    }
                    if(result == CLI_ERROR || result == CLI_ERROR_MSG) {
                        break;
                    }
                    range_value = atoll(command[i]);
                    /* validate if the input value is withing the range */
                    /*specific case for vendor-id range(check for min value 0)*/
                    if((strcmp(p->command,"<0-999999999>")==0) || 
                            (strcmp(p->command,"<0-99999999999999999999>")==0) ||
                            (strcmp(p->command,"<0-15>")==0) || 
                            (strcmp(p->command,"<0-6>")==0) ||
                            (strcmp(p->command,"<0-5>")==0) ||
                            (strcmp(p->command,"<0-7>")==0) ||
                            (strcmp(p->command,"<0-50>")==0) ||
                            (strcmp(p->command,"<0-100>")==0) ||
                            (strcmp(p->command,"<0-300>")==0) ||
                            (strcmp(p->command,"<0-255>")==0) ||
                            (strcmp(p->command,"<0-30>")==0) ||
                            (strcmp(p->command,"<0-65535>")==0) ||
                            (strcmp(p->command,"<0-100000>")==0) ||
                            (strcmp(p->command,"<0-2147483647>")==0) ||
                            (strcmp(p->command,"<0-500>")==0) ||
                            (strcmp(p->command,"<0-127>")==0))
                    {
                        if(range_value >= p->range[0][0] && range_value <= p->range[0][1])
                        {
                            continue;

                        }else {
                            cli_error(cli,"\n\tValue out of Range : %s",command[i]);
                            CLI_ERROR_LOG("Value out of Range : %s\n",command[i]);
                            return CLI_ERROR_MSG;

                        }
                    }
                    else
                    { 
                        // range check for port numbers 
                        if(strcmp(p->command,"<1024-65535>")==0)
                            p->range[0][0] = 1023;
                        // range check for fields starting from 1 
                        if(strcmp(p->command,"<1-65535>")==0 ||
                                strcmp(p->command,"<1-50>")==0 ||
                                strcmp(p->command,"<1-100>")==0 ||
                                strcmp(p->command,"<1-10000000000>")==0 ||
                                strcmp(p->command,"<1-4294967295>")==0)
                            p->range[0][0] = 0;
                        //range check for watch-dog timer
                        if(strcmp(p->command,"<6-65535>")==0)
                            p->range[0][0] = 5;
                        if(range_value > p->range[0][0] && range_value <= p->range[0][1])
                        {
                            continue;

                        }else {
                            cli_error(cli,"\n\tValue out of Range : %s",command[i]);
                            CLI_ERROR_LOG("Value out of Range : %s",command[i]);
                            return CLI_ERROR_MSG;
                        }
                    }

                }
            }
        }

        if(!p) 
        {
            result = CLI_ERROR;
            break;
        }

    }
    if(p){
        if(p->children && 
                !p->children->optionalFlag){
            result = CLI_ERROR_MSG;
            // check for modify and no commands to print invalid command if not used otherwise incomplete command if not fully given depending on mode. 
            if((!strcmp(p->command,"modify") || !strcmp(p->command,"no"))) {
                if((cli->mode == MODE_EXEC) ||
                        (cli->mode == MODE_DIABASE_PTABLE) ||
                        (cli->mode == MODE_DIABASE_REALMTABLE) ||
                        (cli->mode == MODE_DIABASE_LOCALHOST) ||
                        (cli->mode == MODE_CONFIG_ERLBF) ||
                        (cli->mode == MODE_CONFIG_STATIC_ROUTING) ||
                        (cli->mode == MODE_CONFIG_MOD_ERLBF_PEER) ||
                        (cli->mode == MODE_CONFIG_SIGTRAN) ||
                        (cli->mode == MODE_CONFIG_SIGTRAN_SCTP) ||
                        (cli->mode == MODE_CONFIG_SIGTRAN_M3UA) ||
                        (cli->mode == MODE_CONFIG_IWF) ||
                        (cli->mode == MODE_CONFIG_DCCA) ||
                        (cli->mode == MODE_CONFIG_CAP_RO) ||
                        (cli->mode == MODE_CONFIG_CAP_RRB) ||
                        (cli->mode == MODE_TLS_CONFIG)) {
                    cli_error(cli,"\n\tIncomplete Command");
                    CLI_ERROR_LOG("Incomplete Command");
                }
                else
                {
                    cli_error(cli,"\n\tInvalid Command");
                    CLI_ERROR_LOG("Invalid Command");
                }
            }
            else {
                cli_error(cli,"\n\tIncomplete Command");
                CLI_ERROR_LOG("Incomplete Command");
            }
        }
        else{
            if(command[i]) 
            {
                cli_error(cli, "\n\tInvalid Parameter: %s", command[i]);
                CLI_ERROR_LOG("Invalid Parameter = %s",command[i]);
                result = CLI_ERROR_MSG;
            }
        }
    }
    CLI_DEBUG_LOG(" Exited ");
    return result;

}

int cli_run_command(struct cli_def *cli, char *command)
{
    CLI_DEBUG_LOG(" Entered ");
    int r;
    unsigned int num_words, i, f;
    char *words[CLI_MAX_LINE_WORDS] = {0};
    int filters[CLI_MAX_LINE_WORDS] = {0};
    int result;
    int help_flag = 0;

    if (!command) return CLI_ERROR;
    while (isspace(*command))
        command++;

    if (!*command) return CLI_OK;

    num_words = cli_parse_line(command, words, CLI_MAX_LINE_WORDS);
    for (i = f = 0; i < num_words && f < CLI_MAX_LINE_WORDS - 1; i++)
    {
        if (words[i][0] == '|')
            filters[f++] = i;
    }
    for(i=0;i <num_words; i++) {
        if(words[i][0] == '?') {
            help_flag = 1;
            break;
        }

    }

    if(help_flag || (command[0] == 'q')) {
    }else{
        result = command_validate(cli,words);
        if(result == 0) {
        }else{
            if(result == CLI_ERROR)
            {
                cli_error(cli,"\n\tInvalid command");
                CLI_ERROR_LOG("Invalid command");
            }
            for (i = 0; i < num_words; i++)
            {
                free(words[i]);
            }
            return CLI_ERROR;

        }
    }

    filters[f] = 0;

    if (num_words)
        r = cli_find_command(cli, cli->commands, num_words, words, 0, filters);
    else
        r = CLI_ERROR;


    for (i = 0; i < num_words; i++)
        free(words[i]);

    if (r == CLI_QUIT)
        return r;

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

static int cli_get_completions(struct cli_def *cli, char *command, char **completions, int max_completions)
{
    struct cli_command *c;
    struct cli_command *n;
    int num_words, i, k=0;
    char *words[CLI_MAX_LINE_WORDS] = {0};
    int filter = 0;
    int wordflag = 0, j = 0;


    if (!command) return 0;
    while (isspace(*command))
        command++;

    num_words = cli_parse_line(command, words, sizeof(words)/sizeof(words[0]));


    if (!command[0] || command[strlen(command)-1] == ' ')
        num_words++;

    if (!num_words)
        return 0;

    for (i = 0; i < num_words; i++)
    {
        if (words[i] && words[i][0] == '|')
            filter = i;
    }

    if (filter) // complete filters
    {
        unsigned len = 0;

        if (filter < num_words - 1) // filter already completed
        {
            for (i = 0; i < num_words; i++)
                free_z(words[i]);
            return 0;
        }

        if (filter == num_words - 1)
            len = strlen(words[num_words-1]);

        for (i = 0; filter_cmds[i].cmd && k < max_completions; i++)
            if (!len || (len < strlen(filter_cmds[i].cmd)
                        && !strncmp(filter_cmds[i].cmd, words[num_words - 1], len)))
                completions[k++] = filter_cmds[i].cmd;
        completions[k] = NULL;
        for (i = 0; i < num_words; i++)
            free_z(words[i]);
        return k;
    }
    /* below code added for debugging purpose */
    i = 0;

    //#pragma OPTIMIZE OFF
    for (c = cli->commands; c && i < num_words && k < max_completions; c = n)
    {
        n = c->next;

        if (cli->privilege < c->privilege)
            continue;

        if (c->mode != cli->mode && c->mode != MODE_ANY)
            continue;

        //User input string in place of command "WORD"
USER_WORD:
        if(strncasecmp(c->command, USER_INPUT_IND, strlen(USER_INPUT_IND)) == 0)
        {

            if(!(words[i]))
            {
                j = 1;
            }
            else
            {
                if(n)
                {
                    c = n;
                    n = n->next;
                    i++;
                    wordflag = 0;

                    if(words[i] && strncasecmp(c->command, words[i], strlen(words[i])))
                        continue;

                    if(i < num_words - 1)
                    {
                        n = c->children;
                        i++;
                        continue;
                    }

                    completions[k++] = c->command;
                }
                j = 0;
            }
            if(n)
                n = n->next;
            else
            {
                n = c->children;
                i++;
                wordflag = 0;
                continue;
            }
            wordflag = 1;

            continue;
        }

        //User input number in place of command range "<...>"
        if(c->command[0] == '<')
        {

            if(!(words[i]))
            {
                j = 1;
            }
            else
            {
                if(n)
                {
                    c = n;

                    if(strncasecmp(c->command, USER_INPUT_IND, strlen(USER_INPUT_IND)) != 0){
                        n = n->next;
                        i++;
                        wordflag = 0;

                        if(words[i] && strncasecmp(c->command, words[i], strlen(words[i])))
                            continue;

                        if(i < num_words - 1)
                        {
                            n = c->children;
                            i++;
                            continue;
                        }

                        completions[k++] = c->command;
                    }
                    else
                    {
                        i++;
                        n = c->next;
                        goto USER_WORD;
                    }
                }
                j = 0;
            }
            if(n)
                n = n->next;
            else
            {
                n = c->children;
                i++;
                wordflag = 0;
                continue;
            }
            wordflag = 1;

            continue;
        }
        if((words[i] && strncasecmp(c->command, words[i], strlen(words[i]))) && (wordflag == 0))
            continue;

        if((i < num_words - 1) && (wordflag == 0))

        {
            if (strlen(words[i]) < c->unique_len)
                continue;

            n = c->children;
            i++;
            //Optional commands handling for tab completions
            if( n && (n->optionalFlag == true))
            {
                if(words[i])
                {
                    while(strncasecmp(n->command, words[i], strlen(words[i]))){
                        if(n->children && n->children->children)
                            n = n->children->children;
                        // break the while loop if child is not there in the tree for optional parameters
                        else if(!n->children || !n->children->children)
                            break;
                    }
                }
            }
            continue;
        }
        //Copy the next options for tab completions
        if(j == 0)
        {
            completions[k++] = c->command;
            //Optional parameters
            if(c->optionalFlag == true)
            {
                if(c->children && c->children->children)
                    n = c->children->children;
            }
        }

    }
    //#pragma OPTIMIZE ON
    for (i = 0; i < num_words; i++)
            free_z(words[i]);
    return k;
}

static void cli_clear_line(int sockfd, char *cmd, int l, int cursor)
{
    int i;
    if (cursor < l) for (i = 0; i < (l - cursor); i++) write(sockfd, " ", 1);
    for (i = 0; i < l; i++) cmd[i] = '\b';
    for (; i < l * 2; i++) cmd[i] = ' ';
    for (; i < l * 3; i++) cmd[i] = '\b';
    write(sockfd, cmd, i);
    memset(cmd, 0, i);
    l = cursor = 0;
}

void cli_reprompt(struct cli_def *cli)
{
    if (!cli) return;
    cli->showprompt = 1;
}

void cli_regular(struct cli_def *cli, int (*callback)(struct cli_def *cli))
{
    if (!cli) return;
    cli->regular_callback = callback;
}

void cli_regular_interval(struct cli_def *cli, int seconds)
{
    if (seconds < 1) seconds = 1;
    cli->timeout_tm.tv_sec = seconds;
    cli->timeout_tm.tv_usec = 0;
}

#define DES_PREFIX "{crypt}"        /* to distinguish clear text from DES crypted */
#define MD5_PREFIX "$1$"
#if 0
static int pass_matches(char *pass, char *try)
{
    int des;
    if ((des = !strncasecmp(pass, DES_PREFIX, sizeof(DES_PREFIX)-1)))
        pass += sizeof(DES_PREFIX)-1;

#ifndef WIN32
    /*
     * TODO - find a small crypt(3) function for use on windows
     */
    if (des || !strncmp(pass, MD5_PREFIX, sizeof(MD5_PREFIX)-1))
        try = crypt(try, pass);
#endif

    return !strcmp(pass, try);
}
#endif
#define CTRL(c) (c - '@')

static int show_prompt(struct cli_def *cli, int sockfd)
{
    int len = 0;

    if (cli->hostname)
        len += write(sockfd, cli->hostname, strlen(cli->hostname));

    if (cli->modestring)
        len += write(sockfd, cli->modestring, strlen(cli->modestring));

    return len + write(sockfd, cli->promptchar, strlen(cli->promptchar));
}

int create_sock(struct cli_def *cli,int port)
{

    int sock;

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket");
    }

    cli->server_addr.sin_family = AF_INET;
    cli->server_addr.sin_port = port;
    cli->server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(cli->server_addr.sin_zero),8);

    cli->recv_sock = sock;

    if (bind(sock,(struct sockaddr *)&cli->server_addr,
                sizeof(struct sockaddr)) == -1)
    {
        perror("Bind");
    }
    return 0;
}

void* cli_loop(void *args)
{
    unsigned char c;
    int n, l, oldl = 0, is_telnet_option = 0, skip = 0, esc = 0;
    int cursor = 0, insertmode = 1;
    char *cmd = NULL, *oldcmd = 0;
    char *username = NULL, *password = NULL;
    char *negotiate =
        "\xFF\xFB\x03"
        "\xFF\xFB\x01"
        "\xFF\xFD\x03"
        "\xFF\xFD\x01";

    struct cli_def *cli;
    int sockfd;
    struct thread_args *arg;
    char hostname[MAX_HEADER_LEN];
    char promptName[MAX_HEADER_LEN];
    int loginAttempts=0;
    int oldmode;
    arg = (struct thread_args *) args;
    /* Initialization done seperately within a thread */
    cli = cli_init();
    //Increment the NumThreads for this new thread
    IncrementThreadCount(cli);


    //cli_set_banner(cli, "CLI test environment");


    gethostname(hostname,sizeof(hostname));
    cli_set_hostname(cli, hostname);
    cli_regular(cli, regular_callback);
    cli_regular_interval(cli, 5); // Defaults to 1 second
    cli_set_idle_timeout_callback(cli, ONE_HOUR, idle_timeout); // 60 second idle timeout

    //Cli commands tree generation
    cli_commands_init(cli);

    /*create UDP socket to receive data from MESS   */
    create_sock(cli,arg->recv_port);

    /*setting call back functions */
    cli_set_auth_callback(cli, verify_user_password);
    cli_set_adduser_callback(cli, adduser);
    cli_set_deleteuser_callback(cli, deleteuser);
    cli_set_modifyuser_callback(cli, modifyuser);

    //cli_set_enable_callback(cli, check_enable);

    sockfd = arg->socket;

    cli_build_shortest(cli, cli->commands);
    cli->state = STATE_LOGIN;

    cli_free_history(cli);
    write(sockfd, negotiate, strlen(negotiate));

    if ((cmd = malloc(CLI_MAX_LINE_LENGTH)) == NULL)
        RETVALUE(NULL);
    cli->cmd = cmd;
#ifdef WIN32
    /*
     * OMG, HACK
     */
    if (!(cli->client = fdopen(_open_osfhandle(sockfd,0), "w+")))
        RETVALUE(NULL);
    cli->client->_file = sockfd;
#else
    if (!(cli->client = fdopen(sockfd, "w+")))
        RETVALUE(NULL);
#endif

    setbuf(cli->client, NULL);
    if (cli->banner)
        cli_error(cli, "%s", cli->banner);

    // Set the last action now so we don't time immediately
    if (cli->idle_timeout)
        time(&cli->last_action);

    /* start off in unprivileged mode */
    cli_set_privilege(cli, PRIVILEGE_PRIVILEGED);
    oldmode = cli_set_configmode(cli, MODE_EXEC, NULL);
    cli_track_configmode(cli, oldmode, MODE_EXEC, true);

#if 0
    /* no auth required? */
    if (!cli->users && !cli->auth_callback)
        cli->state = STATE_NORMAL;
#endif

    if(arg->signalVal == SIGTERM)
    {
        CLI_ERROR_LOG("arg->signalVal = %d",arg->signalVal);
        /*free cli structure */
        cli_free_history(cli);
        cli_done(cli); 
        free_z(username);
        free_z(password);
        pthread_exit(NULL);
    }

    while (1)
    {
        signed int in_history = 0;
        int lastchar = 0;
        struct timeval tm;

        cli->showprompt = 1;

        if (oldcmd)
        {
            l = cursor = oldl;
            oldcmd[l] = 0;
            cli->showprompt = 1;
            oldcmd = NULL;
            oldl = 0;
        }
        else
        {
            memset(cmd, 0, CLI_MAX_LINE_LENGTH);
            l = 0;
            cursor = 0;
        }

        memcpy(&tm, &cli->timeout_tm, sizeof(tm));

        while (1)
        {
            int sr;
            fd_set r;
            if (cli->showprompt)
            {
                if (cli->state != STATE_PASSWORD && cli->state != STATE_ENABLE_PASSWORD)
                    write(sockfd, "\r\n", 2);
                CLI_DEBUG_LOG("cli->state = %d",cli->state);
                switch (cli->state)
                {
                    case STATE_LOGIN:
                        write(sockfd, "Username: ", strlen("Username: "));
                        break;

                    case STATE_PASSWORD:
                        write(sockfd, "Password: ", strlen("Password: "));
                        break;

                    case STATE_NORMAL:
                    case STATE_ENABLE:
                        show_prompt(cli, sockfd);
                        write(sockfd, cmd, l);
                        if (cursor < l)
                        {
                            int n = l - cursor;
                            while (n--)
                                write(sockfd, "\b", 1);
                        }
                        break;

                    case STATE_ENABLE_PASSWORD:
                        write(sockfd, "Password: ", strlen("Password: "));
                        break;
                    case STATE_ADD_USER:
                        show_prompt(cli, sockfd);
                        write(sockfd, cmd, l);
                        if (cursor < l)
                        {
                            int n = l - cursor;
                            while (n--)
                                write(sockfd, "\b", 1);
                        }
                        break;
                    case  STATE_ADD_USER_PASSWORD:
                        if(cli->user.verifyNewPassword == 'y') {
                            write(sockfd, "Confirm Password: ", strlen("Confirm Password: "));
                        }
                        else {
                            cli_print(cli,"\tNOTE: Password length should be between 6 to 16 characters.\n");
                            write(sockfd, "Password: ", strlen("Password: "));
                        }
                        break;
                    case  STATE_MOD_USER_PASSWORD:
                        if(cli->user.allowNewPassword == 'y') 
                        {
                            cli_print(cli,"\tNOTE: Password length should be between 6 to 16 characters.\n");
                            write(sockfd, "New Password: ", strlen("New Password: "));
                        }
                        else if(cli->user.verifyNewPassword == 'y') {
                            write(sockfd, "Confirm Password: ", strlen("Confirm Password: "));
                        }
                        else {
                            write(sockfd, "Old Password: ", strlen("Old Password: "));
                        }

                        break;
                    case STATE_DELETE_USER_PASSWORD:
                        write(sockfd, "Admin Password: ", strlen("Admin Password: "));
                        break;
                    case STATE_EXIT_WITHOUT_SENT:
                        cli_print(cli,"\tChanges made in this mode are not committed yet. Select \"n\" and type \"commit\" to apply changes, otherwise type \"y\" to exit. \
                                \n\tAre you sure you want to exit ?");
                        write(sockfd, "\t(y or n) ", strlen(" (y or n) "));
                        break;
                    case STATE_USER_EXIT:
                        cli_print(cli,"\tYour cli username will be deleted and you will be logged out of the console !! \n\t Are you sure, you want to delete your cli username ?");
                        write(sockfd, "\t(y or n) ", strlen(" (y or n) "));
                        break;
                    case STATE_DELETE_PEERGROUP:
                        cli_print(cli,"\tNOTE: This Peer-Group could be associated to Routing-Rules.\n\tAre you sure you want to delete ?");
                        write(sockfd, "\t(y or n) ", strlen(" (y or n) "));
                        break;
                    case STATE_ACTIVATE_SWITCHOVER:
                        cli_print(cli,"\tWARNING: This command makes switchover between Active and StandBy nodes.\n\tAre you sure you want to switchover ?");
                        write(sockfd, "\t(y or n) ", strlen(" (y or n) "));
                        break;
                }

                cli->showprompt = 0;
            }

            FD_ZERO(&r);
            FD_SET(sockfd, &r);

            if ((sr = select(sockfd + 1, &r, NULL, NULL, &tm)) < 0)
            {
                /* select error */
                if (errno == EINTR)
                {
                    CLI_ERROR_LOG("errno = EINTR"); 
                    continue;
                }
                perror("select");
                CLI_ERROR_LOG("ERROR! select error");
                l = -1;
                break;
            }

            if (sr == 0)
            {
                /* timeout every second */
                if (cli->regular_callback && cli->regular_callback(cli) != CLI_OK)
                {
                    l = -1;
                    break;
                }

                if (cli->idle_timeout)
                {
                    if (time(NULL) - cli->last_action >= cli->idle_timeout)
                    {
                        if (cli->idle_timeout_callback)
                        {
                            // Call the callback and continue on if successful
                            if (cli->idle_timeout_callback(cli) == CLI_OK)
                            {
                                // Reset the idle timeout counter
                                time(&cli->last_action);
                                continue;
                            }
                        }
                        // Otherwise, break out of the main loop
                        l = -1;
                        break;
                    }
                }

                memcpy(&tm, &cli->timeout_tm, sizeof(tm));
                continue;
            }

            if ((n = read(sockfd, &c, 1)) < 0)
            {
                if (errno == EINTR) {
                    CLI_ERROR_LOG("errno = EINTR"); 
                    continue;
                }
                perror("read");
                CLI_ERROR_LOG("read error");
                l = -1;
                break;
            }

            if (cli->idle_timeout)
                time(&cli->last_action);

            if (n == 0)
            {
                l = -1;
                break;
            }

            if (skip)
            {
                skip--;
                continue;
            }

            if (c == 255 && !is_telnet_option)
            {
                is_telnet_option++;
                continue;
            }

            if (is_telnet_option)
            {
                if (c >= 251 && c <= 254)
                {
                    is_telnet_option = c;
                    continue;
                }

                if (c != 255)
                {
                    is_telnet_option = 0;
                    continue;
                }

                is_telnet_option = 0;
            }

            /* handle ANSI arrows */
            if (esc)
            {
                if (esc == '[')
                {
                    /* remap to readline control codes */
                    switch (c)
                    {
                        case 'A': /* Up */
                            c = CTRL('P');
                            break;

                        case 'B': /* Down */
                            c = CTRL('N');
                            break;

                        case 'C': /* Right */
                            c = CTRL('F');
                            break;

                        case 'D': /* Left */
                            c = CTRL('B');
                            break;

                        default:
                            c = 0;
                    }

                    esc = 0;
                }
                else
                {
                    esc = (c == '[') ? c : 0;
                    continue;
                }
            }

            if (c == 0) continue;
            if (c == '\n') continue;

            if (c == '?')
            {
                write(sockfd, "?\n", 2);
                //continue;
            }

            if (c == '\r')
            {
                if (cli->state != STATE_PASSWORD && 
                        cli->state != STATE_ENABLE_PASSWORD && 
                        cli->state != STATE_ADD_USER_PASSWORD && 
                        cli->state != STATE_MOD_USER_PASSWORD &&
                        cli->state != STATE_DELETE_USER_PASSWORD &&
                        cli->state != STATE_DELETE_PEERGROUP &&
                        cli->state != STATE_ACTIVATE_SWITCHOVER &&
                        cli->state != STATE_EXIT_WITHOUT_SENT)

                    write(sockfd, "\r\n", 2);
                break;
            }

            if (c == 27)
            {
                esc = 1;
                continue;
            }

            if (c == CTRL('C'))
            {
                CLI_DEBUG_LOG("CTRL + C entered");
                write(sockfd, "\a", 1);
                continue;
            }


            /* back word, backspace/delete */
            if (c == CTRL('W') || c == CTRL('U') || c == CTRL('Z') || c == CTRL('H') || c == 0x7f)
            {
                int back = 0;

                if (c == CTRL('W')) /* word */
                {
                    CLI_DEBUG_LOG("CTRL + W entered");
                    int nc = cursor;

                    if (l == 0 || cursor == 0)
                        continue;

                    while (nc && cmd[nc - 1] == ' ')
                    {
                        nc--;
                        back++;
                    }

                    while (nc && cmd[nc - 1] != ' ')
                    {
                        nc--;
                        back++;
                    }
                }
                //clear the line 
                else if (c == CTRL('U') || c == CTRL('Z'))
                {
                    CLI_DEBUG_LOG("CTRL + U entered");
                    int nc = cursor;
                    if ((l == 0 || cursor == 0) && (c != CTRL('Z')))
                        continue;
                    //check for the cursor count
                    while(nc)
                    {
                        nc--;
                        back++;
                    }
                    if(back)
                        memset(cmd, 0, back);
                }
                else /* char */
                {
                    CLI_DEBUG_LOG("CTRL + H entered");
                    if (l == 0 || cursor == 0)
                    {
                        write(sockfd, "\a", 1);
                        continue;
                    }

                    back = 1;
                }

                if (back)
                {
                    while (back--)
                    {
                        if (l == cursor)
                        {
                            cmd[--cursor] = 0;
                            if (cli->state != STATE_PASSWORD && 
                                    cli->state != STATE_ENABLE_PASSWORD && 
                                    cli->state != STATE_ADD_USER_PASSWORD && 
                                    cli->state != STATE_MOD_USER_PASSWORD &&
                                    cli->state != STATE_DELETE_USER_PASSWORD)
                                write(sockfd, "\b \b", 3);
                        }
                        else
                        {
                            int i;
                            cursor--;
                            if (cli->state != STATE_PASSWORD && 
                                    cli->state != STATE_ENABLE_PASSWORD && 
                                    cli->state != STATE_ADD_USER_PASSWORD && 
                                    cli->state != STATE_MOD_USER_PASSWORD &&
                                    cli->state != STATE_DELETE_USER_PASSWORD)
                            {
                                for (i = cursor; i <= l; i++) cmd[i] = cmd[i+1];
                                write(sockfd, "\b", 1);
                                write(sockfd, cmd + cursor, strlen(cmd + cursor));
                                write(sockfd, " ", 1);
                                for (i = 0; i <= (int)strlen(cmd + cursor); i++)
                                    write(sockfd, "\b", 1);
                            }
                        }
                        l--;
                    }
                }
                /* Short cut to go to execution mode from any mode */
                if (c == CTRL('Z'))
                {
                    CLI_DEBUG_LOG("CTRL + Z entered");
                    if (cli->mode != MODE_EXEC)
                    {
                        oldmode  = cli_set_configmode(cli, MODE_EXEC, NULL);
                        cli_track_configmode(cli, oldmode, MODE_EXEC, true);
                        //giving one line space for alignment in telnet after giving CTRL('Z') togo to MODE_EXEC
                        cli_print(cli,"");
                        // making mode count to zero if user gives CTRL('Z') togo to MODE_EXEC
                        cli->num_modes = 0;
                        cli->showprompt = 1;
                    }
                }
                continue;
            }

            /* redraw */
            if (c == CTRL('L'))
            {
                CLI_DEBUG_LOG("CTRL + L entered");
                int i;
                int cursorback = l - cursor;

                if (cli->state == STATE_PASSWORD || 
                        cli->state == STATE_ENABLE_PASSWORD || 
                        cli->state == STATE_ADD_USER_PASSWORD || 
                        cli->state == STATE_MOD_USER_PASSWORD ||
                        cli->state != STATE_DELETE_USER_PASSWORD)
                    continue;

                write(sockfd, "\r\n", 2);
                show_prompt(cli, sockfd);
                write(sockfd, cmd, l);

                for (i = 0; i < cursorback; i++)
                    write(sockfd, "\b", 1);

                continue;
            }
            /* kill to EOL */
            if (c == CTRL('K'))
            {
                CLI_DEBUG_LOG("CTRL + K entered");
                if (cursor == l)
                    continue;

                if (cli->state != STATE_PASSWORD && 
                        cli->state != STATE_ENABLE_PASSWORD && 
                        cli->state != STATE_ADD_USER_PASSWORD && 
                        cli->state != STATE_MOD_USER_PASSWORD &&
                        cli->state != STATE_DELETE_USER_PASSWORD)
                {
                    int c;
                    for (c = cursor; c < l; c++)
                        write(sockfd, " ", 1);

                    for (c = cursor; c < l; c++)
                        write(sockfd, "\b", 1);
                }

                memset(cmd + cursor, 0, l - cursor);
                l = cursor;
                continue;
            }

            /* EOT */
            if (c == CTRL('D'))
            {
                CLI_DEBUG_LOG("CTRL + D entered");
                if (cli->state == STATE_PASSWORD || 
                        cli->state == STATE_ENABLE_PASSWORD ||  
                        cli->state == STATE_ADD_USER_PASSWORD || 
                        cli->state == STATE_MOD_USER_PASSWORD ||
                        cli->state != STATE_DELETE_USER_PASSWORD)
                    break;

                if (l)
                    continue;

                l = -1;
                break;
            }


            /* TAB completion */
            if (c == CTRL('I'))
            {
                CLI_DEBUG_LOG("CTRL + I entered");
                char *completions[CLI_MAX_LINE_WORDS];
                int num_completions = 0;

                if (cli->state == STATE_LOGIN || 
                        cli->state == STATE_PASSWORD || 
                        cli->state == STATE_ENABLE_PASSWORD || 
                        cli->state == STATE_ADD_USER || 
                        cli->state == STATE_ADD_USER_PASSWORD ||
                        cli->state == STATE_MOD_USER_PASSWORD )
                    continue;

                if (cursor != l) continue;

                num_completions = cli_get_completions(cli, cmd, completions, CLI_MAX_LINE_WORDS);
                if (num_completions == 0)
                {
                    write(sockfd, "\a", 1);
                }
                else if (num_completions == 1)
                {
                    // Single completion
                    for (; l > 0; l--, cursor--)
                    {
                        if (cmd[l-1] == ' ' || cmd[l-1] == '|')
                            break;
                        write(sockfd, "\b", 1);
                    }
                    strcpy((cmd + l), completions[0]);
                    l += strlen(completions[0]);
                    cmd[l++] = ' ';
                    cursor = l;
                    write(sockfd, completions[0], strlen(completions[0]));
                    write(sockfd, " ", 1);
                }
                else if (lastchar == CTRL('I'))
                {
                    // double tab
                    int i, k;
                    k = 0;
                    write(sockfd, "\r\n\n  ", 5);
                    for (i = 0; i < num_completions; i++)
                    {
                        if(!strcmp(completions[i],"commit")) {
                            if((cli->mode == MODE_CONFIG_PEER) ||
                                    (cli->mode == MODE_CONFIG_LOCALHOST) ||
                                    (cli->mode == MODE_MODIFY_LOCALHOST) ||
                                    (cli->mode == MODE_CONFIG_REALM) ||
                                    (cli->mode == MODE_STATIC_PEER_CONFIG) || 
                                    (cli->mode == MODE_CONFIG_ADD_ERLBF_PEER) ||
                                    (cli->mode == MODE_CONFIG_DCCA_DESTINATION) ||
                                    (cli->mode == MODE_CONFIG_FAILURE_HANDLING) ||
                                    (cli->mode == MODE_CONFIG_LOCAL) || 
                                    (cli->mode == MODE_CONFIG_SCTP_PROFILE) || 
                                    (cli->mode == MODE_CONFIG_ADD_SCTP_ENDPOINT) || 
                                    (cli->mode == MODE_CONFIG_MODIFY_SCTP_ENDPOINT) || 
                                    (cli->mode == MODE_CONFIG_ADD_ASSOCIATION) || 
                                    (cli->mode == MODE_CONFIG_MODIFY_ASSOCIATION) || 
                                    (cli->mode == MODE_CONFIG_ADD_ASSOCIATION_SET) || 
                                    (cli->mode == MODE_CONFIG_MODIFY_ASSOCIATION_SET) || 
                                    (cli->mode == MODE_CONFIG_DESTINATION) ||
                                    (cli->mode == MODE_CONFIG_ADD_S6A_MAP) ||
                                    (cli->mode == MODE_CONFIG_MODIFY_S6A_MAP) ||
                                    (cli->mode == MODE_CONFIG_ADD_MAP_S6A) ||
                                    (cli->mode == MODE_CONFIG_MODIFY_MAP_S6A) ||
                                    (cli->mode == MODE_CONFIG_CAP_RO_IDP) ||
                                    (cli->mode == MODE_CONFIG_CAP_RO_IDP_SMS) ||
                                    (cli->mode == MODE_CONFIG_REMOTEROUTE) ||
                                    (cli->mode == MODE_TRANS_RULE_SS7) ||
                                    (cli->mode == MODE_TRANS_RULE_DIAMETER) ||
                                    (cli->mode == MODE_CONFIG_RRB_CALL_SCENARIO) ||
                                    (cli->mode == MODE_TRANS_RULE_HTTP))
                            {
                                write(sockfd, completions[i], strlen(completions[i]));
                                k++;
                                if((k % 3 == 0))
                                {
                                    write(sockfd, "\r\n  ", 4);
                                }
                                else
                                    write(sockfd, "                              ", 25-strlen(completions[i]));
                            }
                        }
                        else if((!strcmp(completions[i],"modify") || !strcmp(completions[i],"no"))) {
                            if((cli->mode == MODE_EXEC) ||
                                    (cli->mode == MODE_DIABASE_PTABLE) ||
                                    (cli->mode == MODE_DIABASE_REALMTABLE) ||
                                    (cli->mode == MODE_DIABASE_LOCALHOST) ||
                                    (cli->mode == MODE_CONFIG_ERLBF) ||
                                    (cli->mode == MODE_CONFIG_STATIC_ROUTING) ||
                                    (cli->mode == MODE_CONFIG_MOD_ERLBF_PEER) ||
                                    (cli->mode == MODE_CONFIG_SIGTRAN) ||
                                    (cli->mode == MODE_CONFIG_SIGTRAN_SCTP) ||
                                    (cli->mode == MODE_CONFIG_SIGTRAN_M3UA) || 
                                    (cli->mode == MODE_CONFIG_IWF) ||
                                    (cli->mode == MODE_CONFIG_DCCA) ||
                                    (cli->mode == MODE_CONFIG_CAP_RO) ||
                                    (cli->mode == MODE_CONFIG_CAP_RRB) ||
                                    (cli->mode == MODE_TLS_CONFIG))
                            {
                                write(sockfd, completions[i], strlen(completions[i]));
                                k++;
                                if((k % 3 == 0))
                                {
                                    write(sockfd, "\r\n  ", 4);
                                }
                                else
                                    write(sockfd, "                              ", 25-strlen(completions[i]));
                            }
                        }
                        else
                        {
                            write(sockfd, completions[i], strlen(completions[i]));
                            k++;
                            if((k % 3 == 0))
                            {
                                write(sockfd, "\r\n  ", 4);
                            }
                            else
                                write(sockfd, "                              ", 25-strlen(completions[i]));
                        }
                    }
                    if (k % 3 != 0) write(sockfd, "\r\n", 2);
                    cli->showprompt = 1;
                }
                else
                {
                    // More than one completion
                    lastchar = c;
                    write(sockfd, "\a", 1);
                }
                continue;
            }

            /* history */
            if (c == CTRL('P') || c == CTRL('N'))
            {
                CLI_DEBUG_LOG("CTRL + %c entered",c);
                int history_found = 0;

                if (cli->state == STATE_LOGIN || 
                        cli->state == STATE_PASSWORD || 
                        cli->state == STATE_ENABLE_PASSWORD || 
                        cli->state == STATE_ADD_USER || 
                        cli->state == STATE_ADD_USER_PASSWORD ||
                        cli->state == STATE_MOD_USER_PASSWORD )
                    continue;

                if (c == CTRL('P')) // Up
                {
                    in_history--;
                    if (in_history < 0)
                    {
                        for (in_history = MAX_HISTORY-1; in_history >= 0; in_history--)
                        {
                            if (cli->history[in_history])
                            {
                                history_found = 1;
                                break;
                            }
                        }
                    }
                    else
                    {
                        if (cli->history[in_history]) history_found = 1;
                    }
                }
                else // Down
                {
                    in_history++;
                    if (in_history >= MAX_HISTORY || !cli->history[in_history])
                    {
                        int i = 0;
                        for (i = 0; i < MAX_HISTORY; i++)
                        {
                            if (cli->history[i])
                            {
                                in_history = i;
                                history_found = 1;
                                break;
                            }
                        }
                    }
                    else
                    {
                        if (cli->history[in_history]) history_found = 1;
                    }
                }
                if (history_found && cli->history[in_history])
                {
                    // Show history item
                    cli_clear_line(sockfd, cmd, l, cursor);
                    memset(cmd, 0, CLI_MAX_LINE_LENGTH);
                    strncpy(cmd, cli->history[in_history], CLI_MAX_LINE_LENGTH - 1);
                    l = cursor = strlen(cmd);
                    write(sockfd, cmd, l);
                }

                continue;
            }

            /* left/right cursor motion */
            if (c == CTRL('B') || c == CTRL('F'))
            {
                CLI_DEBUG_LOG("CTRL + %c entered",c);
                if (c == CTRL('B')) /* Left */
                {
                    if (cursor)
                    {
                        if (cli->state != STATE_PASSWORD && 
                                cli->state != STATE_ENABLE_PASSWORD && 
                                cli->state != STATE_ADD_USER_PASSWORD && 
                                cli->state != STATE_DELETE_USER_PASSWORD &&
                                cli->state != STATE_MOD_USER_PASSWORD )
                            write(sockfd, "\b", 1);

                        cursor--;
                    }
                }
                else /* Right */
                {
                    if (cursor < l)
                    {
                        if (cli->state != STATE_PASSWORD && 
                                cli->state != STATE_ENABLE_PASSWORD && 
                                cli->state != STATE_ADD_USER_PASSWORD &&
                                cli->state != STATE_MOD_USER_PASSWORD &&
                                cli->state != STATE_DELETE_USER_PASSWORD)
                            write(sockfd, &cmd[cursor], 1);

                        cursor++;
                    }
                }

                continue;
            }

            /* start of line */
            if (c == CTRL('A'))
            {
                CLI_DEBUG_LOG("CTRL + %c entered",c);
                //int promptLen = 0;
                if (cursor)
                {
                    if (cli->state != STATE_PASSWORD && 
                            cli->state != STATE_ENABLE_PASSWORD && 
                            cli->state != STATE_ADD_USER_PASSWORD && 
                            cli->state != STATE_MOD_USER_PASSWORD &&
                            cli->state != STATE_DELETE_USER_PASSWORD)
                    {
                        write(sockfd, "\r", 1);
                        show_prompt(cli, sockfd);
                        //promptLen = show_prompt(cli, sockfd);
                        //write(sockfd, cmd, l);
                    }

                    //cursor = promptLen; 
                    cursor = 0;
                }

                continue;
            }

            /* end of line */
            if (c == CTRL('E'))
            {
                CLI_DEBUG_LOG("CTRL + %c entered",c);
                if (cursor < l)
                {
                    if (cli->state != STATE_PASSWORD && 
                            cli->state != STATE_ENABLE_PASSWORD && 
                            cli->state != STATE_ADD_USER_PASSWORD && 
                            cli->state != STATE_MOD_USER_PASSWORD &&
                            cli->state != STATE_DELETE_USER_PASSWORD)
                        write(sockfd, &cmd[cursor], l - cursor);

                    cursor = l;
                }

                continue;
            }

            if(!(isprint(c)))
            {    
                /* If not a printable character */
                CLI_DEBUG_LOG("User entered a non printable character");
                continue;
            }              

            /* normal character typed */
            if (cursor == l)
            {
                /* append to end of line */
                cmd[cursor] = c;
                if (l < CLI_MAX_LINE_LENGTH - 1)
                {
                    l++;
                    cursor++;
                }
                else
                {
                    write(sockfd, "\a", 1);
                    continue;
                }
            }
            else
            {
                // Middle of text
                if (insertmode)
                {
                    int i;
                    // Move everything one character to the right
                    if (l >= CLI_MAX_LINE_LENGTH - 2) l--;
                    for (i = l; i >= cursor; i--)
                        cmd[i + 1] = cmd[i];
                    // Write what we've just added
                    cmd[cursor] = c;

                    write(sockfd, &cmd[cursor], l - cursor + 1);
                    for (i = 0; i < (l - cursor + 1); i++)
                        write(sockfd, "\b", 1);
                    l++;
                }
                else
                {
                    cmd[cursor] = c;
                }
                cursor++;
            }

            if (cli->state != STATE_PASSWORD && 
                    cli->state != STATE_ENABLE_PASSWORD && 
                    cli->state != STATE_ADD_USER_PASSWORD && 
                    cli->state != STATE_MOD_USER_PASSWORD &&
                    cli->state != STATE_DELETE_USER_PASSWORD)
            {
                if (c == '?' && cursor == l)
                {
                    write(sockfd, "\r", 1);
                    oldcmd = cmd;
                    oldl = cursor = l - 1;
                    break;
                }
                write(sockfd, &c, 1);
            }

            oldcmd = 0;
            oldl = 0;
            lastchar = c;
        }

        if (l < 0) break;

        if (cli->state == STATE_LOGIN)
        {
            if (l == 0) continue;

            /* require login */
            free_z(username);
            if (!(username = strdup(cmd)))
                RETVALUE(0);
            cli->state = STATE_PASSWORD;
            cli->showprompt = 1;
        }
        else if (cli->state == STATE_PASSWORD)
        {
            /* require password */
            int allowed = 0;

            free_z(password);
            if (!(password = strdup(cmd)))
                RETVALUE(0);
            if (cli->auth_callback)
            {
                int result = 0;
                cli->loginuser = username;      
                result = (int) cli->auth_callback(cli,(unsigned char*)username,(unsigned char*) password) ; 
                if(result == CLI_OK) {
                    allowed++;
                    cli_set_privilege(cli, cli->privilege);
                }else if (result == AUTH_USER_NOT_FOUND){
                    //cli_error(cli,"\n\tUser Not found");
                }else if (result == AUTH_WRONG_PASSWORD) {
                    cli_error(cli,"\n\n\tError!! Login failed due to invalid username %s or password provided.",cli->loginuser);
                    CLI_ERROR_LOG("Error!! Login failed due to invalid username %s or password provided.",cli->loginuser);
                }

            }


            if (allowed)
            {
                cli_error(cli, "");
                cli->state = STATE_NORMAL;
                strncpy(promptName,username,MAX_HEADER_LEN - 1);
                strcat(promptName,"@");
                strcat(promptName,hostname);
                cli_set_hostname(cli,promptName);
            }
            else
            {
                CLI_ERROR_LOG(" login failed ");
                free_z(username);
                free_z(password);
                cli->state = STATE_LOGIN;
                loginAttempts++;
                if(loginAttempts == MAX_LOGIN_ATTEMPTS){
                    cli_error(cli, "\n\tERROR!! Maximum Login Attempts.");
                    CLI_ERROR_LOG(" Maximum Login Attempts ");

                    cli_free_history(cli);
                    cli_done(cli);
                    pthread_exit(NULL);

                }
            }

            cli->showprompt = 1;
#if 0 
            else if (cli->state == STATE_ENABLE_PASSWORD)
            {
                int allowed = 0;
                if (cli->enable_password)
                {
                    /* check stored static enable password */
                    if (pass_matches(cli->enable_password, cmd))
                        allowed++;
                }

                if (!allowed && cli->enable_callback)
                {
                    /* check callback */
                    if (cli->enable_callback(cmd))
                        allowed++;
                }

                if (allowed)
                {
                    cli->state = STATE_ENABLE;
                    cli_set_privilege(cli, PRIVILEGE_PRIVILEGED);
                }
                else
                {
                    cli_error(cli, "\n\nAccess denied");
                    cli->state = STATE_NORMAL;
                }
            }
#endif
        }
        else if (cli->state == STATE_ADD_USER_PASSWORD)
        {
            free_z(password);
            if (!(password = strdup(cmd)))
                RETVALUE(0);
            if(password != NULL) {
                if(cli->user.verifyNewPassword == 'y')
                {
                    if(strcmp((const char*)cli->user.password, password)==0)
                    {
                        cli->max_attempts = 0;
                        cli->state = STATE_NORMAL;
                        if(cli->adduser_callback){
                            cli->adduser_callback(cli,(unsigned char*)"",(unsigned char *)"");
                        }
                    }
                    else
                    {
                        cli->max_attempts++;
                        cli->user.verifyNewPassword = 'n';
                        cli_print(cli, "\n\n\tConfirm Password failed !! Try Again.");
                        CLI_ERROR_LOG(" Confirm Password failed ");
                        if(cli->max_attempts == MAX_LOGIN_ATTEMPTS)
                        {
                            cli_print(cli, "\n\tERROR!! Maximum attemps %d reached.please try again.",MAX_LOGIN_ATTEMPTS);
                            CLI_ERROR_LOG("ERROR!! Maximum attemps %d reached while adding an user.please try again",MAX_LOGIN_ATTEMPTS);
                            cli->max_attempts = 0;
                            cli->state = STATE_NORMAL;
                        }
                        continue;
                    }
                }
                else
                {
                    if(strlen(password)>=6 && strlen(password)<=16)
                    {
                        strncpy((char*)cli->user.password,(const char*)password,MAX_NAME_LEN - 1);
                        cli->user.verifyNewPassword = 'y';
                    }
                    else
                    {
                        cli->max_attempts++;
                        // password validation fails
                        cli_print(cli,"\n\tError!! Password length out of range.");
                        CLI_ERROR_LOG(" Error!! Password length out of range ");
                        if(cli->max_attempts == MAX_LOGIN_ATTEMPTS)
                        {
                            cli_print(cli, "\n\tERROR!! Maximum attemps %d reached.please try again.",MAX_LOGIN_ATTEMPTS);
                            CLI_ERROR_LOG("ERROR!! Maximum attemps %d reached while adding an user.please try again",MAX_LOGIN_ATTEMPTS);
                            cli->max_attempts = 0;
                            cli->state = STATE_NORMAL;
                        }
                        else
                            cli->state = STATE_ADD_USER_PASSWORD;
                    }
                }
            }

        }
        else if (cli->state == STATE_EXIT_WITHOUT_SENT || 
                cli->state == STATE_DELETE_PEERGROUP ||
                cli->state == STATE_ACTIVATE_SWITCHOVER){
            cli->allow_exit = 0;
            int i=0;
            cli->state = STATE_NORMAL;
            while (isspace(cmd[i])) {
                i++;
            }
            cmd = cmd + i;
            // checking the string for "yes (or) no (or) y (or) n" 
            if( (cmd[0]=='y' && cmd[1]=='e' && cmd[2]=='s') || (cmd[0]=='y') || (cmd[0]=='n' && cmd[1]=='o') || (cmd[0]=='n'))
            {
                i=0;
                if((cmd[0]=='y' && cmd[1]=='e' && cmd[2]=='s'))
                    i=i+3;
                else if((cmd[0]=='n' && cmd[1]=='o'))
                    i=i+2;
                else
                    i++;
                while(isspace(cmd[i]))
                    i++;

                if(cmd[i] != '\0') {
                    cli_print(cli,"\n\t*** WRONG OPTION *** " );
                    CLI_ERROR_LOG(" Wrong Option entered ");
                    if(cli->mode == MODE_CONFIG_ERLBF)
                        cli->state = STATE_DELETE_PEERGROUP;
                    else if(cli->mode == MODE_EXEC && cli->req.cmd_id == C_cli_switchover_Id)
                        cli->state = STATE_ACTIVATE_SWITCHOVER;
                    else
                        cli->state = STATE_EXIT_WITHOUT_SENT;
                }
                else
                {
                    if(cmd[0]=='y')
                        cli->allow_exit = 'y';
                    else
                        cli->allow_exit = 'n';
                    cli_int_exit(cli, NULL, NULL, 0);
                }
            }
            else {
                cli_print(cli,"\n\t*** WRONG OPTION *** " );
                CLI_ERROR_LOG(" Wrong Option entered ");
                if(cli->mode == MODE_CONFIG_ERLBF)
                    cli->state = STATE_DELETE_PEERGROUP;
                else if(cli->mode == MODE_EXEC && cli->req.cmd_id == C_cli_switchover_Id)
                    cli->state = STATE_ACTIVATE_SWITCHOVER;
                else
                    cli->state = STATE_EXIT_WITHOUT_SENT;
            }
        }
        else if(cli->state == STATE_USER_EXIT){
            cli->allow_exit = 0;
            cli->delusr = 0;
            cli->state = STATE_NORMAL;
            if(cmd[0]){
                cli->allow_exit = cmd[0];
                cli->delusr = 1;
                cli_int_exit(cli,NULL,NULL,0);
            }
        }
        else if (cli->state == STATE_DELETE_USER_PASSWORD )
        {
            free_z(password);
            if (!(password = strdup(cmd)))
                RETVALUE(0);
            cli->delusr = 0;        
            cli->state = STATE_NORMAL;
            if(password != NULL) {
                strncpy((char*)cli->user.password,(const char*)password,MAX_NAME_LEN - 1);
            }
            cli->state = STATE_NORMAL;
            if(cli->deleteuser_callback){
                cli->deleteuser_callback(cli,(unsigned char*)"",(unsigned char *)"");
#if 0
                // code to exit telnet if user is deleting himself
                if(cli->allow_exit=='y') {
                    cli_print(cli, "\n\tUser is deleted, exiting ...");
                    break;
                }
#endif
            }
        }
        else if (cli->state == STATE_MOD_USER_PASSWORD) 
        {
            free_z(password);
            if (!(password = strdup(cmd)))
                RETVALUE(0);
            if(password != NULL) {
                if (cli->user.allowNewPassword == 'y')
                {
                    if(strlen(cmd)>=6 && strlen(cmd)<=16)
                    {
                        strncpy((char*)cli->user.newPassword,(const char*)password,MAX_NAME_LEN - 1);
                        cli->user.verifyNewPassword ='y';
                        cli->user.allowNewPassword ='n';
                        continue;
                    }
                    else
                    {
                        cli->max_attempts++;
                        // password validation fails
                        cli_print(cli,"\n\n\tError!! Password length out of range.");
                        CLI_ERROR_LOG(" Error!! Password length out of range ");
                        cli->user.verifyNewPassword ='n';
                        cli->user.allowNewPassword ='y';
                        if(cli->max_attempts == MAX_LOGIN_ATTEMPTS)
                        {
                            cli_print(cli, "\n\tERROR!! Maximum attemps %d reached.please try again",MAX_LOGIN_ATTEMPTS);
                            CLI_ERROR_LOG(" ERROR!! Maximum attempts %d reached for modify user.",MAX_LOGIN_ATTEMPTS);
                            cli->state = STATE_NORMAL;
                            cli->user.setNewPassword = 'n';
                            cli->max_attempts = 0;
                            cli->user.verifyNewPassword = 'n';
                            cli->user.allowNewPassword = 'n';
                        }
                        continue;
                    }
                }
                else if(cli->user.verifyNewPassword == 'y') 
                {
                    if(strcmp((const char*)cli->user.newPassword, password)==0) 
                    {
                        /*Allow password change to go through */
                        cli->user.setNewPassword = 'y';
                        cli->max_attempts = 0;
                    }
                    else {
                        cli->max_attempts++;
                        cli->user.allowNewPassword ='y';
                        cli->user.verifyNewPassword ='n';
                        cli_print(cli, "\n\tConfirm Password failed !! Try Again.");
                        CLI_ERROR_LOG(" Confirm Password failed ");
                        if(cli->max_attempts == MAX_LOGIN_ATTEMPTS)
                        {
                            cli_print(cli, "\n\tERROR!! Maximum attemps %d reached.please try again",MAX_LOGIN_ATTEMPTS);
                            CLI_ERROR_LOG(" ERROR!! Maximum attempts %d reached for modify user.",MAX_LOGIN_ATTEMPTS);
                            cli->state = STATE_NORMAL;
                            cli->user.setNewPassword = 'n';
                            cli->max_attempts = 0;
                            cli->user.verifyNewPassword = 'n';
                            cli->user.allowNewPassword = 'n';
                        }
                        continue;
                    }                   
                }
                else{ 
                    strncpy((char*)cli->user.password,(const char*)password,MAX_NAME_LEN - 1);
                }
            }
            if(cli->modifyuser_callback){
                cli->modifyuser_callback(cli,(unsigned char*)"",(unsigned char *)"");
            }

        }
        else
        {
            if (l == 0) continue;
            if (cmd[l - 1] != '?' && strcasecmp(cmd, "history") != 0)
                cli_add_history(cli, cmd);
            if (cli_run_command(cli, cmd) == CLI_QUIT)
            {
                break;
            }
        }

        // Update the last_action time now as the last command run could take a
        // long time to return
        if (cli->idle_timeout)
            time(&cli->last_action);
    }


    /*free cli structure */
    cli_free_history(cli);
    cli_done(cli);

    free_z(username);
    free_z(password);

    NumThreads--;
    pthread_exit(NULL);
}
int sig_handler(int sigVal)
{

    CLI_ERROR_LOG("signal handler called");
    struct thread_args thArgs;
    thArgs.socket = 0;
    thArgs.recv_port = 0;
    thArgs.signalVal = sigVal;
    cli_loop(&thArgs);
    return 0;
}

int cli_file(struct cli_def *cli, FILE *fh, int privilege, int mode)
{
    int oldpriv = cli_set_privilege(cli, privilege);
    int oldmode = cli_set_configmode(cli, mode, NULL);
    char buf[CLI_MAX_LINE_LENGTH];

    cli_track_configmode(cli, oldmode, mode, true);

    while (1)
    {
        char *p;
        char *cmd;
        char *end;

        if (fgets(buf, CLI_MAX_LINE_LENGTH - 1, fh) == NULL)
            break; /* end of file */

        if ((p = strpbrk(buf, "#\r\n")))
            *p = 0;

        cmd = buf;
        while (isspace(*cmd))
            cmd++;

        if (!*cmd)
            continue;

        for (p = end = cmd; *p; p++)
            if (!isspace(*p))
                end = p;

        *++end = 0;
        if (strcasecmp(cmd, "quit") == 0)
            break;

        if (cli_run_command(cli, cmd) == CLI_QUIT)
            break;
    }

    cli_set_privilege(cli, oldpriv);
    oldpriv = cli_set_configmode(cli, oldmode, NULL /* didn't save desc */);
    cli_track_configmode(cli, oldpriv, oldmode, true);


    return CLI_OK;
}

static void _print(struct cli_def *cli, int print_mode, char *format, va_list ap)
{
    va_list aq;
    int n;
    char *p;

    if (!cli) return; // sanity check

    while (1)
    {
        va_copy(aq, ap);
        n = vsnprintf(cli->buffer, cli->buf_size, format, ap);
        if (n >= cli->buf_size)
        {
            cli->buf_size = n + 1;
            cli->buffer = realloc(cli->buffer, cli->buf_size);
            if (!cli->buffer)
                return;
            va_end(ap);
            va_copy(ap, aq);
            continue;
        }
        break;
    }

    if (n < 0) // vsnprintf failed
        return;

    p = cli->buffer;
    do
    {
        char *next = strchr(p, '\n');
        struct cli_filter *f = (print_mode & PRINT_FILTERED) ? cli->filters : 0;
        int print = 1;

        if (next)
            *next++ = 0;
        else if (print_mode & PRINT_BUFFERED)
            break;

        while (print && f)
        {
            print = (f->filter(cli, p, f->data) == CLI_OK);
            f = f->next;
        }
        if (print)
        {
            if (cli->print_callback)
                cli->print_callback(cli, p);
            else if (cli->client)
                fprintf(cli->client, "%s\r\n", p);
        }

        p = next;
    } while (p);

    if (p && *p)
    {
        if (p != cli->buffer)
            memmove(cli->buffer, p, strlen(p));
    }
    else *cli->buffer = 0;
    va_end(aq);
}

void cli_bufprint(struct cli_def *cli, char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    _print(cli, PRINT_BUFFERED|PRINT_FILTERED, format, ap);
    va_end(ap);
}

void cli_vabufprint(struct cli_def *cli, char *format, va_list ap)
{
    _print(cli, PRINT_BUFFERED, format, ap);
}

void cli_print(struct cli_def *cli, char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    _print(cli, PRINT_FILTERED, format, ap);
    va_end(ap);
}

void cli_error(struct cli_def *cli, char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    _print(cli, PRINT_PLAIN, format, ap);
    va_end(ap);
}

struct cli_match_filter_state
{
    int flags;
#define MATCH_REGEX                1
#define MATCH_INVERT                2
    union {
        char *string;
        regex_t re;
    } match;
};

int cli_match_filter_init(struct cli_def *cli, int argc, char **argv, struct cli_filter *filt)
{
    struct cli_match_filter_state *state;
    int rflags;
    int i;
    char *p;

    if (argc < 2)
    {
        if (cli->client)
            fprintf(cli->client, "Match filter requires an argument\r\n");

        return CLI_ERROR;
    }

    filt->filter = cli_match_filter;
    filt->data = state = calloc(sizeof(struct cli_match_filter_state), 1);

    if (argv[0][0] == 'i' || // include/exclude
            (argv[0][0] == 'e' && argv[0][1] == 'x'))
    {
        if (argv[0][0] == 'e')
            state->flags = MATCH_INVERT;

        state->match.string = join_words(argc-1, argv+1);
        return CLI_OK;
    }

#ifdef WIN32
    /*
     * No regex functions in windows, so return an error
     */
    return CLI_ERROR;
#endif

    state->flags = MATCH_REGEX;

    // grep/egrep
    rflags = REG_NOSUB;
    if (argv[0][0] == 'e') // egrep
        rflags |= REG_EXTENDED;

    i = 1;
    while (i < argc - 1 && argv[i][0] == '-' && argv[i][1])
    {
        int last = 0;
        p = &argv[i][1];

        if (strspn(p, "vie") != strlen(p))
            break;

        while (*p)
        {
            switch (*p++)
            {
                case 'v':
                    state->flags |= MATCH_INVERT;
                    break;

                case 'i':
                    rflags |= REG_ICASE;
                    break;

                case 'e':
                    last++;
                    break;
            }
        }

        i++;
        if (last)
            break;
    }

    p = join_words(argc-i, argv+i);
    if ((i = regcomp(&state->match.re, p, rflags)))
    {
        if (cli->client)
            fprintf(cli->client, "Invalid pattern \"%s\"\r\n", p);

        free_z(p);
        return CLI_ERROR;
    }

    free_z(p);
    return CLI_OK;
}

int cli_match_filter(UNUSED(struct cli_def *cli), char *string, void *data)
{
    struct cli_match_filter_state *state = data;
    int r = CLI_ERROR;

    if (!string) // clean up
    {
        if (state->flags & MATCH_REGEX)
            regfree(&state->match.re);
        else
            free(state->match.string);

        free(state);
        return CLI_OK;
    }

    if (state->flags & MATCH_REGEX)
    {
        if (!regexec(&state->match.re, string, 0, NULL, 0))
            r = CLI_OK;
    }
    else
    {
        if (strstr(string, state->match.string))
            r = CLI_OK;
    }

    if (state->flags & MATCH_INVERT)
    {
        if (r == CLI_OK)
            r = CLI_ERROR;
        else
            r = CLI_OK;
    }

    return r;
}

struct cli_range_filter_state {
    int matched;
    char *from;
    char *to;
};

int cli_range_filter_init(struct cli_def *cli, int argc, char **argv, struct cli_filter *filt)
{
    struct cli_range_filter_state *state;
    char *from = 0;
    char *to = 0;

    if (!strncmp(argv[0], "bet", 3)) // between
    {
        if (argc < 3)
        {
            if (cli->client)
                fprintf(cli->client, "Between filter requires 2 arguments\r\n");

            return CLI_ERROR;
        }

        if (!(from = strdup(argv[1])))
            return CLI_ERROR;
        to = join_words(argc-2, argv+2);
    }
    else // begin
    {
        if (argc < 2)
        {
            if (cli->client)
                fprintf(cli->client, "Begin filter requires an argument\r\n");

            return CLI_ERROR;
        }

        from = join_words(argc-1, argv+1);
    }

    filt->filter = cli_range_filter;
    filt->data = state = calloc(sizeof(struct cli_range_filter_state), 1);

    state->from = from;
    state->to = to;

    return CLI_OK;
}

int cli_range_filter(UNUSED(struct cli_def *cli), char *string, void *data)
{
    struct cli_range_filter_state *state = data;
    int r = CLI_ERROR;

    if (!string) // clean up
    {
        free_z(state->from);
        free_z(state->to);
        free_z(state);
        return CLI_OK;
    }

    if (!state->matched)
        state->matched = !!strstr(string, state->from);

    if (state->matched)
    {
        r = CLI_OK;
        if (state->to && strstr(string, state->to))
            state->matched = 0;
    }

    return r;
}

int cli_count_filter_init(struct cli_def *cli, int argc, UNUSED(char **argv), struct cli_filter *filt)
{
    if (argc > 1)
    {
        if (cli->client)
            fprintf(cli->client, "Count filter does not take arguments\r\n");

        return CLI_ERROR;
    }

    filt->filter = cli_count_filter;
    if (!(filt->data = calloc(sizeof(int), 1)))
        return CLI_ERROR;

    return CLI_OK;
}

int cli_count_filter(struct cli_def *cli, char *string, void *data)
{
    int *count = data;

    if (!string) // clean up
    {
        // print count
        if (cli->client)
            fprintf(cli->client, "%d\r\n", *count);

        free(count);
        return CLI_OK;
    }

    while (isspace(*string))
        string++;

    if (*string)
        (*count)++;  // only count non-blank lines

    return CLI_ERROR; // no output
}

void cli_print_callback(struct cli_def *cli, void (*callback)(struct cli_def *, char *))
{
    cli->print_callback = callback;
}

void cli_set_idle_timeout(struct cli_def *cli, unsigned int seconds)
{
    if (seconds < 1) seconds = 0;
    cli->idle_timeout = seconds;
    time(&cli->last_action);
}

void cli_set_idle_timeout_callback(struct cli_def *cli, unsigned int seconds, int (*callback)(struct cli_def *))
{
    cli_set_idle_timeout(cli, seconds);
    cli->idle_timeout_callback = callback;
}

int cli_validate_string(struct cli_def *cli,char *string)
{
    int i = 0; 
    char c;
    for(i=0;i<strlen(string);i++)
    {    
        c = string[i];
        //check for the letter '/' in the given string value
        if(c == '/')
        {    
            cli_error(cli,"\n\tInvalid String = %s, '/' is not allowed to configure in a string.",string);
            CLI_ERROR_LOG("Invalid String = %s, '/' is not allowed to configure in a string.",string);
            return CLI_ERROR_MSG;
        }    
    }
    return CLI_OK;
}
