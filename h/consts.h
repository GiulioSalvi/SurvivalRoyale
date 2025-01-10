/// @brief Exit code when malloc fails.
#define EXIT_ALLOC_FAILURE 2
/// @brief Exit code when popping from a vector fails.
#define EXIT_POP_FAILURE 3
/// @brief Exit code for requests with illegal indexes.
#define EXIT_ILLEGAL_INDEX_FAILURE 4
/// @brief Exit code when the CLI options are illegal.
#define EXIT_CLI_ILLEGAL 5

/// @brief With this action code, the program does nothing.
#define ACTION_NOTHING 0
/// @brief With this action code, the program ignores the configuration file when loading the game configuration.
#define ACTION_IGNORE_CONFIG_FILE 1
/// @brief With this action code, the program does not ask to the user the game configuration when loading the game configuration.
#define ACTION_DONT_ASK_CONFIG_OPTIONS 2
/// @brief With this action code, the program saves the used game configuration to file.
#define ACTION_SAVE_TO_FILE 4
/// @brief With this action code, the program has a verbose logging behaviour.
#define ACTION_BE_VERBOSE 8
/// @brief With this action code, the program starts a match.
#define ACTION_GO 16
/// @brief With this action code, the program has printed help messages.
#define ACTION_HELP 17