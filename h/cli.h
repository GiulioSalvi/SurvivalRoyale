#include "utility.h"
#include "game_configuration.h"

void getHelp(const char* scope);
int handleCLIArguments(char** argv, const int argc);
gameConfiguration getConfigurationFromArguments(char** argv, const int argc);