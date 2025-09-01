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
 * \brief Implementation of functions which handles CLI.
**/

#include "cli.h"

void getHelp(const char* scope) {
    printf("game [--help [option]] | [--go] [--dont-ask-config-options] [--ignore-config-file] [--save-to-file] [--use-tui] [--verbose] [--default-player-LPs <LPs>] [--default-LPs-field <LPs>] [--allow-same-rank <false|true>] [--allow-same-suit <false|true>]\n\n");

    if(strcmp(scope, "generic") == 0 || strlen(scope) == 0) {
        printf("--help [option] (-h [option]):\n\tIf option is not given, then it shows this generic help message. Otherwise if option is given it shows an exhaustive help message for the given option.\n");

        printf("--go (-g):\n\tIt starts a new game.\n");

        printf("--dont-ask-config-options (-d):\n\tIt doesn't asks to the user the configuration options when the program starts.\n");

        printf("--ignore-config-file (-c):\n\tIt ignores the configuration file, if it exists, so that the configuration options saved in it are not loaded.\n");

        printf("--save-to-file (-S):\n\tSaves the configuration loaded to a configuration file.\n");

        printf("--use-tui (-t):\n\tThe game will use the terminal user interface (TUI) when specified.\n");

        printf("--verbose (-v):\n\tThe program has a verbose behaviour if this flag is specified. This option is not saved on file and it is not asked to the user.\n");

        printf("--default-player-LPs <LPs> (-p <LPs>):\n\tSets with how many LPs players spawn.\n");

        printf("--default-LPs-field <LPs> (-f <LPs>):\n\tSets how many LPs there are on the playing field at the beginning of the game.\n");

        printf("--allow-same-rank <false|true> (-r <false|true>):\n\tSets if it is allowed for a player that its cards have the same rank.\n");

        printf("--allow-same-suit <false|true> (-s <false|true>):\n\tSets if it is allowed for a player that its cards have the same suit.\n");
    } else if(strcmp(scope, "help") == 0)
        printf("--help [option] (-h [option]):\n\tIf option is not given, then it shows this generic help message. Otherwise if option is given it shows an exhaustive help message for the given option.\n");
    else if(strcmp(scope, "go") == 0)
        printf("--go (-g):\n\tIt starts a new game. The configuration is loaded from the file if it exists and unless --ignore-config-file has been specified. Otherwise it asks to the user when the program is running unless --dont-ask-config-options has been specified. If so, it uses the default configuration options.\n");
    else if(strcmp(scope, "dont-ask-config-options") == 0)
        printf("--dont-ask-config-options (-d):\n\tIt doesn't asks to the user the configuration options when the program starts.\n");
    else if(strcmp(scope, "ignore-config-file") == 0)
        printf("--ignore-config-file (-c):\n\tIt ignores the configuration file, if it exists, so that the configuration options saved in it are not loaded.\n");
    else if(strcmp(scope, "save-to-file") == 0)
        printf("--save-to-file (-S):\n\tSaves the configuration loaded to a configuration file.\n");
    else if(strcmp(scope, "use-tui") == 0)
        printf("--use-tui (-t):\n\tThe game will use the terminal user interface (TUI) when specified.\n");
    else if(strcmp(scope, "verbose") == 0)
        printf("--verbose (-v):\n\tThe program has a verbose behaviour if this flag is specified. This option is not saved on file and it is not asked to the user. It prints the game configuration when it is loaded and at the beginning of each phase prints the players informations.\n");
    else if(strcmp(scope, "default-player-LPs") == 0)
        printf("--default-player-LPs <LPs> (-p <LPs>):\n\tSets with how many LPs players spawn. If there exists the configuration file and it has not been ignored, the program considers this option instead of the file's option.\n\n\tNotice that also --default-playerLPs=<LPS> and -p=<LPs> are valid command syntaxes.\n");
    else if(strcmp(scope, "default-LPs-field") == 0)
        printf("--default-LPs-field <LPs> (-f <LPs>):\n\tSets how many LPs there are on the playing field at the beginning of the game. If there exists the configuration file and it has not been ignored, the program considers this option instead of the file's option.\n\n\tNotice that also --default-LPs-field=<LPs> and -f=<LPs> are valid command syntaxes.\n");
    else if(strcmp(scope, "allow-same-rank") == 0)
        printf("--allow-same-rank <false|true> (-r <false|true>):\n\tSets if it is allowed for a player that its cards have the same rank. If there exists the configuration file and it has not been ignored, the program considers this option instead of the file's option.\n\n\tNotice that also --allow-same-rank=<false|true> and -r=<false|true> are valid command syntaxes.\n");
    else if(strcmp(scope, "allow-same-suit") == 0)
        printf("--allow-same-suit <false|true> (-s <false|true>):\n\tSets if it is allowed for a player that its cards have the same suit. If there exists the configuration file and it has not been ignored, the program considers this option instead of the file's option.\n\n\tNotice that also --allow-same-suit=<false|true> and -s=<false|true> are valid command syntaxes.\n");
}

