/**
 * \file
 * \brief Implementation of utility functions.
**/

#include "utility.h"

char* substring(const char* str, int start, int length) {
    if (start < 0 || length < 0 || start + length > strlen(str)) {
        return NULL; 
    }

    char* sub = (char*)malloc(length + 1);
    if(sub == NULL)
        exit(EXIT_ALLOC_FAILURE);

    strncpy(sub, str + start, length);
    sub[length] = '\0';

    return sub;
}

int offsetFromNext(const char* str, char c, int start) {
    for(int i = start, p = 0; i < strlen(str); i++, p++)
        if(str[i] == c)
            return p;
    
    return -1;
}

int count(const char* str, char c, int start) {
    int counter = 0;

    for(int i = 0; i < strlen(str); i++)
        if(str[i] == c)
            counter++;

    return counter;
}

bool containsFrom(const char* str, char c, int p) {
    for(int i = p; i < strlen(str); i++)
        if(str[i] == c)
            return true;
    
    return false;
}

bool containsSubstringFrom(const char* str, const char* subStr, int p) {
    if(strcmp(str, subStr) == 0)
        return true;
    
    int strLen = strlen(str);
    int subStrLen = strlen(subStr);
    
    if(p < 0 || p >= strLen || subStrLen == 0 || subStrLen > strLen - p)
        return false;

    for(int i = p; i < strLen; i++)
        if(str[i] == subStr[0] && i + subStrLen < strLen)
            for(int j = 0; j < subStrLen; j++) {
                if(str[i + j] != subStr[j])
                    break;
                else if(j == subStrLen - 1)
                    return true;
            }
        
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
    return isDecimalDigit(d) ?
        decimalDigitToInt(d) :
        (
            isHexDigit(d) ?
            (
                (int)d >= 97 ?
                (int)d - 97 + 10 :
                (int)d - 65 + 10
            ) :
        (int)d
    );
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

int nDigits(int n) {
    int c = 0;

    while(n != 0) {
        n /= 10;
        c++;
    }

    return c;
}