#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
using namespace std;

class Warrior : public Character {
    public:
        Warrior (const string &name, double health, double attackStrength, const string & allegiance);
        void attack (Character & opponent) override;
    private:
        string allegiance;
};

#endif