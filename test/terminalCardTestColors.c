#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

// necessary constants
#define CLEAR_SCREEN "\033[2J\033[H"
#define RESET "\033[0m"
#define BOLD "\033[1m"

#define CARD_WIDTH 15
#define CARD_HEIGHT 9
#define LOG_SECTION_HEIGHT 4
#define MIN_ROWS ((2 * (CARD_HEIGHT + 4)) + (LOG_SECTION_HEIGHT + 2))
#define MIN_COLUMNS ((2 * CARD_WIDTH) + 5)

#define Ace 1
#define Two 2
#define Three 3
#define Four 4
#define Five 5
#define Six 6
#define Seven 7
#define Jack 8
#define Queen 9
#define King 10

#define Clubs 11
#define Spades 12
#define Diamonds 13
#define Hearts 14

const char* CARD_RANK_STRINGS[] = {
    "Ace", "Two", "Three", "Four", "Five",
    "Six", "Seven", "Jack", "Queen", "King"
};

const char* CARD_SUIT_STRINGS[] = {
    "Clubs", "Spades", "Diamonds", "Hearts"
};

// struct to store the relevant data for each player
typedef struct Player {
    int id;
    char* name;
    int lifePoints;
} Player;

// struct to store the page data
typedef struct PageData {
    int playerRows;       // number of rows of players
    int playerPerRow;     // number of players per row
    int playerCount;      // total players on the page
    int rowSpacing;       // spacing between rows (includes card height + text)
    Player** players;     // array of pointers to players
} PageData;

// function prototypes
void drawCardsForPage(PageData* page, int startX, int bestStartColumn);
void drawPageFrame(int maxRows, int maxColumns);
void displayPage(PageData* page, int maxRows, int maxColumns, int bestStartColumn);
void navigatePages(PageData* pagesData, int totalPages, int maxRows, int maxColumns, int bestStartColumn);

const char* getCardColor(int cardRank);
void drawLine(int startingX, int startingY, int length, char direction, char borders);
void drawCard(int startingX, int startingY, int suit, int rank);
void moveCursorAt(unsigned int x, unsigned int y);

Player** initializePlayers(int playerCount);
void freePlayers(Player** players, int playerCount);

PageData* getPageData(int maxRows, int maxColumns, Player** players, int totalPlayers, int* totalPages, int* bestStartColumn);
void freePageData(PageData* pages, int totalPages);
void printPageData(PageData* pages, int totalPages);

bool isTerminalSizeValid(int maxRows, int maxColumns);
void getTerminalSizes(int* maxRows, int* maxColumns);
void clearScreen();

int randomInt(int min, int max);
bool randomBool();

int main() {
    int maxRows, maxColumns;

    // Get terminal dimensions
    screenSize(&maxRows, &maxColumns);

    int totalPlayers = 20;
    int totalPages, bestStartColumn;

    // Initialize players and page data
    Player** players = initializePlayers(totalPlayers);
    PageData* pagesData = getPageData(maxRows, maxColumns, players, totalPlayers, &totalPages, &bestStartColumn);

    // Navigate through pages
    navigatePages(pagesData, totalPages, maxRows, maxColumns, bestStartColumn);

    // Free allocated memory
    freePlayers(players, totalPlayers);
    freePageData(pagesData, totalPages);

    return 0;
}

// Function to navigate through pages
void navigatePages(PageData* pagesData, int totalPages, int maxRows, int maxColumns, int bestStartColumn) {
    int currentPage = 0;
    char input;

    while (1) {
        // Display the current page
        displayPage(&pagesData[currentPage], maxRows, maxColumns, bestStartColumn);

        // Move cursor to the last empty row in the messages section
        cursorPosition(maxRows - 2, maxColumns - 2);
        printfgr(" "); // Ensure cursor is visible and no leftover text

        // Get user input
        input = getchar();

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
        }

        // Clear input buffer
        while (getchar() != '\n');
    }
}

