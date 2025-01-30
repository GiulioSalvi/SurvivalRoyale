/**
 * \file
 * \brief Implementation of TUI functions.
**/

#include "tui.h"

const char* CARD_RANK_STRINGS[] = {
    "Ace", "Two", "Three", "Four", "Five",
    "Six", "Seven", "Jack", "Queen", "King"
};

const char* CARD_SUIT_STRINGS[] = {
    "Clubs", "Spades", "Diamonds", "Hearts"
};

void navigatePages(PageData* pagesData, int totalPages, int maxRows, int maxColumns, int bestStartColumn, int playerIndex, Game* game) {
    int id = pagesData->players[playerIndex]->id;
    Player* player = game->players[playerIndex];
    char input;
    int currentPage = getPageContainingPlayer(pagesData, totalPages, id);
    
    clearScreen();

    displayPage(&pagesData[currentPage], maxRows, maxColumns, bestStartColumn);

    cursorPosition(maxRows - (LOG_SECTION_HEIGHT + 1) + 1, 3);
    printfgr("#b#It's your turn, player %d!!#r# On the #b#playing field#r# there are #b#%d LPs#r#.", id, game->lifePointsOnTheField);

    cursorPosition(maxRows - (LOG_SECTION_HEIGHT + 1) + 2, 3);
    applyEffect(game, playerIndex, true);

    displayPage(&pagesData[currentPage], maxRows, maxColumns, bestStartColumn);

    cursorPosition(maxRows - (LOG_SECTION_HEIGHT + 1) + 3, 3);
    if(!player->revealedFacedDownCard) {
        tellFacedDownCard(player->facedDownCard, 0);

        cursorPosition(maxRows - (LOG_SECTION_HEIGHT + 1) + 4, 3);
        printgr("Do you want reveal it?");
    } else
        printfgr("Your #b#faced down card#r# has been #b##%d#already revealed#r#!", FgBrightRed);

    while(1) {
        cursorPosition(maxRows - 2, maxColumns - 2);
        printgr("  ");
        cursorBack(1);

        input = tolower(getchar());

        cursorPosition(maxRows - (LOG_SECTION_HEIGHT + 1) + 4, 3);
        if(input == 'w') {
            cursorUp(4);
            eraseInDisplay(1);

            currentPage = (currentPage + 1) % totalPages;
            displayPage(&pagesData[currentPage], maxRows, maxColumns, bestStartColumn);
        } else if(input == 's') {
            cursorUp(4);
            eraseInDisplay(1);

            currentPage = (currentPage - 1 + totalPages) % totalPages;
            displayPage(&pagesData[currentPage], maxRows, maxColumns, bestStartColumn);
        } else if(!player->revealedFacedDownCard) {
            if(input == 'y') {
                bool applyEffectHasPrinted = applyEffect(game, playerIndex, false);
                displayPage(&pagesData[currentPage], maxRows, maxColumns, bestStartColumn);

                if(!applyEffectHasPrinted) {
                    cursorPosition(maxRows - (LOG_SECTION_HEIGHT + 1) + 4, 3);
                    eraseInLine(0);
                    drawPageFrame(maxRows, maxColumns);
                }
            } else if(input == 'n')
                printgr("#b#The card has not been revealed#r#.");

            if(input == 'y' || input == 'n') {
                fflush(stdin);
                Pause(true);
                break;
            }
        } else {
            printfgr("Your #b#faced down card#r# has been #b##%d#already revealed#r#!", FgBrightRed);

            fflush(stdin);
            Pause(true);

            break;
        }
    }
}

void displayPage(PageData* page, int maxRows, int maxColumns, int bestStartColumn) {
    drawCardsForPage(page, 3, bestStartColumn); // cards start at the best row to print with even spaces all the data

    drawPageFrame(maxRows, maxColumns);
}

void drawPageFrame(int maxRows, int maxColumns) {
    drawLine(1, 1, maxColumns, 'h', 'u');

    drawLine(2, 1, maxRows - 1, 'v', 'n');
    drawLine(2, maxColumns, maxRows - 1, 'v', 'n');

    drawLine(maxRows, 1, maxColumns, 'h', 'd');

    int logSeparatorRow = maxRows - LOG_SECTION_HEIGHT - 1;
    drawLine(logSeparatorRow, 2, maxColumns - 2, 'h', 'n');

    // Log section border that separates input from messages
    drawLine(maxRows - (LOG_SECTION_HEIGHT), maxColumns - 3, LOG_SECTION_HEIGHT, 'v', 'n');
}

void drawCardsForPage(PageData* page, int startX, int bestStartColumn) {
    int columnSpacing = CARD_WIDTH + 2;
    int currentRow = startX;

    for(int i = 0; i < page->playerCount; i++) {
        int currentCol = bestStartColumn + (i % page->playerPerRow) * columnSpacing;

        Player* player = page->players[i];
        drawCard(currentRow, currentCol, player->facedUpCard.suit, player->facedUpCard.rank);

        cursorPosition(currentRow + CARD_HEIGHT + 1, currentCol + 1);
        printfgr("ID: %d", player->id);
        cursorPosition(currentRow + CARD_HEIGHT + 2, currentCol + 1);
        printfgr("Life: %d #%d#♥#r#", player->lifePoints, FgRed);

        if((i + 1) % page->playerPerRow == 0) {
            currentRow += page->rowSpacing;
        }
    }
}

