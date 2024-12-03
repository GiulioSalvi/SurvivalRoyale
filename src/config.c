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