#include "ansi.h"
#include "main.h"
#include "consts.h"
#include "ansi_const.h"

#ifndef _GUI_H_
    #define _GUI_H_

    #define CARD_WIDTH 15
    #define CARD_HEIGHT 9
    #define LOG_SECTION_HEIGHT 4
    #define MIN_ROWS ((2 * (CARD_HEIGHT + 4)) + (LOG_SECTION_HEIGHT + 2))
    #define MIN_COLUMNS 141 // ((2 * CARD_WIDTH) + 5)

    typedef struct PageData {
        int playerRows;       // number of rows of players
        int playerPerRow;     // number of players per row
        int playerCount;      // total players on the page
        int rowSpacing;       // spacing between rows (includes card height + text)
        Player** players;     // array of pointers to players
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
    void printPageData(PageData* pages, int totalPages);

    bool isTerminalSizeValid(int maxRows, int maxColumns);

    int getPageContainingPlayer(PageData* pagesData, int totalPages, int id);
#endif