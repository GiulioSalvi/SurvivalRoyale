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
 * \brief Definition of functions which handles the configuration file.
**/

#include "utility.h"
#include "game_configuration.h"

#ifndef _CONFIG_FILE_H_
    /// @brief Include guard.
    #define _CONFIG_FILE_H_

    /// @brief Checks by filename if a game configuration file exists.
    /// @return True if exists, false otherwise.
    bool existsConfigurationFile();
    /// @brief Load the game configuration from the file. It checks if the file exists.
    /// @return The game configuration loaded from the file, otherwise the default game configuration.
    GameConfiguration getConfigurationFromFile();
    /// @brief Save the given configuration to the game configuration file. It overwrites an existing file if and only if overwriteIfExists is set to true.
    /// @param configuration The game configuration to be saved.
    /// @param overwriteIfExists Overwriting allowed flag.
    void saveConfigurationToFile(GameConfiguration configuration, bool overwriteIfExists);
#endif