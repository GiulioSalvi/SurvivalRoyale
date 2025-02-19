/**
 * \file
 * \brief Definition of logger functions.
**/

#include "main.h"
#include "includes.h"

#ifndef _LOGS_H_
    /// @brief Include guard.
    #define _LOGS_H_

    /// @brief Generates the logger configuration for the current session. Tries to generate the log file.
    /// @return The logger configuration to use.
    LogsConfiguration prepareLogs();

    /// @brief Prints user-friendly game configuration settings.
    /// @param gameConfiguration The game configuration that has to be printed.
    /// @param logsConfiguration The logs configuration.
    /// @param newLine Flag for determining if the function has to go to a new line before exiting. If the logger is not using the console, this value is ignored and a new line is always generated.
    void printGameConfiguration(GameConfiguration gameConfiguration, LogsConfiguration logsConfiguration, bool newLine);
    /// @brief Prints user-friendly the players' infos.
    /// @param game The game which cointains the players.
    /// @param newLine Flag for determining if the function has to go to a new line before exiting. If the logger is not using the console, this value is ignored and a new line is always generated.
    void printPlayers(Game game, bool newLine);
    /// @brief Prints user-friendly player's info.
    /// @param player The player whose infos have to be printed.
    /// @param logsConfiguration The logs configuration.
    /// @param newLine Flag for determining if the function has to go to a new line before exiting. If the logger is not using the console, this value is ignored and a new line is always generated.
    void printPlayer(Player player, LogsConfiguration logsConfiguration, bool newLine);
    /// @brief Prints user-friendly the card rank and suit.
    /// @param card The card that has to be printed.
    /// @param logsConfiguration The logs configuration.
    /// @param newLine Flag for determining if the function has to go to a new line before exiting. Differently from the behaviour of the other functions, this value is not ignored if the logger is not using the console.
    void printCard(Card card, LogsConfiguration logsConfiguration, bool newLine);
    /// @brief Prints user-friendly the cards deck.
    /// @param deck The deck that has to be printed.
    /// @param logsConfiguration The logs configuration.
    /// @param newLine Flag for determining if the function has to go to a new line before exiting. If the logger is not using the console, this value is ignored and a new line is always generated.
    void printDeck(Card* deck, LogsConfiguration logsConfiguration, bool newLine);
    /// @brief Prints user-friendly the pages' infos.
    /// @param pages An array of structures containing informations about each page.
    /// @param logsConfiguration The logs configuration.
    /// @param totalPages The amount of page structures in the array.
    /// @param newLine Flag for determining if the function has to go to a new line before exiting. If the logger is not using the console, this value is ignored and a new line is always generated.
    void printPageData(PageData pages[], LogsConfiguration logsConfiguration, int totalPages, bool newLine);
#endif