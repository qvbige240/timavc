/**
 * History:
 * ================================================================
 * 2019-12-03 qing.zou created
 *
 */

#ifndef AVC_DEMO_H
#define AVC_DEMO_H

#include "avc_typedef.h"

VMP_BEGIN_DELS

typedef struct _AvcDemoReq
{
    unsigned int            id;

    void                    *ctx;
    vmp_callback_func       pfn_callback;
} AvcDemoReq;

typedef struct _AvcDemoRsp
{
    unsigned int            num;
} AvcDemoRsp;

void *avc_demo_create(void *parent, AvcDemoReq *req);

int avc_demo_start(void *p);

void avc_demo_done(void *p);

VMP_END_DELS

#endif // AVC_DEMO_H
