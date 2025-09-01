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
 * \brief Terminal User Interface (TUI) implementation for card game display.
 *
 * This file contains functions to handle terminal-based user interface components,
 * including drawing cards, player information, and navigation between pages.
**/

#include "ansi.h"
#include "main.h"
#include "consts.h"
#include "ansi_const.h"

#ifndef _GUI_H_
    /// @brief Include guard.
    #define _GUI_H_

    /// @brief Integer const to represent the width of a card.
    #define CARD_WIDTH 15
    /// @brief Integer const to represent the height of a card.
    #define CARD_HEIGHT 9
    /// @brief Integer const to represent the height of the logs section.
    #define LOG_SECTION_HEIGHT 4
    /// @brief Integer const to represent the minimum rows of the terminal in order to start the game.
    #define MIN_ROWS ((2 * (CARD_HEIGHT + 4)) + (LOG_SECTION_HEIGHT + 2))
    /// @brief Integer const to represent the minimum columns of the terminal in order to start the game.
    #define MIN_COLUMNS 141

    /// @brief Struct to represent the layout and data of a page containing player information.
    typedef struct PageData {
        /// @brief The number of rows used to display players on the page.
        int playerRows;
        /// @brief The number of players displayed per row.
        int playerPerRow;
        /// @brief The total number of players on the page.
        int playerCount;
        /// @brief The vertical spacing between rows, including card height and player details.
        int rowSpacing;
        /// @brief An array of pointers to the players displayed on the page.
        Player** players;
    } PageData;

    /**
     * @brief Draws all cards for the current page.
     *
     * @param page The page data containing player information.
     * @param startX The starting row for drawing.
     * @param bestStartColumn The best column position to center the content.
     */
    void drawCardsForPage(PageData* page, int startX, int bestStartColumn);
    
    /**
     * @brief Draws the frame for a page, including borders and separators.
     *
     * @param maxRows The maximum number of terminal rows.
     * @param maxColumns The maximum number of terminal columns.
     */
    void drawPageFrame(int maxRows, int maxColumns);
    
    /**
     * @brief Displays a page of cards and player information.
     *
     * @param page The page data to display.
     * @param maxRows The maximum number of terminal rows.
     * @param maxColumns The maximum number of terminal columns.
     * @param bestStartColumn The best column position to center the content.
     */
    void displayPage(PageData* page, int maxRows, int maxColumns, int bestStartColumn);
    
    /**
     * @brief Navigates between pages and handles player actions during their turn.
     * 
     * @param pagesData The data of all pages.
     * @param totalPages The total number of pages.
     * @param maxRows The maximum number of rows in the terminal.
     * @param maxColumns The maximum number of columns in the terminal.
     * @param bestStartColumn The starting column to align content.
     * @param playerIndex The index of the current player.
     * @param game Pointer to the game state.
     */
    void navigatePages(PageData* pagesData, int totalPages, int maxRows, int maxColumns, int bestStartColumn, int playerIndex, Game* game);

    /**
     * @brief Retrieves the color associated with a card rank.
     *
     * @param cardRank The rank of the card.
     * @return A string representing the terminal color code.
     */
    int getCardColor(int cardRank);
    
    /**
     * @brief Draws a line in the terminal.
     *
     * @param startingX The starting row position.
     * @param startingY The starting column position.
     * @param length The length of the line.
     * @param direction The direction of the line ('h' for horizontal, 'v' for vertical).
     * @param borders The type of border ('u' for upper, 'd' for lower, 'n' for none).
     */
    void drawLine(int startingX, int startingY, int length, char direction, char borders);
    
    /**
     * @brief Draws a card at a specified position.
     *
     * @param startingX The row position to start drawing.
     * @param startingY The column position to start drawing.
     * @param suit The card suit (e.g., Clubs, Spades).
     * @param rank The card rank (e.g., Ace, Two).
     */
    void drawCard(int startingX, int startingY, int suit, int rank);

    /**
     * @brief Computes the page layout for players and allocates memory for the page data.
     * 
     * @param maxRows The maximum number of rows in the terminal.
     * @param maxColumns The maximum number of columns in the terminal.
     * @param players An array of pointers to all players.
     * @param totalPlayers The total number of players in the game.
     * @param totalPages Pointer to store the total number of pages.
     * @param bestStartColumn Pointer to store the starting column for centering the cards.
     * @return Pointer to the array of PageData structs representing the pages.
     */
    PageData* getPageData(int maxRows, int maxColumns, Player** players, int totalPlayers, int* totalPages, int* bestStartColumn);
    
    /**
     * @brief Frees the memory allocated for page data.
     * 
     * @param pages Pointer to the array of PageData structs to be freed.
     * @param totalPages The total number of pages to free.
     */
    void freePageData(PageData* pages, int totalPages);

    /**
     * @brief Checks if the terminal size meets the minimum requirements.
     *
     * @param maxRows The number of terminal rows.
     * @param maxColumns The number of terminal columns.
     * @return True if the terminal size is valid, false otherwise.
     */
    bool isTerminalSizeValid(int maxRows, int maxColumns);

    /**
     * @brief Determines which page contains a player by their ID.
     * 
     * @param pagesData The data of all pages.
     * @param totalPages The total number of pages.
     * @param id The ID of the player to locate.
     * @return The index of the page containing the player, or -1 if not found.
     */
    int getPageContainingPlayer(PageData* pagesData, int totalPages, int id);
    
#endif