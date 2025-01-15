#include "main.h"
#include "includes.h"

#ifndef _LOGS_H_
    #define _LOGS_H_

    LogsConfiguration prepareLogs();

    /// @brief Prints user-friendly game configuration settings.
    /// @param gameConfiguration The game configuration that has to be printed.
    /// @param logsConfiguration The logs configuration.
    /// @param newLine Flag for determining if the function has to go to a new line before exiting.
    void printGameConfiguration(GameConfiguration gameConfiguration, LogsConfiguration logsConfiguration, bool newLine);
    /// @brief Prints user-friendly the players' infos.
    /// @param game The game which cointains the players.
    /// @param newLine Flag for determining if the function has to go to a new line before exiting.
    void printPlayers(Game game, bool newLine);
    /// @brief Prints user-friendly player's info.
    /// @param player The player whose infos have to be printed.
    /// @param logsConfiguration The logs configuration.
    /// @param newLine Flag for determining if the function has to go to a new line before exiting.
    void printPlayer(Player player, LogsConfiguration logsConfiguration, bool newLine);
    /// @brief Prints user-friendly the card rank and suit.
    /// @param card The card that has to be printed.
    /// @param logsConfiguration The logs configuration.
    /// @param newLine Flag for determining if the function has to go to a new line before exiting.
    void printCard(Card card, LogsConfiguration logsConfiguration, bool newLine);
    /// @brief Prints user-friendly the cards deck.
    /// @param deck The deck that has to be printed.
    /// @param logsConfiguration The logs configuration.
    /// @param newLine Flag for determining if the function has to go to a new line before exiting.
    void printDeck(Card* deck, LogsConfiguration logsConfiguration, bool newLine);
#endif