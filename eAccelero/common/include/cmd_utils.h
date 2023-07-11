#ifndef _CMD_UTILS_H_
#define _CMD_UTILS_H_

/* free and zero (to avoid double-free) */
#define free_z(p) do { if (p) { free(p); (p) = 0; } } while (0)
#ifdef __GNUC__
# define UNUSED(d) d __attribute__ ((unused))
#else
# define UNUSED(d) d
#endif

typedef struct _cli_args
{
    int argc;
    char** argv;
} CliArgs;

#endif

