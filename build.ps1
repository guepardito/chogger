if (-Not (Test-Path -Path "./build")) {
    New-Item -ItemType Directory -Force -Path "./build"
}

# Compile the source code
gcc -Wall -Wextra -c chogger.c -o ./build/chogger.o

# Create the static library
ar rcs ./build/libchogger.a ./build/chogger.o