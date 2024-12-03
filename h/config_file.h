#include "config.h"
#include "utility.h"

bool existsConfigurationFile();
gameConfiguration getConfigurationFromFile();
void saveConfigurationToFile(gameConfiguration configuration, bool overwriteIfExists);