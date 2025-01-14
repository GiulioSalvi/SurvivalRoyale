#include "includes.h"

/// @brief ANSI standard black foreground color.
#define FgBlack 30
/// @brief ANSI standard red foreground color.
#define FgRed 31
/// @brief ANSI standard green foreground color.
#define FgGreen 32
/// @brief ANSI standard yellow foreground color.
#define FgYellow 33
/// @brief ANSI standard blue foreground color.
#define FgBlue 34
/// @brief ANSI standard magenta foreground color.
#define FgMagenta 35
/// @brief ANSI standard cyan foreground color.
#define FgCyan 36
/// @brief ANSI standard white foreground color.
#define FgWhite 37
/// @brief ANSI standard bright black foreground color.
#define FgBrightBlack 90
/// @brief ANSI standard bright red foreground color.
#define FgBrightRed 91
/// @brief ANSI standard bright green foreground color.
#define FgBrightGreen 92
/// @brief ANSI standard bright yellow foreground color.
#define FgBrightYellow 93
/// @brief ANSI standard bright blue foreground color.
#define FgBrightBlue 94
/// @brief ANSI standard bright magenta foreground color.
#define FgBrightMagenta 95
/// @brief ANSI standard bright cyan foreground color.
#define FgBrightCyan 96
/// @brief ANSI standard bright white foreground color.
#define FgBrightWhite 97

/// @brief ANSI standard black background color.
#define BgBlack 40
/// @brief ANSI standard red background color.
#define BgRed 41
/// @brief ANSI standard green background color.
#define BgGreen 42
/// @brief ANSI standard yellow background color.
#define BgYellow 43
/// @brief ANSI standard blue background color.
#define BgBlue 44
/// @brief ANSI standard magenta background color.
#define BgMagenta 45
/// @brief ANSI standard cyan background color.
#define BgCyan 46
/// @brief ANSI standard white background color.
#define BgWhite 47
/// @brief ANSI standard bright black background color.
#define BgBrightBlack 100
/// @brief ANSI standard bright red background color.
#define BgBrightRed 101
/// @brief ANSI standard bright green background color.
#define BgBrightGreen 102
/// @brief ANSI standard bright yellow background color.
#define BgBrightYellow 103
/// @brief ANSI standard bright blue background color.
#define BgBrightBlue 104
/// @brief ANSI standard bright magenta background color.
#define BgBrightMagenta 105
/// @brief ANSI standard bright cyan background color.
#define BgBrightCyan 106
/// @brief ANSI standard bright white background color.
#define BgBrightWhite 107

/// @brief Internal const value meaning that no underlining effect has to be applied.
#define No 20
/// @brief Internal const value meaning that single underlining effect has to be applied.
#define SingleUnderlined 21
/// @brief Internal const value meaning that double underlining effect has to be applied.
#define DoublyUnderlined 22