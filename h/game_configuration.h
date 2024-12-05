#ifndef _CONFIG_H_
    #define _CONFIG_H_
    
    #include "includes.h"

    typedef struct {
        int defaultPlayersLPs;
        int defaultLPsOnField;
        bool allowSameRank;
        bool allowSameSuit;
    } gameConfiguration;

    gameConfiguration getDefaultConfiguration();
    bool isDefaultGameConfiguration(const gameConfiguration config);
#endif