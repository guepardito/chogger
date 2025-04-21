# Chogger
**Chogger** is a minimal logging system for C. It allows you to log messages with different severity levels to a file.

# 🚀 Features
- ✅ **Log levels**: DEBUG, INFO, NOTICE, WARN, ERROR, CRIT, ALERT, EMERG
- 📋**File logging:** Appends logs to a file automatically
- 🕒 **Timestamps:** Logs include formatted date and time (`[YYYY-MM-DD HH:MM:SS]`)
- 🧵 **Thread-safe:** Cross-platform mutex support (POSIX and Windows)
- 🧹 **Automatic cleanup:** Automatically closes the log file on exit
- 📦 **Minimal API:** Easy to integrate in any C project

# ✅ usage
1. **Place the `.a` library and `.h` header file in your project:**

    Copy the following files from the library folder into your project:

    - `libchogger.a` (the static library)
    - `chogger.h` (the header file)

2. **Include the header in your source code:**

    In your `main.c` or any other source file that needs to use the logger, include the header like this:

    ```c
    #include "chogger.h"
    ```
    
3. **Initialize the logger and log messages:**

    Inside your `main` function or wherever you want to use the logger, initialize it and log messages as follows:

    ```c
    chog_init(".log");

    chog_log(INFO, "Application started successfully");
    ```

4. **Link the library:**

    Make sure to link the static library while compiling your code using the following:

    On linux:
    ```c
    gcc example.c -L. -lchogger -o main
    ```

    On windows:
    ```c
    gcc example.c ./libchogger.lib -o main.exe
    ```

# 🛠️ Build
To compile `chogger` from source, use the provided build scripts.

- On **Linux**, this will generate `libchogger.a` (static library).
- On **Windows**, this will generate `chogger.lib` (MSVC-compatible static library).

You can then link these files to your projects.