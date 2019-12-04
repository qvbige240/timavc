
/**
 * History:
 * ================================================================
 * 2019-12-03 qing.zou created
 *
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#ifdef __cplusplus
extern "C"
{
#endif

void *log_default_config(void);
void log_set_config(void *config);

void *global_default_config(void);
void global_set_config(void *config);

void *global_default_argv(void);
void global_set_argv(void *argv);

void *global_default_core(void);
void global_set_core(void *core);

#ifdef __cplusplus
}
#endif

#endif //GLOBALS_H