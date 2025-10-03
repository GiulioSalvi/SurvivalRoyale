// Copyright (C) 2025  Giulio Salvi, Jacopo Paradisi
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

/**
 * \file
 * \brief Definition of utility functions.
**/

#include "consts.h"
#include "includes.h"

#ifndef _UTILITY_H_
    /// @brief Include guard.
    #define _UTILITY_H_

    /// @brief Copies a substring (heap-allocated) from the given string. If it fails when allocating memory for the substring, it exits with EXIT_ALLOC_FAILURE exit code.
    /// @param string String to copy from.
    /// @param startPosition The position in str to start copying from.
    /// @param length The length of the substring.
    /// @return Returns the substring (heap-allocated).
    char* substring(const char* string, int startPosition, int length);
    /// @brief Counts the offset in the string between the position and the next occurrence of the given char.
    /// @param string The string to search in for the occurrence.
    /// @param character The char to search to.
    /// @param startPosition The position to start from.
    /// @return Returns the offset from the start position to the next occurrence of the char. If no more occurrences occur, returns -1.
    int offsetFromNext(const char* string, char character, int startPosition);
    /// @brief Counts the number of occurrences in the string of the given char from the given position.
    /// @param string The string to count in.
    /// @param character The char to count.
    /// @param startPosition The position in the string to start counting from.
    /// @return Returns the number of occurrences of the char in the string. If there are not occurrences of the char in the given string, returns 0.
    int count(const char* string, char character, int startPosition);
    /// @brief Checks if there is an occurrence in the string of the given char from the given position.
    /// @param string The string to check in. 
    /// @param character The char to look for.
    /// @param startPosition The position to start from.
    /// @return Returns true if an occurrence is found, false otherwise.
    bool containsFrom(const char* string, char character, int startPosition);
    /// @brief Checks if there is an occurrence in the string of the given substring from the given position.
    /// @param string The string to check in.
    /// @param subString The substring to look for.
    /// @param startPosition The position to start from.
    /// @return Returns true if an occurrence is found, false otherwise.
    bool containsSubstringFrom(const char* string, const char* subString, int startPosition);
    /// @brief Checks if a char is a decimal digit.
    /// @param character The char to check.
    /// @return Returns true if the char is decimal digit, false otherwise.
    bool isDecimalDigit(char character);
    /// @brief Checks if a char is a hexadecimal digit (not case sensitive).
    /// @param character The char to check.
    /// @return Returns true if the char is a hexadecimal digit, false otherwise.
    bool isHexDigit(char character);
    /// @brief If is a decimal digit, converts it to int; Otherwise returns ASCII integer representation of the given char.
    /// @param digit The char to convert.
    /// @return Returns the digit as an integer if the char is a decimal digit, the ASCII integer representation of the given char otherwise.
    int decimalDigitToInt(char digit);
    /// @brief If is a hexadecimal digit (not case sensitive), converts it to int; Otherwise returns ASCII integer representation of the given char.
    /// @param digit The char to convert.
    /// @return Returns the digit as an integer if the char is a hexadecimal digit, the ASCII integer representation of the given char otherwise.
    int hexDigitToInt(char digit);
    /// @brief Evaluates the base of the number (by finding the biggest digit up to hexadecimal digit F, not case-sensitive) and returns it. If the string contains a non-digit char (up to hexadecimal digit F, and that is not '+', '-' or '.'), returns -1.
    /// @param number The number in text format.
    /// @return Returns the base of the number, if the string is valid. Returns -1 otherwise.
    int evaluateBase(char* number);
    /// @brief Evaluates the number of digits of a number. The time complexity of this function is constant (O(1)).
    /// @param number The number to evaluate.
    /// @return Returns the number of digits.
    int nDigits(int number);
#endif