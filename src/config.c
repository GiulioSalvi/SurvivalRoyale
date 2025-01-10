#include "config.h"

gameConfiguration getDefaultConfiguration() {
    const gameConfiguration cfg = {
        .beVerbose = false,
        .allowSameRank = true,
        .allowSameSuit = true,
        .defaultLPsOnField = 0,
        .defaultPlayersLPs = 2
    };

    return cfg;
}

bool isDefaultGameConfiguration(const gameConfiguration config) {
    const gameConfiguration d = getDefaultConfiguration();
    return config.beVerbose == d.beVerbose && 
        config.allowSameRank == d.allowSameRank &&
        config.allowSameSuit == d.allowSameSuit &&
        config.defaultLPsOnField == d.defaultLPsOnField &&
        config.defaultPlayersLPs == d.defaultPlayersLPs;
}

gameConfiguration getGameConfiguration(const int code, const gameConfiguration cliGameConfiguration) {
    if(code == ACTION_HELP)
        exit(EXIT_SUCCESS);
    
    gameConfiguration cfg;
    bool ignoreConfigFile = code & 0b0001;
    bool dontAskConfigOptions = code & 0b0010;
    bool saveToFile = code & 0b0100;
    bool beVerbose = code & 0b1000;

    cfg.beVerbose = beVerbose;

    if(!ignoreConfigFile && existsConfigurationFile())
        return getConfigurationFromFile();
    else if(!isDefaultGameConfiguration(cliGameConfiguration))
        cfg = cliGameConfiguration;
    else if(!dontAskConfigOptions)
        cfg = askConfigurationOptionsViaTerminal();
    else
        cfg = getDefaultConfiguration();

    if(saveToFile)
        saveConfigurationToFile(cfg, true);
    
    return cfg;
}