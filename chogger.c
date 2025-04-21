#include "chogger.h"

typedef struct 
{
    int initialized;
    FILE* output;
} CHOG_LOGGER;

// Global instances used internally
static CHOG_LOGGER logger;
static CHOG_MUTEX chog_logger_mutex;
static CHOG_MUTEX chog_timestamp_mutex;

// Converts a CHOG_LEVEL value to string
const char *chog_level_parser(CHOG_LEVEL level)
{
    switch (level) {
        case CHOG_DEBUG:  return "DEBUG";
        case CHOG_INFO:   return "INFO";
        case CHOG_NOTICE: return "NOTICE";
        case CHOG_WARN:   return "WARN";
        case CHOG_ERROR:  return "ERROR";
        case CHOG_CRIT:   return "CRITICAL";
        case CHOG_ALERT:  return "ALERT";
        case CHOG_EMERG:  return "EMERGENCY";
        default: return "UNKNOWN";
    }
}

const char* chog_get_timestamp() {
    static char buffer[64];

    CHOG_MUTEX_LOCK(chog_timestamp_mutex);
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S]", t);
    CHOG_MUTEX_UNLOCK(chog_timestamp_mutex);

    return buffer;
}

// Initializes the logger by opening the specified file in append mode.
// If the file is successfully opened, the logger is marked as initialized
// The logger will automatially be closed at program exit
void chog_init(const char* file_name)
{
    if (file_name == NULL) 
    {
        printf("Log file name is empty, nothing will be logged. :(\n");
    }
    logger.output = fopen(file_name, "a");

    if (logger.output != NULL)
    {
        logger.initialized = 1;
        atexit(chog_close_logger);
        CHOG_MUTEX_INIT(chog_logger_mutex);
        CHOG_MUTEX_INIT(chog_timestamp_mutex);
    } else
    {
        fprintf(stderr, "Logger not initialized\n");
    }
}

// Closes the log file if it was successfully opened and the logger is initialized
void chog_close_logger()
{
    if (!logger.initialized) return;

    fclose(logger.output);
    logger.output = NULL;
    logger.initialized = 0;

    CHOG_MUTEX_DESTROY(chog_logger_mutex);
    CHOG_MUTEX_DESTROY(chog_timestamp_mutex);
}

// Logs a message with the format: [LEVEL] Message
// Outputs to both stdout and the log file
// Does nothing if the logger has not been initialized
void chog_log(CHOG_LEVEL level, char* msg)
{
    if (!logger.initialized) return;
    const char* parsed_level = chog_level_parser(level);
    const char* timestamp = chog_get_timestamp();

    size_t msg_size = strlen(parsed_level) + strlen(msg) + strlen(timestamp) + 69;
    char* log_msg = malloc(msg_size);
    
    CHOG_MUTEX_LOCK(chog_logger_mutex);
    snprintf(log_msg, msg_size, "%s [%s] %s", timestamp, parsed_level, msg);

    printf("%s\n", log_msg);
    fputs(log_msg, logger.output);
    fputc('\n', logger.output);
    fflush(logger.output);
    CHOG_MUTEX_UNLOCK(chog_logger_mutex);

    free(log_msg);
}