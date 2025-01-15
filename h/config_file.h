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