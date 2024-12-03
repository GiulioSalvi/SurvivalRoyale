#include "includes.h"

#ifndef _CONFIG_H_
    #define _CONFIG_H_
    
    typedef struct {
        int defaultPlayersLPs;
        int defaultLPsOnField;
        bool allowSameRank;
        bool allowSameSuit;
    } gameConfiguration;

    gameConfiguration getDefaultConfiguration();
#endif