/**
 * History:
 * ================================================================
 * 2019-12-03 qing.zou created
 *
 */

#ifndef AVC_H
#define AVC_H

#include "avc_typedef.h"

#ifdef __cplusplus
extern "C"
{
#endif

void avc_init(int argc, char **argv);

void avc_start(void);

void avc_done(void);

#ifdef __cplusplus
}
#endif

#endif // AVC_H
