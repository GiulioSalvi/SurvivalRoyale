#include "utility.h"

/**
 * @brief Implemented following https://en.wikipedia.org/wiki/ANSI_escape_code
 *   
 *  Function's names are as much as possible consistent with the quoted document.
 *  
 *  NOTICE: not every function declared in this header is part of ANSI standard.
 *  NOTICE: for these structures are available some builders function that you should use if you want to build structures with unset properties.
 */

/// @brief Defines how many decimals digits should use printfgr when printing floating-point numbers. If there are leading digits, it approximates the number to a floating-point number with this number of decimal digits
#define NUMBER_DECIMALS_DIGITS 6

/// @brief Defines the type underlined as unsigned integer 1 byte large.
typedef uint8_t underline;
/// @brief Defines the ttype ansiStandardColors as unsigned integer 1 byte large.
typedef uint8_t ansiStandardColors;

/// @brief Defines a basic structure for RGB colors.
typedef struct rgb {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb;

/// @brief Defines a basic structure for standard ANSI foreground color and background color.
typedef struct ansiStandardColor {
    ansiStandardColors fgColor;
    ansiStandardColors bgColor;
} ansiStandardColor;

/// @brief Defines a basic structure for RGB foreground color and background color
typedef struct ansiRgbColor {
    rgb fgRgb;
    rgb bgRgb;
} ansiRgbColor;

/// @brief Defines a union between RGB colors and standard ANSI colors (should not be used externally)
typedef union __color {
    ansiRgbColor rgbColor;
    ansiStandardColor stdColor;
} __color;

/// @brief Defines a struct for representing a generic color
typedef struct color {
    bool isRgbColor;
    __color color;
} color;

/// @brief Defines a struct for graphic rendition including propreties for bold, italic, underlined and colored text
typedef struct graphicRendition {
    bool bold;
    bool italic;
    underline underlined;
    color color;
} graphicRendition;

// BUILDERS section

/// @brief Builds a rgb struct.
/// @return Returns a rgb struct with properties set to NONE.
rgb buildRgb();
/// @brief Builds a ANSI rgb color struct.
/// @return Returns a ANSI rgb color struct with properties set to NONE.
ansiRgbColor buildAnsiRgbColor();
/// @brief Builds a ANSI standard color struct.
/// @return Returns a ANSI standard color struct with properties set to NONE.
ansiStandardColor buildAnsiStandardColor();
/// @brief Builds a color struct.
/// @return Returns a color struct with properties set to NONE. isRgbColor property is set to false.
color buildColor();
/// @brief Builds a graphic rendition struct.
/// @return Returns a graphic rendition struct with properties set to NONE. bold and italic properties are set to false.
graphicRendition buildGrahicRendition();

// BUILDERS section end

// UTILITY FUNCTIONS section

/// Checks if  a rgb struct has valids properties.
bool validateRgb(rgb rgbColor);
/// Clears the entire terminal's window's content.
void clearScreen();
/// Sets the terminal's foreground color.
void setForegroundColor(color color);
/// Sets the terminal's background color.
void setBackgroundColor(color color);
/// Sets both terminal's foreground color and background color, if specified.
void setColor(color color);
/// Prints a text with the graphic rendition specified with the struct.
/// Formats specifiers are not handled.
void printGraphicRendition(char* text, graphicRendition rendition);
/// Prints a text with the graphic rendition specified with custom format specifiers.
///
/// Custom format specifiers: #b# for bold text, #i# for italic text, #u# for underlined text, #du# for doubly underlined text, #n# for setting ANSI standard color represented by n, #bl# for slow blinking, #r# for graphic reset.
/// 
/// For setting RGB colors use #fg;r;g;b# or #bg;r;g;b# where fg or bg represents if the color has to be applied to the foreground or to the background and r, g, b are the values for r, g, b components of the color representation and must be between 0 and 255;
/// If the passed format does not comply with this specification, then the passed format text is going to be printed except for the #s.
/// 
/// Standard C formats specifiers are not handled.
void printgr(char* text);
/// Prints text as printgr but handles standard C format specifiers %, d, i, u, x, X, f, F, s, n.
/// Integers are always interpreted in base 10.
void printfgr(char* text, ...);
/// @brief Gets the char pressed on the keyboard without waiting for 'Enter' to be pressed.
/// @return The pressed char on the keyboard.
char getChar();
/// @brief It returns the width and the height of the screen. On unix-like platforms, in case of errors, it sets them to -1.
/// @param width The width, as the number of columns, for the terminal window.
/// @param height The height, as the number of row, for the terminal window.
void screenSize(int* width, int* height);
// UTILITY FUNCTIONS section end

// CSI section

void cursorUp(int n);
void cursorDown(int n);
void cursorForward(int n);
void cursorBack(int n);
void cursorNextLine(int n);
void cursorPreviousLine(int n);
void cursorHorizontalAbsolute(int n);
void cursorPosition(int n, int m);
void eraseInDisplay(int n);
void eraseInLine(int n);
void scrollUp(int n);
void scrollDown(int n);
void deviceStatusReport(int* row, int* col);

// CSI section end

// SGR section

void graphicReset();
void bold();
void italic();
void underlined();
void slowBlinking();
void doublyUnderlined();
void setStandardForegroundColor(ansiStandardColors foregroundColor);
void setRGBForegroundColor(rgb rgbColor);
void defaultForegroundColor();
void setStandardBackgroundColor(ansiStandardColors backgroundColor);
void setRGBBackgroundColor(rgb rgbColor);
void defaultBackgroundColor();

// SGR section end