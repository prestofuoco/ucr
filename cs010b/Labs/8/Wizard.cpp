#include "Wizard.h"
#include <iostream>
using namespace std;

Wizard::Wizard (const string &name, double health, double attackStrength, int rank) : Character (WIZARD, name, health, attackStrength) {
    this->rank = rank;
}

void Wizard::attack (Character & opponent) {
    if (opponent.getType() == WIZARD) {
        Wizard &opp = dynamic_cast<Wizard &>(opponent);
        double damage = attackStrength * (static_cast<double>(rank) / opp.rank);
        opp.damage(damage);
        cout << "Wizard " << name << " attacks " << opp.getName() << " --- POOF!!" << endl;
        cout << opp.getName() << " takes " << damage << " damage." << endl;
    } 
    else {
        double damage = attackStrength;
        opponent.damage(damage);
        cout << "Wizard " << name << " attacks " << opponent.getName() << " --- POOF!!" << endl;
        cout << opponent.getName() << " takes " << damage << " damage." << endl;
    }
}