// function to display a full page (frame + cards)
void displayPage(PageData* page, int maxRows, int maxColumns, int bestStartColumn) {
    // clear the terminal screen
    clearScreen();

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
        drawCard(currentRow, currentCol, randomInt(Clubs, Hearts), randomInt(Ace, King));

        // Print player name and life points
        cursorPosition(currentRow + CARD_HEIGHT + 1, currentCol + 1);
        printfgr("Name: %s", player->name);
        cursorPosition(currentRow + CARD_HEIGHT + 2, currentCol + 1);
        printfgr("Life: %d ♥", player->lifePoints);

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
        printfgr("┌"); // top-left corner
        for (int i = 1; i < length - 1; i++) {
            cursorPosition(startingX, startingY + i);
            printfgr("─");
        }
        cursorPosition(startingX, startingY + length - 1);
        printfgr("┐"); // top-right corner
    } 
    else if (borders == 'd') { // bottom border with corners
        cursorPosition(startingX, startingY);
        printfgr("└"); // bottom-left corner
        for (int i = 1; i < length - 1; i++) {
            cursorPosition(startingX, startingY + i);
            printfgr("─");
        }
        cursorPosition(startingX, startingY + length - 1);
        printfgr("┘"); // bottom-right corner
    } 
    else if (borders == 'n') { // plain line
        for (int i = 0; i < length; i++) {
            if (direction == 'h') { // horizontal line
                cursorPosition(startingX, startingY + i);
                printfgr("─");
            } 
            else if (direction == 'v') { // vertical line
                cursorPosition(startingX + i, startingY);
                printfgr("│");
            }
        }
    }
}

// function to draw a single card at a specified position
void drawCard(int startingX, int startingY, int suit, int rank) {
    // Get the color for the card
    const char* color = getCardColor(rank);

    // Draw card borders with color
    printfgr("%s", color); // Set color for the border
    drawLine(startingX, startingY, CARD_WIDTH, 'h', 'u'); // Top border
    drawLine(startingX + 1, startingY, CARD_HEIGHT - 1, 'v', 'n'); // Left border
    drawLine(startingX + 1, startingY + CARD_WIDTH - 1, CARD_HEIGHT - 1, 'v', 'n'); // Right border
    drawLine(startingX + CARD_HEIGHT, startingY, CARD_WIDTH, 'h', 'd'); // Bottom border
    printfgr("%s", RESET); // Reset color after drawing the borders

    // Calculate card's center
    int centerCol = startingY + CARD_WIDTH / 2;

    // Display card suit and rank with color
    const char* cardSuitString = CARD_SUIT_STRINGS[suit - Clubs]; // Suit index
    const char* cardRankString = CARD_RANK_STRINGS[rank - 1];    // Rank index

    // Print card suit
    cursorPosition(startingX + 2, centerCol - strlen(cardSuitString) / 2);
    printfgr("%s%s\033[0m", color, cardSuitString);

    // Print card rank
    cursorPosition(startingX + CARD_HEIGHT - 2, centerCol - strlen(cardRankString) / 2);
    printfgr("%s%s\033[0m", color, cardRankString);
}

// function used to get the card's color
const char* getCardColor(int cardRank) {
    switch (cardRank) {
        case Seven:
            return "\033[0;34m"; // Blue (Forces next player)
        case Jack:
            return "\033[0;31m"; // Red (Gives 1 life to the previous player)
        case Queen:
            return "\033[0;33m"; // Yellow (Gives 1 life to the second next player)
        case Ace:
            return "\033[0;35m"; // Magenta (Drops 1 life to the field)
        case King:
            return "\033[0;32m"; // Green (Claims all life points)
        default:
            return "\033[0;37m"; // White (No effect cards 2-6)
    }
}

// function to initialize players
Player** initializePlayers(int playerCount) {
    Player** players = (Player**)malloc(playerCount * sizeof(Player*));
    if (!players) {
        perror("failed to allocate memory for players");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < playerCount; i++) {
        players[i] = (Player*)malloc(sizeof(Player));
        if (!players[i]) {
            perror("failed to allocate memory for player");
            exit(EXIT_FAILURE);
        }

        players[i]->id = i + 1;
        players[i]->lifePoints = 2;

        players[i]->name = (char*)malloc(20 * sizeof(char));
        if (!players[i]->name) {
            perror("failed to allocate memory for player name");
            exit(EXIT_FAILURE);
        }
        snprintf(players[i]->name, 20, "Player_%d", i + 1);
    }

    return players;
}

// function to free players
void freePlayers(Player** players, int playerCount) {
    if (!players) return;

    for (int i = 0; i < playerCount; i++) {
        free(players[i]->name);
        free(players[i]);
    }
    free(players);
}

// function to compute pages of players
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
            printfgr("    Player ID: %d, Name: %s, Life Points: %d\n",
                   pages[i].players[j]->id, 
                   pages[i].players[j]->name, 
                   pages[i].players[j]->lifePoints);
        }
        printfgr("\n");
    }
}

void clearScreen() {
    printfgr(CLEAR_SCREEN);
}


// Function to check if the terminal size is sufficient
bool isTerminalSizeValid(int maxRows, int maxColumns) {
    return (maxRows >= MIN_ROWS) && (maxColumns >= MIN_COLUMNS);
}