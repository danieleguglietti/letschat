#ifndef __THREAD__
#define __THREAD__

#ifdef _WIN32
#   include <windows.h>
#   define ROUTINE_RETV DWORD
#   define ROUTINE_ARGS LPVOID
#else
#   include <pthread.h>
#   include <unistd.h>
#   define ROUTINE_RETV void*
#   define ROUTINE_ARGS void*
#   define __stdcall
#endif

#include <stdint.h>
#include <stdbool.h>

#define ROUTINE(name) ROUTINE_RETV __stdcall name(ROUTINE_ARGS args)

#ifndef __PRIVATE_MODIFIER__
#   define __PRIVATE_MODIFIER__(x) __##x
#   define PRIVATE(x) __PRIVATE_MODIFIER__(x)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef ROUTINE_RETV (__stdcall *routine_t)(ROUTINE_ARGS);
typedef unsigned long threadid_t;
typedef ROUTINE_RETV status_t;

typedef struct thread
{
    // * PUBLIC
    /**
     * @brief The ID of the thread.
     */
    threadid_t id;

    /**
     * @brief The status returned from the thread.
     */
    status_t status;
    // ! PRIVATES
#ifdef _WIN32
    HANDLE PRIVATE(handle);
#endif
    // ? METHODS
    /**
     * @brief Stop the current process waiting for the thread to finish.
     */
    ROUTINE_RETV (*join)(struct thread* thread);
} thread_t;

/**
 * @brief Summon a new thread.
 * 
 * @param routine The routine to execute.
 * @param args The arguments to pass to the routine.
 * @return thread_t* The thread.
 */
thread_t* summon_thread(routine_t routine, ROUTINE_ARGS args);

#ifdef __cplusplus
}
#endif


#endif // __THREAD__