int handleCLIArguments(char** argv, const int argc) {
    if(argc == 1 || ((strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) && argc == 2)) {
        getHelp("generic");
        return ACTION_HELP;
    } else if(argc >= 3 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        if(strcmp(argv[2], "--help") == 0 || strcmp(argv[2], "-h") == 0 || strcmp(argv[2], "help") == 0 || strcmp(argv[2], "h") == 0)
            getHelp("help");
        else if(strcmp(argv[2], "--go") == 0 || strcmp(argv[2], "-g") == 0 || strcmp(argv[2], "go") == 0 || strcmp(argv[2], "g") == 0)
            getHelp("go");
        else if(strcmp(argv[2], "--dont-ask-config-options") == 0 || strcmp(argv[2], "-d") == 0 || strcmp(argv[2], "dont-ask-config-options") == 0 || strcmp(argv[2], "d") == 0)
            getHelp("dont-ask-config-options");
        else if(strcmp(argv[2], "--ignore-config-file") == 0 || strcmp(argv[2], "-c") == 0 || strcmp(argv[2], "ignore-config-file") == 0 || strcmp(argv[2], "c") == 0)
            getHelp("ignore-config-file");
        else if(strcmp(argv[2], "--save-to-file") == 0 || strcmp(argv[2], "-S") == 0 || strcmp(argv[2], "save-to-file") == 0 || strcmp(argv[2], "S") == 0)
            getHelp("save-to-file");
        else if(strcmp(argv[2], "--use-tui") == 0 || strcmp(argv[2], "-t") == 0 || strcmp(argv[2], "use-tui") == 0 || strcmp(argv[2], "t") == 0)
            getHelp("use-tui");
        else if(strcmp(argv[2], "--verbose") == 0 || strcmp(argv[2], "-v") == 0 || strcmp(argv[2], "verbose") == 0 || strcmp(argv[2], "v") == 0)
            getHelp("verbose");
        else if(strcmp(argv[2], "--default-player-LPs") == 0 || strcmp(argv[2], "-p") == 0 || strcmp(argv[2], "default-player-LPs") == 0 || strcmp(argv[2], "p") == 0)
            getHelp("default-player-LPs");
        else if(strcmp(argv[2], "--default-LPs-field") == 0 || strcmp(argv[2], "-f") == 0 || strcmp(argv[2], "default-LPs-field") == 0 || strcmp(argv[2], "f") == 0)
            getHelp("default-LPs-field");
        else if(strcmp(argv[2], "--allow-same-rank") == 0 || strcmp(argv[2], "-r") == 0 || strcmp(argv[2], "allow-same-rank") == 0 || strcmp(argv[2], "r") == 0)
            getHelp("allow-same-rank");
        else if(strcmp(argv[2], "--allow-same-suit") == 0 || strcmp(argv[2], "-s") == 0 || strcmp(argv[2], "allow-same-suit") == 0 || strcmp(argv[2], "s") == 0)
            getHelp("allow-same-suit");
        else {
            printf("Illegal CLI arguments: help option was not recognized.\n");
            exit(EXIT_CLI_ILLEGAL);
        }

        return ACTION_HELP;
    } else {
        int code = ACTION_NOTHING;

        for(int i = 1; i < argc; i++) {
            if(strcmp(argv[i], "--go") == 0 || strcmp(argv[i], "-g") == 0)
                code += ACTION_GO;
            else if(strcmp(argv[i], "--dont-ask-config-options") == 0 || strcmp(argv[i], "-d") == 0)
                code += ACTION_DONT_ASK_CONFIG_OPTIONS;
            else if(strcmp(argv[i], "--ignore-config-file") == 0 || strcmp(argv[i], "-c") == 0)
                code += ACTION_IGNORE_CONFIG_FILE;
            else if(strcmp(argv[i], "--save-to-file") == 0 || strcmp(argv[i], "-S") == 0)
                code += ACTION_SAVE_TO_FILE;
            else if(strcmp(argv[i], "--use-tui") == 0 || strcmp(argv[i], "-t") == 0)
                code += ACTION_USE_TUI;
            else if(strcmp(argv[i], "--verbose") == 0 || strcmp(argv[i], "-v") == 0)
                code += ACTION_BE_VERBOSE;
        }

        if(code == ACTION_NOTHING) {
            printf("Illegal CLI argument: not recognized argument%c.\n", argc > 2 ? 's' : 0);
            exit(EXIT_CLI_ILLEGAL);
        } else if(code - ACTION_GO < 0) {
            printf("Illegal CLI arguments: --go option must be passed with options --dont-ask-config-options and --ignore-config-file.\n");
            exit(EXIT_CLI_ILLEGAL);
        }

        return code - ACTION_GO;
    }
}

