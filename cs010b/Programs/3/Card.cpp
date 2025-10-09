#include <iostream>
#include "Card.h"

using namespace std;

Card::Card() {
    suit = 'c';
    rank = 2;
}

Card::Card(char s, int r) {
    s = tolower(s);
    if (s != 'c' && s != 'd' && s != 'h' && s != 's') {
        rank = 'c';
    }
    else {
        suit = s;
    }
    if (r < 1 || r > 13) {
        rank = 2;
    }
    else {
        rank = r;
    }
}

char Card::getSuit() const {
    return suit;
}

int Card::getRank() const {
    return rank;
}

ostream &operator<<(ostream &out, const Card &card) {
    if (card.rank == 1 || card.rank > 10) {
        if (card.rank == 1) {
            out << "Ace";
        }
        if (card.rank == 11) {
            out << "Jack";
        }
        if (card.rank == 12) {
            out << "Queen";
        }
        if (card.rank == 13) {
            out << "King";
        }
    }

    else {
        out << card.rank;
    }

    if (card.suit == 'c') {
        out << " of Clubs";
    }
    if (card.suit == 'd') {
        out << " of Diamonds";
    }
    if (card.suit == 'h') {
        out << " of Hearts";
    }
    if (card.suit == 's') {
        out << " of Spades";
    }

    return out;
}