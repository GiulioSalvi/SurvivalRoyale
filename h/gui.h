#include "ansi.h"
#include "main.h"
#include "consts.h"
#include "ansi_const.h"

#ifndef _GUI_H_
    /// @brief Include guard.
    #define _GUI_H_

    #define CARD_WIDTH 15
    #define CARD_HEIGHT 9
    #define LOG_SECTION_HEIGHT 4
    #define MIN_ROWS ((2 * (CARD_HEIGHT + 4)) + (LOG_SECTION_HEIGHT + 2))
    #define MIN_COLUMNS 141

    typedef struct PageData {
        int playerRows;
        int playerPerRow;
        int playerCount;
        int rowSpacing;
        Player** players;
    } PageData;

    void drawCardsForPage(PageData* page, int startX, int bestStartColumn);
    void drawPageFrame(int maxRows, int maxColumns);
    void displayPage(PageData* page, int maxRows, int maxColumns, int bestStartColumn);
    void navigatePages(PageData* pagesData, int totalPages, int maxRows, int maxColumns, int bestStartColumn, int playerIndex, Game* game);

    int getCardColor(int cardRank);
    void drawLine(int startingX, int startingY, int length, char direction, char borders);
    void drawCard(int startingX, int startingY, int suit, int rank);

    PageData* getPageData(int maxRows, int maxColumns, Player** players, int totalPlayers, int* totalPages, int* bestStartColumn);
    void freePageData(PageData* pages, int totalPages);

    bool isTerminalSizeValid(int maxRows, int maxColumns);

    int getPageContainingPlayer(PageData* pagesData, int totalPages, int id);
#endif