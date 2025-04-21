#ifndef __CHOGGER_H__
#define __CHOGGER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include <winbase.h>
    typedef CRITICAL_SECTION CHOG_MUTEX;
    #define CHOG_MUTEX_INIT(m) InitializeCriticalSection(&m)
    #define CHOG_MUTEX_LOCK(m) EnterCriticalSection(&m)
    #define CHOG_MUTEX_UNLOCK(m) LeaveCriticalSection(&m)
    #define CHOG_MUTEX_DESTROY(m) DeleteCriticalSection(&m)
#else
    #include <pthread.h>
    typedef pthread_mutex_t CHOG_MUTEX;
    #define CHOG_MUTEX_INIT(m) pthread_mutex_init(&m, NULL)
    #define CHOG_MUTEX_LOCK(m) pthread_mutex_lock(&m)
    #define CHOG_MUTEX_UNLOCK(m) pthread_mutex_unlock(&m)
    #define CHOG_MUTEX_DESTROY(m) pthread_mutex_destroy(&m)
#endif

// Enum that represents different log severity levels
typedef enum 
{
    CHOG_DEBUG,   // Detailed debugging information
    CHOG_INFO,    // General information messages
    CHOG_NOTICE,  // Normal but significant conditions
    CHOG_WARN,    // Warning conditions
    CHOG_ERROR,   // Error conditions
    CHOG_CRIT,    // Critical conditions
    CHOG_ALERT,   // Action must be taken immediately
    CHOG_EMERG    // System is unusable
} CHOG_LEVEL;



/// @brief Initializes the logger with the given file name (append mode)
/// @param file_name Path to the log file
/// @return A CHOG_LOGGER struct with state info. If file can't be opened, logger will not be initialized
void chog_init(const char* file_name);

/// @brief Closes the log file if the logger was initialized
void chog_close_logger();

/// @brief Logs a message with a given severity level
/// @param level Log level (DEBUG, INFO, etc)
/// @param msg The message to be logged
void chog_log(CHOG_LEVEL level, char*  msg);

#endif