/**
 * \file
 * \brief Implementation of game-related functions.
**/

#include "tui.h"
#include "ansi.h"
#include "main.h"
#include "logs.h"
#include "ansi_const.h"

int main(int argc, char** argv) {
    // 
    // return 0;

    srand(time(NULL));
    const GameConfiguration gameCfg = getGameConfiguration(handleCLIArguments(argv, argc), getConfigurationFromArguments(argv, argc));
    const LogsConfiguration logsCfg = gameCfg.beVerbose ? prepareLogs() : (LogsConfiguration){.fileName = "", .useConsole = true};
    
    checkTerminal();
    setupTerminal();
    
    clearScreen();

    if(gameCfg.beVerbose)
        printGameConfiguration(gameCfg, logsCfg, true);
    Card* deck = prepareCardDeck();
    const int playersCounter = askPlayerNumber();
    clearScreen();

    Game game = prepareGame(playersCounter, deck, gameCfg);
    game.logsConfiguration = logsCfg;
    if(gameCfg.beVerbose)
        printPlayers(game, false);
    
    while(!handleGamePhase(&game)) {
        removeDeadPlayers(&game);
        withdrawCards(&game);
        shuffleDeck(deck);
        giveCards(&game, deck);

        if(gameCfg.beVerbose)
            printPlayers(game, false);
    }

    withdrawCards(&game);
    removeDeadPlayers(&game);
    announceWinner(*game.players[0]);

    freeDeck(deck);
    freeGame(&game);

    return 0;
}

void checkTerminal() {
    if(!checkTerminalSize()) {
        printfgr("#b##%d#The terminal is too small for the game to be played.#r#\n", FgBrightRed);
        exit(EXIT_TERMINAL_TOO_SMALL);
    }
    if(!checkTerminalHost()) {
        printf("The terminal's host is not supported. Please, use Windows Terminal App.\n");
        exit(EXIT_WINDOWS_TERMINAL_HOST_NOT_SUPPORTED);
    }
}

void setupTerminal() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
}

bool checkTerminalSize() {
    int maxRows = 0, maxColumns = 0;
    screenSize(&maxColumns, &maxRows);
    
    return isTerminalSizeValid(maxRows, maxColumns);
}

bool checkTerminalHost() {
    #ifdef _WIN32
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot == INVALID_HANDLE_VALUE) {
            printf("Errore durante la creazione dello snapshot.\n");
            return false;
        }

        DWORD processId = GetCurrentProcessId();
        while (processId != 0) {
            PROCESSENTRY32 pe32;
            pe32.dwSize = sizeof(PROCESSENTRY32);

            int found = 0;
            if (Process32First(hSnapshot, &pe32)) {
                do {
                    if (pe32.th32ProcessID == processId) {
                        // printf("PID: %lu - Nome: %s\n", processId, pe32.szExeFile);
                        if(strcmp(pe32.szExeFile, "WindowsTerminal.exe") == 0)
                            return true;

                        processId = pe32.th32ParentProcessID;
                        found = 1;
                        break;
                    }
                } while (Process32Next(hSnapshot, &pe32));
            }

            if (!found) {
                // printf("Processo con PID %lu non trovato o accesso negato.\n", processId);
                CloseHandle(hSnapshot);
                return false;
            }

            if (processId == 0) {
                // printf("Raggiunto il processo radice.\n");
                CloseHandle(hSnapshot);
                return false;
            }
        }

        CloseHandle(hSnapshot);
        return false;
    #else
        return true;
    #endif
}

int randomInt(const int min, const int max) {
    return rand()%(max - min + 1) + min;
}

GameConfiguration askConfigurationOptionsViaTerminal() {
    GameConfiguration cfg;
    int n = -1;
    char opt = '\0';

    do {
        if(opt != '\0') {
            clearScreen();
            printfgr("#b##%d#The valid options are y, Y, n and N.\n#r#", (int)FgBrightRed);
        }

        printgr("#b#Can the players have the cards with the same rank? (y,Y,n,N) #r#");
        fflush(stdin);
        scanf("%c", &opt);
    } while(opt != 'y' && opt != 'Y' && opt != 'n' && opt != 'N');
    cfg.allowSameRank = opt == 'y' || opt == 'Y';

    opt = '\0';
    do {
        if(opt != '\0') {
            clearScreen();
            printfgr("#b##%d#The valid options are y, Y, n, N.\n#r#", (int)FgBrightRed);
        }

        printgr("#b#Can the players have the cards with the same suit? (y, Y, n, N) #r#");
        fflush(stdin);
        scanf("%c", &opt);
    } while(opt != 'y' && opt != 'Y' && opt != 'n' && opt != 'N');
    cfg.allowSameSuit = opt == 'y' || opt == 'Y';

    do {
        if(n < 0 && n != -1) {
            clearScreen();
            printfgr("#b##%d#The value must be positive.\n#r#", (int)FgBrightRed);
        }

        printgr("#b#How many LPs on the field should there be by default? #r#");
        fflush(stdin);
        const int a = scanf("%d", &n);
        if(a == 0)
            n = -2;
    } while(n < 0);
    cfg.defaultLPsOnField = n;

    n = -1;
    do {
        if(n <= 0 && n != -1) {
            clearScreen();
            printfgr("#b##%d#The value must be positive and not zero.\n#r#", (int)FgBrightRed);
        }

        printgr("#b#How many LPs should the players have by default? #r#");
        fflush(stdin);
        const int a = scanf("%d", &n);
        if(a == 0)
            n = -2;
    } while(n < 1);
    cfg.defaultPlayersLPs = n;

    cfg.beVerbose = false;

    return cfg;
}

