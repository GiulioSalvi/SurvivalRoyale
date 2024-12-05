#include "config.h"

gameConfiguration getDefaultConfiguration() {
    gameConfiguration cfg = {
        .allowSameRank = true,
        .allowSameSuit = true,
        .defaultLPsOnField = 0,
        .defaultPlayersLPs = 2
    };

    return cfg;
}

bool isDefaultGameConfiguration(const gameConfiguration config) {
    gameConfiguration d = getDefaultConfiguration();
    return config.allowSameRank == d.allowSameRank &&
        config.allowSameSuit == d.allowSameSuit &&
        config.defaultLPsOnField == d.defaultLPsOnField &&
        config.defaultPlayersLPs == d.defaultPlayersLPs;
}

gameConfiguration getGameConfiguration(const int code, const gameConfiguration cliGameConfiguration) {
    bool ignoreConfigFile = code - ACTION_IGNORE_CONFIG_FILE == 0 || code - ACTION_IGNORE_CONFIG_FILE - ACTION_DONT_ASK_CONFIG_OPTIONS == 0;
    bool dontAskConfigOptions = code - (ignoreConfigFile ? ACTION_IGNORE_CONFIG_FILE : 0) - ACTION_DONT_ASK_CONFIG_OPTIONS == 0;

    if(!ignoreConfigFile && existsConfigurationFile())
        return getConfigurationFromFile();
    else if(!isDefaultGameConfiguration(cliGameConfiguration))
        return cliGameConfiguration;
    else if(!dontAskConfigOptions)
        return askConfigurationOptionsViaTerminal();
    else
        return getDefaultConfiguration();
}