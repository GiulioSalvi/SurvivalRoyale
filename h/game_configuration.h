// Copyright (C) 2025  Giulio Salvi, Jacopo Paradisi
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

/**
 * \file
 * \brief Definition of the game configuration structure and definition of related accessory functions.
**/

#include "includes.h"

#ifndef _GAME_CONFIGURATION_H_
    /// @brief Include guard.
    #define _GAME_CONFIGURATION_H_
    
    /// @brief The game configuration structure.
    typedef struct GameConfiguration {
        /// @brief The default amount of LPs that every player have at the beginning of a match.
        int defaultPlayersLPs;
        /// @brief The default amount of LPs on the playing field at the beginning of a match.
        int defaultLPsOnField;
        /// @brief Determines if a player can have cards with the same rank. It increases randomness if set to false.
        bool allowSameRank;
        /// @brief Determines if a player can have cards with the same suit It increases randomness if set to false.
        bool allowSameSuit;
        /// @brief Determines if the program has to have a verbose logging behaviour.
        bool beVerbose;
        /// @brief Determines if the gama has to use the terminal user interface (TUI).
        bool useTui;
    } GameConfiguration;

    /// @brief Retrieves the default game configuration.
    /// @return The default game configuration.
    GameConfiguration getDefaultConfiguration();
    /// @brief Determines if a given game configuration is the default one.
    /// @param config The game configuration to compare.
    /// @return True if the given game configuration is the default one, false otherwise.
    bool isDefaultGameConfiguration(const GameConfiguration config);
#endif