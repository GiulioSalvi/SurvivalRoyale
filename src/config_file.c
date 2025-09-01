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
 * \brief Implementation of functions which handles the configuration file.
**/

#include "config_file.h"

bool existsConfigurationFile() {
    FILE* cfgFile = fopen("./game.cfg", "r");
    if(!cfgFile)
        return false;
    else {
        fclose(cfgFile);
        return true;
    }
}

GameConfiguration getConfigurationFromFile() {
    if(existsConfigurationFile()) {
        FILE* cfgFile = fopen("./game.cfg", "r");

        while(feof(cfgFile) == 0) {
            char line[128];

            char* _ = fgets(line, 128, cfgFile);
            if(!containsFrom(line, '=', 0))
                continue;
            else {
                GameConfiguration cfg = getDefaultConfiguration();
                errno = 0;
                char* endptr;
                const int equalPosition = offsetFromNext(line, '=', 0);
                char* settingName = substring(line, 0, equalPosition);
                char* settingValue = substring(line, equalPosition + 1, strlen(line) - equalPosition - 1);

                if(settingValue[strlen(settingValue) - 1] == '\n')
                    settingValue[strlen(settingValue) - 1] = '\0';

                if(strcmp("useTui", settingName) == 0)
                    cfg.useTui = strcmp("true", settingValue) == 0;
                if(strcmp("beVerbose", settingName) == 0)
                    cfg.beVerbose = strcmp("true", settingValue) == 0;
                else if(strcmp("allowSameRank", settingName) == 0)
                    cfg.allowSameRank = strcmp("true", settingValue) == 0;
                else if(strcmp("allowSameSuit", settingName) == 0)
                    cfg.allowSameSuit = strcmp("true", settingValue) == 0;
                else if(strcmp("defaultPlayersLPs", settingName) == 0) {
                    const int rs = strtol(settingValue, &endptr, 10);

                    if(errno == ERANGE || *endptr != '\0')
                        continue;
                    else
                        cfg.defaultPlayersLPs = rs;
                } else if(strcmp("defaultLPsOnField", settingName) == 0) {
                    const int rs = strtol(settingValue, &endptr, 10);

                    if(errno == ERANGE || *endptr != '\0')
                        continue;
                    else
                        cfg.defaultLPsOnField = rs;
                }

                free(settingName);
                free(settingValue);
            }
        }
        
        fclose(cfgFile);
    }
    
    return getDefaultConfiguration();
}

void saveConfigurationToFile(GameConfiguration configuration, bool overwriteIfExists) {
    if(!overwriteIfExists && existsConfigurationFile())
        return;

    FILE* cfgFile = fopen("game.cfg", "w+");

    fprintf(cfgFile, "useTui=%s\n", configuration.useTui ? "true" : "false");
    fprintf(cfgFile, "beVerbose=%s\n", configuration.beVerbose ? "true" : "false");
    fprintf(cfgFile, "allowSameRank=%s\n", configuration.allowSameRank ? "true" : "false");
    fprintf(cfgFile, "allowSameSuit=%s\n", configuration.allowSameSuit ? "true" : "false");
    fprintf(cfgFile, "defaultPlayersLPs=%d\n", configuration.defaultPlayersLPs);
    fprintf(cfgFile, "defaultLPsOnField=%d\n", configuration.defaultLPsOnField);
    
    fclose(cfgFile);
}