#include "../h/ansi.h"
#include "../h/main.h"
#include "../h/ansi_const.h"

int main() {
    // 
    // return 0;
    srand(time(NULL));
    clearScreen();
    
    Card** deck = prepareCardDeck();
    int playersCounter = askPlayerNumber();

    Game game = prepareGame(playersCounter, deck);
    for(int i = 0; i < game.playersCounter; i++)
        printPlayer(*game.players[i], true);
    handleGamePhase(&game);

    return 0;
}

int randomInt(int min, int max) {
    return rand()%(max - min + 1) + min;
}

int askPlayerNumber() {
    // bool first = true;
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

Card* buildCard() {
    Card* card = malloc(sizeof(Card));

    card->suit = -1;
    card->rank = -1;

    return card;
}

Card** buildDeck() {
    Card** deck = malloc(sizeof(Card*)*40);

    for(int i = 0; i < 40; i++)
        deck[i] = buildCard();

    return deck;
}

Player* buildPlayer() {
    Player* player = malloc(sizeof(Player));

    player->id = -1;
    player->facedUpCard = buildCard();
    player->facedDownCard = buildCard();

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

Card** prepareCardDeck() {
    Card** deck = buildDeck();

    for(int i = 0; i < 40; i++) {
        Card* card = buildCard();

        do {
            card->suit = randomInt(Clubs, Hearts); 
            card->rank = randomInt(Ace, King);
        } while(deckHasCard(deck, *card));

        deck[i] = card;
    }

    return deck;
}

Game prepareGame(int playersCounter, Card** deck) {
    Game game = buildGame(playersCounter);
    game.lifePointsOnTheField = 0;

    for(int i = 0; i < game.playersCounter; i++) {
        Player* player = malloc(sizeof(Player));
        
        do
            player = preparePlayer(i + 1, deck);
        while(cardsWereGiven(game.players, game.playersCounter, *player) || cardAreEqual(*player->facedUpCard, *player->facedDownCard));

        game.players[i] = player;
    }

    return game;
}

Player* preparePlayer(int id, Card** deck) {
    Player* player = buildPlayer();

    player->id = id;
    player->lifePoints = 2;
    player->facedUpCard = deck[randomInt(0, 39)];
    player->facedDownCard = deck[randomInt(0, 39)];

    return player;
}

void shuffleDeck(Card** deck) {
    for(int i = 39; i > 0; i--) {
        int j = randomInt(0, i);

        Card* tmp = deck[i];
        deck[i] = deck[j];
        deck[j] = tmp;
    }
}

bool handleGamePhase(Game* game) {
    int starterPlayerID = randomInt(0, game->playersCounter - 1);
    printfgr("\nThe current phase starts from #b#player %d#r#.\n", starterPlayerID + 1);

    for(int i = 0; i < game->playersCounter; i++) {
        int id = (i + starterPlayerID)%game->playersCounter;
        Player* player = game->players[id];
        printfgr("\n#b#It's your turn, player %d!!#r# You have #b##%d#%d LPs#r#.\n", id + 1, FgBrightCyan, player->lifePoints);
        
        revealCard(*player->facedUpCard, id + 1, true, false);
        applyEffect(game, id, true);
        printgr("\n");

        if(!player->revealedFacedDownCard) {
            revealCard(*player->facedDownCard, id + 1, false, false);

            if(revealFacedDownCard(*player->facedDownCard))
                applyEffect(game, id, false);
            else
                printgr("#b#The card has not been revealed#r#.\n");
        } else
            printfgr("#b#Player %d#r#, your #b#faced down card#r# has been #b##%d#already revealed#r#!\n", id + 1, FgBrightRed);
    }
}

void applyEffect(Game* game, int playerId, bool facedUpCard) {
    Player* player = game->players[playerId];
    
    if(!facedUpCard) {
        if(game->players[playerId]->revealedFacedDownCard) {
            printfgr("#b#Player %d#r#, your #b#faced down card#r# has been #b##%d#already revealed#r#! #b#No effect on the last card has been applied#r#.\n", playerId + 1, FgBrightRed);
            return;
        }
        
        player->revealedFacedDownCard = true;
    }

    if((facedUpCard ? player->facedUpCard->rank : player->facedDownCard->rank) == Ace) {
        game->lifePointsOnTheField++;
        player->lifePoints--;

        printfgr("Now #b#player %d#r# has #b##%d#%d LPs#r#. ", playerId + 1, FgBrightRed, player->lifePoints);
        printfgr("Now on the #b#playing field#r# there are #b##%d#%d LPs#r#.\n", FgGreen, game->lifePointsOnTheField);
    } else if((facedUpCard ? player->facedUpCard->rank : player->facedDownCard->rank) == Seven) {
        revealCard(*game->players[(playerId + 1)%game->playersCounter]->facedDownCard, (playerId + 1)%game->playersCounter + 1, false, true);
        applyEffect(game, (playerId + 1)%game->playersCounter, false);
    } else if((facedUpCard ? player->facedUpCard->rank : player->facedDownCard->rank) == Jack) {
        player->lifePoints--;
        game->players[(playerId == 0 ? game->playersCounter : playerId) - 1]->lifePoints++;

        printfgr("Now #b#player %d#r# has #b##%d#%d LPs#r#. ", playerId + 1, FgBrightRed, player->lifePoints);
        printfgr("Now #b#player %d#r# has #b##%d#%d LPs#r#.\n", playerId == 0 ? game->playersCounter : playerId, FgGreen, game->players[(playerId == 0 ? game->playersCounter : playerId) - 1]->lifePoints);
    } else if((facedUpCard ? player->facedUpCard->rank : player->facedDownCard->rank) == Queen) {
        player->lifePoints--;
        game->players[(playerId + 2)%game->playersCounter]->lifePoints++;

        printfgr("Now #b#player %d#r# has #b##%d#%d LPs#r#. ", playerId + 1, FgBrightRed, player->lifePoints);
        printfgr("Now #b#player %d#r# has #b##%d#%d LPs#r#.\n", (playerId + 2)%game->playersCounter + 1, FgGreen, game->players[(playerId + 2)%game->playersCounter]->lifePoints);
    } else if((facedUpCard ? player->facedUpCard->rank : player->facedDownCard->rank) == King) {
        player->lifePoints += game->lifePointsOnTheField;
        game->lifePointsOnTheField = 0;

        printfgr("Now #b#player %d#r# has #b##%d#%d LPs#r#. ", playerId + 1, FgGreen, player->lifePoints);
        printfgr("Now on the #b#playing field#r# there are #b##%d#0 LPs#r#.\n", FgBrightYellow);
    } else
        printgr("#b#No effect on the last card has been applied#r#.\n");
}

bool revealFacedDownCard(Card card) {
    char ans = ' ';
    bool first = true;

    fflush(stdin);

    do {
        if(!first) {
            scrollUp(1);
            cursorHorizontalAbsolute(1);
            eraseInDisplay(0);
        } else
            first = false;

        printgr("Do you want to #b#reveal#r# your #b#faced down#r# card and #b#apply its effect#r#?? ");
        scanf("%c", &ans);
    } while(ans != 'Y' && ans != 'N' && ans != 'y' && ans != 'n');

    printgr("\n");

    return ans == 'Y' || ans == 'y';
}

bool deckHasCard(Card** deck, Card card) {
    for(int i = 0; i < 40; i++)
        if(cardAreEqual(*deck[i], card))
            return true;
    
    return false;
}

bool cardAreEqual(Card card1, Card card2) {
    return card1.rank == card2.rank && card1.suit == card2.suit;
}

bool cardsWereGiven(Player** players, int playersCounter, Player player) {
    for(int i = 0; i < playersCounter; i++)
        if(cardAreEqual(*player.facedDownCard, *players[i]->facedDownCard) || cardAreEqual(*player.facedUpCard, *players[i]->facedUpCard))
            return true;

    return false;
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
            printgr("One");
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

void revealCard(Card card, int playerID, bool facedUp, bool newLine) {
    printfgr("Player %d #b#faced ", playerID);
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

    printCard(*player.facedUpCard, false);
    printgr("#r# faced up and #b#");
    printCard(*player.facedDownCard, false);
    printgr("#r# faced down.");

    if(newLine)
        printgr("\n");
}