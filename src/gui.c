#include "gui.h"

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

    // if(!player->revealedFacedDownCard) {
    //     revealCard(player->facedDownCard, id, false, false);

    //     if(revealFacedDownCard(player->facedDownCard))
    //         applyEffect(game, playerIndex, false);
    //     else
    // } else
    // Pause(true);

    char input;
    int currentPage = getPageContainingPlayer(pagesData, totalPages, id);

    while (1) {
        // clear the terminal screen
        clearScreen();
        
        cursorPosition(maxRows - (LOG_SECTION_HEIGHT + 1) + 1, 3);
        printfgr("#b#It's your turn, player %d!!#r# On the #b#playing field#r# there are #b#%d LPs#r#.", id, game->lifePointsOnTheField);

        cursorPosition(maxRows - (LOG_SECTION_HEIGHT + 1) + 2, 3);
        applyEffect(game, playerIndex, true);

        // Display the current page
        displayPage(&pagesData[currentPage], maxRows, maxColumns, bestStartColumn);

        cursorPosition(maxRows - (LOG_SECTION_HEIGHT + 1) + 3, 3);
        if(!player->revealedFacedDownCard)
            tellFacedDownCard(player->facedDownCard);
        else
            printfgr("Your #b#faced down card#r# has been #b##%d#already revealed#r#!", FgBrightRed);
        
        // Move cursor to the last empty row in the messages section
        cursorPosition(maxRows - 2, maxColumns - 2);
        printgr(" "); // Ensure cursor is visible and no leftover text

        // Get user input
        input = getchar();

        cursorPosition(maxRows - (LOG_SECTION_HEIGHT + 1) + 4, 3);
        // Handle input
        if (input == 'w') {
            // Move to the next page or loop back to the first page
            currentPage = (currentPage + 1) % totalPages;
        } else if (input == 's') {
            // Move to the previous page or loop back to the last page
            currentPage = (currentPage - 1 + totalPages) % totalPages;
        } else if (input == 'e') {
            // Exit the program
            clearScreen();
            break;
        } else if(!player->revealedFacedDownCard) {
            if(input == 'y') {
                applyEffect(game, playerIndex, false);
                displayPage(&pagesData[currentPage], maxRows, maxColumns, bestStartColumn);
            } else if(input == 'n')
                printgr("#b#The card has not been revealed#r#.");

            while(getchar() != '\n');

            Pause(true);
            break;
        } else {
            printfgr("Your #b#faced down card#r# has been #b##%d#already revealed#r#!", FgBrightRed);
            
            clearScreen();
            // Clear input buffer
            while(getchar() != '\n');
            
            break;
        } 

        // Clear input buffer
        while(getchar() != '\n');
    }
}

// function to display a full page (frame + cards)
void displayPage(PageData* page, int maxRows, int maxColumns, int bestStartColumn) {
    // draw all the cards for the current page
    drawCardsForPage(page, 3, bestStartColumn); // cards start at the best row to print with even spaces all the data

    // draw the page frame (borders and separator)
    drawPageFrame(maxRows, maxColumns);
}

// function to draw the page frame (borders and separator)
void drawPageFrame(int maxRows, int maxColumns) {
    // Top border
    drawLine(1, 1, maxColumns, 'h', 'u'); // Top border with corners

    // Left and right vertical borders
    drawLine(2, 1, maxRows - 1, 'v', 'n');             // Left vertical border
    drawLine(2, maxColumns, maxRows - 1, 'v', 'n');    // Right vertical border

    // Separator above the log section (2 lines above the bottom border)
    int logSeparatorRow = maxRows - LOG_SECTION_HEIGHT - 1;
    drawLine(logSeparatorRow, 2, maxColumns - 2, 'h', 'n'); // Horizontal separator

    // Bottom border
    drawLine(maxRows, 1, maxColumns, 'h', 'd'); // Bottom border with corners

    // Log section border that separates input from messages
    drawLine(maxRows - (LOG_SECTION_HEIGHT), maxColumns - 3, LOG_SECTION_HEIGHT, 'v', 'n');
}

// function to draw all cards for the current page
void drawCardsForPage(PageData* page, int startX, int bestStartColumn) {
    int columnSpacing = CARD_WIDTH + 2;  // spacing between cards
    int currentRow = startX;  // starting row position

    for (int i = 0; i < page->playerCount; i++) {
        // Calculate column position
        int currentCol = bestStartColumn + (i % page->playerPerRow) * columnSpacing;

        // Draw the card
        Player* player = page->players[i];
        drawCard(currentRow, currentCol, player->facedUpCard.suit, player->facedUpCard.rank);

        // Print player name and life points
        cursorPosition(currentRow + CARD_HEIGHT + 1, currentCol + 1);
        printfgr("ID: %u", player->id);
        cursorPosition(currentRow + CARD_HEIGHT + 2, currentCol + 1);
        printfgr("Life: %u ♥", player->lifePoints);

        // Move to the next row after completing a row
        if ((i + 1) % page->playerPerRow == 0) {
            currentRow += page->rowSpacing;
        }
    }
}


