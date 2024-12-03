#include "consts.h"
#include "includes.h"

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
/// Checks if there is an occoruncy of the passed char from the passed position in the passed string.
bool containsFrom(const char* str, char c, int p);
/// Checks if a char is a decimal digit.
bool isDecimalDigit(char c);
/// Checks if a char is a hexadecimal digit (not case sensitive).
bool isHexDigit(char c);
/// If is a decimal digit, converts it to int;
/// Otherwise returns int representation of passed char.
int decimalDigitToInt(char d);
/// If is a hexadecimal digit (not case sensitive), converts it to int;
/// Otherwise returns int representation of passed char.
int hexDigitToInt(char d);
/// Evalutates the base of the number (by finding the biggest digit up to hex F) and returns it.
/// If the string contains a non-digit char, returns -1.
int evalutateBase(char* num);
int nDigits(int n);