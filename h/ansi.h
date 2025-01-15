/**
 * \file 
 * \brief Implemented following https://en.wikipedia.org/wiki/ANSI_escape_code.
 *   
 *  Function's names are as much as possible consistent with the quoted document.
 *  
 * 
 *  NOTICE: not every function declared in this header is part of ANSI standard.
 * 
 *  NOTICE: for these structures are available some builders function that you should use if you want to build structures with unset properties.
**/

#include "vector.h"
#include "utility.h"

#ifndef _ANSI_H_
    /// @brief Include guard.
    #define _ANSI_H_
    
    /// @brief Defines how many decimals digits should use printfgr when printing floating-point numbers. If there are leading digits, it approximates the number to a floating-point number with this amount of decimal digits
    #define NUMBER_DECIMALS_DIGITS 6

    /// @brief Defines the type underlined as unsigned integer 1 byte large.
    typedef uint8_t underline;
    /// @brief Defines the ttype ansiStandardColors as unsigned integer 1 byte large.
    typedef uint8_t ansiStandardColors;

    /// @brief Defines a basic structure for RGB colors.
    typedef struct rgb {
        /// @brief Red component field.
        uint8_t r;
        /// @brief Green component field.
        uint8_t g;
        /// @brief Blue component field.
        uint8_t b;
    } rgb;

    /// @brief Defines a basic structure for standard ANSI foreground color and background color for a piece of printable text.
    typedef struct ansiStandardColor {
        /// @brief Foreground ANSI standard color field.
        ansiStandardColors fgColor;
        /// @brief Background ANSI standard color field.
        ansiStandardColors bgColor;
    } ansiStandardColor;

    /// @brief Defines a basic structure for RGB foreground color and background color for a piece of printable text.
    typedef struct ansiRgbColor {
        /// @brief Foreground RGB color field.
        rgb fgRgb;
        /// @brief Background RGB color field.
        rgb bgRgb;
    } ansiRgbColor;

    /// @brief Defines a union between RGB colors and standard ANSI colors (should not be used externally)
    typedef union __color {
        /// @brief RGB color field.
        ansiRgbColor rgbColor;
        /// @brief ANSI standard color field.
        ansiStandardColor stdColor;
    } __color;

    /// @brief Defines a struct for representing a generic color
    typedef struct color {
        /// @brief Boolean flag for determining if the color field is an ansiRgbColor or an ansiStandardColor.
        bool isRgbColor;
        /// @brief Color field.
        __color color;
    } color;

    /// @brief Defines a struct for graphic rendition including properties for bold, italic, underlined and colored text
    typedef struct graphicRendition {
        /// @brief Boolean flag to determine if
        bool bold;
        bool italic;
        underline underlined;
        color color;
    } graphicRendition;


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
    graphicRendition buildGraphicRendition();


    /// @brief Checks if  a rgb struct has valid properties, meaning that all the properites' values are between 0 and 255.
    /// @param rgbColor The struct to be checked.
    /// @return True if it is valid, false otherwise.
    bool validateRgb(rgb rgbColor);
    /// @brief Clears the entire terminal's window's content.
    void clearScreen();
    /// @brief Sets the terminal's foreground color.
    /// @param color The foreground color to be set.
    void setForegroundColor(color color);
    /// @brief Sets the terminal's background color.
    /// @param color The background color to be set.
    void setBackgroundColor(color color);
    /// @brief Sets both terminal's foreground color and background color, if specified.
    /// @param color The colors to be set.
    void setColor(color color);
    /// @brief Prints a text with the graphic rendition specified with the struct. Standard C format specifiers are not handled.
    /// @param text The text to be printed.
    /// @param rendition The graphic rendition for the text.
    void printGraphicRendition(char* text, graphicRendition rendition);
    /// @brief Prints a text with the graphic rendition specified with custom graphic rendition format specifiers.
    /// 
    /// Custom graphic rendition format specifiers: #b# for bold text, #i# for italic text, #u# for underlined text, #du# for doubly underlined text, #n# for setting ANSI standard color represented by n, #bl# for slow blinking, #r# for graphic reset.
    ///
    /// For setting RGB colors use #fg;r;g;b# or #bg;r;g;b# where fg or bg represents if the color has to be applied to the foreground or to the background and r, g, b are the values for r, g, b components of the color representation and must be between 0 and 255;
    ///
    /// If the passed format does not comply with this specification, then the passed format text is going to be printed except for the #s.
    ///
    /// If printing # is needed, use ##.
    ///
    /// Standard C formats specifiers are not handled.
    /// @param text The text with custom graphic rendition format specifiers to be printed.
    void printgr(const char* text);
    /// @brief Prints text as printgr but handles standard C format specifiers %, d, i, u, x, X, f, F, s, n. Integers are always interpreted in base 10.
    /// @param text The text with custom graphic rendition format specifiers and standard C format specifiers.
    /// @param Values Values to be contacetaned.
    void printfgr(char* text, ...);
    /// @brief Gets the char pressed on the keyboard without waiting for 'Enter' to be pressed.
    /// @return The pressed char on the keyboard.
    char getChar();
    /// @brief Waits for the user to press a key without waiting for 'Enter' to be pressed.
    /// @param clear Flag for determining if the screen has to be cleaned, if set to true.
    void Pause(bool clear);
    /// @brief It returns the width and the height of the screen. On unix-like platforms, in case of errors, it sets them to -1.
    /// @param width The width, as the number of columns, for the terminal window.
    /// @param height The height, as the number of row, for the terminal window.
    void screenSize(int* width, int* height);


    /// @brief Moves the cursor up by n rows.
    /// @param n The rows to go up.
    void cursorUp(int n);
    /// @brief Moves the cursor down by n rows.
    /// @param n The rows to go down.
    void cursorDown(int n);
    /// @brief Moves the cursor to the right by n columns.
    /// @param n The columns to go forward.
    void cursorForward(int n);
    /// @brief Moves the cursor to the left by n columns.
    /// @param n The columns to go backward.
    void cursorBack(int n);
    /// @brief Moves the cursor at the beginning of the line n rows down.
    /// @param n The rows to go down.
    void cursorNextLine(int n);
    /// @brief Moves the cursor at the beginning of the line n rows up.
    /// @param n The rows to go up.
    void cursorPreviousLine(int n);
    /// @brief Moves the cursor to column n.
    /// @param n The column to go to.
    void cursorHorizontalAbsolute(int n);
    /// @brief Moves the cursor at n-th row and at the m-th column.
    /// @param n The row to go to.
    /// @param m The column to go to.
    void cursorPosition(int n, int m);
    /// @brief Clears part of the screen.
    /// @param n If n is set to 0, it clears from the cursor to the end of the screen. If n is set to 1, it clears from the cursor to the beginning of the screen. If n is set to 2, it clears the entire screen (on MS-DOS moves the cursor to the upper left corner). If n is set to 3, it clears the screen and erases the scrollback buffer.
    void eraseInDisplay(int n);
    /// @brief Erases part of the line.
    /// @param n If n is set to 0, it clears from the cursor to the end of the line. If n is set to 1, it clears from the cursor to the beginning of the line. If n is set to 2, it clears the entire line. In any case the cursor position is unchanged.
    void eraseInLine(int n);
    /// @brief Scrolls the whole page up by n rows.
    /// @param n The number of the rows to scroll up.
    void scrollUp(int n);
    /// @brief Scrolls the whole page down by n rows.
    /// @param n The number of the rows to scroll down.
    void scrollDown(int n);
    /// @brief Gets the cursor position.
    /// @param row The row of the cursor.
    /// @param col The column of the cursor.
    void deviceStatusReport(int* row, int* col);


    /// @brief Resets the graphic rendition.
    void graphicReset();
    /// @brief Toggles bold text.
    void bold();
    /// @brief Toggles italic text.
    void italic();
    /// @brief Toggles singled underlined text.
    void underlined();
    /// @brief Toggles slow blinking.
    void slowBlinking();
    /// @brief Toggles doubly underlined text.
    void doublyUnderlined();
    /// @brief Sets the ANSI standard foreground color.
    /// @param foregroundColor The ANSI standard foreground color to be set.
    void setStandardForegroundColor(ansiStandardColors foregroundColor);
    /// @brief Sets the RGB foreground color.
    /// @param rgbColor The RGB foreground color to be set.
    void setRGBForegroundColor(rgb rgbColor);
    /// @brief Resets the foreground color.
    void defaultForegroundColor();
    /// @brief Sets the ANSI standard background color.
    /// @param backgroundColor The ANSI standard background color to be set.
    void setStandardBackgroundColor(ansiStandardColors backgroundColor);
    /// @brief Sets the RGB  background color.
    /// @param rgbColor The RGB  background color to be set.
    void setRGBBackgroundColor(rgb rgbColor);
    /// @brief Resets the background color.
    void defaultBackgroundColor();
#endif