/**
 * History:
 * ================================================================
 * 2019-12-03 qing.zou created
 *
 */

#ifndef AVC_CORE_H
#define AVC_CORE_H

#include "avc_typedef.h"

#include "avc_demo.h"

VMP_BEGIN_DELS

typedef struct avc_core_t
{
    void    *core;
} avc_core_t;

void avc_core_init(void);
void avc_core_done(void);

VMP_END_DELS

#endif // AVC_CORE_H
