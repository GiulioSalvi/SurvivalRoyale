#include "ansi.h"
#include "logs.h"
#include "ansi_const.h"

LogsConfiguration prepareLogs() {
    LogsConfiguration logsConfiguration;
    struct tm* ltm = localtime(&(time_t){time(NULL)});

    int writtenChars = snprintf(logsConfiguration.fileName, fileNameBufferSize, "logs/%02d-%02d-%d_%02d,%02d,%02d.log",
        ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900,
        ltm->tm_hour, ltm->tm_min, ltm->tm_sec
    );

    if(writtenChars != fileNameBufferSize - 1) {
        logsConfiguration.useConsole = true;
        printfgr("#b##%d#Failed to create a log file, the console is going to be used.#r#\n", FgBrightRed);
        return logsConfiguration;
    }
    
    FILE* logsFile = fopen(logsConfiguration.fileName, "a+");
    if(logsFile == NULL) {
        logsConfiguration.useConsole = true;
        printfgr("#b##%d#Failed to create a log file, the console is going to be used.#r#\n", FgBrightRed);
    } else {
        fclose(logsFile);
        logsConfiguration.useConsole = false;
    }

    return logsConfiguration;
}

void printGameConfiguration(GameConfiguration configuration, LogsConfiguration logsConfiguration, bool newLine) {
    FILE* outStream = !logsConfiguration.useConsole ? fopen(logsConfiguration.fileName, "a+") : stdout;

    fprintf(outStream, "Allow cards with the same rank: ");
    fflush(outStream);
    if(configuration.allowSameRank)
        fprintf(outStream, "true");
    else
        fprintf(outStream, "false");
    fflush(outStream);

    fprintf(outStream, ", allow cards with the same suit: ");
    fflush(outStream);
    if(configuration.allowSameSuit)
        fprintf(outStream, "true");
    else
        fprintf(outStream, "false");
    fflush(outStream);

    fprintf(outStream, ", default LPs on the playing field: %d, default players' LPs: %d.\n", configuration.defaultLPsOnField, configuration.defaultPlayersLPs);
    fflush(outStream);

    fprintf(outStream, !logsConfiguration.useConsole || newLine ? "\n" : "");
    fflush(outStream);

    if(!logsConfiguration.useConsole)
        fclose(outStream);
}

void printPlayers(Game game, bool newLine) {
    for(int i = 0; i < game.playersCounter; i++)
        printPlayer(*game.players[i], game.logsConfiguration, i == game.playersCounter - 1 ? newLine : true);
}

void printPlayer(Player player, LogsConfiguration logsConfiguration, bool newLine) {
    if(logsConfiguration.useConsole) {
        printfgr("Player #b#%d#r# with #b#%d LPs#r# has cards #b#", player.id, player.lifePoints);

        printCard(player.facedUpCard, logsConfiguration, false);
        printgr("#r# faced up and #b#");
        printCard(player.facedDownCard, logsConfiguration, false);
        printgr("#r# faced down.");

        if(newLine)
            printgr("\n");
    } else {
        FILE* logFile = fopen(logsConfiguration.fileName, "a+");
        
        fprintf(logFile, "Player %d with %d LPs has cards ", player.id, player.lifePoints);
        fflush(logFile);
        fclose(logFile);

        printCard(player.facedUpCard, logsConfiguration, false);

        logFile = fopen(logsConfiguration.fileName, "a+");
        fprintf(logFile, " faced up and ");
        fflush(logFile);
        fclose(logFile);

        printCard(player.facedDownCard, logsConfiguration, false);

        logFile = fopen(logsConfiguration.fileName, "a+");
        fprintf(logFile, " faced down.\n");
        fflush(logFile);
        fclose(logFile);
    }
}

void printCard(Card card, LogsConfiguration logsConfiguration, bool newLine) {
    FILE* outStream = !logsConfiguration.useConsole ? fopen(logsConfiguration.fileName, "a+") : stdout;
    switch(card.suit) {
        case Clubs:
            fprintf(outStream, "Clubs");
            break;
        case Spades:
            fprintf(outStream, "Spades");
            break;
        case Diamonds:
            fprintf(outStream, "Diamonds");
            break;
        case Hearts:
            fprintf(outStream, "Hearts");
            break;
    }

    fprintf(outStream, " ");

    switch(card.rank) {
        case Ace:
            fprintf(outStream, "Ace");
            break;
        case Two:
            fprintf(outStream, "Two");
            break;
        case Three:
            fprintf(outStream, "Three");
            break;
        case Four:
            fprintf(outStream, "Four");
            break;
        case Five:
            fprintf(outStream, "Five");
            break;
        case Six:
            fprintf(outStream, "Six");
            break;
        case Seven:
            fprintf(outStream, "Seven");
            break;
        case Jack:
            fprintf(outStream, "Jack");
            break;
        case Queen:
            fprintf(outStream, "Queen");
            break;
        case King:
            fprintf(outStream, "King");
            break;
    }

    fprintf(outStream, !logsConfiguration.useConsole || newLine ? "\n" : "");

    fflush(outStream);
    if(!logsConfiguration.useConsole)
        fclose(outStream);
}

void printDeck(Card* deck, LogsConfiguration logsConfiguration, bool newLine) {
    for(int i = 0; i < 40; i++)
        printCard(deck[i], logsConfiguration, i == 39 ? newLine : true);
}