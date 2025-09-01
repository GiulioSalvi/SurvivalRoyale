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
 * \brief Definition of functions which handles CLI.
**/

#include "utility.h"
#include "game_configuration.h"

#ifndef _CLI_H_
    /// @brief Include guard.
    #define _CLI_H_

    /// @brief Prints the generic help message or a detailed help message describing a particular option.
    /// @param scope Generic scope or a CLI option (shorthands are not handled).
    void getHelp(const char* scope);
    /// @brief It validates and intreprets the CLI options.
    /// @param argv The CLI options vector.
    /// @param argc The length of argv.
    /// @return If the CLI options are legal, it returns a bit-masked action code meaning the action that the program has to take of, otherwise exits with EXIT_CLI_ILLEGAL. If the user was legally asking for help, it returns ACTION_HELP; otherwise it exits with EXIT_CLI_ILLEGAL.
    int handleCLIArguments(char** argv, const int argc);
    /// @brief Generates a game configuration from the given options. If some options are not specified, the default game configuration values for that option are used.
    /// @param argv The CLI options vector.
    /// @param argc The length of argv.
    /// @return The game configuration generated.
    GameConfiguration getConfigurationFromArguments(char** argv, const int argc);
#endif