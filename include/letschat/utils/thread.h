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

#define ROUTINE(name) ROUTINE_RETV __stdcall name(ROUTINE_ARGS args)
typedef ROUTINE_RETV (__stdcall *routine_t)(ROUTINE_ARGS);

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


#endif // __THREAD__
