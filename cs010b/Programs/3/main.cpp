#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

#include "Deck.h"
#include "Card.h"

// Returns true if vector of Cards passed in contains at least 2 Cards with the same rank.
bool hasPair(const vector<Card> &hand) {
    bool result = false;
    unsigned int i;
    unsigned int j;

    for (i = 0; i < hand.size(); ++i) {
        for (j = i + 1; j < hand.size(); ++j) {
            if (hand.at(i).getRank() == hand.at(j).getRank()) {
                return true;
            }
        }
    }
    return result;
}

// Sends to output stream a hand of Cards on a single line, 
// each Card separated by a comma.
// If the vector is empty, do not output anything.
// Example (vector size of 3): Ace of Spades, Two of Hearts, King of Clubs 
ostream & operator<<(ostream &out, const vector<Card> &hand) {
    for (unsigned int i = 0; i < hand.size(); ++i) {
        out << hand.at(i);
        if (i < hand.size() - 1) {
            out << ',';
        }
    }
    return out;
}

int main() {
    srand(2222);
    
    ofstream outFS;
    string yn;
    string filename;
    int userNum;
    int userDeals;
    int i;
    int j;
    int pairCount = 0;
    double percentage;

    cout << "Do you want to output all hands to a file?(Yes/No)" << endl;
    cin >> yn;

    if (yn == "Yes") {
        cout << "Enter name of output file: ";
        cin >> filename;
        outFS.open(filename);
        
        if (!outFS.is_open()) {
            cout << "Error opening " << filename << endl;
            exit(EXIT_FAILURE); 
        }

        cout << "Enter number of cards per hand: " << endl;
        cin >> userNum;
        cout << "Enter number of deals (simulations): " << endl;
        cin >> userDeals;

        vector<Card> hand;
        Deck d;
        Card temp;

        /*(for (i = 0; i < userDeals; ++i) {
            d.shuffleDeck();
            hand.clear();
            
            for (j = 0; j < userNum; ++j) {
                temp = d.dealCard();
                hand.push_back(temp);
            }

            if (hasPair(hand)) {
                outFS << "Found Pair!! ";
                ++pairCount;
            }
            else {
                outFS << "             ";
            }          

            for (j = 0; j < userNum; ++j) {
                outFS << hand.at(j);
                if (j < userNum - 1) {
                    outFS << ", ";
                }
            }

            outFS << endl;
        }*/

        for (i = 0; i < userDeals; ++i) {
            d.shuffleDeck();
            while(d.deckSize() > userNum) {
                for (j = 0; j < userNum; ++j) {
                    hand.clear();
                    for (int n = 0; n < userNum; ++n) {
                        temp = d.dealCard();
                        hand.push_back(temp);
                    }                    
                    if (hasPair(hand)) {
                        outFS << "Found Pair!! ";
                        ++pairCount;
                    }
                    else {
                        outFS << "             ";
                    }          
                    for (int m = 0; m < userNum; ++m) {
                        outFS << hand.at(m);
                        if (j < userNum - 1) {
                            outFS << ", ";
                        }
                    }

                    outFS << endl;                    
                }
            }
        }
        
        percentage = (static_cast<double>(pairCount) / userDeals) * 100.0;
        cout << "Chances of receiving a pair in a hand of " << userNum << " cards is: " << percentage << '%' << endl;
        outFS.close();
    }

    else if (yn == "No") {
        cout << "Enter number of cards per hand: " << endl;
        cin >> userNum;
        cout << "Enter number of deals (simulations): " << endl;
        cin >> userDeals;

        vector<Card> hand;
        Deck d;
        d.shuffleDeck();

        for (i = 0; i < userDeals; ++i) {
            hand.clear();
            for (j = 0; j < userNum; ++j) {
                hand.push_back(d.dealCard());
            }
            if (hasPair(hand)) {
                ++pairCount;
            }
        }

        percentage = (static_cast<double>(pairCount) / userDeals) * 100.0;
        cout << "Chances of receiving a pair in a hand of " << userNum << " cards is: " << percentage << '%' << endl;
    }

    return 0;
}