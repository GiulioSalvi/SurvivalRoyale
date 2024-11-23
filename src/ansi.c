#include "../h/includes.h"
#include "../h/ansi.h"

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
    system("clear");
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
            } else if(strcmp(substr, "bl") == 0) {
                i += 2;
                slowBlinking();
            } else if(strcmp(substr, "r") == 0) {
                i++;
                graphicReset();
            }
        } else
            printf("%c", text[i]);

        
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

void deviceStatusReport(int* row, int* col) {
    printgr("\e[6n");

    #ifndef _WIN32
        scanf("\e[%d;%dR", row, col);
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