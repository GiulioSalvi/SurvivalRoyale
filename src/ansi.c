/**
 * \file 
 * \brief Implemented following https://en.wikipedia.org/wiki/ANSI_escape_code.
 *   
 *  Function's names are as much as possible consistent with the quoted document.
 *  
 *  NOTICE: not every function declared in this header is part of ANSI standard.
 * 
 *  NOTICE: for these structures are available some builders function that you should use if you want to build structures with unset properties.
**/

#include "ansi.h"

// BUILDERS section

rgb buildRgb() {
    rgb rgb = {
        .r = NONE,
        .g = NONE,
        .b = NONE
    };
    
    return rgb;
}

ansiRgbColor buildAnsiRgbColor() {
    ansiRgbColor c = {
        .fgRgb = buildRgb(),
        .bgRgb = buildRgb()
    };

    return c;
}

ansiStandardColor buildAnsiStandardColor() {
    ansiStandardColor c = {
        .fgColor = NONE,
        .bgColor = NONE
    };
    
    return c;
}

color buildColor() {
    color c = {
        .isRgbColor = false,
        .color = {
            .stdColor = buildAnsiStandardColor()
        }
    };

    return c;
}

graphicRendition buildGraphicRendition() {
    graphicRendition gr = {
        .bold = false,
        .italic = false,
        .underlined = NONE,
        .color = buildColor()
    };

    return gr;
}

//BUILDERS section end

// UTILITY FUNCTIONS section

bool validateRgb(rgb rgbColor) {
    if(rgbColor.r < 0 || rgbColor.r > 255)
        return false;
    if(rgbColor.g < 0 || rgbColor.g > 255)
        return false;
    if(rgbColor.b < 0 || rgbColor.b > 255)
        return false;
    
    return true;
}

void clearScreen() {
    eraseInDisplay(1);
    eraseInDisplay(2);

    cursorPosition(1, 1);
}

void setForegroundColor(color color) {
    if(color.isRgbColor) {
        if(!validateRgb(color.color.rgbColor.fgRgb))
            return;
        
        setRGBForegroundColor(color.color.rgbColor.fgRgb);
    } else
        setStandardForegroundColor(color.color.stdColor.fgColor);
}

void setBackgroundColor(color color) {
    if(color.isRgbColor) {
        if(!validateRgb(color.color.rgbColor.bgRgb))
            return;
        
        setRGBBackgroundColor(color.color.rgbColor.bgRgb);
    } else
        setStandardBackgroundColor(color.color.stdColor.bgColor);
}

void setColor(color color) {
    if(color.isRgbColor)
        if(!validateRgb(color.color.rgbColor.bgRgb) || !validateRgb(color.color.rgbColor.fgRgb))
            return;
    
    setBackgroundColor(color);
    setForegroundColor(color);
}

void printGraphicRendition(char* text, graphicRendition rendition) {
    if(rendition.bold)
        bold();
    if(rendition.italic)
        italic();
    if(rendition.underlined == 1)
        underlined();
    else if(rendition.underlined == 2)
        doublyUnderlined();
    if(rendition.color.isRgbColor)
        setColor(rendition.color);

    printf("%s", text);
    graphicReset();
}

