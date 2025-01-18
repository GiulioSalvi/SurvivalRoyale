/**
 * \file
 * \brief Definition of utility functions.
**/

#include "consts.h"
#include "includes.h"

#ifndef _UTILITY_H_
    /// @brief Include guard.
    #define _UTILITY_H_

    /// @brief Copies a substring (heap-allocated) from the passed string.
    /// @param string String to copy from.
    /// @param startPosition The position in str to start to copy from.
    /// @param length The length of the substring.
    /// @return The substring (heap-allocated).
    char* substring(const char* string, int startPosition, int length);
    /// @brief Counts the offset in the string between the position and the next occoruncy of the passed char.
    /// @param string The string where to search the occoruncy.
    /// @param character The char to search to.
    /// @param startPosition The position where to start
    /// @return The offset from the start position to the next occorncy of the char. Otherwise, if no more occoruncies occur, returns -1.
    int offsetFromNext(const char* string, char character, int startPosition);
    /// @brief Counts the number of occoruncies in the string, from a passed position, of the passed char.
    /// @param string The string to count from.
    /// @param character The char to count on the occoruncies in the string.
    /// @param startPosition The start position in the string to count from.
    /// @return Returns the number of occoruncies of the char in the string. If there are not occoruncies of the char in the passed string, returns 0.
    int count(const char* string, char character, int startPosition);
    /// @brief Checks if there is an occoruncy of the passed char from the passed position in the passed string.
    /// @param string The string to check in. 
    /// @param character The char to look for.
    /// @param startPosition The position from which starts.
    /// @return True if an occoruncy is found, false otherwise.
    bool containsFrom(const char* string, char character, int startPosition);
    /// @brief Checks if there is an occoruncy of the passed substring from the passed position in the passed string.
    /// @param string The string to check in.
    /// @param subString The substring to look for.
    /// @param startPosition The position from which starts.
    /// @return True if an occoruncy is found, false otherwise.
    bool containsSubstringFrom(const char* string, const char* subString, int startPosition);
    /// @brief Checks if a char is a decimal digit.
    /// @param character The char to check.
    /// @return True if the char is decimal digit, false otherwise.
    bool isDecimalDigit(char character);
    /// @brief Checks if a char is a hexadecimal digit (not case sensitive).
    /// @param character The char to check.
    /// @return True if the char is a hexadecima digit, false otherwise.
    bool isHexDigit(char character);
    /// @brief If is a decimal digit, converts it to int; Otherwise returns ASCII integer representation of the passed char.
    /// @param digit The char to convert.
    /// @return The digit as an integer if the char is a decimal digit, ASCII integer representation of the passed char otherwise.
    int decimalDigitToInt(char digit);
    /// @brief If is a hexadecimal digit (not case sensitive), converts it to int; Otherwise returns ASCII integer representation of the passed char.
    /// @param digit The char to convert.
    /// @return The digit as an integer if the char is a hexadecimal giti, ASCII integer representation of the passed char otherwise.
    int hexDigitToInt(char digit);
    /// @brief Evalutates the base of the number (by finding the biggest digit up to hexadecimal digit F) and returns it. If the string contains a non-digit char (up to hexadecimal digit F), returns -1.
    /// @param number The number in text format.
    /// @return The base of the number, if it is valid. Otherwise -1.
    int evalutateBase(char* number);
    /// @brief Evalutates the number of digits of a number. The time complexity of this function is constant (O(1)).
    /// @param number The number to evalutate.
    /// @return The number of digits.
    int nDigits(int number);
#endif