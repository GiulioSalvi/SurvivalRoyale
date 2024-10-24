#ifndef INCLUDES
    #define INCLUDES

    #ifndef NONE
        #define NONE -1
    #endif


    #ifndef ENTER
        #ifdef _WIN32
            #define ENTER '\r'
        #else
            #define ENTER '\n'
        #endif
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
    #include <stdio.h>
    #include <stdarg.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
#endif