GameConfiguration getConfigurationFromArguments(char** argv, const int argc) {
    GameConfiguration cfg = getDefaultConfiguration();

    for(int i = 1; i < argc; i++) {
        if(
            containsSubstringFrom(argv[i], "--default-player-LPs", 0) ||
            containsSubstringFrom(argv[i], "-p", 0) ||
            containsSubstringFrom(argv[i], "--default-LPs-field", 0) ||
            containsSubstringFrom(argv[i], "-f", 0) ||
            containsSubstringFrom(argv[i], "--allow-same-rank", 0) ||
            containsSubstringFrom(argv[i], "-r", 0) ||
            containsSubstringFrom(argv[i], "--allow-same-suit", 0) ||
            containsSubstringFrom(argv[i], "-s", 0)
        ) {
            char* optionName = "";
            char* optionValue = "";

            if(containsFrom(argv[i], '=', 0)) {
                const int equalPosition = offsetFromNext(argv[i], '=', 0);
                optionName = substring(argv[i], 0, equalPosition);
                optionValue = substring(argv[i], equalPosition + 1, strlen(argv[i]) - equalPosition - 1);
            } else {
                optionName = argv[i];
                optionValue = argv[i + 1];
                
                i++;
            }

            errno = 0;
            char* endptr;
            if(strcmp(optionName, "--default-player-LPs") == 0 || strcmp(optionName, "-p") == 0) {
                int n = strtol(optionValue, &endptr, 10);

                if(errno == ERANGE || *endptr != '\0') {
                    printf("Illegal CLI arguments: a number was expected.\n");
                    exit(EXIT_CLI_ILLEGAL);
                }

                cfg.defaultPlayersLPs = n;
            } else if(strcmp(optionName, "--default-LPs-field") == 0 || strcmp(optionName, "-f") == 0) {
                int n = strtol(optionValue, &endptr, 10);

                if(errno == ERANGE || *endptr != '\0') {
                    printf("Illegal CLI arguments: a number was expected.\n");
                    exit(EXIT_CLI_ILLEGAL);
                }

                cfg.defaultLPsOnField = n;
            } else if(strcmp(optionName, "--allow-same-rank") == 0 || strcmp(optionName, "-r") == 0) {
                if(strcmp(optionValue, "true") == 0 || strcmp(optionValue, "false") == 0)
                    cfg.allowSameRank = strcmp(optionValue, "true") == 0;
                else {
                    printf("Illegal CLI arguments: true or false were expected.\n");
                    exit(EXIT_CLI_ILLEGAL);
                }
            } else if(strcmp(optionName, "--allow-same-suit") == 0 || strcmp(optionName, "-s") == 0) {
                if(strcmp(optionValue, "true") == 0 || strcmp(optionValue, "false") == 0)
                    cfg.allowSameSuit = strcmp(optionValue, "true") == 0;
                else {
                    printf("Illegal CLI arguments: true or false were expected.\n");
                    exit(EXIT_CLI_ILLEGAL);
                }
            }
        }
    }

    return cfg;
}