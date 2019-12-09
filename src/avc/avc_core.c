/**
 * History:
 * ================================================================
 * 2019-12-03 qing.zou created
 *
 */

#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

#include "avc.h"
#include "avc_core.h"

typedef struct _PrivInfo
{
    int                 cond;

    pthread_t           core_thread;
    pthread_mutex_t     core_mutex;

    bool                initialized;

    void                *process;
    void                *demo;
    void                *node_state;
} PrivInfo;


/** task demo **/
static int demo_callback(void* p, int msg, void* arg)
{
    if (msg != 0) {
        VMP_LOGE("demo_callback failed");
        return -1;
    }
    return 0;
}
static void task_demo_start(PrivInfo* thiz)
{
    AvcDemoReq req = {0};
    req.id              = 1;
    // req.svc             = thiz->svc;
    // req.process         = thiz->process;
    req.ctx             = thiz;
    req.pfn_callback    = demo_callback;
    thiz->demo = avc_demo_create(thiz, &req);
    if (thiz->demo) {
        avc_demo_start(thiz->demo);
    }
}

static void *avc_core_thread(void *arg)
{
    PrivInfo *thiz = (PrivInfo *)arg;

    while (thiz->cond)
    {
        sleep(5);
    }
    return NULL;
}

static int avc_core_start(PrivInfo *thiz)
{
    int ret = 0;
    pthread_mutexattr_t attr;

    if (!thiz)
        return -1;

    if (pthread_mutexattr_init(&attr) != 0)
        goto fail;
    if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) != 0)
        goto fail;
    if (pthread_mutex_init(&thiz->core_mutex, &attr) != 0)
        goto fail;

    ret = pthread_create(&thiz->core_thread, NULL, avc_core_thread, (void *)thiz);
    if (ret != 0)
        VMP_LOGE("create thread 'avc_core_thread' failed");

    return 0;

fail:
    avc_core_done();
    return -1;
}

static int avc_core_stop(PrivInfo *thiz)
{
    void *thread_result;

    if (!thiz)
        return -1;

    if (thiz->initialized)
    {
        thiz->initialized = false;
        pthread_join(thiz->core_thread, &thread_result);
    }

    return 0;
}

void avc_core_init(void)
{
    avc_core_t *avc = global_default_core();

    PrivInfo *thiz = calloc(1, sizeof(PrivInfo));
    if (thiz)
    {
        thiz->cond = 1;
        thiz->initialized = true;
        avc->core = thiz;

        avc_core_start(thiz);
    }
}

void avc_core_done(void)
{
    avc_core_t *avc = global_default_core();
    PrivInfo *thiz = avc->core;
    if (thiz)
    {
        avc_core_stop(thiz);

        pthread_mutex_destroy(&thiz->core_mutex);
        free(thiz);
        avc->core = NULL;
    }
}
