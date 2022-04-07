#include "letschat/utils/thread.h"
#include <stdlib.h>

#define IS_NULL(x) (x == NULL)
#define NOT_NULL(x) (x != NULL)

static ROUTINE_RETV join(thread_t* thread)
{
#ifdef _WIN32
    WaitForSingleObject(
        thread->PRIVATE(handle),
        INFINITE
    );

    GetExitCodeThread(thread->PRIVATE(handle), &thread->status);
#else
    pthread_join(thread->id, &thread->status);
#endif // _WIN32

    return thread->status;
}

static void cancel(thread_t* thread)
{
#ifdef _WIN32
    TerminateThread(thread->PRIVATE(handle), 0);
    CloseHandle(thread->PRIVATE(handle));
#else
    pthread_cancel(thread->id);
#endif // _WIN32
}

static void detach(thread_t* thread)
{
#ifdef _WIN32
    CloseHandle(thread->PRIVATE(handle));
#else
    pthread_detach(thread->id);
#endif // _WIN32
}

static void thread_free(thread_t* thread)
{
#ifdef _WIN32
    CloseHandle(thread->PRIVATE(handle));
#else
    thread->status = NULL;
#endif // _WIN32

    thread->join = NULL;
    thread->cancel = NULL;

    free(thread);
}

thread_t* summon_thread(routine_t routine, ROUTINE_ARGS args)
{
    thread_t* thread = (thread_t*) malloc(sizeof *thread);
    if (IS_NULL(thread))
    {
        return NULL;
    }

    thread->join = join;
    thread->cancel = cancel;
    // thread->detach = detach;
    thread->close = thread_free;
#ifdef _WIN32
    thread->PRIVATE(handle) = CreateThread(
        NULL,
        0,
        routine,
        args,
        0,
        &thread->id
    );
#else
    int success = pthread_create(&thread->id, NULL, routine, args);
    if (success != 0) 
    {
        free(thread);
        return NULL;
    }
#endif // _WIN32
    
    return thread;
}

static void lock(mutex_t* mutex)
{
#ifdef _WIN32
    WaitForSingleObject(mutex->PRIVATE(mutex), INFINITE);
#else
    pthread_mutex_lock(&mutex->PRIVATE(mutex));
#endif // _WIN32
}

static void release(mutex_t* mutex)
{
#ifdef _WIN32
    ReleaseMutex(mutex->PRIVATE(mutex));
#else
    pthread_mutex_unlock(&mutex->PRIVATE(mutex));
#endif // _WIN32
}

static void mutex_destroy(mutex_t* mutex)
{
#ifdef _WIN32
    CloseHandle(mutex->PRIVATE(mutex));
#else
    pthread_mutex_destroy(&mutex->PRIVATE(mutex));
#endif // _WIN32

    mutex->lock = NULL;
    mutex->release = NULL;
    mutex->destroy = NULL;

    free(mutex);
}


mutex_t* mutex_init() 
{
    mutex_t* mutex = (mutex_t*) malloc(sizeof *mutex);
    if (IS_NULL(mutex))
    {
        return NULL;
    }

    mutex->lock = lock;
    mutex->release = release;
    mutex->destroy = mutex_destroy;

#ifdef _WIN32
    mutex->PRIVATE(mutex) = CreateMutex(
        NULL,
        FALSE,
        NULL
    );
#else
    pthread_mutex_init(&mutex->PRIVATE(mutex), NULL);
#endif // _WIN32

    return mutex;
}
