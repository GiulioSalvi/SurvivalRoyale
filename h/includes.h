/**
 * \file
 * \brief Preprocessor file used for including library for modules.
**/

/// @brief Used in some structure for meaning that a field is unset, instead of using NULL.
#define NONE 1

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
    #include <tlhelp32.h>
#else
    #include <unistd.h>
    #include <termios.h>
    #include <sys/ioctl.h>
#endif

#include <math.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdalign.h>