// function to draw a line in the terminal
void drawLine(int startingX, int startingY, int length, char direction, char borders) {
    if (borders == 'u') { // upper border with corners
        cursorPosition(startingX, startingY);
        printgr("┌"); // top-left corner
        for (int i = 1; i < length - 1; i++) {
            cursorPosition(startingX, startingY + i);
            printgr("─");
        }
        cursorPosition(startingX, startingY + length - 1);
        printgr("┐"); // top-right corner
    } 
    else if (borders == 'd') { // bottom border with corners
        cursorPosition(startingX, startingY);
        printgr("└"); // bottom-left corner
        for (int i = 1; i < length - 1; i++) {
            cursorPosition(startingX, startingY + i);
            printgr("─");
        }
        cursorPosition(startingX, startingY + length - 1);
        printgr("┘"); // bottom-right corner
    } 
    else if (borders == 'n') { // plain line
        for (int i = 0; i < length; i++) {
            if (direction == 'h') { // horizontal line
                cursorPosition(startingX, startingY + i);
                printgr("─");
            } 
            else if (direction == 'v') { // vertical line
                cursorPosition(startingX + i, startingY);
                printgr("│");
            }
        }
    }
}

// function to draw a single card at a specified position
void drawCard(int startingX, int startingY, int suit, int rank) {
    // Get the color for the card
    int color = getCardColor(rank);

    // Draw card borders with color
    printfgr("#%d#", color);
    drawLine(startingX, startingY, CARD_WIDTH, 'h', 'u'); // Top border
    drawLine(startingX + 1, startingY, CARD_HEIGHT - 1, 'v', 'n'); // Left border
    drawLine(startingX + 1, startingY + CARD_WIDTH - 1, CARD_HEIGHT - 1, 'v', 'n'); // Right border
    drawLine(startingX + CARD_HEIGHT, startingY, CARD_WIDTH, 'h', 'd'); // Bottom border
    defaultForegroundColor();

    // Calculate card's center
    int centerCol = startingY + CARD_WIDTH / 2;

    // Display card suit and rank with color
    const char* cardSuitString = CARD_SUIT_STRINGS[suit - Clubs]; // Suit index
    const char* cardRankString = CARD_RANK_STRINGS[rank - 1];    // Rank index

    // Print card suit
    cursorPosition(startingX + 2, centerCol - strlen(cardSuitString) / 2);
    printfgr("#%d#%s", color, cardSuitString);
    graphicReset();

    // Print card rank
    cursorPosition(startingX + CARD_HEIGHT - 2, centerCol - strlen(cardRankString) / 2);
    printfgr("#%d#%s", color, cardRankString);
    graphicReset();
}

// function used to get the card's color
int getCardColor(int cardRank) {
    switch (cardRank) {
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
    int upperSectionHeight = maxRows - (1 + 1 + LOG_SECTION_HEIGHT + 1 + 1); // // Upper line + upper minimal space + log section + line above

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
    if (!pagesData) {
        exit(EXIT_ALLOC_FAILURE);
    }

    int playersArrayIndex = 0; // Track players assigned to pages

    for (int i = 0; i < *totalPages; i++) {
        int playersOnThisPage = (playersArrayIndex + playersInEachFilledPage > totalPlayers)
                                    ? totalPlayers - playersArrayIndex
                                    : playersInEachFilledPage;

        // Fill page data
        pagesData[i].playerRows = availableRows;
        pagesData[i].playerPerRow = displayablePlayersPerRow;
        pagesData[i].playerCount = playersOnThisPage;
        pagesData[i].rowSpacing = rowSpacing;

        pagesData[i].players = (Player**)malloc(sizeof(Player*) * playersOnThisPage);
        if (!pagesData[i].players) {
            exit(EXIT_ALLOC_FAILURE);
        }

        for (int j = 0; j < playersOnThisPage; j++) {
            pagesData[i].players[j] = players[playersArrayIndex++];
        }
    }

    return pagesData;
}

// function to free page data
void freePageData(PageData* pages, int totalPages) {
    for (int i = 0; i < totalPages; i++) {
        free(pages[i].players);
    }
    free(pages);
}

// function to print page data
void printPageData(PageData* pages, int totalPages) {
    for (int i = 0; i < totalPages; i++) {
        printfgr("Page %d:\n", i + 1);
        printfgr("  Rows: %d, Players Per Row: %d, Total Players: %d\n", 
               pages[i].playerRows, pages[i].playerPerRow, pages[i].playerCount);

        for (int j = 0; j < pages[i].playerCount; j++) {
            printfgr("    Player ID: %d, Life Points: %d\n",
                   pages[i].players[j]->id,  
                   pages[i].players[j]->lifePoints);
        }
        printfgr("\n");
    }
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