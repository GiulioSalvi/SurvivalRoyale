#include "utility.h"
#include "game_configuration.h"

bool existsConfigurationFile();
gameConfiguration getConfigurationFromFile();
void saveConfigurationToFile(gameConfiguration configuration, bool overwriteIfExists);