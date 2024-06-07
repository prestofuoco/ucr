#include <cstdlib>
#include <vector>
#include <algorithm>
#include "Deck.h"
#include "Card.h"

using namespace std;

unsigned int i;
unsigned int j;
char c;

Deck::Deck() {
    for (i = 0; i < 4; ++i) {
        if (i == 0) {
            c = 'c';
        }
        if (i == 1) {
            c = 'd';
        }
        if (i == 2) {
            c = 'h';
        }
        if (i == 3) {
            c = 's';
        }
        for (j = 1; j < 14; ++j) {
            theDeck.insert(theDeck.begin(), Card(c, j));
        }
   }
}

Card Deck::dealCard() {
    Card temp = theDeck.back();
    dealtCards.push_back(temp);
    theDeck.pop_back();
    return temp;
}

void Deck::shuffleDeck() {
    theDeck.insert(theDeck.end(), dealtCards.begin(), dealtCards.end());
    dealtCards.clear();
    random_shuffle(theDeck.begin(), theDeck.end());
}

unsigned Deck::deckSize() const {
    return theDeck.size();
}