int askPlayerNumber() {
    int playersCounter = 2;

    do {
        if(playersCounter < 2 || playersCounter > 20) {
            playersCounter = 0;
            clearScreen();
            
            printfgr("#b##%d#The players number must be between 2 and 20.\n#r#", (int)FgBrightRed);
        }

        printgr("#b#Please, insert the players number: #r#");
        scanf("%d", &playersCounter);
    } while(playersCounter < 2 || playersCounter > 20);

    return playersCounter;
}

Card buildCard() {
    Card card;

    card.suit = -1;
    card.rank = -1;

    return card;
}

Card* buildDeck() {
    Card* deck = malloc(sizeof(Card)*40);

    for(int i = 0; i < 40; i++)
        deck[i] = buildCard();

    return deck;
}

Player* buildPlayer() {
    Player* player = malloc(sizeof(Player));

    player->id = -1;
    player->facedUpCard = buildCard();
    player->facedDownCard = buildCard();
    player->revealedFacedDownCard = false;

    return player;
}

Game buildGame(int playersCounter) {
    Game game;

    game.playersCounter = playersCounter;
    game.players = malloc(sizeof(Player*)*game.playersCounter);

    for(int i = 0; i < game.playersCounter; i++)
        game.players[i] = buildPlayer();

    return game;
}

void freeDeck(Card* deck) {
    free(deck);
}

void freePlayer(Player* player) {
    free(player);
}

void freePlayers(Player** players, int playersCounter) {
    for(int i = 0; i < playersCounter; i++)
        freePlayer(players[i]);
    free(players);
}

void freeGame(Game* game) {
    freePlayers(game->players, game->playersCounter);
}

Card* prepareCardDeck() {
    Card* deck = buildDeck();

    for(int i = 0; i < 40; i++) {
        Card card = buildCard();

        do {
            card.suit = randomInt(Clubs, Hearts); 
            card.rank = randomInt(Ace, King);
        } while(deckHasCard(deck, card));

        deck[i] = card;
    }

    return deck;
}

Game prepareGame(int playersCounter, Card* deck, GameConfiguration configuration) {
    Game game = buildGame(playersCounter);
    game.lifePointsOnTheField = configuration.defaultLPsOnField;

    for(int i = 0; i < game.playersCounter; i++) {
        Player* player = malloc(sizeof(Player));
        
        do
            player = preparePlayer(i + 1, deck, configuration);
        while(cardsWereGiven(game.players, game.playersCounter, *player) || cardAreEqual(player->facedUpCard, player->facedDownCard) || (!configuration.allowSameRank ? player->facedUpCard.rank == player->facedDownCard.rank : false) || (!configuration.allowSameSuit ? player->facedUpCard.suit == player->facedDownCard.suit : false));

        game.players[i] = player;
    }

    game.gameConfiguration = configuration;

    return game;
}

Player* preparePlayer(int id, Card* deck, GameConfiguration configuration) {
    Player* player = buildPlayer();

    player->id = id;
    player->lifePoints = configuration.defaultPlayersLPs;
    player->facedUpCard = deck[randomInt(0, 39)];
    player->facedDownCard = deck[randomInt(0, 39)];

    return player;
}

void shuffleDeck(Card* deck) {
    for(int i = 39; i > 0; i--) {
        int j = randomInt(0, i);

        Card tmp = deck[i];
        deck[i] = deck[j];
        deck[j] = tmp;
    }
}

