#include "chogger.h"

// Global logger instance used internally
static CHOG_LOGGER logger;

// Initializes the logger by opening the specified file in append mode.
// If the file is successfully opened, the logger is marked as initialized
// The logger will automatially be closed at program exit
CHOG_LOGGER chog_init(const char* file_name)
{
    if (file_name == NULL) 
    {
        printf("Log file name is empty, nothing will be logged. :(");
    }
    logger.output = fopen(file_name, "a");
    if (logger.output != NULL) logger.initialized = 1;

    // Register the cleanup function to be called at exit
    atexit(chog_close_logger);
    return logger;
}

// Closes the log file if it was successfully opened and the logger is initialized
void chog_close_logger()
{
    if (logger.initialized && logger.output) fclose(logger.output);
}

// Converts a CHOG_LEVEL value to string
const char *chog_level_parser(CHOG_LEVEL level)
{
    switch (level) {
        case DEBUG:  return "DEBUG";
        case INFO:   return "INFO";
        case NOTICE: return "NOTICE";
        case WARN:   return "WARN";
        case ERROR:  return "ERROR";
        case CRIT:   return "CRITICAL";
        case ALERT:  return "ALERT";
        case EMERG:  return "EMERGENCY";
        default:     return "UNKNOWN";
    }
}

// Logs a message with the format: [LEVEL] Message
// Outputs to both stdout and the log file
// Does nothing if the logger has not been initialized
void chog_log(CHOG_LEVEL level, char* msg)
{
    if (!logger.initialized) return;
    const char* parsed_level = chog_level_parser(level);

    size_t msg_size = strlen(parsed_level) + strlen(msg) + 69;
    char* log_msg = malloc(msg_size);
    
    snprintf(log_msg, msg_size, "[%s] %s\n", parsed_level, msg);

    printf("%s", log_msg);
    fprintf(logger.output, log_msg);
    fflush(logger.output);
}