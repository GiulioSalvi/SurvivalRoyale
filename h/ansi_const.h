#include "includes.h"

/// @brief ANSI standard black foreground color.
const uint8_t FgBlack = 30;
/// @brief ANSI standard red foreground color.
const uint8_t FgRed = 31;
/// @brief ANSI standard green foreground color.
const uint8_t FgGreen = 32;
/// @brief ANSI standard yellow foreground color.
const uint8_t FgYellow = 33;
/// @brief ANSI standard blue foreground color.
const uint8_t FgBlue = 34;
/// @brief ANSI standard magenta foreground color.
const uint8_t FgMagenta = 35;
/// @brief ANSI standard cyan foreground color.
const uint8_t FgCyan = 36;
/// @brief ANSI standard white foreground color.
const uint8_t FgWhite = 37;
/// @brief ANSI standard bright black foreground color.
const uint8_t FgBrightBlack = 90;
/// @brief ANSI standard bright red foreground color.
const uint8_t FgBrightRed = 91;
/// @brief ANSI standard bright green foreground color.
const uint8_t FgBrightGreen = 92;
/// @brief ANSI standard bright yellow foreground color.
const uint8_t FgBrightYellow = 93;
/// @brief ANSI standard bright blue foreground color.
const uint8_t FgBrightBlue = 94;
/// @brief ANSI standard bright magenta foreground color.
const uint8_t FgBrightMagenta = 95;
/// @brief ANSI standard bright cyan foreground color.
const uint8_t FgBrightCyan = 96;
/// @brief ANSI standard bright white foreground color.
const uint8_t FgBrightWhite = 97;

/// @brief ANSI standard black background color.
const uint8_t BgBlack = 40;
/// @brief ANSI standard red background color.
const uint8_t BgRed = 41;
/// @brief ANSI standard green background color.
const uint8_t BgGreen = 42;
/// @brief ANSI standard yellow background color.
const uint8_t BgYellow = 43;
/// @brief ANSI standard blue background color.
const uint8_t BgBlue = 44;
/// @brief ANSI standard magenta background color.
const uint8_t BgMagenta = 45;
/// @brief ANSI standard cyan background color.
const uint8_t BgCyan = 46;
/// @brief ANSI standard white background color.
const uint8_t BgWhite = 47;
/// @brief ANSI standard bright black background color.
const uint8_t BgBrightBlack = 100;
/// @brief ANSI standard bright red background color.
const uint8_t BgBrightRed = 101;
/// @brief ANSI standard bright green background color.
const uint8_t BgBrightGreen = 102;
/// @brief ANSI standard bright yellow background color.
const uint8_t BgBrightYellow = 103;
/// @brief ANSI standard bright blue background color.
const uint8_t BgBrightBlue = 104;
/// @brief ANSI standard bright magenta background color.
const uint8_t BgBrightMagenta = 105;
/// @brief ANSI standard bright cyan background color.
const uint8_t BgBrightCyan = 106;
/// @brief ANSI standard bright white background color.
const uint8_t BgBrightWhite = 107;

/// @brief Internal const value meaning that no underlining effect has to be applied.
const uint8_t No = 20;
/// @brief Internal const value meaning that single underlining effect has to be applied.
const uint8_t SingleUnderlined = 21;
/// @brief Internal const value meaning that double underlining effect has to be applied.
const uint8_t DoublyUnderlined = 22;