void printgr(const char* text) {
    for(int i = 0; i < strlen(text); i++) {
        if(text[i] == '#') {
            int offset = 0;
            if(containsFrom(text, '#', i + 1))
                offset = offsetFromNext(text, '#', ++i);
            else
                continue;

            errno = 0;
            char* substr = substring(text, i, offset), *endptr;
            int n = 0;

            if(isDecimalDigit(text[i]))
                n = strtol(substr, &endptr, 10);
            
            if(offset == 0)
                printf("#");
            if(offset >= 8) { // rgb
                int semicolonCount = count(substr, ';', 0);

                if(semicolonCount == 3) { // valid rgb (#fg;r;g;b# or #bg;r;g;b#)
                    int semicolonOffset = offsetFromNext(text, ';', i) - 1;
                    
                    if(semicolonOffset != 1)
                        continue;
                    
                    char* str = substring(text, i, 2);
                    bool fg = strcmp("fg", str) == 0;
                    free(str);
                    i += 3;
                    rgb rgb = buildRgb();

                    for(int j = 0; j <= 2; j++) {
                        semicolonOffset = j == 2 ? offsetFromNext(text, '#', i) - 1 : offsetFromNext(text, ';', i);
                        
                        errno = 0;
                        char* v = substring(text, i, semicolonOffset), *endptr_;
                        int n = strtol(v, &endptr_, 10);
                        free(v);
                        if(errno == ERANGE || *endptr_ != '\0' && endptr_ == NULL)
                            break;

                        if(j == 0)
                            rgb.r = n;
                        else if(j == 1)
                            rgb.g = n;
                        else if(j == 2)
                            rgb.b = n;

                        i += j == 2 ? semicolonOffset : semicolonOffset + 1;
                    }
                    
                    if(fg)
                        setRGBForegroundColor(rgb);
                    else
                        setRGBBackgroundColor(rgb);
                }
            } else if((n >= 30 && n <= 37) || (n >= 90 && n <= 97) || (n >= 40 && n <= 47) || (n >= 100 && n <= 107)) { // standard
                if((n >= 30 && n <= 37) || (n >= 90 && n <= 97)) {
                    setStandardForegroundColor(n);
                    i += offset;
                } else if((n >= 40 && n <= 47) || (n >= 100 && n <= 107)) {
                    setStandardBackgroundColor(n);
                    i += offset;
                }
            } else if(strcmp(substr, "b") == 0) {
                i++;
                bold();
            } else if(strcmp(substr, "i") == 0) {
                i++;
                italic();
            } else if(strcmp(substr, "u") == 0) {
                i++;
                underlined();
            } else if(strcmp(substr, "du") == 0) {
                i += 2;
                doublyUnderlined();
            } else if(strcmp(substr, "bl") == 0) {
                i += 2;
                slowBlinking();
            } else if(strcmp(substr, "r") == 0) {
                i++;
                graphicReset();
            }

            free(substr);
        } else
            printf("%c", text[i]);

        
        fflush(stdout);
    }
}

void printfgr(char* text, ...) {
    va_list args;
    va_start(args, text);

    vector* t = buildVector();

    for(int i = 0; i < strlen(text); i++) {
        if(text[i] != '%')
            pushBack(t, text[i]);
        else {
            i++;

            if(text[i] == '%')
                pushBack(t, '%');
            else if(text[i] == 'd' || text[i] == 'i' || text[i] == 'u' || text[i] == 'x' || text[i] == 'X') {
                int n = va_arg(args, int), snLen = nDigits(n) + 2;
                char* sn = (char*)malloc(snLen*sizeof(char));
                if(sn == NULL)
                    exit(EXIT_ALLOC_FAILURE);

                snprintf(sn, snLen, "%d", n);

                for(int j = 0; j < strlen(sn); j++)
                    pushBack(t, sn[j]);
                
                free(sn);
            } else if(text[i] == 'f' || text[i] == 'F') {
                double n = va_arg(args, double);
                char format[16];
                snprintf(format, 16, "%%.%df", NUMBER_DECIMALS_DIGITS);

                int snLen = NUMBER_DECIMALS_DIGITS + nDigits(floor(n)) + 3;
                char* sn = (char*)malloc(snLen*sizeof(char));
                if(sn == NULL)
                    exit(EXIT_ALLOC_FAILURE);

                snprintf(sn, snLen, format, n);

                for(int j = 0; j < strlen(sn); j++) 
                    pushBack(t, sn[j]);
                
                free(sn);
            } else if(text[i] == 's') {
                char* s = va_arg(args, char*);

                for(int j = 0; j < strlen(s); j++) 
                    pushBack(t, *(s + j));

            } else if(text[i] == 'n')
                ;
        }
    }
    
    pushBack(t, '\0');
    printgr(t->data);

    freeVector(t);
}

