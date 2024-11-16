#include "../h/includes.h"
#include "../h/ansi.h"

int printedLines = 0;

//STRING FUNCTIONS section

char* substring(const char* str, int start, int length) {
    if (start < 0 || length < 0 || start + length > strlen(str)) {
        return NULL; 
    }

    char* sub = (char*)malloc(length + 1);

    strncpy(sub, str + start, length);
    sub[length] = '\0';

    return sub;
}

int offsetFromNext(char c, const char* str, int start) {
    for(int i = start, p = 0; i < strlen(str); i++, p++)
        if(str[i] == c)
            return p;
    
    return -1;
}

int count(char c, const char* str, int start) {
    int counter = 0;

    for(int i = 0; i < strlen(str); i++)
        if(str[i] == c)
            counter++;

    return counter;
}

char* concatenate(int num, ...) {
    va_list args;
    va_start(args, num);

    int totalLength = 0;
    for (int i = 0; i < num; i++) {
        char* str = va_arg(args, char*);
        totalLength += strlen(str);
    }

    char* result = (char*)malloc(totalLength + 1);
    if (result == NULL) {
        va_end(args);
        return NULL;
    }

    result[0] = '\0';
    va_start(args, num);
    for (int i = 0; i < num; i++) {
        char* str = va_arg(args, char*);
        strcat(result, str);
    }

    va_end(args);
    return result;
}

bool containsFrom(const char* str, char c, int p) {
    for(int i = p; i < strlen(str); i++)
        if(str[i] == c)
            return true;
    
    return false;
}

bool isDecimalDigit(char c) {
    return (int)c >= 48 && (int)c <= 57;
}

bool isHexDigit(char c) {
    return isDecimalDigit(c) || ((int)c >= 65 && (int)c <= 70) || ((int)c >= 97 && (int)c <= 102);
}

int decimalDigitToInt(char d) {
    return isDecimalDigit(d) ? (int)d - 48 : (int)d;
}

int hexDigitToInt(char d) {
    return isDecimalDigit(d) ? decimalDigitToInt(d) : (isHexDigit(d) ? ((int)d >= 97 ? (int)d - 97 + 10 : (int)d - 65 + 10) : (int)d);
}

int evalutateBase(char* num) {
    char max = -1;

    for(int i = 0; i < strlen(num); i++) {
        if(isHexDigit(num[i])) {
            if(num[i] > max)
                max = num[i];
        } else
            return -1;
    }

    return hexDigitToInt(max) + 1;
    
}

#ifndef _WIN32
    void itoa(int n, char* str, int base) {
        int p = 0;
        char* s = (char*)malloc(sizeof(char)*1);

        if(n < 0)
            *(s + p++) = '-';
        else if(n == 0) {
            *str = '0';
            return;
        }

        while(n > 0) {
            *(s + p++) = (char)(48 + n%10);
            n /= 10;
        }
        *(s + p) = '\0';

        for(int i = strlen(s) - 1; i >= 0; i--) {
            *(str + (strlen(s) - 1 - i)) = *(s + i);
        }
        *(str + strlen(s)) = '\0';
    }
#endif

//STRING FUNCTIONS section end

// BUILDERS section

rgb buildRgb() {
    rgb rgb = {
        r: NONE,
        g: NONE,
        b: NONE
    };
    
    return rgb;
}

ansiRgbColor buildAnsiRgbColor() {
    ansiRgbColor c = {
        fgRgb: buildRgb(),
        bgRgb: buildRgb()
    };

    return c;
}

ansiStandardColor buildAnsiStandardColor() {
    ansiStandardColor c = {
        fgColor: NONE,
        bgColor: NONE
    };
    
    return c;
}

color buildColor() {
    color c = {
        isRgbColor: NONE,
        color: {
            stdColor: buildAnsiStandardColor()
        }
    };

    return c;
}

graphicRendition buildGrahicRendition() {
    graphicRendition gr = {
        bold: NONE,
        italic: NONE,
        underlined: NONE,
        color: buildColor()
    };

    return gr;
}

//BUILDERS section end

// UTILITY FUNCTIONS section