bool handleGamePhase(Game* game) {
    int starterPlayerPosition = randomInt(0, game->playersCounter - 1);
    int maxRows = 0, maxColumns = 0, totalPages = 0, bestStartColumn = 0;
    screenSize(&maxColumns, &maxRows);
    PageData* pages = getPageData(maxRows, maxColumns, game->players, game->playersCounter, &totalPages, &bestStartColumn);
    
    drawPageFrame(maxRows, maxColumns);
    cursorPosition(maxRows - (LOG_SECTION_HEIGHT + 1) + 1, 3);
    printfgr("The current phase starts from #b#player %d#r#.", game->players[starterPlayerPosition]->id);
    Pause(false);

    printPageData(pages, game->logsConfiguration, totalPages, true);

    for(int i = 0; i < game->playersCounter; i++) {
        navigatePages(pages, totalPages, maxRows, maxColumns, bestStartColumn, (i + starterPlayerPosition)%game->playersCounter, game);
    }

    announceDeadPlayers(game);
    freePageData(pages, totalPages);

    return isGameEnded(game);
}

bool isGameEnded(Game* game) {
    int c = 0;

    for(int i = 0; i < game->playersCounter; i++)
        if(game->players[i]->lifePoints > 0)
            c++;
    
    return c == 1;
}

bool applyEffect(Game* game, int playerPosition, bool facedUpCard) {
    Player* player = game->players[playerPosition];
    
    if(!facedUpCard) {
        if(game->players[playerPosition]->revealedFacedDownCard) {
            printfgr("#b#Player %d's faced down card#r# has been #b##%d#already revealed#r#! #b#No effect by the last card has been applied#r#.", player->id, FgBrightRed);
            return true;
        }
        
        player->revealedFacedDownCard = true;
    }

    if((facedUpCard ? player->facedUpCard.rank : player->facedDownCard.rank) == Ace) {
        game->lifePointsOnTheField++;
        if(player->lifePoints > 0)
            player->lifePoints--;

        printfgr("By the effect of the #b#player %d's faced %s card#r# now on the #b#playing field#r# there are #b##%d#%d LPs#r#.", player->id, facedUpCard ? "up" : "down", FgGreen, game->lifePointsOnTheField);
        return true;
    } else if((facedUpCard ? player->facedUpCard.rank : player->facedDownCard.rank) == Seven) {
        tellFacedDownCard(game->players[(playerPosition + 1)%game->playersCounter]->facedDownCard, game->players[(playerPosition + 1)%game->playersCounter]->id);
        
        Pause(false);
        cursorHorizontalAbsolute(3);
        for(int i = 0; i < 134; i++)
            printgr(" ");
        cursorHorizontalAbsolute(3);

        return applyEffect(game, (playerPosition + 1)%game->playersCounter, false);
    } else if((facedUpCard ? player->facedUpCard.rank : player->facedDownCard.rank) == Jack) {
        if(player->lifePoints > 0)
            player->lifePoints--;
        game->players[(playerPosition == 0 ? game->playersCounter : playerPosition) - 1]->lifePoints++;
        
        return false;
        // printfgr("Now #b#player %d#r# has #b##%d#%d LPs#r#. ", player->id, FgBrightRed, player->lifePoints);
        // printfgr("Now #b#player %d#r# has #b##%d#%d LPs#r#.\n", game->players[(playerPosition == 0 ? game->playersCounter : playerPosition) - 1]->id, FgGreen, game->players[(playerPosition == 0 ? game->playersCounter : playerPosition) - 1]->lifePoints);
    } else if((facedUpCard ? player->facedUpCard.rank : player->facedDownCard.rank) == Queen) {
        if(player->lifePoints > 0)
            player->lifePoints--;
        game->players[(playerPosition + 2)%game->playersCounter]->lifePoints++;

        return false;
        // printfgr("Now #b#player %d#r# has #b##%d#%d LPs#r#. ", player->id, FgBrightRed, player->lifePoints);
        // printfgr("Now #b#player %d#r# has #b##%d#%d LPs#r#.\n", game->players[(playerPosition + 2)%game->playersCounter]->id, FgGreen, game->players[(playerPosition + 2)%game->playersCounter]->lifePoints);
    } else if((facedUpCard ? player->facedUpCard.rank : player->facedDownCard.rank) == King) {
        player->lifePoints += game->lifePointsOnTheField;
        game->lifePointsOnTheField = 0;

        // printfgr("Now #b#player %d#r# has #b##%d#%d LPs#r#. ", player->id, FgGreen, player->lifePoints);
        printfgr("By the effect of the #b#player %d's faced %s card#r# now on the #b#playing field#r# there are #b##%d#0 LPs#r#.", player->id, facedUpCard ? "up" : "down", FgBrightYellow);
        return true;
    } else {
        printfgr("#b#No effect by the player %d's faced %s card has been applied#r#.", player->id, facedUpCard ? "up" : "down");
        return true;
    }
}

