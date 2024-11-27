#ifndef INCLUDES
    #define INCLUDES

    #ifndef NONE
        #define NONE -1
    #endif

    #ifdef _WIN32
        #include <conio.h>
        #include <windows.h>
    #else
        #include <unistd.h>
        #include <termios.h>
    #endif

    #include <math.h>
    #include <time.h>
    #include <errno.h>
    #include <stdio.h>
    #include <assert.h>    
    #include <stdarg.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include <stdalign.h>
#endif