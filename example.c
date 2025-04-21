#include "chogger.h"

int main() {
    chog_init("example.log");

    chog_log(CHOG_INFO, "Application started.");
    chog_log(CHOG_DEBUG, "Debugging details here.");
    chog_log(CHOG_WARN, "This is a warning message.");
    chog_log(CHOG_ERROR, "Something went wrong!!!");
    chog_log(CHOG_NOTICE, "This message notice message.");

    chog_close_logger();
    return 0;
}
