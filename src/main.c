#include "ansi.h"
#include "main.h"
#include "ansi_const.h"

int main(int argc, char** argv) {
    // 
    // return 0;
    gameConfiguration cfg = getGameConfiguration(handleCLIArguments(argv, argc), getConfigurationFromArguments(argv, argc));
    srand(time(NULL));
    clearScreen();
    
    // printGameConfiguration(cfg, true);
    Card* deck = prepareCardDeck();
    int playersCounter = askPlayerNumber();

    clearScreen();
    Game game = prepareGame(playersCounter, deck, cfg);
    // printPlayers(game, false);
    
    while(!handleGamePhase(&game)) {
        removeDeadPlayers(&game);
        withdrawCards(&game);
        shuffleDeck(deck);
        giveCards(&game, deck, cfg);

        // printPlayers(game, false);
    }
    
    withdrawCards(&game);
    removeDeadPlayers(&game);
    announceWinner(*game.players[0]);

    freeDeck(deck);
    freeGame(&game);

    return 0;
}

int randomInt(int min, int max) {
    return rand()%(max - min + 1) + min;
}

gameConfiguration askConfigurationOptionsViaTerminal() {
    gameConfiguration cfg;
    int n = 0;
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
        if(n < 0) {
            clearScreen();
            printfgr("#b##%d#The value must be positive.\n#r#", (int)FgBrightRed);
        }

        printgr("#b#How many LPs on the field should there be by default? #r#");
        fflush(stdin);
        scanf("%d", &n);
    } while(n < 0);
    cfg.defaultLPsOnField = n;

    n = 1;
    do {
        if(n <= 0) {
            clearScreen();
            printfgr("#b##%d#The value must be positive and not zero.\n#r#", (int)FgBrightRed);
        }

        printgr("#b#How many LPs should the players have by default? #r#");
        fflush(stdin);
        scanf("%d", &n);
    } while(n <= 0);
    cfg.defaultPlayersLPs = n;
    
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

Game prepareGame(int playersCounter, Card* deck, gameConfiguration configuration) {
    Game game = buildGame(playersCounter);
    game.lifePointsOnTheField = configuration.defaultLPsOnField;

    for(int i = 0; i < game.playersCounter; i++) {
        Player* player = malloc(sizeof(Player));
        
        do
            player = preparePlayer(i + 1, deck, configuration);
        while(cardsWereGiven(game.players, game.playersCounter, *player) || cardAreEqual(player->facedUpCard, player->facedDownCard) || (!configuration.allowSameRank ? player->facedUpCard.rank == player->facedDownCard.rank : false) || (!configuration.allowSameSuit ? player->facedUpCard.suit == player->facedDownCard.suit : false));

        game.players[i] = player;
    }

    return game;
}

Player* preparePlayer(int id, Card* deck, gameConfiguration configuration) {
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
    printfgr("The current phase starts from #b#player %d#r#.\n\n", game->players[starterPlayerPosition]->id);

    for(int i = 0; i < game->playersCounter; i++) {
        int position = (i + starterPlayerPosition)%game->playersCounter, id = game->players[position]->id;
        Player* player = game->players[position];
        printfgr("#b#It's your turn, player %d!!#r# You have #b##%d#%d LPs#r#.\n", id, FgBrightCyan, player->lifePoints);
        
        revealCard(player->facedUpCard, id, true, false);
        applyEffect(game, position, true);
        printgr("\n");

        if(!player->revealedFacedDownCard) {
            revealCard(player->facedDownCard, id, false, false);

            if(revealFacedDownCard(player->facedDownCard))
                applyEffect(game, position, false);
            else
                printgr("#b#The card has not been revealed#r#.\n");
        } else
            printfgr("#b#Player %d#r#, your #b#faced down card#r# has been #b##%d#already revealed#r#!\n", id, FgBrightRed);
        
        Pause(true);
    }

    announceDeadPlayers(game);

    return isGameEnded(game);
}

bool isGameEnded(Game* game) {
    int c = 0;

    for(int i = 0; i < game->playersCounter; i++)
        if(game->players[i]->lifePoints > 0)
            c++;
    
    return c == 1;
}

