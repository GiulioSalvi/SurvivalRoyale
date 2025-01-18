/**
 * \file
 * \brief Implementation of functions which retrieves the game configuration from the possible sources.
**/

#include "config.h"

GameConfiguration getDefaultConfiguration() {
    const GameConfiguration cfg = {
        .beVerbose = false,
        .allowSameRank = true,
        .allowSameSuit = true,
        .defaultLPsOnField = 0,
        .defaultPlayersLPs = 2
    };

    return cfg;
}

bool isDefaultGameConfiguration(const GameConfiguration config) {
    const GameConfiguration d = getDefaultConfiguration();
    return config.beVerbose == d.beVerbose && 
        config.allowSameRank == d.allowSameRank &&
        config.allowSameSuit == d.allowSameSuit &&
        config.defaultLPsOnField == d.defaultLPsOnField &&
        config.defaultPlayersLPs == d.defaultPlayersLPs;
}

GameConfiguration getGameConfiguration(const int code, const GameConfiguration cliGameConfiguration) {
    if(code == ACTION_HELP)
        exit(EXIT_SUCCESS);
    
    GameConfiguration cfg;
    bool ignoreConfigFile = code & 0b0001;
    bool dontAskConfigOptions = code & 0b0010;
    bool saveToFile = code & 0b0100;
    bool beVerbose = code & 0b1000;

    if(!ignoreConfigFile && existsConfigurationFile())
        return getConfigurationFromFile();
    else if(!isDefaultGameConfiguration(cliGameConfiguration))
        cfg = cliGameConfiguration;
    else if(!dontAskConfigOptions)
        cfg = askConfigurationOptionsViaTerminal();
    else
        cfg = getDefaultConfiguration();
    
    cfg.beVerbose = beVerbose;

    if(saveToFile)
        saveConfigurationToFile(cfg, true);
    
    return cfg;
}