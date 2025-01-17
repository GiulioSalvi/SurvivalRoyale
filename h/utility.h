#include "consts.h"
#include "includes.h"

#ifndef _UTILITY_H_
    /// @brief Include guard.
    #define _UTILITY_H_

    /// @brief Copies a substring from the passed string.
    /// @param str String to copy from.
    /// @param start The position in str to start to copy from.
    /// @param length The length of the substring.
    /// @return The substring.
    char* substring(const char* str, int start, int length);
    /// @brief Counts the offset in the string between the position and the next occoruncy of the passed char.
    /// @param c The char to search to.
    /// @param str The string where to search the occoruncy.
    /// @param start The position where to start
    /// @return The offset from the start position to the next occorncy of the char. Otherwise, if no more occoruncies occur, returns -1.
    int offsetFromNext(const char* str, char c, int start);
    /// @brief Counts the number of occoruncies in the string, from a passed position, of the passed char.
    /// @param c The char to count on the occoruncies in the string.
    /// @param str The string to count from.
    /// @param start The start position in the string to count from.
    /// @return Returns the number of occoruncies of the char in the string. If there are not occoruncies of the char in the passed string, returns 0.
    int count(const char* str, char c, int start);
    /// @brief Checks if there is an occoruncy of the passed char from the passed position in the passed string.
    /// @param str The string to check in. 
    /// @param c The char to look for.
    /// @param p The position from which starts.
    /// @return True if an occoruncy is found, false otherwise.
    bool containsFrom(const char* str, char c, int p);
    /// @brief Checks if there is an occoruncy of the passed substring from the passed position in the passed string.
    /// @param str The string to check in.
    /// @param subStr The substring to look for.
    /// @param p The position from which starts.
    /// @return True if an occoruncy is found, false otherwise.
    bool containsSubstringFrom(const char* str, const char* subStr, int p);
    /// @brief Checks if a char is a decimal digit.
    /// @param c The char to check.
    /// @return True if the char is decimal digit, false otherwise.
    bool isDecimalDigit(char c);
    /// @brief Checks if a char is a hexadecimal digit (not case sensitive).
    /// @param c The char to check.
    /// @return True if the char is a hexadecima digit, false otherwise.
    bool isHexDigit(char c);
    /// @brief If is a decimal digit, converts it to int; Otherwise returns ASCII integer representation of the passed char.
    /// @param d The char to convert.
    /// @return The digit as an integer if the char is a decimal digit, ASCII integer representation of the passed char otherwise.
    int decimalDigitToInt(char d);
    /// @brief If is a hexadecimal digit (not case sensitive), converts it to int; Otherwise returns ASCII integer representation of the passed char.
    /// @param d The char to convert.
    /// @return The digit as an integer if the char is a hexadecimal giti, ASCII integer representation of the passed char otherwise.
    int hexDigitToInt(char d);
    /// @brief Evalutates the base of the number (by finding the biggest digit up to hexadecimal digit F) and returns it. If the string contains a non-digit char, returns -1.
    /// @param num The number in text format.
    /// @return The base of the number, if it is valid. Otherwise -1.
    int evalutateBase(char* num);
    /// @brief Evalutates the number of digits of a number.
    /// @param n The number.
    /// @return The number of digits.
    int nDigits(int n);
#endif