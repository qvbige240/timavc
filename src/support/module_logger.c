/**
 * History:
 * ================================================================
 * 2019-12-03 qing.zou created
 *
 */

#include "vpk/vpk_util.h"
#include "vpk/vpk_filesys.h"

#include "vmp_log.h"

#include "globals.h"
#include "module_logger.h"

static const char *const LOG_LEVELS[] =
{
    "FATAL",
    "ERROR",
    "WARN",
    "INFO",
    "DEBUG",
};

const char *get_log_level_value(int level)
{
    unsigned int i = 0;
    for (i = 0; i < sizeof(LOG_LEVELS) / sizeof(LOG_LEVELS[0]); i++)
    {
        if (strcmp(LOG_LEVELS[i], LOG_LEVELS[level]) == 0)
        {
            return LOG_LEVELS[i];
        }
    }
    return LOG_LEVELS[i - 1];
}

static int mod_zlog_conf(log_config_t *config)
{
    FILE *fp = NULL;
    //int mode = tima_default_config()->log_mode;
    //int level = tima_default_config()->log_level;
    //char* log_path = tima_default_config()->log_path;
    //char* conf_path = tima_default_config()->data_path;
    //int level = 3;		// info
    //char* log_path = "./log/";
    //char* conf_path = "./tima/";
    int mode = config->log_mode;
    int level = config->log_level;
    char *log_path = config->log_path;
    char *conf_path = config->data_path;

    int file_len = config->file_len;
    int file_cnt = config->file_cnt;

    if (!vpk_exists(conf_path))
    {
        int ret = 0;
        char tmp[256] = {0};
        vpk_pathname_get(conf_path, tmp);
        printf("full: %s, pathname: %s\n", conf_path, tmp);
        ret = vpk_mkdir_mult(conf_path);
        printf("vpk_mkdir_mult \'%s\' ret = %d\n", conf_path, ret);
    }

    unsigned int pos = 0;
    char file[256] = {0};

    if (!vpk_exists(conf_path))
    {
        strcpy(file, "/tmp/zlog.conf");
    }
    else
    {
        vpk_snprintf(file, &pos, MAX_PATH_SIZE, "%s/%s", conf_path, "zlog.conf");
        //sprintf(file, "%s/%s", conf_path, "zlog.conf");
    }

    //char cmd[256] = {0};
    //sprintf(cmd, "rm -rf %s\n", file);
    //vpk_system_ex(cmd, 3);

    fp = fopen(file, "wb");
    if (!fp)
    {
        fprintf(0, "fopen ERROR!\n");
        return -1;
    }

    fprintf(fp, "[global]\n");
    fprintf(fp, "buffer min = 1024\n");
    fprintf(fp, "buffer max = 2MB\n");
    fprintf(fp, "rotate lock file = /tmp/zlog.lock\n");
    //fprintf(fp,"rotate lock file = self\n");
    fprintf(fp, "default format = \"%%d(%%F %%T) %%-6V (%%c:%%F:%%L) - %%m%%n\"\n");
    fprintf(fp, "[formats]\n");
    //fprintf(fp,"simple	= \"%%d (%%4p:%%15F:%%4L) %%-5V - %%m\"\n");
    //fprintf(fp,"default	= \"%%d(%%F %%T) %%-6V - %%m%%n\"\n");
    //fprintf(fp,"default	= \"%%d(%%F %%T) %%-6V (%%F:%%L) - %%m%%n\"\n");
    //fprintf(fp,"normal	= \"%%d(%%F %%T.%%l) %%-6V (%%c:%%F:%%L) - %%m%%n\"\n");
    fprintf(fp, "default	= \"%%d(%%F %%T).%%us %%-6V (%%F:%%L) - %%m%%n\"\n");
    fprintf(fp, "[rules]\n");
    if (mode & 0x01)
        fprintf(fp, "*.%s         >stdout;default\n", get_log_level_value(level));
    if (mode & 0x02)
        fprintf(fp, "*.%s       \"%s%s.log\",%dMB * %d ~ \"%s%s.log.#2r\";\n",
                get_log_level_value(level), log_path, "tima", file_len, file_cnt, log_path, "tima");
    //fwrite(buffer, 1, strlen(buffer), fp);
    fflush(fp);
    fclose(fp);

    if (!vpk_exists(log_path))
    {
        int ret = 0;
        char tmp[256] = {0};
        vpk_pathname_get(log_path, tmp);
        printf("log_path full: %s, pathname: %s\n", log_path, tmp);
        ret = vpk_mkdir_mult(log_path);
        printf("vpk_mkdir_mult \'%s\' ret = %d\n", log_path, ret);
    }

    int rc = dzlog_init(file, "vmp-rl");
    if (rc)
    {
        printf("zlog init failed\n");
        return -1;
    }

    VMP_LOGI("hello, zlog");

    return 0;
}

static int mod_log_load(const char *conf, log_config_t *lc)
{
    if (!conf)
    {
        strcpy(lc->data_path, "./conf/");
        strcpy(lc->log_path, "./log/");
        lc->log_mode = 3;
        lc->log_level = 4;

        lc->file_len = 10; /* MB */
        lc->file_cnt = 15;
    }

    return 0;
}

int mod_log_init(int procname, const char *conf)
{
#ifdef USE_ZLOG
    log_config_t *config = calloc(1, sizeof(log_config_t));
    mod_log_load(conf, config);
    log_set_config(config);

    //return tima_zlog_init(procname);
    return mod_zlog_conf(config);
#else
    return 0;
#endif
}
