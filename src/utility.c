/**
 * \file
 * \brief Implementation of utility functions.
**/

#include "utility.h"

char* substring(const char* string, int startPosition, int length) {
    if (startPosition < 0 || length < 0 || startPosition + length > strlen(string)) {
        return NULL; 
    }

    char* sub = (char*)malloc(length + 1);
    if(sub == NULL)
        exit(EXIT_ALLOC_FAILURE);

    strncpy(sub, string + startPosition, length);
    sub[length] = '\0';

    return sub;
}

int offsetFromNext(const char* string, char character, int startPosition) {
    for(int i = startPosition, p = 0; i < strlen(string); i++, p++)
        if(string[i] == character)
            return p;
    
    return -1;
}

int count(const char* string, char character, int startPosition) {
    int counter = 0;

    for(int i = startPosition; i < strlen(string); i++)
        if(string[i] == character)
            counter++;

    return counter;
}

bool containsFrom(const char* string, char character, int startPosition) {
    for(int i = startPosition; i < strlen(string); i++)
        if(string[i] == character)
            return true;
    
    return false;
}

bool containsSubstringFrom(const char* string, const char* subString, int startPosition) {
    if(strcmp(string, subString) == 0)
        return true;
    
    int strLen = strlen(string);
    int subStrLen = strlen(subString);
    
    if(startPosition < 0 || startPosition >= strLen || subStrLen == 0 || subStrLen > strLen - startPosition)
        return false;

    for(int i = startPosition; i < strLen; i++)
        if(string[i] == subString[0] && i + subStrLen < strLen)
            for(int j = 0; j < subStrLen; j++) {
                if(string[i + j] != subString[j])
                    break;
                else if(j == subStrLen - 1)
                    return true;
            }
        
    return false;
}

bool isDecimalDigit(char character) {
    return character >= '0' && character <= '9';
}

bool isHexDigit(char character) {
    return isDecimalDigit(character) || (character >= 'a' && character <= 'f') || (character >= 'A' && character <= 'F');
}

int decimalDigitToInt(char digit) {
    return (int)(isDecimalDigit(digit) ? digit - '0' : digit);
}

int hexDigitToInt(char digit) {
    return isDecimalDigit(digit) ?
        decimalDigitToInt(digit) :
        (
            isHexDigit(digit) ?
            (
                digit >= 'a' ?
                (int)(digit - 'a') + 10 :
                (int)(digit - 'A') + 10
            ) :
        (int)digit
    );
}

int evalutateBase(char* number) {
    char max = -1;

    for(int i = 0; i < strlen(number); i++) {
        if(isHexDigit(number[i])) {
            if(number[i] > max)
                max = number[i];
        } else
            return -1;
    }

    return hexDigitToInt(max) + 1;
    
}

int nDigits(int number) {
    return number == 0 ? 1 : (int)log10(abs(number)) + 1;
}