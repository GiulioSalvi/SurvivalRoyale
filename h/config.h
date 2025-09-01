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
 * \brief Definition of functions which retrieves the game configuration from the possible sources.
**/

#include "cli.h"
#include "config_file.h"

#ifndef _CONFIG_H_
    /// @brief Include guard.
    #define _CONFIG_H_

    /// @brief Gets the game configuration based on the action code. If action code is ACTION_HELP, the program exits successfully. If the program is asked to save the game configuration to a file, it overwrites by default the existing game configuration file.
    /// @param code The action code.
    /// @param cliGameConfiguration The possible CLI game configuration.
    /// @return The game configuration that the game will use. 
    GameConfiguration getGameConfiguration(const int code, const GameConfiguration cliGameConfiguration);
    /// @brief Asks to the user via terminal the game configuration.
    /// @return The game configuration asked via terminal.
    GameConfiguration askConfigurationOptionsViaTerminal();
#endif