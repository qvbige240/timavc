/**
 * History:
 * ================================================================
 * 2019-12-03 qing.zou created
 *
 */

#include <unistd.h>

#include "avc.h"
#include "avc_core.h"

void avc_init(int argc, char **argv)
{
    avc_core_t *core = calloc(1, sizeof(avc_core_t));
    global_set_core(core);

    global_set_argv((void *)argv);

    mod_log_init(PROCESS_AVC, NULL);

    avc_core_init();
}

void avc_start(void)
{
    while (1)
    {
        sleep(10);
    }
}

void avc_done(void)
{
    avc_core_done();

    avc_core_t *core = global_default_core();
    if (core)
    {
        free(core);
        global_set_core(NULL);
    }
}
