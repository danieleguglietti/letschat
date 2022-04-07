#ifndef __THREAD__
#define __THREAD__

#ifndef __PRIVATE_MODIFIER__
#   define __PRIVATE_MODIFIER__(x) __##x
#   define PRIVATE(x) __PRIVATE_MODIFIER__(x)
#endif

#ifdef _WIN32
#   include <windows.h>
#   define ROUTINE_RETV DWORD
#   define ROUTINE_ARGS LPVOID
#   define MUTEX HANDLE
#else
#   include <pthread.h>
#   include <unistd.h>
#   define ROUTINE_RETV void*
#   define ROUTINE_ARGS void*
#   ifndef __stdcall
#       define __stdcall
#   endif
#   define MUTEX pthread_mutex_t
#endif // _WIN32

#include <stdint.h>
#include <stdbool.h>

#define ROUTINE(name) ROUTINE_RETV __stdcall name(ROUTINE_ARGS args)

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
     * 
     * @param thread The thread to wait for.
     * @return The thread status.
     */
    ROUTINE_RETV (*join)(struct thread* thread);

    /**
     * @brief Cancel the execution of the thread.
     * 
     * @param thread The thread to deattach.
     */
    void (*cancel)(struct thread* thread);

    /**
     * @brief Detach the thread from the main thread.
     * 
     * @param thread The thread to detach.
     */
    void (*detach)(struct thread* thread);

    /**
     * @brief Free the memory allocated for the thread.
     * 
     * @param thread The thread to free.
     */
    void (*close)(struct thread* thread);
} thread_t;

typedef struct mutex
{
    // * PUBLIC
    // ! PRIVATES
    /**
     * @brief The mutex.
     */
    MUTEX PRIVATE(mutex);
    // ? METHODS
    /**
     * @brief Lock the mutex to the current thread.
     * 
     * @param mutex The mutex to lock the thread to.
     */
    void (*lock)(struct mutex* mutex);

    /**
     * @brief Release the ownership of the mutex from the current thread.
     * 
     * @param thread The mutex to release the thread is locked to.
     */
    void (*release)(struct mutex* mutex);

    /**
     * @brief Destroy the mutex.
     * 
     * @param mutex The mutex to destroy.
     */
    void (*destroy)(struct mutex* mutex);
} mutex_t;

/**
 * @brief Summon a new thread.
 * 
 * @param routine The routine to execute.
 * @param args The arguments to pass to the routine.
 * @return thread_t* The thread.
 */
thread_t* summon_thread(routine_t routine, ROUTINE_ARGS args);

/**
 * @brief Initialize a new mutex.
 * 
 * @return mutex_t The new mutex.
 */
mutex_t* mutex_init();

#ifdef __cplusplus
}
#endif


#endif // __THREAD__