void applyEffect(Game* game, int playerPosition, bool facedUpCard) {
    Player* player = game->players[playerPosition];
    
    if(!facedUpCard) {
        if(game->players[playerPosition]->revealedFacedDownCard) {
            printfgr("#b#Player %d#r#, your #b#faced down card#r# has been #b##%d#already revealed#r#! #b#No effect by the last card has been applied#r#.\n", player->id, FgBrightRed);
            return;
        }
        
        player->revealedFacedDownCard = true;
    }

    if((facedUpCard ? player->facedUpCard.rank : player->facedDownCard.rank) == Ace) {
        game->lifePointsOnTheField++;
        player->lifePoints--;

        printfgr("Now #b#player %d#r# has #b##%d#%d LPs#r#. ", player->id, FgBrightRed, player->lifePoints);
        printfgr("Now on the #b#playing field#r# there are #b##%d#%d LPs#r#.\n", FgGreen, game->lifePointsOnTheField);
    } else if((facedUpCard ? player->facedUpCard.rank : player->facedDownCard.rank) == Seven) {
        revealCard(game->players[(playerPosition + 1)%game->playersCounter]->facedDownCard, game->players[(playerPosition + 1)%game->playersCounter]->id, false, true);
        applyEffect(game, (playerPosition + 1)%game->playersCounter, false);
    } else if((facedUpCard ? player->facedUpCard.rank : player->facedDownCard.rank) == Jack) {
        player->lifePoints--;
        game->players[(playerPosition == 0 ? game->playersCounter : playerPosition) - 1]->lifePoints++;

        printfgr("Now #b#player %d#r# has #b##%d#%d LPs#r#. ", player->id, FgBrightRed, player->lifePoints);
        printfgr("Now #b#player %d#r# has #b##%d#%d LPs#r#.\n", game->players[(playerPosition == 0 ? game->playersCounter : playerPosition) - 1]->id, FgGreen, game->players[(playerPosition == 0 ? game->playersCounter : playerPosition) - 1]->lifePoints);
    } else if((facedUpCard ? player->facedUpCard.rank : player->facedDownCard.rank) == Queen) {
        player->lifePoints--;
        game->players[(playerPosition + 2)%game->playersCounter]->lifePoints++;

        printfgr("Now #b#player %d#r# has #b##%d#%d LPs#r#. ", player->id, FgBrightRed, player->lifePoints);
        printfgr("Now #b#player %d#r# has #b##%d#%d LPs#r#.\n", game->players[(playerPosition + 2)%game->playersCounter]->id, FgGreen, game->players[(playerPosition + 2)%game->playersCounter]->lifePoints);
    } else if((facedUpCard ? player->facedUpCard.rank : player->facedDownCard.rank) == King) {
        player->lifePoints += game->lifePointsOnTheField;
        game->lifePointsOnTheField = 0;

        printfgr("Now #b#player %d#r# has #b##%d#%d LPs#r#. ", player->id, FgGreen, player->lifePoints);
        printfgr("Now on the #b#playing field#r# there are #b##%d#0 LPs#r#.\n", FgBrightYellow);
    } else
        printgr("#b#No effect on the last card has been applied#r#.\n");
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

void giveCards(Game* game, Card* deck, gameConfiguration configuration) {
    for(int i = 0; i < game->playersCounter; i++)
        if(game->players[i]->lifePoints > 0) {
            Player* player = buildPlayer();
            player->id = game->players[i]->id;
            player->lifePoints = game->players[i]->lifePoints;

            do {
                player->facedUpCard = deck[randomInt(0, 39)];
                player->facedDownCard = deck[randomInt(0, 39)];
            } while(cardsWereGiven(game->players, game->playersCounter, *player) || cardAreEqual(player->facedUpCard, player->facedDownCard) || (!configuration.allowSameRank ? player->facedUpCard.rank == player->facedDownCard.rank : false) || (!configuration.allowSameSuit ? player->facedUpCard.suit == player->facedDownCard.suit : false));

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

void Pause(bool clear) {
    getChar();

    if(clear)
        clearScreen();
}

void printCard(Card card, bool newLine) {
    switch(card.suit) {
        case Clubs:
            printgr("Clubs");
            break;
        case Spades:
            printgr("Spades");
            break;
        case Diamonds:
            printgr("Diamonds");
            break;
        case Hearts:
            printgr("Hearts");
            break;
    }

    printgr(" ");

    switch(card.rank) {
        case Ace:
            printgr("Ace");
            break;
        case Two:
            printgr("Two");
            break;
        case Three:
            printgr("Three");
            break;
        case Four:
            printgr("Four");
            break;
        case Five:
            printgr("Five");
            break;
        case Six:
            printgr("Six");
            break;
        case Seven:
            printgr("Seven");
            break;
        case Jack:
            printgr("Jack");
            break;
        case Queen:
            printgr("Queen");
            break;
        case King:
            printgr("King");
            break;
    }

    if(newLine)
        printgr("\n");
}

void printDeck(Card* deck, bool newLine) {
    for(int i = 0; i < 40; i++)
        printCard(deck[i], i == 39 ? newLine : true);
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

void revealCard(Card card, int playerId, bool facedUp, bool newLine) {
    printfgr("Player %d #b#faced ", playerId);
    if(facedUp)
        printgr("up");
    else
        printgr("down");
    printgr("#r# card is a #b#");
    printCard(card, false);
    printgr("#r#, the effect is: ");
    printCardEffect(card, true);

    if(newLine)
        printgr("\n");
}

void printPlayer(Player player, bool newLine) {
    printfgr("Player #b#%d#r# with #b#%d LPs#r# has cards #b#", player.id, player.lifePoints);

    printCard(player.facedUpCard, false);
    printgr("#r# faced up and #b#");
    printCard(player.facedDownCard, false);
    printgr("#r# faced down.");

    if(newLine)
        printgr("\n");
}

void printPlayers(Game game, bool newLine) {
    for(int i = 0; i < game.playersCounter; i++)
        printPlayer(*game.players[i], i == game.playersCounter - 1 ? newLine : true);
}

void printGameConfiguration(gameConfiguration configuration, bool newLine) {
    printgr("Allow cards with the same rank: ");
    if(configuration.allowSameRank)
        printgr("true");
    else
        printgr("false");

    printgr(", allow cards with the same suit: ");
    if(configuration.allowSameSuit)
        printgr("true");
    else
        printgr("false");

    printfgr(", default LPs on the playing field: %d, default players' LPs: %d.\n", configuration.defaultLPsOnField, configuration.defaultPlayersLPs);

    if(newLine)
        printgr("\n");
}