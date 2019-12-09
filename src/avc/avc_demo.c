/**
 * History:
 * ================================================================
 * 2019-12-03 qing.zou created
 *
 */

#include "avc_demo.h"

typedef struct _PrivInfo
{
    void                *parent;
    
    AvcDemoReq          req;
    AvcDemoRsp          rsp;

    int                 cond;

    bool                initialized;

    pthread_t           thread;
    pthread_mutex_t     mutex;
} PrivInfo;

static void avc_demo_test(PrivInfo *thiz)
{
    VMP_LOGD("avc_demo_test run test");
}

static void *avc_demo_thread(void *arg)
{
    PrivInfo *thiz = (PrivInfo *)arg;

    avc_demo_test(thiz);

    while (thiz->cond)
    {
        sleep(5);
    }
    return NULL;
}

static int avc_demo_start(PrivInfo *thiz)
{
    int ret = 0;
    pthread_mutexattr_t attr;

    if (!thiz)
        return -1;

    if (pthread_mutexattr_init(&attr) != 0)
        goto fail;
    if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) != 0)
        goto fail;
    if (pthread_mutex_init(&thiz->mutex, &attr) != 0)
        goto fail;

    ret = pthread_create(&thiz->thread, NULL, avc_demo_thread, (void *)thiz);
    if (ret != 0)
        VMP_LOGE("create thread 'avc_demo_thread' failed");

    return 0;

fail:
    avc_demo_done();
    return -1;
}

static int avc_demo_stop(PrivInfo *thiz)
{
    void *thread_result;

    if (!thiz)
        return -1;

    thiz->cond = 0;

    if (thiz->initialized)
    {
        thiz->initialized = false;
        pthread_join(thiz->core_thread, &thread_result);
    }

    return 0;
}

void *avc_demo_create(void *parent, AvcDemoReq *req)
{
    PrivInfo *thiz = calloc(1, sizeof(PrivInfo));
    if (thiz)
    {
        thiz->cond          = 1;
        thiz->initialized   = true;

        thiz->req           = *req;
        thiz->parent        = parent;
    }

    return thiz;
}

static void avc_demo_destroy(PrivInfo *thiz)
{
    if (thiz)
    {
        pthread_mutex_destroy(&thiz->mutex);
        free(thiz);
    }
}

void avc_demo_done(void *p)
{
    PrivInfo *thiz = p;
    if (thiz != NULL)
    {
        avc_demo_stop(thiz);

        avc_demo_destroy(thiz);
    }
}
