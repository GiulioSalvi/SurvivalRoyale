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
#define LOG_SECTION_HEIGHT 3
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

void drawLine(int startingX, int startingY, int length, char direction, char borders);
void drawCard(int startingX, int startingY, int suit, int rank, bool hidden);
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
    getTerminalSizes(&maxRows, &maxColumns);

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
        moveCursorAt(maxRows - 2, maxColumns - 2);
        printf(" "); // Ensure cursor is visible and no leftover text

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

    // drawing the upper line
    drawLine(1, 1, maxColumns, 'h', 'u'); // top border

    // drawing the leftside line
    drawLine(2, 1, maxRows - 1, 'v', 'n'); // left border

    // drawing the rightside line
    drawLine(2, maxColumns, maxRows - 1, 'v', 'n'); // right border

    // drawing the separator between the cards section and the logs section
    drawLine(maxRows - 2 - LOG_SECTION_HEIGHT, 2, maxColumns - 2, 'h', 'n'); // separator

    // drawing the bottom line
    drawLine(maxRows - 1, 1, maxColumns, 'h', 'd'); // bottom border

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
        drawCard(currentRow, currentCol, randomInt(Clubs, Hearts), randomInt(Ace, King), randomBool());

        // Print player name and life points
        moveCursorAt(currentRow + CARD_HEIGHT + 1, currentCol + 1);
        printf("Name: %s", player->name);
        moveCursorAt(currentRow + CARD_HEIGHT + 2, currentCol + 1);
        printf("Life: %d ♥", player->lifePoints);

        // Move to the next row after completing a row
        if ((i + 1) % page->playerPerRow == 0) {
            currentRow += page->rowSpacing;
        }
    }
}


// function to draw a line in the terminal
void drawLine(int startingX, int startingY, int length, char direction, char borders) {
    if (borders == 'u') { // upper border with corners
        moveCursorAt(startingX, startingY);
        printf("┌"); // top-left corner
        for (int i = 1; i < length - 1; i++) {
            moveCursorAt(startingX, startingY + i);
            printf("─");
        }
        moveCursorAt(startingX, startingY + length - 1);
        printf("┐"); // top-right corner
    } 
    else if (borders == 'd') { // bottom border with corners
        moveCursorAt(startingX, startingY);
        printf("└"); // bottom-left corner
        for (int i = 1; i < length - 1; i++) {
            moveCursorAt(startingX, startingY + i);
            printf("─");
        }
        moveCursorAt(startingX, startingY + length - 1);
        printf("┘"); // bottom-right corner
    } 
    else if (borders == 'n') { // plain line
        for (int i = 0; i < length; i++) {
            if (direction == 'h') { // horizontal line
                moveCursorAt(startingX, startingY + i);
                printf("─");
            } 
            else if (direction == 'v') { // vertical line
                moveCursorAt(startingX + i, startingY);
                printf("│");
            }
        }
    }
}

// function to draw a single card at a specified position
void drawCard(int startingX, int startingY, int suit, int rank, bool hidden) {
    // draw card borders
    drawLine(startingX, startingY, CARD_WIDTH, 'h', 'u'); // top border
    drawLine(startingX + 1, startingY, CARD_HEIGHT - 1, 'v', 'n'); // left border
    drawLine(startingX + 1, startingY + CARD_WIDTH - 1, CARD_HEIGHT - 1, 'v', 'n'); // right border
    drawLine(startingX + CARD_HEIGHT, startingY, CARD_WIDTH, 'h', 'd'); // bottom border

    // calculate card's center
    int centerCol = startingY + CARD_WIDTH / 2;

    if (hidden) {
        // display a hidden card ("?")
        moveCursorAt(startingX + CARD_HEIGHT / 2, centerCol);
        printf("?");
    } else {
        // display card suit and rank
        const char* cardSuitString = CARD_SUIT_STRINGS[suit - Clubs]; // suit index
        const char* cardRankString = CARD_RANK_STRINGS[rank - 1];    // rank index

        // print card suit
        moveCursorAt(startingX + 2, centerCol - strlen(cardSuitString) / 2);
        printf("%s", cardSuitString);

        // print card rank
        moveCursorAt(startingX + CARD_HEIGHT - 2, centerCol - strlen(cardRankString) / 2);
        printf("%s", cardRankString);
    }
}

// function to move the cursor to a specified position
void moveCursorAt(unsigned int x, unsigned int y) {
    printf("\033[%u;%uH", x, y); // escape sequence for cursor movement
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
    int upperSectionHeight = maxRows - (1 + 1 + LOG_SECTION_HEIGHT + 2 + 1); // Upper line + upper minimal space + log section + line above + one empty line

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
        perror("Failed to allocate memory for pages");
        exit(EXIT_FAILURE);
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
            perror("Failed to allocate memory for player pointers");
            exit(EXIT_FAILURE);
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
        printf("Page %d:\n", i + 1);
        printf("  Rows: %d, Players Per Row: %d, Total Players: %d\n", 
               pages[i].playerRows, pages[i].playerPerRow, pages[i].playerCount);

        for (int j = 0; j < pages[i].playerCount; j++) {
            printf("    Player ID: %d, Name: %s, Life Points: %d\n",
                   pages[i].players[j]->id, 
                   pages[i].players[j]->name, 
                   pages[i].players[j]->lifePoints);
        }
        printf("\n");
    }
}

void getTerminalSizes(int* maxRows, int* maxColumns) {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        perror("failed to get terminal sizes");
        exit(EXIT_FAILURE);
    }

    *maxRows = w.ws_row;
    *maxColumns = w.ws_col;
}

void clearScreen() {
    printf(CLEAR_SCREEN);
}


// Function to check if the terminal size is sufficient
bool isTerminalSizeValid(int maxRows, int maxColumns) {
    return (maxRows >= MIN_ROWS) && (maxColumns >= MIN_COLUMNS);
}

// Function to generate a random integer between min and max (inclusive)
int randomInt(int min, int max) {
    if (min > max) {
        int temp = min;
        min = max;
        max = temp;
    }
    return (rand() % (max - min + 1)) + min;
}

bool randomBool() {
    return rand() % 2 == 0; // 50% chance for true or false
}


/*
    // drawing the upper line
    drawLine(1, 1, maxColumns, 'h', 'u');

    // drawing the leftside line
    drawLine(2, 1, maxRows - 1, 'v', 'n');

    // drawing the rightside line
    drawLine(2, maxColumns, maxRows - 1, 'v', 'n');

    // drawing the separator between the cards section and the logs section
    drawLine(maxRows - 2 - LOG_SECTION_HEIGTH, 2, maxColumns - 2, 'h', 'n');

    // drawing the bottom line
    drawLine(maxRows - 1, 1, maxColumns, 'h', 'd');
    */