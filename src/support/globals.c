/**
 * History:
 * ================================================================
 * 2019-12-03 qing.zou created
 *
 */

#include "globals.h"

struct globals
{
    void    *log;
    void    *config;
    void    *core;      /* avc core */

    void    *argv;      /* main arg: char* argv[]  */
} g_globals;

void *log_default_config(void)
{
    return g_globals.log;
}

void log_set_config(void *config)
{
    g_globals.log = config;
}

void *global_default_config(void)
{
    return g_globals.config;
}

void global_set_config(void *config)
{
    g_globals.config = config;
}

void *global_default_argv(void)
{
    return g_globals.argv;
}

void global_set_argv(void *argv)
{
    g_globals.argv = argv;
}

void *global_default_core(void)
{
    return g_globals.core;
}

void global_set_core(void *core)
{
    g_globals.core = core;
}