char getChar() {
    fflush(stdin);

    #ifndef _WIN32
        struct termios term;
        tcgetattr(STDIN_FILENO, &term);

        term.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &term);

        char c;
        int rs = read(STDIN_FILENO, &c, 1);

        tcgetattr(STDIN_FILENO, &term);

        term.c_lflag |= (ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &term);

        return rs == 1 ? c : -1;
    #else
        return getch();
    #endif
}

void Pause(bool clear) {
    getChar();

    if(clear)
        clearScreen();
}

void screenSize(int* width, int* height) {
    #ifndef _WIN32
        struct winsize ws;

        if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1) {
            *width = ws.ws_col;
            *height = ws.ws_row;
        } else {
            *width = -1;
            *height = -1;
        }
    #else
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

        if (GetConsoleScreenBufferInfo(hStdout, &csbi)) {
            *width = csbi.dwSize.X;
            *height = csbi.dwSize.Y;
        }

        CloseHandle(hStdout);
    #endif
}

// UTILITY FUNCTIONS section end

// CSI section

void cursorUp(int n) {
    if(n <= 0)
        return;
    
    printf("\e[%dA", n);
}

void cursorDown(int n) {
    if(n <= 0)
        return;
    
    printf("\e[%dB", n);
}

void cursorForward(int n) {
    if(n <= 0) 
        return;
    
    printf("\e[%dC", n);
}

void cursorBack(int n) {
    if(n <= 0) 
        return;
    
    printf("\e[%dD", n);
}

void cursorNextLine(int n) {
    if(n <= 0) 
        return;
    
    printf("\e[%dE", n);
}

void cursorPreviousLine(int n) {
    if(n <= 0) 
        return;

    printf("\e[%dF", n);
}

void cursorHorizontalAbsolute(int n) {
    if(n <= 0) 
        return;
    
    printf("\e[%dG", n);
}

void cursorPosition(int n, int m) {
    if(n <= 0) 
        return;
    if(m <= 0)
        return;

    printf("\e[%d;%dH", n, m);
}

void eraseInDisplay(int n) {
    if(n < 0 || n > 3)
        return;

    printf("\e[%dJ", n);
}

void eraseInLine(int n) {
    if(n < 0 || n > 2)
        return;
    
    printf("\e[%dK", n);
}

void scrollUp(int n) {
    if(n <= 0)
        return;
    
    printf("\e[%dS", n);
}

void scrollDown(int n) {
    if(n <= 0)
        return;

    printf("\e[%dT", n);
}

void deviceStatusReport(int* row, int* col) {
    #ifndef _WIN32
        printgr("\e[6n");
        int _ = scanf("\e[%d;%dR", row, col);
    #else
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

        if (GetConsoleScreenBufferInfo(hStdout, &csbi)) {
            *col = csbi.dwCursorPosition.X + 1;
            *row = csbi.dwCursorPosition.Y + 1;
        }

        CloseHandle(hStdout);
    #endif
}

// CSI section end

// SGR section

void graphicReset() {
    printf("\e[0m");
}

void bold() {
    printf("\e[1m");
}

void italic() {
    printf("\e[3m");
}

void underlined() {
    printf("\e[4m");
}

void slowBlinking() {
    printf("\e[5m");
}

void doublyUnderlined() {
    printf("\e[21m");
}

void setStandardForegroundColor(ansiStandardColors foregroundColor) {
    printf("\e[%dm", (int)foregroundColor);
}

void setRGBForegroundColor(rgb rgbColor) {
    if(!validateRgb(rgbColor))
        return;
    
    printf("\e[38;2;%d;%d;%dm", rgbColor.r, rgbColor.g, rgbColor.b);
}

void defaultForegroundColor() {
    printf("\e[39m");
}

void setStandardBackgroundColor(ansiStandardColors backgroundColor) {
    printf("\e[%dm", (int)backgroundColor);
}

void setRGBBackgroundColor(rgb rgbColor) {
    if(!validateRgb(rgbColor))
        return;
    
    printf("\e[48;2;%d;%d;%dm", rgbColor.r, rgbColor.g, rgbColor.b);
}

void defaultBackgroundColor() {
    printf("\e[49m");
}

// SGR section end