void drawLine(int startingX, int startingY, int length, char direction, char borders) {
    if(borders == 'u') {
        cursorPosition(startingX, startingY);
        printgr("┌");
        for(int i = 1; i < length - 1; i++) {
            cursorPosition(startingX, startingY + i);
            printgr("─");
        }
        cursorPosition(startingX, startingY + length - 1);
        printgr("┐");
    } else if(borders == 'd') {
        cursorPosition(startingX, startingY);
        printgr("└");
        for(int i = 1; i < length - 1; i++) {
            cursorPosition(startingX, startingY + i);
            printgr("─");
        }
        cursorPosition(startingX, startingY + length - 1);
        printgr("┘");
    } else if(borders == 'n') {
        for(int i = 0; i < length; i++) {
            if(direction == 'h') {
                cursorPosition(startingX, startingY + i);
                printgr("─");
            } else if(direction == 'v') {
                cursorPosition(startingX + i, startingY);
                printgr("│");
            }
        }
    }
}

void drawCard(int startingX, int startingY, int suit, int rank) {
    int color = getCardColor(rank);

    printfgr("#%d#", color);
    drawLine(startingX, startingY, CARD_WIDTH, 'h', 'u');
    drawLine(startingX + 1, startingY, CARD_HEIGHT - 1, 'v', 'n');
    drawLine(startingX + 1, startingY + CARD_WIDTH - 1, CARD_HEIGHT - 1, 'v', 'n');
    drawLine(startingX + CARD_HEIGHT, startingY, CARD_WIDTH, 'h', 'd');
    defaultForegroundColor();

    int centerCol = startingY + CARD_WIDTH / 2;

    const char* cardSuitString = CARD_SUIT_STRINGS[suit - Clubs];
    const char* cardRankString = CARD_RANK_STRINGS[rank - 1];

    cursorPosition(startingX + 2, centerCol - strlen(cardSuitString) / 2);
    printfgr("#%d#%s", color, cardSuitString);
    graphicReset();

    cursorPosition(startingX + CARD_HEIGHT - 2, centerCol - strlen(cardRankString) / 2);
    printfgr("#%d#%s", color, cardRankString);
    graphicReset();
}

int getCardColor(int cardRank) {
    switch(cardRank) {
        case Seven:
            return FgBlue;
        case Jack:
            return FgRed;
        case Queen:
            return FgYellow;
        case Ace:
            return FgMagenta;
        case King:
            return FgGreen;
        default:
            return FgWhite;
    }
}

PageData* getPageData(int maxRows, int maxColumns, Player** players, int totalPlayers, int* totalPages, int* bestStartColumn) {
    // Constants for card layout
    int columnSpacing = CARD_WIDTH + 5;  // Card width + spacing between cards
    int rowSpacing = CARD_HEIGHT + 3;   // Card height + name row + life points row + minimum space row

    // Calculate the height of the upper section
    int upperSectionHeight = maxRows - (1 + 1 + LOG_SECTION_HEIGHT + 1 + 1); // Upper line + upper minimal space + log section + line above

    // Determine usable rows in the upper section
    int availableRows = upperSectionHeight / rowSpacing;

    // Adjust usable columns for horizontal centering
    int usableColumns = maxColumns - 2; // Subtract minimal padding
    int displayablePlayersPerRow = usableColumns / columnSpacing;

    // Calculate the remaining space for centering cards horizontally
    int totalCardWidth = displayablePlayersPerRow * columnSpacing;
    int remainingSpace = usableColumns - totalCardWidth;
    *bestStartColumn = 3 + (remainingSpace / 2); // Center cards horizontally

    // Total players per page
    int playersInEachFilledPage = availableRows * displayablePlayersPerRow;
    *totalPages = (totalPlayers + playersInEachFilledPage - 1) / playersInEachFilledPage;

    // Allocate memory for pages
    PageData* pagesData = (PageData*)malloc(sizeof(PageData) * (*totalPages));
    if(!pagesData)
        exit(EXIT_ALLOC_FAILURE);

    int playersArrayIndex = 0; // Track players assigned to pages

    for(int i = 0; i < *totalPages; i++) {
        int playersOnThisPage = (playersArrayIndex + playersInEachFilledPage > totalPlayers)
                                    ? totalPlayers - playersArrayIndex
                                    : playersInEachFilledPage;

        // Fill page data
        pagesData[i].playerRows = availableRows;
        pagesData[i].playerPerRow = displayablePlayersPerRow;
        pagesData[i].playerCount = playersOnThisPage;
        pagesData[i].rowSpacing = rowSpacing;

        pagesData[i].players = (Player**)malloc(sizeof(Player*) * playersOnThisPage);
        if(!pagesData[i].players)
            exit(EXIT_ALLOC_FAILURE);

        for(int j = 0; j < playersOnThisPage; j++)
            pagesData[i].players[j] = players[playersArrayIndex++];
    }

    return pagesData;
}

void freePageData(PageData* pages, int totalPages) {
    for(int i = 0; i < totalPages; i++)
        free(pages[i].players);

    free(pages);
}

bool isTerminalSizeValid(int maxRows, int maxColumns) {
    return (maxRows >= MIN_ROWS) && (maxColumns >= MIN_COLUMNS);
}

int getPageContainingPlayer(PageData* pagesData, int totalPages, int id) {
    for(int i = 0; i < totalPages; i++)
        for(int j = 0; j < pagesData[i].playerCount; j++)
            if(pagesData[i].players[j]->id == id) return i;

    return -1;
}