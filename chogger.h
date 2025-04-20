#ifndef __CHOGGER_H__
#define __CHOGGER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

typedef struct 
{
    int initialized;
    FILE* output;
} CHOG_LOGGER;

/// @brief Initializes the logger with the given file name (append mode)
/// @param file_name Path to the log file
/// @return A CHOG_LOGGER struct with state info. If file can't be opened, logger will not be initialized
CHOG_LOGGER chog_init(const char* file_name);

/// @brief Closes the log file if the logger was initialized
void chog_close_logger();

/// @brief Logs a message with a given severity level
/// @param level Log level (DEBUG, INFO, etc)
/// @param msg The message to be logged
void chog_log(CHOG_LEVEL level, char*  msg);

/// @brief Converts a CHOG_LEVEL enum to a string
/// @param level Log level (DEBUG, INFO, etc)
/// @return String representation of the level, or "UNKNOWN" if invalid
const char* chog_level_parser(CHOG_LEVEL level);

#endif