void initialClearScreen() {
    int row = 0, _ = 0;

    deviceStatusReport(&_, &row);
    printedLines += row;

    clearScreen();
}

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
    cursorUp(printedLines);
    eraseInDisplay(2);

    printedLines -= printedLines;
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
    if(rendition.bold != NONE)
        bold();
    if(rendition.italic != NONE)
        italic();
    if(rendition.underlined == 1)
        underlined();
    else if(rendition.underlined == 2)
        doublyUnderlined();
    if(rendition.color.isRgbColor != NONE)
        setColor(rendition.color);

    printf("%s", text);
    printedLines += count(ENTER, text, 0);
    graphicReset();
}

void printgr(char* text) {
    for(int i = 0; i < strlen(text); i++) {
        if(text[i] == '#') {
            int offset = 0;
            if(containsFrom(text, '#', i + 1))
                offset = offsetFromNext('#', text, ++i);
            else
                continue;

            char* substr = substring(text, i, offset);
            int n = atoi(substr);

            if(offset >= 8) { // rgb
                int semicolonCount = count(';', substr, 0);

                if(semicolonCount == 3) { // valid rgb (#fg;r;g;b# or #bg;r;g;b#)
                    int semicolonOffset = offsetFromNext(';', text, i) - 1;

                    if(semicolonOffset != 1) 
                        continue;
                    
                    bool fg = strcmp("fg", substring(text, i, 2)) == 0;
                    i += 3;
                    rgb rgb = buildRgb();

                    for(int j = 0; j <= 2; j++) {
                        if(j == 2)
                            semicolonOffset = offsetFromNext('#', text, i) - 1;
                        else
                            semicolonOffset = offsetFromNext(';', text, i) - 1;
                        
                        if(j == 0)
                            rgb.r = atoi(substring(text, i, semicolonOffset + 1));
                        else if(j == 1)
                            rgb.g = atoi(substring(text, i, semicolonOffset + 1));
                        else if(j == 2)
                            rgb.b = atoi(substring(text, i, semicolonOffset + 1));
                        
                        if(j <= 1)
                            i += semicolonOffset + 2;
                        else
                            i += offsetFromNext('#', text, i);
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
            }
            
            if(strcmp(substr, "b") == 0) {
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
            } else if(strcmp(substr, "r") == 0) {
                i++;
                graphicReset();
            }
        } else {
            printf("%c", text[i]);

            if(text[i] == ENTER)
                printedLines++;
        }
        
        fflush(stdout);
    }
}

void printfgr(char* text, ...) {
    va_list args;
    va_start(args, text);

    int p = 0;
    char* t = (char*)calloc(strlen(text), sizeof(char));
    for(int i = 0; i < strlen(text); i++) {
        if(text[i] != '%')
            *(t + p++) = text[i];
        else {
            i++;

            if(text[i] == '%')
                *(t + p) = '%';
            else if(text[i] == 'd' || text[i] == 'i' || text[i] == 'u' || text[i] == 'x' || text[i] == 'X') {
                int n = va_arg(args, int);
                char* sn = (char*)malloc(sizeof(char)*1);

                itoa(n, sn, 10);

                for(int j = 0; j < strlen(sn); j++) 
                    *(t + p++) = *(sn + j);
            } else if(text[i] == 'f' || text[i] == 'F') {
                double n = va_arg(args, double);
                char* sn = (char*)malloc(sizeof(char)*1);
                
                gcvt(n, 6, sn);

                for(int j = 0; j < strlen(sn); j++) 
                    *(t + p++) = *(sn + j);
            } else if(text[i] == 's') {
                char** s = va_arg(args, char**);

                for(int j = 0; j < strlen(*s); j++) 
                    *(t + p++) = *(*s + j);
            } else if(text[i] == 'n')
                ;
        }
    }
    
    *(t + p++) = '\0';
    printgr(t);
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

void deviceStatusReport(int* col, int* row) {
    printgr("\033[6n");

    #ifndef _WIN32
        inputf("\033[%d;%dR", row, col);
    #else
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

        if (GetConsoleScreenBufferInfo(hStdout, &csbi)) {
            *col = csbi.dwCursorPosition.X + 1;
            *row = csbi.dwCursorPosition.Y + 1;
        }
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

void doublyUnderlined() {
    printf("\e[21m");
}

void setStandardForegroundColor(ansiStandardForegroundColors foregroundColor) {
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

void setStandardBackgroundColor(ansiStandardBackgroundColors backgroundColor) {
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

// INPUTS section

char getChar() {
    #ifndef _WIN32
        char c;
        if(read(STDIN_FILENO, &c, 1) == 1)
            return c;
        else
            return -1;
    #else
        return getch();
    #endif
}

void prepareAnsi() {
    #ifndef _WIN32
        struct termios term;
        tcgetattr(STDIN_FILENO, &term);

        term.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
    #else
        ;
    #endif
}

void endAnsi() {
    #ifndef _WIN32
        struct termios term;
        tcgetattr(STDIN_FILENO, &term);

        term.c_lflag |= (ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
    #else
        ;
    #endif
}

void endInputf(va_list args, int enterCount) {
    printedLines += enterCount;
    va_end(args);

    endAnsi();
}

int inputf(const char* format, ...) {
    prepareAnsi();

    va_list args;
    va_start(args, format);

    char c;
    int inputs = count('%', format, 0), p = 0, i = 0, enterCount = 0, successfulInputs = 0, formatLen = strlen(format), consumedChars = 0;
    for(p = 0; feof(stdin) == 0 && i < inputs && p < formatLen; p++) {
        if(format[p++] == '%') {
            if(strcmp(substring(format, p, 1), "%") == 0) {
                i++;
                successfulInputs++;
            } else if(strcmp(substring(format, p, 1), "c") == 0) { // char
                if(feof(stdin) != 0) {
                    endInputf(args, enterCount);

                    return -2;
                }

                while((c = getChar()) == ENTER) {
                    // prints consumed char
                    printf("%c", c);
                    fflush(stdout);

                    enterCount += 2;
                    consumedChars++;
                }

                // prints c and a new line
                printf("%c\n", c);
                fflush(stdout);

                enterCount += 2;
                
                char* charRef = va_arg(args, char*);
                *charRef = c;
                
                // checks if argument was really char* type
                if(*charRef != c) {
                    endInputf(args, enterCount);

                    return -3;
                }

                i++;
                successfulInputs++;
            } else if(strcmp(substring(format, p, 1), "d") == 0) { // decimal integer
                if(feof(stdin) != 0) {
                    endInputf(args, enterCount);

                    return -2;
                }

                char* num = (char*)malloc(sizeof(char)*1);
                int j = 0, sign = 0;
                bool skip = false; // flag to skip if invalid input has been inserted
                
                // gets buffered the input as a string
                while((c = getChar()) != ENTER) {
                    // prints consumed char
                    printf("%c", c);
                    fflush(stdout);

                    consumedChars++;

                    if(c == '+'){
                        if(sign != 0 || j > 0) {
                            skip = true;
                            break;
                        }

                        sign = 1;
                    } else if(c == '-') {
                        if(sign != 0 || j > 0) {
                            skip = true;
                            break;
                        }
                        
                        sign = -1;
                    } else if(!isDecimalDigit(c)) {
                        skip = true;
                        break;
                    } else
                        *(num + j++) = c;
                }
                
                // prints a new line
                printf("\n");
                fflush(stdout);
                
                enterCount += 2;

                if(skip) {
                    i++;
                    free(num);
                    continue;
                } else
                    *(num + j++) = '\0';
                
                if(sign == 0)
                    sign = 1;

                // converts the num buffered as a string to int
                int n = 0;
                for(int k = 0; k < strlen(num); k++) {
                    n += decimalDigitToInt(num[k]);
                    if(k < strlen(num) - 1)
                        n *= 10;
                }
                n *= sign;

                int* intBuffer = va_arg(args, int*);
                *intBuffer = n;
                
                // checks if argument was really int* type
                if(*intBuffer != n) {
                    endInputf(args, enterCount);
                    free(num);

                    return -3;
                }

                free(num);
                i++;
                successfulInputs++;
            } else if(strcmp(substring(format, p, 1), "i") == 0) { // integer
                if(feof(stdin) != 0) {
                    endInputf(args, enterCount);

                    return -2;
                }

                char* num = (char*)malloc(sizeof(char)*1);
                int j = 0, sign = 0;
                bool skip = false; // flag to skip if invalid input has been inserted

                // gets buffered input as a string
                while((c = getChar()) != ENTER) {
                    // prints consumed char
                    printf("%c", c);
                    fflush(stdout);
                    
                    consumedChars++;

                    if(c == '+') {
                        if(sign != 0 || j > 0) {
                            skip = true;
                            break;
                        }

                        sign = 1;
                    } else if(c == '-') {
                        if(sign != 0 || j > 0) {
                            skip = true;
                            break;
                        }

                        sign = -1;
                    } else if(!isDecimalDigit(c)) {
                        skip = true;
                        break;
                    } else
                        *(num + j++) = c;
                }

                // prints a new line
                printf("\n");
                fflush(stdout);

                enterCount += 2;

                if(skip) {
                    i++;
                    free(num);
                    continue;
                } else
                    *(num + j++) = '\0';
                
                if(sign == 0)
                    sign = 1;

                // evalutates the base of the given number
                int base = evalutateBase(num), n = 0;
                // converts the num buffered as a string to int
                for(int k = strlen(num) - 1; k >= 0; k--)
                    n += pow(base, strlen(num) - 1 - k)*hexDigitToInt(num[k]);          
                n *= sign;

                int* intBuffer = va_arg(args, int*);
                *intBuffer = n;

                // checks if argument was really int* type
                if(*intBuffer != n) { 
                    endInputf(args, enterCount);
                    free(num);

                    return -3;
                }

                free(num);
                i++;
                successfulInputs++;
            } else if(strcmp(substring(format, p, 1), "u") == 0) { // unsigned decimal integer
                if(feof(stdin) != 0) {
                    endInputf(args, enterCount);

                    return -2;
                }

                char* num = (char*)malloc(sizeof(char)*1);
                int j = 0;
                bool skip = false; // flag to skip if invalid input has been inserted

                // gets buffered input as a string
                while((c = getChar()) != ENTER) {
                    // prints consumed char
                    printf("%c", c);
                    fflush(stdout);

                    if(!isDecimalDigit(c)) {
                        skip = true;
                        break;
                    } else
                        *(num + j++) = c;
                }

                // prints a new line
                printf("\n");
                fflush(stdout);

                enterCount += 2;

                if(skip) {
                    i++;
                    free(num);
                    continue;
                } else 
                    *(num + j++) = '\0';

                // converts the num buffered as a string to int
                int n = 0;
                for(int k = 0; k < strlen(num); k++) {
                    n += decimalDigitToInt(num[k]);
                    if(k < strlen(num) - 1)
                        n *= 10;
                }

                int* intBuffer = va_arg(args, int*);
                *intBuffer = n;

                // checks if argument was really int* type
                if(*intBuffer != n) {
                    endInputf(args, enterCount);
                    free(num);

                    return -3;
                }

                free(num);
                i++;
                successfulInputs++;
            } else if(strcmp(substring(format, p, 1), "x") == 0 || strcmp(substring(format, p, 1), "X") == 0) { // unsigned hexadecimal integer
                if(feof(stdin) != 0) {
                    endInputf(args, enterCount);

                    return -2;
                }

                char* num = (char*)malloc(sizeof(char)*1);
                int j = 0;
                bool skip = false; // flag to skip if invalid input has been inserted

                // gets buffered input as a string
                while((c = getChar()) != ENTER) {
                    // prints consumed char
                    printf("%c", c);
                    fflush(stdout);

                    if(!isHexDigit(c)) {
                        skip = true;
                        break;
                    } else
                        *(num + j++) = c;
                }

                // prints a new line
                printf("\n");
                fflush(stdout);

                enterCount += 2;

                if(skip) {
                    i++;
                    free(num);
                    continue;
                } else
                    *(num + j++) = '\0';

                // converts the num buffered as a string to int
                int n = 0;
                for(int k = strlen(num) - 1; k >= 0; k--)
                    n += pow(16, strlen(num) - 1 - k)*hexDigitToInt(num[k]);
                
                int* intBuffer = va_arg(args, int*);
                *intBuffer = n;

                // checks if argument was really int* type
                if(*intBuffer != n) {
                    endInputf(args, enterCount);
                    free(num);

                    return -3;
                }

                free(num);
                i++;
                successfulInputs++;
            } else if(strcmp(substring(format, p, 1), "f") == 0 || strcmp(substring(format, p, 1), "F") == 0) { // decimal floating point number
                if(feof(stdin) != 0) {
                    endInputf(args, enterCount);

                    return -2;
                }
                
                char* num = (char*)malloc(sizeof(char)*1);
                int j = 0, sign = 0, pointP = 0;
                bool skip = false; // flag to skip if invalid input has been inserted

                // gets buffred input as a string
                while((c = getChar()) != ENTER) {
                    // prints consumed char
                    printf("%c", c);
                    fflush(stdout);
                    
                    consumedChars++;

                    if(c == '+') {
                        if(sign != 0) {
                            skip = true;
                            break;
                        }

                        sign = 1;
                    } else if(c == '-') {
                        if(sign != 0  || j > 0) {
                            skip = true;
                            break;
                        }

                        sign = -1;
                    } else if(c == '.' || c == ',') {
                        if(pointP != 0) {
                            skip = true;
                            break;
                        }
                        
                        if(j == 0)
                            *(num + j++) = '0';
                        
                        pointP = j;
                        *(num + j++) = c;
                    } else if(!isDecimalDigit(c)) {
                        skip = true;
                        break;
                    } else
                        *(num + j++) = c;
                }

                // prints a new line
                printf("\n");
                fflush(stdout);

                enterCount += 2;

                if(skip) {
                    i++;
                    free(num);
                    continue;
                } else {
                    if(pointP == 0) {
                        pointP = j;
                        *(num + j++) = '.';
                        *(num + j++) = '0';
                    }

                    *(num + j++) = '\0';
                }
                
                if(sign == 0)
                    sign = 1;
                
                // converts the num buffered as a string to float
                float n = 0.0;
                // evalutates integer part
                for(int k = 0; k < pointP; k++) {
                    n += decimalDigitToInt(num[k]);
                    if(k < pointP - 1)
                        n *= 10;
                }
                // evalutates fractional part
                for(int k = pointP + 1; k < strlen(num); k++)
                    n += (float)decimalDigitToInt(num[k])*pow(10, pointP - k);
                n *= sign;

                float* floatBuffer = va_arg(args, float*);
                *floatBuffer = n;

                // checks is argument was really float* type
                if(*floatBuffer != n) {
                    endInputf(args, enterCount);
                    free(num);

                    return -3;
                }

                free(num);
                i++;
                successfulInputs++;
            } else if(strcmp(substring(format, p, 1), "s") == 0) { // string
                if(feof(stdin) != 0) {
                    endInputf(args, enterCount);

                    return -2;
                }
                
                char** s = va_arg(args, char**);
                int j = 0;
                while((c = getChar()) != (p + 1 == formatLen ? ENTER : ' ')  && feof(stdin) == 0) {
                    // prints consumed char
                    printf("%c", c);
                    fflush(stdout);

                    consumedChars++;

                    *(*s + j++) = c;
                }
                
                *(*s + j++) = '\0';

                consumedChars++;
                if(p + 1 == formatLen) {
                    enterCount += 2;
                    
                    // prints a new line
                    printf("\n");
                    fflush(stdout);
                } else {
                    printf(" ");
                    fflush(stdout);
                }

                // checks if argument was really char* type
                if(j - 1 != strlen(*s)) {
                    endInputf(args, enterCount);
                    free(s);

                    return -3;
                }

                free(s);
                i++;
                successfulInputs++;
            } else if(strcmp(substring(format, p, 1), "n") == 0) { // n consumed chars
                int* consumedCharsBuffer = va_arg(args, int*);
                *consumedCharsBuffer = consumedChars;

                // checks if argument was really int* type
                if(*consumedCharsBuffer != consumedChars) {
                    endInputf(args, enterCount);
                    
                    return -3;
                }

                i++;
                successfulInputs++;
            } else { // Handles non-format-specifiers chars, if not whitespaces returns
                if(feof(stdin) != 0) {
                    endInputf(args, enterCount);

                    return -1;
                }
                
                while((c = getChar()) != format[p] && feof(stdin) == 0) {
                    // prints consumed char
                    printf("%c", c == ENTER ? ENTER : c);
                    // fflush(stdout);

                    if (c == ENTER)
                        enterCount += 2;
                    consumedChars++;
                }
            }
        }
    }

    endInputf(args, enterCount);

    return successfulInputs;
}

// INPUTS section end