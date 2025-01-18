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