bool revealFacedDownCard(Card card) {
    char ans = '\0';
    fflush(stdin);

    do {
        if(ans != '\0') {
            scrollUp(1);
            cursorHorizontalAbsolute(1);
            eraseInDisplay(0);
        }

        printgr("Do you want to #b#reveal#r# your #b#faced down#r# card and #b#apply its effect#r#?? (y,Y,n,N) ");
        scanf("%c", &ans);
    } while(ans != 'Y' && ans != 'N' && ans != 'y' && ans != 'n');

    printgr("\n");

    return ans == 'Y' || ans == 'y';
}

void giveCards(Game* game, Card* deck) {
    for(int i = 0; i < game->playersCounter; i++)
        if(game->players[i]->lifePoints > 0) {
            Player* player = buildPlayer();
            player->id = game->players[i]->id;
            player->lifePoints = game->players[i]->lifePoints;

            do {
                player->facedUpCard = deck[randomInt(0, 39)];
                player->facedDownCard = deck[randomInt(0, 39)];
            } while(cardsWereGiven(game->players, game->playersCounter, *player) ||
                cardAreEqual(player->facedUpCard, player->facedDownCard) ||
                (!game->gameConfiguration.allowSameRank ? player->facedUpCard.rank == player->facedDownCard.rank : false) || (!game->gameConfiguration.allowSameSuit ? player->facedUpCard.suit == player->facedDownCard.suit : false)
            );

            freePlayer(game->players[i]);
            game->players[i] = player;
        }
}

void announceDeadPlayers(Game* game) {
    for(int i = 0; i < game->playersCounter; i++)
        if(game->players[i]->lifePoints == 0)
            printfgr("#%d##b#Player %d, you are dead.#r#\n", FgBrightRed, game->players[i]->id);
}

int countDeadPlayers(Game* game) {
    int c = 0;

    for(int i = 0; i < game->playersCounter; i++)
        if(game->players[i]->lifePoints == 0)
            c++;

    return c;
}

void removeDeadPlayers(Game* game) {
    int newPlayersCounter = game->playersCounter - countDeadPlayers(game);
    if(game->playersCounter == newPlayersCounter)
        return;
    
    Player** players = (Player**)malloc(newPlayersCounter*sizeof(Player*));

    for(int i = 0, p = 0; i < game->playersCounter; i++) {
        if(game->players[i]->lifePoints > 0)
            players[p++] = game->players[i];
        else
            freePlayer(game->players[i]);
    }
    free(game->players);

    game->players = players;
    game->playersCounter = newPlayersCounter;
}

void withdrawCards(Game* game) {
    for(int i = 0; i < game->playersCounter; i++) {
        game->players[i]->facedUpCard = buildCard();
        game->players[i]->facedDownCard = buildCard();
    }
}

void announceWinner(Player player) {
    printfgr("\n#b##%d#Congratulations player %d, you have won!!#r#\n", FgBrightGreen, player.id);
}

bool deckHasCard(Card* deck, Card card) {
    for(int i = 0; i < 40; i++)
        if(cardAreEqual(deck[i], card))
            return true;
    
    return false;
}

bool cardAreEqual(Card card1, Card card2) {
    return card1.rank == card2.rank && card1.suit == card2.suit;
}

bool cardsWereGiven(Player** players, int playersCounter, Player player) {
    for(int i = 0; i < playersCounter; i++)
        if(players[i]->lifePoints > 0)
            if(cardAreEqual(player.facedDownCard, players[i]->facedDownCard) || cardAreEqual(player.facedUpCard, players[i]->facedUpCard))
                return true;

    return false;
}

void printCardEffect(Card card, bool newLine) {
    if(card.rank == Ace)
        printgr("you drop #b#1 LP#r# to the #b#playing field#r#.");
    else if(card.rank >= Two && card.rank <= Six)
        printgr("#b#none#r#.");
    else if(card.rank == Seven)
        printgr("you force the #b#next player#r# to reveal #b#his faced down card#r# and #b#apply its effect#r#.");
    else if(card.rank == Jack)
        printgr("you give #b#1 LP#r# to the #b#previous player#r#.");
    else if(card.rank == Queen)
        printgr("you give #b#1 LP#r# to the #b#second following player#r#.");
    else if(card.rank == King)
        printgr("you claim #b#all#r# the #b#LPs#r# on the playing field.");
    
    if(newLine)
        printgr("\n");
}

void tellFacedDownCard(Card card, int playerId) {
    LogsConfiguration logsConfiguration = {.fileName = "", .useConsole = true};
    
    if(playerId == 0)
        printgr("Your");
    else
        printfgr("Player %d's", playerId);
    printgr(" #b#faced down#r# card is a #b#");
    printCard(card, logsConfiguration, false);

    printgr("#r#. The effect is: ");
    printCardEffect(card, false);
}