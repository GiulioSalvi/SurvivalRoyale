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

gameConfiguration getConfigurationFromFile() {
    
    if(existsConfigurationFile()) {
        gameConfiguration cfg;
        FILE* cfgFile = fopen("./game.cfg", "r");

        while(feof(cfgFile) == 0) {
            char line[128];

            fgets(line, 256, cfgFile);
            if(!containsFrom(line, '=', 0))
                continue;
            else {
                errno = 0;
                char* endptr;
                int equalsPosition = offsetFromNext(line, '=', 0);
                char* settingName = substring(line, 0, equalsPosition);
                char* settingValue = substring(line, equalsPosition + 1, strlen(line) - equalsPosition - 1);

                if(settingValue[strlen(settingValue) - 1] == '\n')
                    settingValue[strlen(settingValue) - 1] = '\0';

                if(strcmp("allowSameRank", settingName) == 0) {
                    cfg.allowSameRank = strcmp("true", settingValue) == 0;
                } else if(strcmp("allowSameSuit", settingName) == 0) {
                    cfg.allowSameSuit = strcmp("true", settingValue) == 0;
                } else if(strcmp("defaultPlayersLPs", settingName) == 0) {
                    int rs = strtol(settingValue, &endptr, 10);

                    if(errno == ERANGE || *endptr != '\0')
                        continue;
                    else
                        cfg.defaultPlayersLPs = rs;
                } else if(strcmp("defaultLPsOnField", settingName) == 0) {
                    int rs = strtol(settingValue, &endptr, 10);

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

void saveConfigurationToFile(gameConfiguration configuration, bool overwriteIfExists) {
    if(!overwriteIfExists && existsConfigurationFile())
        return;

    FILE* cfgFile = fopen("game.cfg", "w");

    fputs("allowSameRank=", cfgFile);
    if(configuration.allowSameRank)
        fputs("true", cfgFile);
    else
        fputs("false", cfgFile);
    fputs("\n", cfgFile);

    fputs("allowSameSuit=", cfgFile);
    if(configuration.allowSameSuit)
        fputs("true", cfgFile);
    else
        fputs("false", cfgFile);
    fputs("\n", cfgFile);

    fputs("defaultPlayersLPs=", cfgFile);
    int snLen = nDigits(configuration.defaultPlayersLPs) + 2;
    char* sn = (char*)malloc(snLen*sizeof(char));
    if(sn == NULL)
        exit(EXIT_ALLOC_FAILURE);

    snprintf(sn, snLen, "%d", configuration.defaultPlayersLPs);
    fputs(sn, cfgFile);
    fputs("\n", cfgFile);
    free(sn);

    fputs("defaultLPsOnField=", cfgFile);
    snLen = nDigits(configuration.defaultLPsOnField) + 2;
    sn = (char*)malloc(snLen*sizeof(char));
    if(sn == NULL)
        exit(EXIT_ALLOC_FAILURE);
    
    snprintf(sn, snLen, "%d", configuration.defaultLPsOnField);
    fputs(sn, cfgFile);
    fputs("\n", cfgFile);
    free(sn);
    fclose(cfgFile);
}