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
#endif

    return thread->status;
}

static void cancel(thread_t* thread)
{
#ifdef _WIN32
    TerminateThread(thread->PRIVATE(handle), 0);
    CloseHandle(thread->PRIVATE(handle));
#else
    pthread_cancel(thread->id);
#endif
}

static void suspend(thread_t* thread)
{
#ifdef _WIN32
    SuspendThread(thread->PRIVATE(handle));
#else
    // TODO: Implement POSIX-Like Thread Suspension.
#endif
}

static void resume(thread_t* thread)
{
#ifdef _WIN32
    ResumeThread(thread->PRIVATE(handle));
#else
    // TODO: Implement POSIX-Like Thread Resume.
#endif
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
    thread->suspend = suspend;
    thread->resume = resume;
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
#endif
    
    return thread;
}

void thread_free(thread_t* thread)
{
#ifdef _WIN32
    CloseHandle(thread->PRIVATE(handle));
#else
    thread->status = NULL;
#endif

    thread->join = NULL;
    thread->cancel = NULL;
    thread->resume = NULL;
    thread->suspend = NULL;

    free(thread);
}
