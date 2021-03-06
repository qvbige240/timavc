/**
 * History:
 * ================================================================
 * 2019-12-03 qing.zou created
 *
 */

#ifndef MODULE_LOGGER_H
#define MODULE_LOGGER_H

#include "vpk/vpk_typedef.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum
{
    PROCESS_APP,
    PROCESS_DAEMON,
    PROCESS_AVC,
};

typedef struct log_config_t
{
    char    data_path[MAX_PATH_SIZE + 1];
    char    log_path[MAX_PATH_SIZE + 1];
    int     log_mode;
    int     log_level; /* @level  All level: "FATAL", "ERROR", "WARN", "INFO", "DEBUG". */

    int     file_len;
    int     file_cnt;

    //char	network_file[MAX_PATH_SIZE+1];
} log_config_t;

int mod_log_init(int procname, const char *conf);

#ifdef __cplusplus
}
#endif

#endif // MODULE_LOGGER_H
