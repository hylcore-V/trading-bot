#ifndef COMMAND_H
#define COMMAND_H

#include <inttypes.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_platform.h>

// <https://stackoverflow.com/a/44383330/1987178>
#ifdef _WIN32
# define PRIexitcode "lu"
# ifdef _WIN64
#   define PRIsizet PRIu64
# else
#   define PRIsizet PRIu32
# endif
#else
# define PRIsizet "zu"
# define PRIexitcode "d"
#endif

#ifdef __WINDOWS__
# include <winsock2.h> // not needed here, but must never be included AFTER windows.h
# include <windows.h>
# define PROCESS_NONE NULL
  typedef HANDLE process_t;
  typedef DWORD exit_code_t;
#else
# include <sys/types.h>
# define PROCESS_NONE -1
  typedef pid_t process_t;
  typedef int exit_code_t;
#endif
# define NO_EXIT_CODE -1

enum process_result {
    PROCESS_SUCCESS,
    PROCESS_ERROR_GENERIC,
    PROCESS_ERROR_MISSING_BINARY,
};

enum process_result cmd_execute(const char *path, const char *const argv[], process_t *process);
SDL_bool cmd_terminate(process_t pid);
SDL_bool cmd_simple_wait(process_t pid, exit_code_t *exit_code);

process_t adb_execute(const char *serial, const char *const adb_cmd[], int len);
process_t adb_forward(const char *serial, uint16_t local_port, const char *device_socket_name);
process_t adb_forward_remove(const char *serial, uint16_t local_port);
process_t adb_reverse(const char *serial, const char *device_socket_name, uint16_t local_port);
process_t adb_reverse_remove(const char *serial, const char *device_socket_name);
process_t adb_push(const char *serial, const char *local, const char *remote);
process_t adb_install(const char *serial, const char *local);

// convenience function to wait for a successful process execution
// automatically log process errors with the provided process name
SDL_bool process_check_success(process_t process, const char *name);

#endif
