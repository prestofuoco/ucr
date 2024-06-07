#include "Elf.h"
#include <iostream>
using namespace std;

Elf::Elf (const string &name, double health, double attackStrength, const string & familyName) : Character (ELF, name, health, attackStrength) {
    this->familyName = familyName;
}

void Elf::attack (Character & opponent) {
    if (opponent.getType() == ELF) {
        Elf &opp = dynamic_cast<Elf &>(opponent);
        if (familyName == opp.familyName) {
            cout << "Elf " << name << " does not attack Elf " << opp.getName() << "." << endl;
            cout << "They are both members of the " << familyName << " family." << endl;
            return;
        }
    }
    double damage = (health / MAX_HEALTH) * attackStrength;
    opponent.damage(damage);
    cout << "Elf " << name << " shoots an arrow at " << opponent.getName() << " --- TWANG!!" << endl;
    cout << opponent.getName() << " takes " << damage << " damage." << endl;
}