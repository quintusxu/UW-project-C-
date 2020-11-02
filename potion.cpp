//
//  potion.cpp
//  a4q5
//
//  Created by Aurora Jin on 2018-07-10.
//  Copyright © 2018 Aurora Jin. All rights reserved.
//

#include "potion.hpp"
#include "player.hpp"
#include "floor.hpp"
#include <cstdlib>
#include <ctime>


Potion::Potion() {
    srand(time(NULL));
    int w = rand() % 6;
    if (w == 0) {
        type = TypeofPotion::RH;
    } else if (w == 1) {
        type = TypeofPotion::BA;
    } else if (w == 2) {
        type = TypeofPotion::BD;
    } else if (w == 3) {
        type = TypeofPotion::PH;
    } else if (w == 4) {
        type = TypeofPotion::WA;
    } else {
        type = TypeofPotion::WD;
    }
}

bool Potion::isRevealed() {
    return revealed;
}

TypeofPotion Potion::getType() {
    return type;
}

void Potion::accept(Player *p) {
    p->visit(this);
    if (!revealed) {
        p->eaten.emplace_back(type);
        for (unsigned i = 0; i < f->potions.size(); i++) {
            if (f->potions.at(i)->getType() == type) {
                f->potions.at(i)->setRevealed();
            }
        }
    }
    f->notified(this);
}


void Potion::setType(TypeofPotion t) {
    type = t;
}

void Potion::setRevealed() {
    revealed = true;
}

Potion::~Potion() {}





