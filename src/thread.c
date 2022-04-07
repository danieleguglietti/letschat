#include "letschat/utils/thread.h"
#include <pthread.h>
#include <stdlib.h>

#define IS_NULL(x) (x == NULL)
#define NOT_NULL(x) (x != NULL)

static ROUTINE_RETV join(thread_t* thread)
{
#ifdef _WIN32
    thread->status = WaitForSingleObject(
        thread->PRIVATE(handle),
        INFINITE
    );
#else
    pthread_join(thread->id, &thread->status);
#endif

    return thread->status;
}

thread_t* summon_thread(routine_t routine, ROUTINE_ARGS args)
{
    thread_t* thread = (thread_t*) malloc(sizeof *thread);
    if (IS_NULL(thread))
    {
        return NULL;
    }

    thread->join = join;
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